//
// Created by Hugues Soares on 2025-08-01.
//

#include "player.h"

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>

using namespace godot;

void Player::_bind_methods() 
{
    // Bind exported properties.
    ClassDB::bind_method(D_METHOD("set_mouse_sensitivity", "sensitivity"), &Player::set_mouse_sensitivity);
    ClassDB::bind_method(D_METHOD("get_mouse_sensitivity"), &Player::get_mouse_sensitivity);
    ClassDB::bind_method(D_METHOD("set_tilt_limit", "limit"), &Player::set_tilt_limit);
    ClassDB::bind_method(D_METHOD("get_tilt_limit"), &Player::get_tilt_limit);

    // Add properties with export ranges.
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "mouse_sensitivity", PROPERTY_HINT_RANGE, "0.0,1.0"), "set_mouse_sensitivity", "get_mouse_sensitivity");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "tilt_limit"), "set_tilt_limit", "get_tilt_limit");
}

Player::Player() 
{
}

Player::~Player() 
{
}

void Player::_ready() 
{
    _camera3D = get_node<godot::Camera3D>("CameraPivot/SpringArm3D/Camera3D");
    _cameraPivot = get_node<Node3D>("CameraPivot");
}

void Player::_unhandled_input(const Ref<InputEvent> &event) {    
    Ref<InputEventMouseMotion> motion_event = event;
    if (motion_event.is_valid()) {
        // Apply horizontal rotation.
        Vector3 rotation_degrees = get_rotation_degrees();
        rotation_degrees.y -= motion_event->get_relative().x * _mouseSensitivity;
        set_rotation_degrees(rotation_degrees);
        
        // Apply vertical rotation.
        rotation_degrees = _cameraPivot->get_rotation_degrees();
        rotation_degrees.x -= motion_event->get_relative().y * _mouseSensitivity;
        rotation_degrees.x = Math::clamp(rotation_degrees.x, -tilt_limit, tilt_limit);
        _cameraPivot->set_rotation_degrees(rotation_degrees);
    }
}

// Update the node at fixed time intervals.
void Player::_physics_process(double delta) 
{
    UtilityFunctions::print("foo!");

    Vector3 direction = Vector3();

    if (Input::get_singleton()->is_action_pressed("move_right")) 
    {
        direction.x += 1.0f;
    }
    if (Input::get_singleton()->is_action_pressed("move_left")) 
    {
        direction.x -= 1.0f;
    }
    if (Input::get_singleton()->is_action_pressed("move_down")) 
    {
        direction.z += 1.0f;
    }
    if (Input::get_singleton()->is_action_pressed("move_up")) 
    {
        direction.z -= 1.0f;
    }

    // Make sure we do not go faster if we move diagonally.
    if (direction != Vector3()) 
    {
        direction = direction.normalized();
        get_node<Node3D>("Pivot")->set_basis(Basis::looking_at(direction));
    }

    // Ground velocity.
    _targetVelocity.x = direction.x * _speed;
    _targetVelocity.z = direction.z * _speed;

    // Vertical velocity.
    if (!is_on_floor())
    {
        _targetVelocity.y -= _fallAcceleration * delta;
    }

    // Moving the character.
    set_velocity(_targetVelocity);
    move_and_slide();
}

void Player::set_mouse_sensitivity(float p_sensitivity) {
    _mouseSensitivity = p_sensitivity;
}

float Player::get_mouse_sensitivity() const {
    return _mouseSensitivity;
}

void Player::set_tilt_limit(float p_limit) {
    tilt_limit = p_limit;
}

float Player::get_tilt_limit() const {
    return tilt_limit;
}
