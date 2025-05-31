#include "burger_part.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/variant/string.hpp>


using namespace godot;

void BurgerPart::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_height"), &BurgerPart::get_height);
    ClassDB::bind_method(D_METHOD("set_height", "p_height"), &BurgerPart::set_height);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "height"), "set_height", "get_height");

    ClassDB::bind_method(D_METHOD("get_price"), &BurgerPart::get_price);
    ClassDB::bind_method(D_METHOD("set_price", "p_price"), &BurgerPart::set_price);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "price"), "set_price", "get_price");

    ClassDB::bind_method(D_METHOD("get_name"), &BurgerPart::get_name);
    ClassDB::bind_method(D_METHOD("set_name", "p_name"), &BurgerPart::set_name);

    ADD_PROPERTY(PropertyInfo(Variant::STRING, "name"), "set_name", "get_name");
}

BurgerPart::BurgerPart() {}

BurgerPart::~BurgerPart() {}

void BurgerPart::_ready() {
    print_line("ready steady burgerpart go");
}

void BurgerPart::_process(double delta) {
    //
}


double BurgerPart::get_height(){
    return height;
}
double BurgerPart::get_price(){
    return price;
}
String BurgerPart::get_name() {
    return name;
}

void BurgerPart::set_height(double p_height){
    height = p_height;
}
void BurgerPart::set_price(double p_price){
    price = p_price;
}
void BurgerPart::set_name(String p_name) {
    name = p_name;
}
