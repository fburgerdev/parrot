#include "common.hh"
#include "entity_preset.hh"
#include "utils/serial_node.hh"

namespace Parrot {
  // (constructor) for Asset
  EntityPreset::EntityPreset(const AssetPath& path, AssetAPI& api)
    : Asset(path) {
    auto json = path.applySubpathToJSON(
      SerialNode::loadFromJSON(path.file)
    );
    loadFromSerialNode(json, api);
  }
  EntityPreset::EntityPreset(const SerialNode& node, const AssetPath& path, AssetAPI& api)
    : Asset(path) {
    loadFromSerialNode(node, api);
  }

  // loadFromSerialNode
  void EntityPreset::loadFromSerialNode(const SerialNode& node, AssetAPI& api) {
    // tag
    if (node.contains("tag")) {
      tag = string(node.at("tag"));
    }
    // transform
    if (node.contains("transform")) {
      // position
      if (node.at("transform").contains("position")) {
        transform.position = Vec3<float32>(
          DefaultFloat(node.at("transform").at("position")[0]),
          DefaultFloat(node.at("transform").at("position")[1]),
          DefaultFloat(node.at("transform").at("position")[2])
        );
      }
      // rotation
      if (node.at("transform").contains("rotation")) {
        transform.rotation = Vec3<float32>(
          DefaultFloat(node.at("transform").at("rotation")[0]),
          DefaultFloat(node.at("transform").at("rotation")[1]),
          DefaultFloat(node.at("transform").at("rotation")[2])
        );
      }
      // scale
      if (node.at("transform").contains("scale")) {
        transform.scale = Vec3<float32>(
          DefaultFloat(node.at("transform").at("scale")[0]),
          DefaultFloat(node.at("transform").at("scale")[1]),
          DefaultFloat(node.at("transform").at("scale")[2])
        );
      }
    }
    // children
    if (node.contains("children")) {
      for (const auto& child : node.at("children")) {
        children.emplace_back(child, api);
      }
    }
    // components
    if (node.contains("components")) {
      for (const auto& [name, data] : node.at("components").items()) {
        if (g_registry<
          Factory<Component>, const SerialNode&, const AssetPath&, AssetAPI&
        >.contains(name)) {
          component_factories.emplace_back(
            g_registry<
            Factory<Component>, const SerialNode&, const AssetPath&, AssetAPI&
            >.at(name).second(data, getAssetPath(), api)
          );
        }
        else {
          LOG_ASSET_WARNING(
            "unregistered component '{}' in node, will be ignored ", name
          );
        }
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