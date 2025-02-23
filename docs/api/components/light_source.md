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

### AmbientLight

#### `intensity`

```cpp
DefaultFloat AmbientLight::intensity
```

#### `color`

```cpp
Vec3<uint8> AmbientLight::color
```

### DirectionalLight

#### `direction`

```cpp
Vec3<> DirectionalLight::direction
```

#### `intensity`

```cpp
DefaultFloat DirectionalLight::intensity
```

#### `color`

```cpp
Vec3<uint8> DirectionalLight::color
```

### PointLight

#### `position`

```cpp
Vec3<> PointLight::position
```

#### `range`

```cpp
DefaultFloat PointLight::range
```

#### `intensity`

```cpp
DefaultFloat PointLight::intensity
```

#### `color`

```cpp
Vec3<uint8> PointLight::color
```

### SpotLight

#### `position`

```cpp
Vec3<> SpotLight::position
```

#### `direction`

```cpp
Vec3<> SpotLight::direction
```

#### `angle`

```cpp
DefaultFloat SpotLight::angle
```

#### `intensity`

```cpp
DefaultFloat SpotLight::intensity
```

#### `color`

```cpp
Vec3<uint8> SpotLight::color
```
