# Scripting

## Updates

Every script in the hierarchy is updated regularly.
This is done by invoking `onUpdate` on every iteration of the game loop. 

### `onUpdate`

```c++
void Script::onUpdate(float32 delta_time);
```

> Update the script.

*Arg* `delta_time` is the seconds elapsed since the start of the previous game
loop iteration (or since the game loop started for the first iteration).

## Events

In order to communicate with objects that are higher in the hierarchy,
you can use events.

### `resolveEvent`

```c++
virtual bool Script::resolveEvent(const Event& e);
```

> Try to resolve the given event.

*Return* if the event could be resolved.

> [!NOTE]
> This method can be overloaded to fit your needs.
> By default, the method does nothing and returns `false`.

### `raiseEvent`

```c++
void Script::raiseEvent(const Event& e);
```

> Raise an event at the script.

First, try to resolve the event using `Script::resolveEvent`.
If the event could not be resolved,
propagate the event recursively to its parent, if existent.
