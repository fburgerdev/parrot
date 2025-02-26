# Window

## API

### Titlebar
    
#### `getTitle`

```c++
const string& Window::getTitle()
```

> Get the title of the physical window.

#### `setIcon`

```c++
void Window::setIcon(const uchar* bytes, uint width, uint height)
```

> Set the window icon in both the titlebar and the tray.

### Open / Close

#### `isOpen`

```c++
bool Window::isOpen() const
```

> Find out whether the window is marked as open.

> [!NOTE]
> This does not reflect the actual physical state of the window,
> but whether one should proceed with the update loop or not.

#### `close`

```c++
void Window::close()
```

> Mark the window as closed.

> [!NOTE]
> This does not physically close the window,
> but rather mark the window as closed so that the update loop stops in the next iteration.

### Cursor

#### `setCursorState`

```c++
void Window::setCursorState(CursorState state)
```

> Set the cursor state of for the window.

`CursorState` has one of the following values:
- `NORMAL` - Cursor is shown and can be moved around normally.
- `HIDDEN` - Cursor is hidden but can be moved around normally.
- `CAPTURED` - Cursor is hidden and at a fixed position, mouse movement events still occur.


#### `getCursorCoords`

```c++
Vec2<> Window::getCursorCoords() const
```

> Get the cursor coordinates relative to the windows top-left corner.