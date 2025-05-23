#include "player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/character_body3d.hpp>


using namespace godot;

void Player::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_speed"), &Player::get_speed);
    ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &Player::set_speed);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");

    ClassDB::bind_method(D_METHOD("get_jump_velocity"), &Player::get_jump_velocity);
    ClassDB::bind_method(D_METHOD("set_jump_velocity", "p_jump_velocity"), &Player::set_jump_velocity);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "jump_velocity"), "set_jump_velocity", "get_jump_velocity");
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
//        print_line("ha ha");
        set_velocity(new_velocity);
    }

    move_and_slide();
}

void Player::set_speed(const double p_speed) {
    speed = p_speed;
}

void Player::set_jump_velocity(const double p_jump_velocity) {
    jump_velocity = p_jump_velocity;
}

double Player::get_speed() const {
    return speed;
}

double Player::get_jump_velocity() const {
    return jump_velocity;
}