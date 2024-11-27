#include "common.hh"
#include "mesh.hh"
#include "debug/debug.hh"
#include "tinyobj/objloader.hh"
using namespace tinyobj;

namespace Parrot {
	// Mesh
	Mesh::Mesh(const stdf::path& filepath) {
        ObjReader reader;
        ObjReaderConfig config;
        config.triangulate = true;
        reader.ParseFromFile(filepath.string(), config);

        // errors / warnings
        if (!reader.Error().empty()) {
            LOG_ASSET_ERROR("failed to load mesh {}", filepath);
            LOG_ASSET_ERROR("obj-loader error message:\n{}", reader.Error());
            return;
        }
        if (!reader.Warning().empty()) {
            LOG_ASSET_WARNING("obj-loader warning message:\n{}", reader.Warning());
        }

        auto& attrib = reader.GetAttrib();
        auto& shapes = reader.GetShapes();
        auto& materials = reader.GetMaterials();

        // shapes
        for (const auto& shape : reader.GetShapes()) {
            usize offset = 0;
            // polygon (vertex_count = 3 since triangulate)
            for (uint vertex_count : shape.mesh.num_face_vertices) {
                // face
                for (usize v = 0; v < vertex_count; v++) {
                    auto idx = shape.mesh.indices[offset + v];

                    // position
                    Vec3<float32> position(
                        attrib.vertices[3 * usize(idx.vertex_index) + 0],
                        attrib.vertices[3 * usize(idx.vertex_index) + 1],
                        attrib.vertices[3 * usize(idx.vertex_index) + 2]
                    );

                    // normal
                    Vec3<float32> normal(0, 0, -1);
                    if (idx.normal_index >= 0) {
                        normal.x = attrib.normals[3 * usize(idx.normal_index) + 0];
                        normal.y = attrib.normals[3 * usize(idx.normal_index) + 1];
                        normal.z = attrib.normals[3 * usize(idx.normal_index) + 2];
                    }

                    // tex_coords
                    Vec2<float32> tex_coords(0, 0);
                    if (idx.texcoord_index >= 0) {
                        tex_coords.x = attrib.texcoords[2 * usize(idx.texcoord_index) + 0];
                        tex_coords.y = attrib.texcoords[2 * usize(idx.texcoord_index) + 1];
                    }

                    // Optional: vertex colors
                    // float32 red   = attrib.colors[3*usize(idx.vertex_index)+0];
                    // float32 green = attrib.colors[3*usize(idx.vertex_index)+1];
                    // float32 blue  = attrib.colors[3*usize(idx.vertex_index)+2];

                    vertices.push_back({
                        .position = position,
                        .normal = normal,
                        .tex_coords = tex_coords,
                    });
                    indices.push_back(indices.size());
                }
                offset += vertex_count;

                // material
                //shape.mesh.material_ids[vertex_count];
            }
        }
        LOG_ASSET_DEBUG("loaded mesh {} ({} vertices and {} indices)", filepath, vertices.size(), indices.size());
	}
}