---
layout: default
title: Home
---

# 🦜 Overview

## 🔌 API Documentation

| 🏛️ Hierarchy |
| - |
| [App](api/hierarchy/app.md) | The top-level object, handling initialization, asset management and the main loop. |
| [Stage](api/hierarchy/stage.md) | Manages a window and a stack of scenes, rendered sequentially on top of each other. |
| [Window](api/hierarchy/window.md) | Represents a physical window where rendering and user interactions occur. |
| [Scene](api/hierarchy/scene.md) | A collection of entities in a 3 dimensional coordinate system. |
| [Entity](api/hierarchy/entity.md) | A fundamental object that holds and organizes various components and child entities for behavior and rendering. |

| 🧩 Components |
| - |
| [Camera](api/components/camera.md) | Defines the viewpoint and projection for rendering the scene. |
| [RenderObject](api/components/render_object.md) | Represents a visual object in the scene with a mesh and material data. |
| [LightSource](api/components/light_source.md) | Emits light in the scene, affecting how objects are shaded and rendered. |
