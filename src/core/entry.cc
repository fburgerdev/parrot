#include "common.hh"
#include "app.hh"
#include "debug/debug.hh"

// (static) console figures
static std::string s_info = R""""(
--------------------------------------------------------
|  _____                     _                  .--,   |
| |  __ \                   | |             ,.-( (o)\  |
| | |__) |_ _ _ __ _ __ ___ | |_           /   .)/\ ') |
| |  ___/ _` | '__| '__/ _ \| __|       .',./'/    )/  |
| | |  | (_| | |  | | | (_) | |_     ()=///=))))==()   |
| |_|   \__,_|_|  |_|  \___/ \__|      /               |
--------------------------------------------------------

Parrot: v0.0
Window-API: GLFW
Graphics-API: OpenGL
)"""";
static std::string s_debug_head =
"================= parrot debug console =================";
static std::string s_debug_foot =
"========================================================";

namespace Parrot {
    // setup (defined in client-app)
    stdf::path setup();

    // (static) launch
    static void launch() {
        logger.setLevel("asset", LogLevel::DEBUG);
        logger.setLevel("core", LogLevel::DEBUG);
        logger.setLevel("ecs", LogLevel::DEBUG);
        logger.setLevel("graphics", LogLevel::DEBUG);
        logger.setLevel("math", LogLevel::DEBUG);
        logger.setLevel("window", LogLevel::DEBUG);

        cout << s_info << endl;
        cout << s_debug_head << endl;
        App app(setup());
        app.run();
        cout << s_debug_foot << endl;
    }
}

// main
int main() {
    Parrot::launch();
}