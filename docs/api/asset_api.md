# AssetAPI

## API

### `addAsset`

```c++
UUID AssetAPI::addAsset(SharedPtr<Asset> asset)
```

> Add an asset to the asset-manager.

*Return* the uuid to the asset passed. 

### `lockAsset`

```c++
SharedPtr<Asset> AssetAPI::lockAsset(const AssetKey& key, AssetFactory factory)
```

> Lock an asset for usage.

*Return* asset corresponding to provided key.
