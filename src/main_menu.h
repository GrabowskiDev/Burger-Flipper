// main_menu.h
#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/node_path.hpp>

namespace godot {

    class MainMenu : public Node {
        GDCLASS(MainMenu, Node)

    private:
        NodePath start_button_path;

    protected:
        static void _bind_methods();

    public:
        MainMenu();
        ~MainMenu();

        void _ready() override;
        void _on_start_button_pressed();

        void set_start_button_path(NodePath p_path);
        NodePath get_start_button_path() const;
    };

}

#endif // MAIN_MENU_H