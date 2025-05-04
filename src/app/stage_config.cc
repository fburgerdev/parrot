#include "common.hh"
#include "stage_config.hh"

namespace Parrot {
  // (constructor) for Asset
  StageConfig::StageConfig(const AssetPath& path, AssetAPI& api)
    : Asset(path) {
    auto json = getAssetPath().applySubpathToNode(
      SerialNode::loadFromJSON(path.file)
    );
    loadFromSerialNode(json, api);
  }
  StageConfig::StageConfig(
    const SerialNode& node, const AssetPath& path, AssetAPI& api
  ) : Asset(path) {
    loadFromSerialNode(node, api);
  }

  // loadFromSerialNode
  void StageConfig::loadFromSerialNode(
    const SerialNode& node, AssetAPI& api
  ) {
    // window
    window = AssetHandle<WindowConfig>(node.at("window"), api);
    // scene(s)
    if (node.contains("scene")) {
      scenes.emplace_back(
        AssetHandle<SceneConfig>(node.at("scene"), api)
      );
    }
    if (node.contains("scenes")) {
      for (const auto& scene : node.at("scenes")) {
        scenes.emplace_back(
          AssetHandle<SceneConfig>(scene, api)
        );
      }
    }
    // scripts
    if (node.contains("scripts")) {
      for (const auto& script : node.at("scripts")) {
        scripts.emplace_back(string(script));
      }
    }
  }
}