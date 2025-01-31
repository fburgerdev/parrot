#include "common.hh"
#include "asset_registry.hh"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Parrot {
  // (constructor)
  AssetRegistry::AssetRegistry(const stdf::path& asset_directory)
    : _asset_directory(asset_directory) {
    add(asset_directory);
  }

  // getUUID
  UUID AssetRegistry::getUUID(const AssetPath& asset_path) const {
    return _uuid_map.at(asset_path);
  }
  UUID AssetRegistry::getUUID(const AssetKey& key) const {
    if (std::holds_alternative<UUID>(key)) {
      return std::get<UUID>(key);
    }
    else {
      return getUUID(std::get<AssetPath>(key));
    }
  }
  // getAssetPath
  const AssetPath& AssetRegistry::getAssetPath(UUID uuid) const {
    return _asset_path_map.at(uuid);
  }
  const AssetPath& AssetRegistry::getAssetPath(const AssetKey& key) const {
    if (std::holds_alternative<UUID>(key)) {
      return getAssetPath(std::get<UUID>(key));
    }
    else {
      return std::get<AssetPath>(key);
    }
  }

  // contains
  bool AssetRegistry::contains(UUID uuid) const {
    return _asset_path_map.contains(uuid);
  }
  bool AssetRegistry::contains(const AssetPath& asset_path) const {
    return _uuid_map.contains(asset_path);
  }
  // find
  const AssetPath* AssetRegistry::find(UUID uuid) const {
    auto it = _asset_path_map.find(uuid);
    if (it != _asset_path_map.end()) {
      return &it->second;
    }
    else {
      return nullptr;
    }
  }
  UUID AssetRegistry::find(const AssetPath& asset_path) const {
    auto it = _uuid_map.find(asset_path);
    if (it != _uuid_map.end()) {
      return it->second;
    }
    else {
      return 0;
    }
  }
  // add
  void AssetRegistry::add(UUID uuid, const AssetPath& asset_path) {
    _asset_path_map.emplace(uuid, asset_path);
    _uuid_map.emplace(asset_path, uuid);
  }
  void AssetRegistry::add(const stdf::path& path) {
    if (stdf::is_regular_file(path)) {
      if (path.extension().string() == ".json") {
        string source = (ostrstream() << ifstream(path).rdbuf()).str();
        auto json = json::parse(source);
        if (json.contains("uuid")) {
          add(json.at("uuid"), stdf::relative(path, _asset_directory));
        }
        else {
          // TODO: log warning
        }
      }
      else {
        add(generateUUID(), stdf::relative(path, _asset_directory));
      }
    }
    else if (stdf::is_directory(path)) {
      auto iterator = stdf::directory_iterator(path);
      for (auto entry : iterator)  {
        add(entry.path());
      }
    }
  }
  void AssetRegistry::add(const AssetPath& asset_path) {
    string source = (
      ostrstream() << ifstream(asset_path.filepath).rdbuf()
    ).str();
    auto json = asset_path.applySubpathToJSON(json::parse(source));
    if (json.contains("uuid")) {
      add(json.at("uuid"), asset_path);
    }
    else {
      // TODO: log warning
    }
  }
  // remove
  void AssetRegistry::remove(UUID uuid) {
    auto it = _asset_path_map.find(uuid);
    _uuid_map.erase(it->second);
    _asset_path_map.erase(it);
  }
  void AssetRegistry::remove(const AssetPath& asset_path) {
    auto it = _uuid_map.find(asset_path);
    _asset_path_map.erase(it->second);
    _uuid_map.erase(it);
  }
}