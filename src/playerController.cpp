#include "playerController.hpp"

PlayerController::PlayerController() {
    set_physics_process(true);
    set_process_unhandled_input(true);

    m_speed = 10;
}

PlayerController::~PlayerController() {

}

void PlayerController::_bind_methods() {
    ClassDB::bind_method(D_METHOD("getSpeed"), &PlayerController::getSpeed);
    ClassDB::bind_method(D_METHOD("setSpeed", "m_speed"), &PlayerController::setSpeed);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "setSpeed", "getSpeed");

    ClassDB::bind_method(D_METHOD("getRotationSensitivity"), &PlayerController::getRotationSensitivity);
    ClassDB::bind_method(D_METHOD("setRotationSensitivity", "m_rotationSensitivity"), &PlayerController::setRotationSensitivity);

    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "rotationSensitivity"), "setRotationSensitivity", "getRotationSensitivity");

    ClassDB::bind_method(D_METHOD("getSmoothingSpeed"), &PlayerController::getSmoothingSpeed);
    ClassDB::bind_method(D_METHOD("setSmoothingSpeed", "m_smoothingSpeed"), &PlayerController::setSmoothingSpeed);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "smoothingSpeed"), "setSmoothingSpeed", "getSmoothingSpeed");
}

void PlayerController::_ready() {
    Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_CAPTURED);
}
void PlayerController::_input(const Ref<InputEventKey> &event) {
    if (!event.is_valid())
        return;

    // If t is pressed, either freeze the camera movement or unfreeze it
    if (event->is_pressed() && event->get_keycode() == Key::KEY_T) 
    {
        if (m_pauseControl)
        {
            // Switches to play -> mouse dissapears and camera movement is free
            Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_CAPTURED);
            m_pauseControl = false;
        }
        else {
            // Switches to freeze -> mouse appears and camera movement freezes
            Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_VISIBLE);
            m_pauseControl = true;
        }
    }
}
void PlayerController::_unhandled_input(const Ref<InputEvent> &a_event) {
    Ref<InputEventMouseMotion> mouseMotion = a_event;

    if (!mouseMotion.is_valid())
        return;

    // If mouse input is valid, update the target with the motion and clamp the vertical movement
    Vector2 motion = mouseMotion->get_relative();
    m_targetRotation.y -= motion.x * m_rotationSensitivity.x;
    m_targetRotation.x -= motion.y * m_rotationSensitivity.y;

    m_targetRotation.x = CLAMP(m_targetRotation.x, -90.0f, 90.0f);
}
void PlayerController::_physics_process(double a_delta) {
    m_direction.zero();
    m_velocity.zero();

    if (Input::get_singleton()->is_key_pressed(KEY_E)) m_direction.z -= 1; // Forward
    if (Input::get_singleton()->is_key_pressed(KEY_D)) m_direction.z += 1; // Back
    if (Input::get_singleton()->is_key_pressed(KEY_S)) m_direction.x -= 1; // Left
    if (Input::get_singleton()->is_key_pressed(KEY_F)) m_direction.x += 1; // Right
    if (Input::get_singleton()->is_key_pressed(KEY_SPACE)) m_direction.y += 1; // Up
    if (Input::get_singleton()->is_key_pressed(KEY_CTRL)) m_direction.y -= 1; // Down

    UtilityFunctions::print("Direction X: ", std::floor(m_direction.x * 10.0) / 10.0, " Z: ", std::floor(m_direction.z * 10.0) / 10.0, " Y: ", std::floor(m_direction.y * 10.0) / 10.0);

    if (m_direction != Vector3(0, 0, 0))
        m_direction.normalized();
    
    // global movement
    Transform3D transform = get_global_transform();

    Vector3 move_dir = (transform.basis.get_column(0) * m_direction.x) + 
                       (transform.basis.get_column(1) * m_direction.y) +
                       (transform.basis.get_column(2) * m_direction.z);
    move_dir = move_dir.normalized();

    Vector3 new_pos = get_global_position() + move_dir * m_speed * a_delta;
    set_global_position(new_pos);

    if (m_pauseControl)
        return;

    // Lerp to the targetRotation, which is set in the unhandled input and update the node's position
    m_smoothedRotation = m_smoothedRotation.lerp(m_targetRotation, (float)a_delta * m_smoothingSpeed);

    set_rotation_degrees(Vector3(m_smoothedRotation.x, m_smoothedRotation.y, 0));
}