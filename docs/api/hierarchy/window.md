# Window

## API

### Titlebar
    
#### `getTitle`

```cpp
const string& Window::getTitle()
```

#### `setIcon`

```cpp
void Window::setIcon(const uchar* bytes, uint width, uint height)
```

### Open / Close

#### `isOpen`

```cpp
bool Window::isOpen() const
```

#### `close`

```cpp
void Window::close()
```

### Cursor

#### `setCursorState`

```cpp
void Window::setCursorState(CursorState state)
```

`CursorState`
- `NORMAL`
- `HIDDEN`
- `CAPTURED`

#### `getCursorCoords`

```cpp
Vec2<> Window::getCursorCoords() const
```
