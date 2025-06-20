#include "player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/scene_tree.hpp>


using namespace godot;

void Player::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_speed"), &Player::get_speed);
    ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &Player::set_speed);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");

    ClassDB::bind_method(D_METHOD("get_jump_velocity"), &Player::get_jump_velocity);
    ClassDB::bind_method(D_METHOD("set_jump_velocity", "p_jump_velocity"), &Player::set_jump_velocity);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "jump_velocity"), "set_jump_velocity", "get_jump_velocity");

    ClassDB::bind_method(D_METHOD("get_head"), &Player::get_head);
    ClassDB::bind_method(D_METHOD("set_head", "p_head"), &Player::set_head);

    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "head"), "set_head", "get_head");

    ClassDB::bind_method(D_METHOD("get_hand"), &Player::get_hand);
    ClassDB::bind_method(D_METHOD("set_hand", "p_hand"), &Player::set_hand);

    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "hand"), "set_hand", "get_hand");
}

Player::Player() {
    speed = 5.0;
    jump_velocity = 3.0;
}

Player::~Player() {
    //cleanup
}

void Player::_process(double delta) {
    if (!is_on_floor()) {
        Vector3 new_velocity = get_velocity() + (get_gravity() * delta);
        set_velocity(new_velocity);
    }

    Vector3 new_velocity = get_movement_vector();
    new_velocity.y = get_velocity().y;
    if (!is_on_floor()) {
        new_velocity += (get_gravity() * delta);
    }

    set_velocity(new_velocity);

    move_and_slide();

    if (Input::get_singleton()->is_action_just_pressed("exit")) {
        get_tree()->quit();
    }
}

void Player::_ready() {
    Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_CAPTURED);
//    Ref<PackedScene> scene = ResourceLoader::get_singleton()->load("res://assets/burger_parts/burger_bottom.fbx", "PackedScene");
//    add_to_hand(scene);
    current_object = nullptr;
}

void Player::add_to_hand(Ref<PackedScene> scene){
    Node3D *node_hand = get_node<Node3D>(hand);
//    print_line("pre instantiating a scene");
    if (scene.is_valid() && current_object == nullptr) {
//        print_line("instantiating a scene");
        Node *node = scene->instantiate();
        node_hand->add_child(node);
        current_object = node;
    }
}

void Player::add_to_hand_node(godot::Node *node) {
//    if (current_object) {return;}
    Node3D *node_hand = get_node<Node3D>(hand);
    if (node->get_parent() != node_hand) {
        node_hand->add_child(node);
    }
    current_object = node;
}

void Player::remove_from_hand() {
    current_object = nullptr;
}

Vector3 Player::get_movement_vector() {
    double right_movement = Input::get_singleton()->get_action_strength("move_right") - Input::get_singleton()->get_action_strength("move_left");
    double forward_movement = Input::get_singleton()->get_action_strength("move_forward") - Input::get_singleton()->get_action_strength("move_backward");

    Vector3 local_dir(right_movement, 0, -forward_movement);

    Vector3 global_dir = get_global_transform().basis.xform(local_dir);

    return global_dir.normalized() * speed;
}

void Player::_unhandled_input(const Ref<InputEvent> &event) {
    Ref<InputEventMouseMotion> mouse_motion = event;
    if (mouse_motion.is_valid()) {
        Vector2 rel = mouse_motion->get_relative();
        Node3D *node_head = get_node<Node3D>(head);
        Node3D *node_hand = get_node<Node3D>(hand);

        // Obrót gracza w osi Y (lewo/prawo)
        this->rotate_y(-rel.x * 0.005);

        // Obrót głowy/kamery w osi X (góra/dół)
        head_pitch = Math::clamp(head_pitch - rel.y * 0.005, -Math_PI/2, Math_PI/2);
        node_head->set_rotation(Vector3(head_pitch, 0, 0));

//        print_line(current_object);
//        if (current_object) {
//            current_object->queue_free();
//            current_object = nullptr;
//        }
//        print_line(node_head->get_rotation());
    }
}

void Player::set_speed(const double p_speed) {
    speed = p_speed;
}

void Player::set_jump_velocity(const double p_jump_velocity) {
    jump_velocity = p_jump_velocity;
}

void Player::set_head(NodePath p_head) {
    head = p_head;
}

void Player::set_hand(NodePath p_hand) {
    hand = p_hand;
}

//void Player::set_bottom_bun(Ref<Object> p_bottom_bun) {
//    bottom_bun = p_bottom_bun;
//}
double Player::get_speed() const {
    return speed;
}

double Player::get_jump_velocity() const {
    return jump_velocity;
}

NodePath Player::get_head() const {
    return head;
}

NodePath Player::get_hand() const {
    return hand;
}

void Player::set_current_object(godot::Node *p_current_object) {
    current_object = p_current_object;
}

Node *Player::get_current_object() {
    return current_object;
}

//Ref<Object> Player::get_bottom_bun() const {
//    return bottom_bun;
//}