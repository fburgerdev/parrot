# RenderObject

## API

### `model`

```c++
AssetHandle<Model> RenderObject::model
```

> The handle to the model used to render this render-object.

> ![NOTE]
> Values in materials defined within this model are preferred over values in `RenderObject::material` on render. 

### `material`

```c++
AssetHandle<Material> RenderObject::material
```

> The handle to the material used to render this render-object.

> ![NOTE]
> Values in materials defined within the model `RenderObject::model` are preferred over values in this material on render. 

### `is_opaque`

```c++
bool RenderObject::is_opaque
```

> Decides whether the render-object is put in the opaque or translucent render batch.
