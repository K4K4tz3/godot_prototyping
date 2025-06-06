#ifndef PLAYER_CONTROLLER_HPP
#define PLAYER_CONTROLLER_HPP

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

class PlayerController : public CharacterBody3D {
    GDCLASS(PlayerController, CharacterBody3D)

private:
    float speed_;
    float turnSpeed_;

    Vector3 direction_;
    Vector3 velocity_;
    float aimVelocity_;
    
    Vector2 rotationSensitivity = Vector2(0.1, 0.1);
    Vector2 smoothedRotation = Vector2();
    Vector2 targetRotation = Vector2();
    float smoothingSpeed = 6.0f;

    bool pauseControl_ = false;

protected:
    static void _bind_methods();
public:
    PlayerController();
    ~PlayerController();

    void _ready();
    void _input(const Ref<InputEventKey> &event);
    void _unhandled_input(const Ref<InputEvent> &event);
    void _physics_process(double a_delta);
    
    void setSpeed(const float a_speed) { speed_ = a_speed; };
    float getSpeed() const { return speed_; };
    void setTurnSpeed(const float a_turnSpeed) { turnSpeed_ = a_turnSpeed; };
    float getTurnSpeed() const { return turnSpeed_; };
};

#endif