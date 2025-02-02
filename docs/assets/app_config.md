# App-Config

## Format

### `.json`
```jsonc
{
  "uuid": 123456789, // default: random
  "name": "App Name", // default: "Unnamed App"
  "main": [ <window-config>, <scene-config> ],
  "asset-manager": {
    "loading-policy": "app|scene|lazy", // default: "lazy"
    "unloading-policy": "app|scene|unused" // default: "app"
  }
}
```
