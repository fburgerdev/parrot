#pragma once
#include "common.hh"

namespace Parrot {
  namespace OpenGL {
    // UniformType
    enum class UniformType {
      // scalars
      BOOL, INT32, UINT32, FLOAT32, FLOAT64,
      // vectors
      VEC2_BOOL, VEC2_INT32, VEC2_UINT32, VEC2_FLOAT32, VEC2_FLOAT64,
      VEC3_BOOL, VEC3_INT32, VEC3_UINT32, VEC3_FLOAT32, VEC3_FLOAT64,
      VEC4_BOOL, VEC4_INT32, VEC4_UINT32, VEC4_FLOAT32, VEC4_FLOAT64,
      // matrices
      MAT2X2_FLOAT32, MAT2X2_FLOAT64, MAT2X3_FLOAT32,
      MAT2X3_FLOAT64, MAT2X4_FLOAT32, MAT2X4_FLOAT64,
      MAT3X2_FLOAT32, MAT3X2_FLOAT64, MAT3X3_FLOAT32,
      MAT3X3_FLOAT64, MAT3X4_FLOAT32, MAT3X4_FLOAT64,
      MAT4X2_FLOAT32, MAT4X2_FLOAT64, MAT4X3_FLOAT32,
      MAT4X3_FLOAT64, MAT4X4_FLOAT32, MAT4X4_FLOAT64,
      // TODO: opaque types... (samples, images, atomic counters)
    };

    // UniformBuffer
    class UniformBuffer {
    public:
      // (constructor)
      UniformBuffer(usize size);
      UniformBuffer(const void* buffer, usize size);
      UniformBuffer(const UniformBuffer&) = delete;
      UniformBuffer(UniformBuffer&& other) noexcept;
      // (destructor)
      ~UniformBuffer();
      // (assignment)
      UniformBuffer& operator=(const UniformBuffer&) = delete;
      UniformBuffer& operator=(UniformBuffer&& other) noexcept;

      // overwriteData
      void overwriteData(const void* buffer, usize size, usize offset = 0);

      // getBindingPoint
      uint getBindingPoint() const;

      // bind / unbind
      void bind() const;
      static void unbind();
    private:
      static inline uint s_buffer_count = 0;

      uint _gpu_id = 0, _binding_point = 0;
      bool _is_static;
    };
  }
}