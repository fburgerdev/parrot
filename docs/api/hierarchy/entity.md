# Entity

## API

### Tag

#### `getTag`

```cpp
const string& Entity::getTag() const
```

#### `findByTag`

```cpp
Set<Entity*> Entity::findByTag(strview tag)
```

```cpp
Set<const Entity*> Entity::findByTag(strview tag) const
```

### Children

#### `createChild`

```cpp
Entity& Entity::createChild(bool is_visible = false)
```

#### `destroyChild`

```cpp
bool Entity::destroyChild(UUID uuid)
```

```cpp
bool Entity::destroyChild(strview tag)
```

#### `foreachChild`

```cpp
void Entity::foreachChild(Func<void(Entity&)> func)
```

```cpp
void Entity::foreachChild(Func<void(const Entity&)> func) const
```

### Components

#### `hasComponent`

```cpp
template<class T>
bool Entity::hasComponent() const
```

#### `getComponent`

```cpp
template<class T>
T& Entity::getComponent()
```

```cpp
template<class T>
const T& Entity::getComponent() const
```

#### `addComponent`

```cpp
template<class T, class... TArgs>
T& Entity::addComponent(TArgs&&... args)
```

#### `removeComponent`

```cpp
template<class T>
void Entity::removeComponent()
```

### Transform

```cpp
Transform<> Entity::transform
```
