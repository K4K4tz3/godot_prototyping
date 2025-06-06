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
    int m_movementMode;
    float m_speed;

    Vector3 m_direction;
    Vector3 m_velocity;
    Vector3 m_position;

    void moveGlobal();
    void moveLocal();
    
protected:
    static void _bind_methods();
public:
    PlayerController();
    ~PlayerController();

    void _ready();
    void _input(const Ref<InputEventKey> &m_event);
    void _unhandled_input(const Ref<InputEvent> &m_event);
    void _physics_process(double a_delta);
    
    void setSpeed(const float a_speed) { m_speed = a_speed; };
    float getSpeed() const { return m_speed; };
//
// Camera Movement
//
private:
    Vector2 m_rotationSensitivity = Vector2(0.1, 0.1);
    Vector2 m_smoothedRotation = Vector2();
    Vector2 m_targetRotation = Vector2();
    float m_smoothingSpeed = 6.0f;

    bool m_pauseControl = false;

public:
    void setRotationSensitivity(const Vector2 a_rotationSensitivity) { m_rotationSensitivity = a_rotationSensitivity; };
    Vector2 getRotationSensitivity() { return m_rotationSensitivity; };
    void setSmoothingSpeed(const float a_smoothingSpeed) { m_smoothingSpeed = a_smoothingSpeed; };
    float getSmoothingSpeed() const { return m_smoothingSpeed; };
};

#endif