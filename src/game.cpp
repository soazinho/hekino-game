//
// Created by Hugues Soares on 2025-08-01.
//

#include "game.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/string.hpp>

using namespace godot;

void Game::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_amplitude"), &Game::get_amplitude);
    ClassDB::bind_method(D_METHOD("set_amplitude", "p_amplitude"), &Game::set_amplitude);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "amplitude"), "set_amplitude", "get_amplitude");

    ClassDB::bind_method(D_METHOD("get_speed"), &Game::get_speed);
    ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &Game::set_speed);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed", PROPERTY_HINT_RANGE, "0,20,0.01"), "set_speed", "get_speed");

    ADD_SIGNAL(MethodInfo("position_changed", PropertyInfo(Variant::OBJECT, "node"), PropertyInfo(Variant::VECTOR2, "new_pos")));

    ClassDB::bind_method(D_METHOD("_on_sprite2d_position_changed"), &Game::_on_sprite2d_position_changed);
}

Game::Game() {
    time_passed = 0.0;
    amplitude = 10.0;
    speed = 1.0;
}

Game::~Game() {
    // Add your cleanup here.
}

void Game::_process(double delta) {
    time_passed += speed * delta;

    Vector2 new_position = Vector2(
        amplitude + (amplitude * sin(time_passed * 2.0)),
        amplitude + (amplitude * cos(time_passed * 1.5))
    );

    set_position(new_position);

    time_emit += delta;
    if (time_emit > 1.0) {
        emit_signal("position_changed", this, new_position);

        time_emit = 0.0;
    }
}

void Game::set_amplitude(const double p_amplitude) {
    amplitude = p_amplitude;
}

double Game::get_amplitude() const {
    return amplitude;
}

void Game::set_speed(const double p_speed) {
    speed = p_speed;
}

double Game::get_speed() const {
    return speed;
}

void Game::_on_sprite2d_position_changed(godot::Node* node, godot::Vector2 new_pos) {
    if (node) {
        godot::String class_name = node->get_class();
        godot::String message = "The position of " + class_name + " is now " + godot::String(new_pos);
        UtilityFunctions::print(message);
    }
}