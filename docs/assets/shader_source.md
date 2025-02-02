# Shader-Source

## Format
Shaders are loaded using the [GLSL](https://www.khronos.org/opengl/wiki/Core_Language_(GLSL)) shader language,

extended with _snippet_ capabilities.

### Snippets

#### Shader Stage
```
[[vertex(<glsl-version>)]]
```

```
[[fragment(<glsl-version>)]]
```

declares the _shader stage_ with its respective _glsl version_ for the subsequent code
until overwritten with another _shader stage_ or a _snippet definition_.
> e.g. `<glsl-version>` 330 core

#### Snippet Definition
```
[[snippet "<identifier>"]]
```
declares the _snippet definition_ with the given _identifier_ for the subsequent code
until overwritten with another _snippet definition_ or a _shader stage_.

#### Snippet Include
```
[[include "<identifier>"]]
```
```
[[include "<identifier>" optional]]
```
includes (copy-paste) a defined snippet with the given _identifier_,
either fails if snippet does not exist (1) or includes empty snippet (2).