#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/character_body3d.hpp>

namespace godot {


class Player : public CharacterBody3D {
    GDCLASS(Player, CharacterBody3D)

private:
    double speed;
    double jump_velocity;

protected:
    static void _bind_methods();

public:
    Player();
    ~Player();

    void set_speed(const double p_speed);
    double get_speed() const;
    void set_jump_velocity(const double p_jump_velocity);
    double get_jump_velocity() const;

    void _process(double delta) override;
};

}

#endif //PLAYER_H
