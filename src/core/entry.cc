#include "common.hh"
#include "app.hh"

namespace Parrot {
    // setup (defined in client-app)
    stdf::path setup();

    // launch
    void launch() {
        App app(setup());
        app.run();
    }
}

// main
int main() {
    Parrot::launch();
}