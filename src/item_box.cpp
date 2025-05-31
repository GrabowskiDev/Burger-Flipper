#include "item_box.h"
#include "player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/area3d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

using namespace godot;

void ItemBox::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_item_scene"), &ItemBox::get_item_scene);
    ClassDB::bind_method(D_METHOD("set_item_scene", "p_scene"), &ItemBox::set_item_scene);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "item_scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_item_scene", "get_item_scene");

    ClassDB::bind_method(D_METHOD("_on_body_entered_item_box", "body"), &ItemBox::_on_body_entered_item_box);
}

ItemBox::ItemBox() {
//    time_passed = 0;
}

ItemBox::~ItemBox() {
    //cleanup
}

void ItemBox::_ready() {
    this->connect("body_entered", Callable(this, "_on_body_entered_item_box"));
    print_line("ready item box");
}

void ItemBox::_on_body_entered_item_box(Node *body) {
    print_line("colllll");
    if (Player *player = Object::cast_to<Player>(body)) {
        print_line("adding");
        player->add_to_hand(item_scene);
    }
}

void ItemBox::_process(double delta) {
//    this.body_entered
}


void ItemBox::set_item_scene(Ref <PackedScene> p_scene) {
    item_scene = p_scene;
}

Ref<PackedScene> ItemBox::get_item_scene() const {
    return item_scene;
}

