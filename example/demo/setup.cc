#include "client.hh"
#include "scripts/controller.hh"
#include "scripts/rotate.hh"

#define SCRIPT_ID(NAME) typeid(NAME).hash_code()
#define SCRIPT_FACTORY(NAME) [] { return ::std::make_unique<NAME>(); }
#define REGISTER_SCRIPT(NAME) ::Parrot::g_script_registry.emplace(#NAME, ScriptRecord(SCRIPT_ID(NAME), SCRIPT_FACTORY(NAME)));

namespace Parrot {
    // setup
    stdf::path setup() {
        REGISTER_SCRIPT(PlayerController);
        REGISTER_SCRIPT(Rotate);
        return ".app.json";
    }
}