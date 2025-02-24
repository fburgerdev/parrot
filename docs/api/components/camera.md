# Camera

## API

### `value`

```cpp
Variant<PerspectiveCamera, OrthographicCamera> Camera::value
```

> The type-specific data of the camera.

### PerspectiveCamera

#### `fov`

```cpp
float32 PerspectiveCamera::fov
```

> The field-of-view of the perspective-camera.

*Default value* is `pi/2`, i.e. 90deg.

#### `z_range`

```cpp
Vec2<float32> PerspectiveCamera::z_range
```

> The depth range `{min, max}` where objects are captured by the camera.

*Default value* is `{0.01, 10'000.0}`.

### OrthographicCamera

#### `scale`

```cpp
float32 OrthographicCamera::scale
```

> The scale of the orthographic-camera.

The larger the scale, the more objects can be seen with the camera and the
smaller they appear.

*Default value* is `1`.

#### `z_range`

```cpp
Vec2<float32> OrthographicCamera::z_range
```

> The depth range `{min, max}` where objects are captured by the camera.

*Default value* is `{0.01, 10'000.0}`.
