#include "common.hh"
#include "script.hh"
#include "log.hh"

namespace Parrot {
  // onAttach / onDetach
  void Script::onAttach() {
    LOG_APP_TRACE("Script::onAttach");
  }
  void Script::onDetach() {
    LOG_APP_TRACE("Script::onDetach");
  }

  // onUpdate
  void Script::onUpdate([[maybe_unused]] float32 delta_time) {
    LOG_APP_TRACE("Script::onUpdate(delta_time={})", delta_time);
  }

  // resolveEvent
  bool Script::resolveEvent([[maybe_unused]] const Event& e) {
    return false;
  }
}