#include "gameManager.hpp"

GameManager::GameManager() {
    bool isNotEditor = false;
    if (!Engine::get_singleton()->is_editor_hint())
    {
        isNotEditor = true;

        spawnPlayer();
    }

    set_process(isNotEditor);
    set_process_input(isNotEditor);
}
GameManager::~GameManager() {
}

void GameManager::_bind_methods() {

}

void GameManager::_input(const Ref<InputEventKey> &event) {
    if (!event.is_valid())
        return;
    
    Ref<InputEventKey> event_key = event;
    if (event_key.is_valid() && event_key->is_pressed() && event_key->get_keycode() == Key::KEY_ESCAPE)
    {
        despawnPlayer();

        get_tree()->quit();
    }
}
void GameManager::_process(double delta) {
}

void GameManager::spawnPlayer() {
    playerScene_ = ResourceLoader::get_singleton()->load("res://player.tscn");

    if (playerScene_.is_valid())
    {
        playerInstance_ = Object::cast_to<PlayerController>(playerScene_->instantiate());

        if (playerScene_.is_valid())
        {
            playerInstance_->set_name("Player");
            add_child(playerInstance_);
            playerInstance_->set_position(Vector3(0, 0, 0));

            Camera3D* camera = Object::cast_to<Camera3D>(playerInstance_->find_child("Camera3D"));
            if (camera)
                camera->make_current();
        }
        else
            UtilityFunctions::print("ERROR::INSTANTIATION_NOT_WORKED: PlayerController from player.tscn could not be instantiated");
    }
    else
        UtilityFunctions::print("ERROR::RESOURCE: player.tscn could not be found or loaded");
}
void GameManager::despawnPlayer() {
    playerInstance_->queue_free();
    playerInstance_ = nullptr;
    
    playerScene_.unref();
}