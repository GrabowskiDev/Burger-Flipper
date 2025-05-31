#ifndef BURGER_PART_H
#define BURGER_PART_H

#include <godot_cpp/classes/mesh_instance3d.hpp>

namespace godot {

    class BurgerPart : public MeshInstance3D {
        GDCLASS(BurgerPart, MeshInstance3D)

    private:
        double height;
        double price;
        String name;

    protected:
        static void _bind_methods();

    public:
        BurgerPart();
        ~BurgerPart();

        void _ready() override;
        void _process(double delta) override;

        double get_height();
        double get_price();
        String get_name();

        void set_height(double p_height);
        void set_price(double p_price);
        void set_name(String p_name);
    };

}

#endif //BURGER_PART_H
