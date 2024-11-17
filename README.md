# Parrot
Parrot is an educational game/graphics engine build in C++.

Technologies used:
- window-api: [glfw](https://github.com/glfw/glfw)
- graphics-api: _opengl_ using [glad](https://github.com/Dav1dde/glad)
- assets: [nlohmann/json](https://github.com/nlohmann/json), [nothings/stb](https://github.com/nothings/stb/blob/master/stb_image.h)
## Asset Formats
### Format: ".app.json"
```jsonc
{
    // general
    "name": "App Name", // default: "Unnamed App"
    "main": "<window>",
    
    // assets
    "loading-policy": "app|scene|lazy", // default: "lazy"
    "unloading-policy": "app|scene|unused" // default: "app"
}
```
### Format: ".wndw.json"
```jsonc
{
    // general
    "uuid": 1234567889,
    "title": "Window Title", // default: "Untitled Window"
    "size": [ 1080, 720 ], // default: [ 1080, 720 ]

    // content
    "scene": "<scene>" // default: null
}
```
### Format: ".scn.json
```jsonc
{
    // general
    "uuid": 1234567889,
    "name": "Scene Name", // default: "Unnamed Scene"
    
    // hierarchy
    "root": "<entity>" // default: null
}
```
### Format: ".entt.json"
```jsonc
{
    // general
    "uuid": 1234567889,
    "tag": "Entity Tag", // default: "Entity"

    // transform
    "transform": {
        "position": [ 0, 0, 0 ], // default: [ 0, 0, 0 ]
        "rotation": [ 0, 0, 0 ], // default: [ 0, 0, 0 ]
        "scale": [ 1, 1, 1 ] // default: [ 1, 1, 1 ]
    },
    // children
    "children": [ // default: []
        "<entity>", /* ... */
    ],
    // scripts
    "scripts": { // default: {}
        "script_name": {
            /* depends on script */
        }, /* ... */
    },
    // components
    "components": { // default: {}
        "component_name": {
            /* depends on component */
        }, /* ... */
    }
}
```