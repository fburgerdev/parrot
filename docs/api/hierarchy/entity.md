# Entity

## Tag

### `getTag`

```c++
const string& Entity::getTag() const;
```

> Get the tag of the entity.

### `findByTag`

```c++
Set<Entity*> Entity::findByTag(strview tag);
```

```c++
Set<const Entity*> Entity::findByTag(strview tag) const;
```

> Find all children entities (recursively) with the given tag.

## Transform

```c++
Transform<> Entity::transform;
```

> The entities transform relative to its parent entity.

The transform properties apply in the following order:
1. scale
2. rotate
3. offset

```c++
Vec3<> Transform::position;
```

> The entities position in the scene.

The position is relative to the parent entities position.

```
Vec3<> Transform::rotation;
```

> The entities (euler) rotation in the scene.

The entities rotation is represented using an euler roation where
- x holds the rotation around the x axis (or 'yaw') from `0` to `2*pi`
- y holds the rotation around the x axis (or 'pitch') from `0` to `2*pi`
- z holds the rotation around the x axis (or 'roll') from `0` to `2*pi`

and is applied in the y->x->z (or yaw->pitch->roll) order.
For more information see [pitch, yaw, and roll](https://simple.wikipedia.org/wiki/pitch,_yaw,_and_roll).

The rotation is relative to its parent rotation.

```c++
Vec3<> Transform::scale;
```

> The entities scale in the scene.

The scale is relative to the parent entities scale.

### Example

// TODO

## Children

### `createChild`

```c++
Entity& Entity::createChild(bool is_visible = false);
```

> Create a child entity and return a reference.

*Arg* `is_visible` sets the visibility of the created child entity.

*Return* a reference to the created child entity.
### `destroyChild`

```c++
bool Entity::destroyChild(UUID uuid);
```

> Destroy the child entity with the given UUID, if existent.

*Return* whether such a child existed.

```c++
bool Entity::destroyChild(strview tag);
```

> Destroy **all** child entities with the given tag.

*Return* whether at least one child was destroyed.

### `foreachChild`

```c++
void Entity::foreachChild(Func<void(Entity&)> func);
```

```c++
void Entity::foreachChild(Func<void(const Entity&)> func) const;
```

> Call the given callback for each child entity.

## Components

### `hasComponent`

```c++
template<class T>
bool Entity::hasComponent() const;
```

> Find out whether the entity has a component of the given type.

### `getComponent`

```c++
template<class T>
T& Entity::getComponent();
```

```c++
template<class T>
const T& Entity::getComponent() const;
```

> Get the component of the given type.

> [!NOTE]
> This function fails if the entity does not have a component of the given type.

### `addComponent`

```c++
template<class T, class... Args>
T& Entity::addComponent(Args&&... args);
```

> Emplace a component of the given type.

*Return* a reference to added component.

> [!NOTE]
> This function fails if the entity already has a component of the given type.

### `removeComponent`

```c++
template<class T>
void Entity::removeComponent();
```

> Remove the component of the given type.

> [!NOTE]
> This function fails if the entity does not have a component of the given type.
