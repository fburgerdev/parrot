#include "common.hh"
#include "render_object.hh"
#include "core/log.hh"
#include "utils/serial_node.hh"

namespace Parrot {
  // (constructor) for Asset
  RenderObject::RenderObject(const AssetPath& path, AssetAPI& api)
    : Asset(path) {
    auto json = path.applySubpathToNode(
      SerialNode::loadFromJSON(path.file)
    );
    loadFromSerialNode(json, api);
  }
  RenderObject::RenderObject(
    const SerialNode& node, const AssetPath& path, AssetAPI& api
  ) : Asset(path) {
    loadFromSerialNode(node, api);
  }

  // loadFromSerialNode
  void RenderObject::loadFromSerialNode(
    const SerialNode& node, AssetAPI& api
  ) {
    model = AssetHandle<Model>(node.at("model"), api);
    if (node.contains("material")) {
      material = AssetHandle<Material>(node.at("material"), api);
    }
    else {
      material = AssetHandle<Material>(
        AssetPath(stdf::path(".parrot/model.mat.json")), api
      );
    }
    if (node.contains("opaque") && !node.at("opaque")) {
      is_opaque = false;
    }
  }

  // TODO: make << overload more verbose
  // << (stream)
  ostream& operator<<(ostream& stream, const RenderObject& render_object) {
    return stream << "RenderObject()";
  }
}