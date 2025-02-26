# Math

## Basic Math

Currently, the default floating point data type is a `float32`.

```cpp
using DefaultFloat = float32;
```

## Vec\<T, N\>

### Arithmetic

```cpp
Vec<T, N> Vec<T, N>::operator+(const Vec<T, N>& other) const;
Vec<T, N> Vec<T, N>::operator-(const Vec<T, N>& other) const;
Vec<T, N> Vec<T, N>::operator*(T scalar) const;
Vec<T, N> Vec<T, N>::operator/(T scalar) const;

Vec<T, N> Vec<T, N>::operator+=(const Vec<T, N>& other) const;
Vec<T, N> Vec<T, N>::operator-=(const Vec<T, N>& other) const;
Vec<T, N> Vec<T, N>::operator*=(T scalar) const;
Vec<T, N> Vec<T, N>::operator/=(T scalar) const;
```

> Standard component-wise vector arithmetic.

### Dot Product

```cpp
template<class T, usize N>
T dot(const Vec<T, N>& x, const Vec<T, N>& y);
```

> The mathematical scalar product.

*Return* the sum of the component-wise products.

### Cross Product

```cpp
template<class T>
Vec3<T> cross(const Vec3<T>& x, const Vec3<T>& y);
```

> The mathematical cross product.

*Return* the surface normal orthogonal to `x` and `y`,
following the [right-hand-rule](https://en.wikipedia.org/wiki/right-hand_rule).

### Vec2\<T\>

```cpp
T Vec2<T>::x;
T Vec2<T>::y;
```

> The x and y components of the vector.

### Vec3\<T\>

```cpp
T Vec3<T>::x;
T Vec3<T>::y;
T Vec3<T>::z;
```

> The x, y and z components of the vector.

### Vec4\<T\>

```cpp
T Vec4<T>::x;
T Vec4<T>::y;
T Vec4<T>::z;
T Vec4<T>::w;
```

> The x, y, z and w components of the vector.
