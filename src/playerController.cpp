#include "playerController.hpp"

PlayerController::PlayerController() {
    set_physics_process(true);
    set_process_unhandled_input(true);

    speed_ = 10;
    turnSpeed_ = 1;
}

PlayerController::~PlayerController() {

}

void PlayerController::_bind_methods() {
    ClassDB::bind_method(D_METHOD("getSpeed"), &PlayerController::getSpeed);
    ClassDB::bind_method(D_METHOD("setSpeed", "speed_"), &PlayerController::setSpeed);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "setSpeed", "getSpeed");

    ClassDB::bind_method(D_METHOD("getTurnSpeed"), &PlayerController::getTurnSpeed);
    ClassDB::bind_method(D_METHOD("setTurnSpeed", "turnSpeed_"), &PlayerController::setTurnSpeed);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "turnSpeed"), "setTurnSpeed", "getTurnSpeed");
}

void PlayerController::_ready() {
    Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_CAPTURED);
}
void PlayerController::_input(const Ref<InputEventKey> &event) {
    if (!event.is_valid())
        return;

    if (event->is_pressed() && event->get_keycode() == Key::KEY_T) 
    {
        pauseControl_ = pauseControl_ ? false : true;
    }
}
void PlayerController::_unhandled_input(const Ref<InputEvent> &event) {
    Ref<InputEventMouseMotion> mouseMotion = event;

    if (!mouseMotion.is_valid())
        return;

    Vector2 motion = mouseMotion->get_relative();
    targetRotation.y -= motion.x * rotationSensitivity.x;
    targetRotation.x -= motion.y * rotationSensitivity.y;

    targetRotation.x = CLAMP(targetRotation.x, -90.0f, 90.0f);
}
void PlayerController::_physics_process(double a_delta) {
    direction_.zero();
    velocity_.zero();
    aimVelocity_ = 0;

    if (Input::get_singleton()->is_key_pressed(KEY_E)) direction_.z -= 1; // Forward
    if (Input::get_singleton()->is_key_pressed(KEY_D)) direction_.z += 1; // Back
    if (Input::get_singleton()->is_key_pressed(KEY_S)) direction_.x -= 1; // Left
    if (Input::get_singleton()->is_key_pressed(KEY_F)) direction_.x += 1; // Right

    if (direction_ != Vector3(0, 0, 0))
    {
        direction_.normalized();
    }

    if (direction_ != Vector3(0, 0, 0))
        direction_.normalized();
    
    direction_ = to_global(direction_) - get_transform().get_origin();

    velocity_.x = direction_.x * speed_ * a_delta;
    velocity_.z = direction_.z * speed_ * a_delta;

    set_velocity(velocity_);
    move_and_slide();


    if (pauseControl_)
        return;

    // camera
    smoothedRotation = smoothedRotation.lerp(targetRotation, (float)a_delta * smoothingSpeed);

    set_rotation_degrees(Vector3(smoothedRotation.x, smoothedRotation.y, 0));
}