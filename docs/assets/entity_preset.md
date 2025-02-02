# Entity-Preset

## Format

### `.json`
```jsonc
{
  // general
  "uuid": 1234567889, // default: random
  "tag": "Entity Tag", // default: "Entity"
  
  // transform
  "transform": { // default: {}
    "position": [ 0, 0, 0 ], // default: [ 0, 0, 0 ]
    "rotation": [ 0, 0, 0 ], // default: [ 0, 0, 0 ]
    "scale": [ 1, 1, 1 ] // default: [ 1, 1, 1 ]
  },
  
  // children
  "children": [ <entity-config> /* ... */ ], // default: []
  
  // components
  "components": { // default: {}
    "<component-name>": <component> /* ... */
  },
  // scripts
  "scripts": [ "<script-name>" /* ... */ ] // default: []
}
```
