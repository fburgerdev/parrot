#pragma once

namespace Parrot {
  // getID
  template<class T>
  usize Script::getID() {
    return typeid(T).hash_code();
  }
}