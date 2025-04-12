#include <gtest/gtest.h>
#include "core/asset_handle.hh"
#include <nlohmann/json.hpp>
using namespace Parrot;

// TestAsset
class TestAsset : public Asset {
public:
  // (constructor)
  TestAsset(const AssetPath& path, AssetAPI&)
    : Asset(path) {}
};

// TestAssetAPI
class TestAssetAPI : public AssetAPI {
public:
  // addAsset
  virtual UUID addAsset(SharedPtr<Asset> asset) override {
    return asset->getUUID();
  }
  // lockAsset
  virtual SharedPtr<const Asset> lockAsset(
    const AssetKey& key, AssetFactory factory
  ) override {
    return factory(AssetPath(stdf::path("invalid/path")));
  }
};

// (static) s_invalid_path
static AssetPath s_invalid_path = AssetPath(stdf::path("invalid/path"));

// bool()
TEST(AssetHandleTest, operatorBool) {
  TestAssetAPI api;
  auto uuid_json = nlohmann::json::parse("0");
  auto path_json = nlohmann::json::parse("\"invalid/path\"");
  EXPECT_FALSE(bool(AssetHandle<TestAsset>()));
  EXPECT_TRUE(bool(AssetHandle<TestAsset>(0, api)));
  EXPECT_TRUE(bool(AssetHandle<TestAsset>(s_invalid_path, api)));
  EXPECT_TRUE(bool(AssetHandle<TestAsset>(AssetKey(s_invalid_path), api)));
}

// lock
TEST(AssetHandleTest, lock) {
  TestAssetAPI api;
  auto locked = AssetHandle<TestAsset>(s_invalid_path, api).lock();
  EXPECT_EQ(locked->getAssetPath(), s_invalid_path);
}

// createHandleFromJSON
TEST(AssetHandleTest, createHandleFromJSON) {
  TestAssetAPI api;
  auto locked = AssetHandle<TestAsset>(s_invalid_path, api).lock();
  EXPECT_EQ(locked->getAssetPath(), s_invalid_path);
}