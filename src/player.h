#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot {


class Player : public CharacterBody3D {
    GDCLASS(Player, CharacterBody3D)

private:
    double speed;
    double jump_velocity;
    NodePath head;
    NodePath hand;
    Node *current_object;
    Vector3 get_movement_vector();
    double head_pitch = 0.0;

//    Ref<Object> bottom_bun;


protected:
    static void _bind_methods();

public:
    Player();
    ~Player();

    void set_head(NodePath p_head);
    NodePath get_head() const;

    void set_hand(NodePath p_hand);
    NodePath get_hand() const;

    void set_speed(const double p_speed);
    double get_speed() const;

    void set_jump_velocity(const double p_jump_velocity);
    double get_jump_velocity() const;

    void _process(double delta) override;
    void _ready() override;
    void _unhandled_input(const godot::Ref<godot::InputEvent> &event) override;


//    void set_bottom_bun(Ref<Object> p_bottom_bun);
//    Ref<Object> get_bottom_bun() const;

};

}

#endif //PLAYER_H
