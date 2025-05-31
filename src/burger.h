#ifndef BURGER_H
#define BURGER_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/variant/node_path.hpp>
#include <godot_cpp/variant/array.hpp>
#include "player.h"
#include "burger_part.h"
//#include <vector>

namespace godot {

    class Burger : public Node3D {
        GDCLASS(Burger, Node3D)

    private:
        NodePath interact_area;
        Array burger_elements;
        double curr_height;
        bool is_empty;
        bool is_done;


    protected:
        static void _bind_methods();
        void _on_body_entered_burger(Node *body);

    public:
        Burger();
        ~Burger();

        void add_to_burger(Player *player, BurgerPart *element);

        void _ready() override;
        void _process(double delta) override;

        NodePath get_interact_area();
        void set_interact_area(NodePath p_interact_area);
    };

}

#endif //BURGER_H
