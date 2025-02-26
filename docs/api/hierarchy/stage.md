# Stage

## API

### Window

```c++
Window Stage::window
```

> The window the stage renders all scenes to.

### Root

```c++
List<Pair<Scene, Renderer>>::scene_layers
```

> A stack of scene-renderer pairs that are rendered to the window one after another.

Each pair consists of a scene and a renderer where the respective renderer is
used to render its respective scene to the window.