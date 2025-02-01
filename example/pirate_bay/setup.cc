#include "client.hh"
#include "scripts/fps.hh"
#include "scripts/controller.hh"

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
    };
    template<>
    Map<string, RegistryEntry<Script, Window&>>
        g_registry<Script, Window&> = {
        {
            "FPS",
            {
                typeid(FPS).hash_code(),
                [](Window& window) {
                    return std::make_unique<FPS>(window);
                }
            }
        },
    };

    // setup
    stdf::path setup() {
        return stdf::path(__FILE__).parent_path() / ".app.json";
    }
}