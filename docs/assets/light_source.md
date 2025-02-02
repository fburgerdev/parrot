# Light-Source

## Format

### `.json`

#### Ambient-Light

```jsonc
{
  "type": "ambient",
  "intensity": 1.0, // default: 1.0
  "color": [ 255, 255, 255 ] // default: [ 255, 255, 255 ]
}
```

#### Directional-Light

```jsonc
{
  "type": "directional",
  "direction": [ 0, 0, 1 ], // default: [ 0, 0, 1 ]
  "intensity": 1.0, // default: 1.0
  "color": [ 255, 255, 255 ] // default: [ 255, 255, 255 ]
}
```

#### Point-Light

```jsonc
{
  "type": "point",
  "position": [ 0, 0, 0 ], // default: [ 0, 0, 0 ]
  "range": 1.0, // default: 1.0
  "intensity": 1.0, // default: 1.0
  "color": [ 255, 255, 255 ] // default: [ 255, 255, 255 ]
}
```

#### Spot-Light

```jsonc
{
  "type": "spot",
  "position": [ 0, 0, 0 ], // default: [ 0, 0, 0 ]
  "direction": [ 0, 0, 1 ], // default: [ 0, 0, 1 ]
  "angle": 1.57079, // default: 1.57079 (90deg)
  "intensity": 1.0, // default: 1.0
  "color": [ 255, 255, 255 ] // default: [ 255, 255, 255 ]
}
```
