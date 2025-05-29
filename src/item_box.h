#ifndef ITEM_BOX_H
#define ITEM_BOX_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>


namespace godot {

    class ItemBox : public Node3D {
        GDCLASS(ItemBox, Node3D)

    private:
        Ref<PackedScene> item_scene;

    protected:
        static void _bind_methods();

    public:
        ItemBox();
        ~ItemBox();

        void _process(double delta) override;

        void set_item_scene(Ref<PackedScene> p_scene);
        Ref<PackedScene> get_item_scene() const;
    };

}


#endif //ITEM_BOX_H
