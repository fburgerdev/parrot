#pragma once

namespace Parrot {
  namespace OpenGL {
    // createVertexBuffer
    template<class... Args>
    VertexBuffer& Context::createVertexBuffer(Args&&... args) {
      return _vertex_buffers.try_emplace(
        generateUUID(), std::forward<Args>(args)...
      ).first->second;
    }
    // createIndexBuffer
    template<class... Args>
    IndexBuffer& Context::createIndexBuffer(Args&&... args) {
      return _index_buffers.try_emplace(
        generateUUID(), std::forward<Args>(args)...
      ).first->second;
    }
    // createUniformBuffer
    template<class... Args>
    UniformBuffer& Context::createUniformBuffer(Args&&... args) {
      return _uniform_buffers.try_emplace(
        generateUUID(), std::forward<Args>(args)...
      ).first->second;
    }
    // createVertexArray
    template<class... Args>
    VertexArray& Context::createVertexArray(Args&&... args) {
      return _vertex_arrays.try_emplace(
        generateUUID(), std::forward<Args>(args)...
      ).first->second;
    }
  }
}