#include "burger.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/area3d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include "player.h"
#include "burger_part.h"

using namespace godot;

void Burger::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_interact_area"), &Burger::get_interact_area);
    ClassDB::bind_method(D_METHOD("set_interact_area", "p_interact_area"), &Burger::set_interact_area);

    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "interact_area"), "set_interact_area", "get_interact_area");

    ClassDB::bind_method(D_METHOD("_on_body_entered_burger", "body"), &Burger::_on_body_entered_burger);
    ClassDB::bind_method(D_METHOD("_on_body_exited_burger", "body"), &Burger::_on_body_exited_burger);
}

Burger::Burger() {
    curr_height = 0;
    is_done = false;
    is_empty = true;
}

Burger::~Burger() {
    player_in_burger = nullptr;
}

void Burger::_ready() {
    Area3D *interact_area_node = get_node<Area3D>(interact_area);
    interact_area_node->connect("body_entered", Callable(this, "_on_body_entered_burger"));
    interact_area_node->connect("body_exited", Callable(this, "_on_body_exited_burger"));
    print_line("ready burger");
}

void Burger::_process(double delta) {
    if (is_done) return;
    if (player_in_burger && Input::get_singleton()->is_action_just_pressed("interact")) {
        Node* current_object = player_in_burger->get_current_object();
        if (BurgerPart *burger_part = Object::cast_to<BurgerPart>(current_object)) {
            add_to_burger(burger_part);
        }
    }
}

void Burger::_on_body_entered_burger(Node *body) {
    if (Player *player = Object::cast_to<Player>(body)) {
        player_in_burger = player;
    }
}

void Burger::_on_body_exited_burger(Node *body) {
    if (Object::cast_to<Player>(body) == player_in_burger) {
        player_in_burger = nullptr;
    }
}

NodePath Burger::get_interact_area() {
    return interact_area;
}

void Burger::set_interact_area(NodePath p_interact_area) {
    interact_area = p_interact_area;
}

void Burger::add_to_burger(BurgerPart *element){
    if(is_done || player_in_burger == nullptr){ return; }

    String name_of_element = element->get_name();
    print_line(name_of_element);

    if(is_empty && name_of_element == "bottom_bun"){
        element->get_parent()->remove_child(element);
        curr_height += element->get_height();
        burger_elements.append(element);
        is_empty = false;
        add_child(element);
        player_in_burger->set_current_object(nullptr);
    }else if(!is_empty && !(name_of_element == "bottom_bun")){
        element->get_parent()->remove_child(element);
        print_line(curr_height);
        burger_elements.append(element);
        add_child(element);
        element->set_position(Vector3(0, curr_height  + (element->get_height())/2, 0));
        curr_height += element->get_height();
        player_in_burger->set_current_object(nullptr);

        if(name_of_element == "top_bun"){
            is_done = true;
            set_position(Vector3(0,0,0));
            Node *parent = get_parent();
            if (Player *player = Object::cast_to<Player>(get_tree()->get_first_node_in_group("player_group"))) {
                parent->remove_child(this);
                player->add_to_hand_node(this);
            }
            player_in_burger = nullptr;
            return;
        }
    }
}