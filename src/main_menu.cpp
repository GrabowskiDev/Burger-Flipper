// main_menu.cpp
#include "main_menu.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

using namespace godot;

void MainMenu::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_on_start_button_pressed"), &MainMenu::_on_start_button_pressed);
    ClassDB::bind_method(D_METHOD("set_start_button_path", "p_path"), &MainMenu::set_start_button_path);
    ClassDB::bind_method(D_METHOD("get_start_button_path"), &MainMenu::get_start_button_path);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "start_button_path"), "set_start_button_path", "get_start_button_path");

    ClassDB::bind_method(D_METHOD("_on_quit_button_pressed"), &MainMenu::_on_quit_button_pressed);
    ClassDB::bind_method(D_METHOD("set_quit_button_path", "p_path"), &MainMenu::set_quit_button_path);
    ClassDB::bind_method(D_METHOD("get_quit_button_path"), &MainMenu::get_quit_button_path);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "quit_button_path"), "set_quit_button_path", "get_quit_button_path");
}

MainMenu::MainMenu() {}
MainMenu::~MainMenu() {}

void MainMenu::_ready() {
    if (!start_button_path.is_empty()) {
        Button *start_button = get_node<Button>(start_button_path);
        if (start_button) {
            start_button->connect("pressed", Callable(this, "_on_start_button_pressed"));
        }
    }
    if (!quit_button_path.is_empty()) {
        Button *quit_button = get_node<Button>(quit_button_path);
        if (quit_button) {
            quit_button->connect("pressed", Callable(this, "_on_quit_button_pressed"));
        }
    }
}

void MainMenu::_on_start_button_pressed() {
    if (is_inside_tree()) {
        get_tree()->change_scene_to_file("res://main.tscn");
    }
}

void MainMenu::_on_quit_button_pressed() {
    if (is_inside_tree()) {
        get_tree()->quit();
    }
}

void MainMenu::set_start_button_path(NodePath p_path) {
    start_button_path = p_path;
}

NodePath MainMenu::get_start_button_path() const {
    return start_button_path;
}

void MainMenu::set_quit_button_path(godot::NodePath p_path) {
    quit_button_path = p_path;
}

NodePath MainMenu::get_quit_button_path() const {
    return quit_button_path;
}