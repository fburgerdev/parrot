#pragma once

namespace Parrot {
  template<class T>
  usize BasicComponent<T>::getID() const {
    return typeid(BasicComponent<T>).hash_code();
  }
}