#include "player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>


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

    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "p_head"), "set_head", "get_head");

//    ClassDB::bind_method(D_METHOD("_unhandled_input", "event"), &Player::_unhandled_input);
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
}

void Player::_ready() {
    Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_CAPTURED);
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
//        node_head->set_rotation_edit_mode(Node3D::ROTATION_EDIT_MODE_BASIS);

        // Obrót gracza w osi Y (lewo/prawo)
        this->rotate_y(-rel.x * 0.005);

        // Obrót głowy/kamery w osi X (góra/dół)
        head_pitch = Math::clamp(head_pitch - rel.y * 0.005, -Math_PI/2, Math_PI/2);
        node_head->set_rotation(Vector3(head_pitch, 0, 0));

        print_line(node_head->get_rotation());
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

double Player::get_speed() const {
    return speed;
}

double Player::get_jump_velocity() const {
    return jump_velocity;
}

NodePath Player::get_head() const {
    return head;
}