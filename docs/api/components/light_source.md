# LightSource

## API

### `value`

```cpp
Variant<
  AmbientLight,
  DirectionalLight,
  PointLight,
  SpotLight
> LightSource::value
```

> The type-specific data of the light-source.

### AmbientLight

#### `intensity`

```cpp
DefaultFloat AmbientLight::intensity
```

> The light intensity of the ambient-light.

*Default value* is `1`.

#### `color`

```cpp
Vec3<uint8> AmbientLight::color
```

> The emitting color of the ambient-light.

*Default value* is `{255,255,255}`, i.e white.

### DirectionalLight

#### `direction`

```cpp
Vec3<> DirectionalLight::direction
```

> The direction the directional-light is pointing to.

> [!IMPORTANT]
> This vector is expected to be normalized.

#### `intensity`

```cpp
DefaultFloat DirectionalLight::intensity
```

> The light intensity of the directional-light.

*Default value* is `1`.

#### `color`

```cpp
Vec3<uint8> DirectionalLight::color
```

> The emitting color of the directional-light.

*Default value* is `{255,255,255}`, i.e white.

### PointLight

#### `position`

```cpp
Vec3<> PointLight::position
```

> The position where the point-light is located.

#### `range`

```cpp
DefaultFloat PointLight::range
```

> The maximum distance the point-light illuminates objects.

#### `intensity`

```cpp
DefaultFloat PointLight::intensity
```

> The light intensity of the directional-light.

*Default value* is `1`.

#### `color`

```cpp
Vec3<uint8> PointLight::color
```

> The emitting color of the point-light.

*Default value* is `{255,255,255}`, i.e white.

### SpotLight

#### `position`

```cpp
Vec3<> SpotLight::position
```

> The position where the spot-light is located.

#### `direction`

```cpp
Vec3<> SpotLight::direction
```

> The direction the spot-light is pointing to.

> [!IMPORTANT]
> This vector is expected to be normalized.

#### `angle`

```cpp
DefaultFloat SpotLight::angle
```

> The maximum angle the spot-light emits light based on `SpotLight::direction`.

*Default value* is `pi/2`, i.e. 90deg.

#### `intensity`

```cpp
DefaultFloat SpotLight::intensity
```

> The light intensity of the spot-light.

*Default value* is `1`.

#### `color`

```cpp
Vec3<uint8> SpotLight::color
```

> The emitting color of the spot-light.

*Default value* is `{255,255,255}`, i.e white.
