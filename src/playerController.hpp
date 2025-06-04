#ifndef PLAYER_CONTROLLER_HPP
#define PLAYER_CONTROLLER_HPP

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/camera3d.hpp>

using namespace godot;

class PlayerController : public CharacterBody3D {
    GDCLASS(PlayerController, CharacterBody3D)

private:
protected:
    static void _bind_methods();
public:
    PlayerController();
    ~PlayerController();

    void _input(const Ref<InputEventKey> &event_key);
    void _process(double a_delta);
};

#endif