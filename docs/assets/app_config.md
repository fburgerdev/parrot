# App-Config

## Format

### `.json`
```jsonc
{
  "uuid": 123456789, // default: random
  "name": "App Name", // default: "Unnamed App"
  "stage": <stage>,
  "asset-manager": {
    "loading-policy": "app|scene|lazy", // default: "lazy"
    "unloading-policy": "app|scene|unused" // default: "app"
  }
}
```
