#include "gameManager.hpp"

GameManager::GameManager() {
    bool isNotEditor = false;
    if (!Engine::get_singleton()->is_editor_hint())
    {
        isNotEditor = true;
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
        get_tree()->quit();
}
void GameManager::_process(double delta) {
}