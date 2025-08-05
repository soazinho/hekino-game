//
// Created by Hugues Soares on 2025-08-01.
//

#include "player.h"

#include <godot_cpp/classes/input.hpp>

using namespace godot;

void Player::_bind_methods() 
{
}

Player::Player() 
{
}

Player::~Player() 
{
}

void Player::_ready() 
{
}

// Update the node at fixed time intervals.
void Player::_physics_process(double delta) 
{
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
