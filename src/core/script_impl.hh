#pragma once

namespace Parrot {
  template<class T>
  usize Script::getID() {
    return typeid(T).hash_code();
  }
}