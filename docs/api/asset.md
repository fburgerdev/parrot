# Asset Management

## Asset Path

### `(constructor)`

```c++
AssetPath::AssetPath(const stdf::path& file);
```

```c++
AssetPath::AssetPath(const stdf::path& file, strview sub);
```

```c++
AssetPath::AssetPath(strview path);
```

> Uniquely identifies the storage location of an asset.

Examples for an `AssetPath` are

```c++
AssetPath("materials/water.mat.json")
```

to locate an entire asset file or

```c++
AssetPath("scenes/main.scn.json:root.children[0]")
```

to locate obly specific data in an asset file.
The above `AssetPath` would locate this asset
```jsonc
// in scenes/main.scn.json
{
  ...
  "root": {
    ...
    "children": [
      {
        // this json object is located
      }
      ...
    ]
    ...
  }
  ...
}
```

## Asset Key

```c++
using AssetKey = Variant<UUID, AssetPath>;
```

> A unique key to an asset.

For development, assets are usually identified using an `AssetPath` since this
option more expressive. For distribution, assets are usually identified using
`UUID` since this option is more performant. However this is just a general
tendency and is currently not enforced.

## Asset API

### `addAsset`

```c++
UUID AssetAPI::addAsset(SharedPtr<Asset> asset);
```

> Register an asset to the asset-manager.

This method is useful when you create an asset dynamically,
i.e. in a script, but want it to be accessible outside of this script.

*Return* the uuid to the asset registered. 

> [!IMPORTANT]
> The asset-manager will only hold a weak reference to the added asset.
> This means, that if you do not reference the asset in other places, it is not
> saved and you will not be able to use it at any place.
