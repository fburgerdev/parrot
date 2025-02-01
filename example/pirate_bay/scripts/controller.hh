#pragma once
#include "fps.hh"

namespace Parrot {
  // PlayerController
  class PlayerController : public EntityScript {
  public:
    // PlayerController
    PlayerController(Entity& entity)
      : EntityScript(entity) {}

    // resolveEvent
    virtual bool resolveEvent(const Event& e) override {
      if (const FPSEvent* fpse = dynamic_cast<const FPSEvent*>(&e)) {
        _is_captured = fpse->is_captured;
        if (!_is_captured) {
          _mouse_pos = std::nullopt;
        }
      }
      if (_is_captured) {
        if (const WindowEvent* we = dynamic_cast<const WindowEvent*>(&e)) {
          if (auto* kp = we->getKeyPress()) {
            if (kp->state == KeyState::PRESSED ||
                kp->state == KeyState::RELEASED) {
              if (kp->code == KeyCode::KEY_W) {
                _w = (kp->state == KeyState::PRESSED);
              }
              else if (kp->code == KeyCode::KEY_A) {
                _a = (kp->state == KeyState::PRESSED);
              }
              else if (kp->code == KeyCode::KEY_S) {
                _s = (kp->state == KeyState::PRESSED);
              }
              else if (kp->code == KeyCode::KEY_D) {
                _d = (kp->state == KeyState::PRESSED);
              }
              else if (kp->code == KeyCode::KEY_SPACE) {
                _space = (kp->state == KeyState::PRESSED);
              }
              else if (kp->code == KeyCode::KEY_LEFT_CONTROL) {
                _ctrl = (kp->state == KeyState::PRESSED);
              }
            }
            return true;
          }
          if (auto* mm = we->getMouseMove()) {
            if (_mouse_pos) {
              Vec2<> delta = (mm->coords - *_mouse_pos);
              entity->transform.rotation.y -= _mouse_speed * delta.x;
              entity->transform.rotation.x -= _mouse_speed * delta.y;
              entity->transform.rotation.x = clamp(
                entity->transform.rotation.x, -PI<> / 2, +PI<> / 2
              );
            }
            _mouse_pos = mm->coords;
          }
        }
      }
      return false;
    }
    // onUpdate
    virtual void onUpdate(float32 delta_time) override {
      if (_is_captured) {
        auto rotation_matrix = calcRotationMatrix(entity->transform.rotation);
        auto forward = Vec3<>(rotation_matrix * Vec4<>(0, 0, 1, 0));
        auto up = Vec3<>(rotation_matrix * Vec4<>(0, 1, 0, 0));
        auto right = Vec3<>(rotation_matrix * Vec4<>(1, 0, 0, 0));
        if (_w) {
          entity->transform.position += forward * _move_speed * delta_time;
        }
        if (_a) {
          entity->transform.position -= right * _move_speed * delta_time;
        }
        if (_s) {
          entity->transform.position -= forward * _move_speed * delta_time;
        }
        if (_d) {
          entity->transform.position += right * _move_speed * delta_time;
        }
        if (_space) {
          entity->transform.position += up * _move_speed * delta_time;
        }
        if (_ctrl) {
          entity->transform.position -= up * _move_speed * delta_time;
        }
      }
    }  
  private:
    bool _is_captured = false;
    DefaultFloat _move_speed = 10.0, _mouse_speed = 0.001;
    Opt<Vec2<>> _mouse_pos;
    bool _w = false, _a = false, _s = false, _d = false;
    bool _space = false, _ctrl = false;
  };
}