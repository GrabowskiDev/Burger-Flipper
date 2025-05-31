#include "burger.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/area3d.hpp>
#include "player.h"
#include "burger_part.h"

using namespace godot;

void Burger::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_interact_area"), &Burger::get_interact_area);
    ClassDB::bind_method(D_METHOD("set_interact_area", "p_interact_area"), &Burger::set_interact_area);

    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "interact_area"), "set_interact_area", "get_interact_area");

    ClassDB::bind_method(D_METHOD("_on_body_entered_burger", "body"), &Burger::_on_body_entered_burger);
}

Burger::Burger() {
    curr_height = 0;
    is_done = false;
    is_empty = true;
}

Burger::~Burger() {
    //cleanup
}

void Burger::_process(double delta) {
//    time_passed += delta;

//    Vector2 new_position = Vector2(10.0 + (10.0 * sin(time_passed * 2.0)), 10.0 + (10.0 * cos(time_passed * 1.5)));

//    set_position(new_position);
}

void Burger::_ready() {
    Area3D *interact_area_node = get_node<Area3D>(interact_area);
    interact_area_node->connect("body_entered", Callable(this, "_on_body_entered_burger"));
    print_line("ready burger");
}

void Burger::_on_body_entered_burger(Node *body) {
    print_line("something entered body in burger");

    if (Player *player = Object::cast_to<Player>(body)) {
        Node* current_object = player->get_current_object();
//        print_line("something entered body in burger 222");
        if (BurgerPart *burger_part = Object::cast_to<BurgerPart>(current_object)) {
//            print_line("something entered body in burger 333333");
            add_to_burger(player, burger_part);
        }
    }
}

NodePath Burger::get_interact_area() {
    return interact_area;
}

void Burger::set_interact_area(NodePath p_interact_area) {
    interact_area = p_interact_area;
}

void Burger::add_to_burger(Player *player, BurgerPart *element){
    if(is_done){ return; }
    print_line("a");

    String name_of_element = element->get_name();
    print_line(name_of_element);

    if(is_empty && name_of_element == "bottom_bun"){
        element->get_parent()->remove_child(element);

//        element->set_position(Vector3(0, curr_height, 0));
        curr_height += element->get_height();
        burger_elements.append(element);
        is_empty = false;
        add_child(element);
        player->set_current_object(nullptr);
    }else if(!is_empty && !(name_of_element == "bottom_bun")){
        element->get_parent()->remove_child(element);

        print_line(curr_height);
        burger_elements.append(element);
        add_child(element);
        element->set_position(Vector3(0, curr_height  + (element->get_height())/2, 0));
        curr_height += element->get_height();
        player->set_current_object(nullptr);

        if(name_of_element == "top_bun"){
            is_done = true;
            set_position(Vector3(0,0,0));
            get_parent()->remove_child(this);
            player->add_to_hand_node(this);
        }
    }
}