#include "client.hh"
#include "scripts/controller.hh"
#include "scripts/rotate.hh"

namespace Parrot {
    // (global) registry
    template<>
    Map<string, RegistryEntry<Script, Entity&>>
        g_registry<Script, Entity&> = {
        {
            "PlayerController",
            {
                typeid(PlayerController).hash_code(),
                [](Entity& entity) {
                    return std::make_unique<PlayerController>(entity);
                }
            }
        },
        {
            "Rotate",
            {
                typeid(Rotate).hash_code(),
                [] (Entity& entity) {
                    return std::make_unique<Rotate>(entity);
                }
            }
        },
    };

    // setup
    stdf::path setup() {
        return ".app.json";
    }
}