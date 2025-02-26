# Entity

## API

### Tag

#### `getTag`

```c++
const string& Entity::getTag() const
```

> Get the tag of the entity.

#### `findByTag`

```c++
Set<Entity*> Entity::findByTag(strview tag)
```

```c++
Set<const Entity*> Entity::findByTag(strview tag) const
```

> Find all children entities (recursively) with the given tag.

### Children

#### `createChild`

```c++
Entity& Entity::createChild(bool is_visible = false)
```

> Create a child entity and return a reference.

*Arg* `is_visible` sets the visibility of the created child entity.

*Return* a reference to the created child entity.
#### `destroyChild`

```c++
bool Entity::destroyChild(UUID uuid)
```

> Destroy the child entity with the given UUID, if existent.

*Return* whether such a child existed.

```c++
bool Entity::destroyChild(strview tag)
```

> Destroy **all** child entities with the given tag.

*Return* whether at least one child was destroyed.

#### `foreachChild`

```c++
void Entity::foreachChild(Func<void(Entity&)> func)
```

```c++
void Entity::foreachChild(Func<void(const Entity&)> func) const
```

> Call the given callback for each child entity.

### Components

#### `hasComponent`

```c++
template<class T>
bool Entity::hasComponent() const
```

> Find out whether the entity has a component of the given type.

#### `getComponent`

```c++
template<class T>
T& Entity::getComponent()
```

```c++
template<class T>
const T& Entity::getComponent() const;
```

> Get the component of the given type.

> [!NOTE]
> This function fails if the entity does not have a component of the given type.

#### `addComponent`

```c++
template<class T, class... TArgs>
T& Entity::addComponent(TArgs&&... args)
```

> Emplace a component of the given type.

*Return* a reference to added component.

> [!NOTE]
> This function fails if the entity already has a component of the given type.

#### `removeComponent`

```c++
template<class T>
void Entity::removeComponent()
```

> Remove the component of the given type.

> [!NOTE]
> This function fails if the entity does not have a component of the given type.

### Transform

```c++
Transform<> Entity::transform
```
