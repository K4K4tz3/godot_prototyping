#ifndef GAME_MANGER_H
#define GAME_MANAGER_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/classes/camera2d.hpp>


using namespace godot;

class GameManager : public Node {
    GDCLASS(GameManager, Node)

private:

protected:
    static void _bind_methods();

public:
    GameManager();
    ~GameManager();

    void _input(const Ref<InputEventKey> &event);
    void _process(double delta);
};

#endif