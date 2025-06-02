#ifndef ITEM_BOX_H
#define ITEM_BOX_H

#include <godot_cpp/classes/area3d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include "player.h"


namespace godot {

    class ItemBox : public Area3D {
        GDCLASS(ItemBox, Area3D)

    private:
        Ref<PackedScene> item_scene;
        Player *player_in_box = nullptr;

    protected:
        static void _bind_methods();
        void _on_body_entered_item_box(Node *body);
        void _on_body_exited_item_box(Node *body);

    public:
        ItemBox();
        ~ItemBox();

        void _process(double delta) override;
        void _ready() override;

        void set_item_scene(Ref<PackedScene> p_scene);
        Ref<PackedScene> get_item_scene() const;
    };

}


#endif //ITEM_BOX_H
