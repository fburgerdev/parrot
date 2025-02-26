# LightSource

## API

### `value`

```c++
Variant<
  AmbientLight,
  DirectionalLight,
  PointLight,
  SpotLight
> LightSource::value;
```

> The type-specific data of the light-source.

### AmbientLight

#### `intensity`

```c++
DefaultFloat AmbientLight::intensity;
```

> The light intensity of the ambient-light.

*Default value* is `1`.

#### `color`

```c++
Vec3<uint8> AmbientLight::color;
```

> The emitting color of the ambient-light.

*Default value* is `{255,255,255}`, i.e white.

### DirectionalLight

#### `direction`

```c++
Vec3<> DirectionalLight::direction;
```

> The direction the directional-light is pointing to.

> [!IMPORTANT]
> This vector is expected to be normalized.

#### `intensity`

```c++
DefaultFloat DirectionalLight::intensity;
```

> The light intensity of the directional-light.

*Default value* is `1`.

#### `color`

```c++
Vec3<uint8> DirectionalLight::color;
```

> The emitting color of the directional-light.

*Default value* is `{255,255,255}`, i.e white.

### PointLight

#### `position`

```c++
Vec3<> PointLight::position;
```

> The position where the point-light is located.

#### `range`

```c++
DefaultFloat PointLight::range;
```

> The maximum distance the point-light illuminates objects.

#### `intensity`

```c++
DefaultFloat PointLight::intensity;
```

> The light intensity of the directional-light.

*Default value* is `1`.

#### `color`

```c++
Vec3<uint8> PointLight::color;
```

> The emitting color of the point-light.

*Default value* is `{255,255,255}`, i.e white.

### SpotLight

#### `position`

```c++
Vec3<> SpotLight::position;
```

> The position where the spot-light is located.

#### `direction`

```c++
Vec3<> SpotLight::direction;
```

> The direction the spot-light is pointing to.

> [!IMPORTANT]
> This vector is expected to be normalized.

#### `angle`

```c++
DefaultFloat SpotLight::angle;
```

> The maximum angle the spot-light emits light based on `SpotLight::direction`.

*Default value* is `pi/2`, i.e. 90deg.

#### `intensity`

```c++
DefaultFloat SpotLight::intensity;
```

> The light intensity of the spot-light.

*Default value* is `1`.

#### `color`

```c++
Vec3<uint8> SpotLight::color;
```

> The emitting color of the spot-light.

*Default value* is `{255,255,255}`, i.e white.
