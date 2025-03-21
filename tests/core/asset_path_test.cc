#include <gtest/gtest.h>
#include "core/asset_path.hh"
#include <nlohmann/json.hpp>
using namespace Parrot;

// AssetPathTest
class AssetPathTest : public testing::Test {
protected:
	// (constructor)
	AssetPathTest() {
		json = nlohmann::json::parse(
			"{"
			"\"key1\":1,"
			"\"key2\":{\"key3\":3},"
			"\"key4\":[0,1],"
			"\"key5\":[0,1,{\"key6\":5},3]"
			"}"
		);
		tests = {
			{
				"path/to/file.extension",
				{
					"path/to/file.extension", "",
					{}, json,
				},
			},
			{
				"path/to/file.extension:key1",
				{
					"path/to/file.extension", "key1",
					{ "key1" }, json.at("key1"),
				},
			},
			{
				"path/to/file.extension:key2.key3",
				{
					"path/to/file.extension", "key2.key3",
					{ "key2", "key3" }, json.at("key2").at("key3"),
				},
			},
			{
				"path/to/file.extension:key4[0]",
				{
					"path/to/file.extension", "key4[0]",
					{ "key4", "0" }, json.at("key4").at(0),
				},
			},
			{
				"path/to/file.extension:key5[2].key6",
				{
					"path/to/file.extension", "key5[2].key6",
					{ "key5", "2", "key6" }, json.at("key5").at(2).at("key6"),
				},
			},
		};
	}
	// json, tests
	nlohmann::json json;
	Map<strview, Tuple<strview, strview, List<string>, nlohmann::json>> tests;
};

// (constructor)
TEST_F(AssetPathTest, constructor) {
	for (auto& [input, output] : tests) {
		auto asset_path = AssetPath(input);
		EXPECT_EQ(asset_path.file, std::get<0>(output));
		EXPECT_EQ(asset_path.sub, std::get<1>(output));
	}
}

// splitSubpath
TEST_F(AssetPathTest, splitSubpath) {
	for (auto& [input, output] : tests) {
		auto asset_path = AssetPath(input);
		EXPECT_EQ(asset_path.splitSubpath(), std::get<2>(output));
	}
}
// applySubpathToJSON
TEST_F(AssetPathTest, applySubpathToJSON) {
	for (auto& [input, output] : tests) {
		auto asset_path = AssetPath(input);
		EXPECT_EQ(asset_path.applySubpathToJSON(json), std::get<3>(output));
	}
}
// << (stream)
TEST_F(AssetPathTest, operatorStream) {
	for (auto& [input, output] : tests) {
		{
			auto asset_path = AssetPath(input);
			strstream stream;
			stream << asset_path;
			EXPECT_EQ(stream.str(), string(input));
		}
		{
			auto asset_path = AssetPath(input);
			asset_path.debug_root = "path";
			strstream stream;
			stream << asset_path;
			stdf::path relative_path = stdf::relative(input, *asset_path.debug_root);
			EXPECT_EQ(stream.str(), relative_path.string());
		}
	}
}