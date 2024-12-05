# Parrot
Parrot is a game engine written in C++ created for educational purposes.
The engine lets you develop games using custom asset formats and C++ scripts.

![image](https://github.com/user-attachments/assets/998e8642-6cc0-464e-9837-f3d0b7d5a54c)

technologies used:
- window-api: [glfw](https://github.com/glfw/glfw)
- graphics-api: _opengl_ using [glad](https://github.com/Dav1dde/glad)
- assets: [nlohmann/json](https://github.com/nlohmann/json), [nothings/stb](https://github.com/nothings/stb/blob/master/stb_image.h), [tinyobjloader/tinyobjloader](https://github.com/tinyobjloader/tinyobjloader)

## Architecture
![image](https://github.com/user-attachments/assets/ea4ed375-3b5d-4436-a083-19cd35f29509)

modules:
- `core` create, run and destroy apps and playing-units + connect to client code 
- `window` create, update and destroy physical windows
- `ecs` provide [ecs](https://en.wikipedia.org/wiki/Entity_component_system) api with scenes, entities and components
- `graphics` handle graphics data like meshes or materials and communicate with the gpu
- `asset-manager` manage the client asset-directory and handle the assets lifetimes

> besides the `core` module, no modules depend on each other

## Scripting
In order to have logic in your game, you can add scripts written in C++.
### Example Script
```cc
#include "path/to/src/client.hh"

class ScriptName : public Script {
    ScriptName(Entity& entity)
        : entity(entity) {}

    virtual bool resolveEvent(const Event& e) override {
        if (auto* mouse_move = e.getMouseMove()) {
            std::cout << "Mouse was moved!" << std::endl;
        }
        return false;
    }
    virtual void onUpdate(float32 delta_time) override {
        std::cout << "I'm getting updated!" << std::endl;
    }

    Entity& entity;
}
```
this is a script that you can attach to entities.

You can add scripts to
- Apps
- Playing-Units (Window, Scene)
- Entities

>[!IMPORTANT]  
>in the current development state you can only attach scripts to entities

![image](https://github.com/user-attachments/assets/00378e8a-0136-4394-b641-36f90eb172ee)


## Asset Formats
For now, all assets are stored in a _.json_ format.
> handles can be either uuids (i.e. numbers), filepaths (i.e. strings) or inlined (i.e. objects) 

### Format: ".app.json"
```jsonc
{
    // general
    "name": "App Name", // default: "Unnamed App"
    "main": [
        "<window-handle>",
        "<scene-handle>",
        [ "ScriptName1", /* ... */ ] // optional
    ],
    
    // assets
    "loading-policy": "app|scene|lazy", // default: "lazy"
    "unloading-policy": "app|scene|unused" // default: "app"

    // scripts
    "scripts": [ // default: []
        "ScriptName1", /* ... */
    ]
}
```
### Format: ".wndw.json"
```jsonc
{
    "uuid": 1234567889,
    "title": "Window Title", // default: "Untitled Window"
    "size": [ 1080, 720 ], // default: [ 1080, 720 ]
}
```
### Format: ".scn.json
```jsonc
{
    // general
    "uuid": 1234567889,
    "name": "Scene Name", // default: "Unnamed Scene"
    
    // hierarchy
    "root": "<entity-handle>" // default: null
}
```
### Format: ".entt.json"
```jsonc
{
    // general
    "uuid": 1234567889,
    "tag": "Entity Tag", // default: "Entity"

    // transform
    "transform": { // default: {}
        "position": [ 0, 0, 0 ], // default: [ 0, 0, 0 ]
        "rotation": [ 0, 0, 0 ], // default: [ 0, 0, 0 ]
        "scale": [ 1, 1, 1 ] // default: [ 1, 1, 1 ]
    },
    // children
    "children": [ // default: []
        "<entity-handle>", /* ... */
    ],
    // components
    "components": { // default: {}
        "component_name": {
            /* data depends on component */
        }, /* ... */
    },
    // scripts
    "scripts": [ // default: []
        "ScriptName1", /* ... */
    ]
}
```
### Format: ".mesh.json"
```jsonc
{
    // general
    "uuid": 1234567889,
    "resource": "path/to/mesh.obj"
}
```
### Format: ".shader.json"
```jsonc
{
    // general
    "uuid": 1234567889,
    "vertex": {
        "resource": "path/to/vertex_shader.vs.glsl"
    },
    "fragment": {
        "resource": "path/to/fragment_shader.fs.glsl"
    }
}
```
