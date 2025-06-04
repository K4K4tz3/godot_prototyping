#include "playerController.hpp"

PlayerController::PlayerController() {
    set_physics_process(true);

    speed_ = 10;
}

PlayerController::~PlayerController() {

}

void PlayerController::_bind_methods() {
    ClassDB::bind_method(D_METHOD("getSpeed"), &PlayerController::getSpeed);
    ClassDB::bind_method(D_METHOD("setSpeed", "speed_"), &PlayerController::setSpeed);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "sped"), "setSpeed", "getSpeed");
}

void PlayerController::_physics_process(double a_delta) {
    direction_.zero();
    velocity_.zero();

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

    velocity_.x = direction_.x * speed_;
    velocity_.z = direction_.z * speed_;

    set_velocity(velocity_);
    move_and_slide();
}