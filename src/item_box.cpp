#include "item_box.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

using namespace godot;

void ItemBox::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_item_scene"), &ItemBox::get_item_scene);
    ClassDB::bind_method(D_METHOD("set_item_scene", "p_scene"), &ItemBox::set_item_scene);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "exported_scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_item_scene", "get_item_scene");
}

ItemBox::ItemBox() {
//    time_passed = 0;
}

ItemBox::~ItemBox() {
    //cleanup
}

void ItemBox::_process(double delta) {
//    time_passed += delta;
//
//    Vector2 new_position = Vector2(10.0 + (10.0 * sin(time_passed * 2.0)), 10.0 + (10.0 * cos(time_passed * 1.5)));
//
//    set_position(new_position);
}

void ItemBox::set_item_scene(Ref <PackedScene> p_scene) {
    item_scene = p_scene;
}

Ref<PackedScene> ItemBox::get_item_scene() const {
    return item_scene;
}

