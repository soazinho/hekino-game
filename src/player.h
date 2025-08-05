//
// Created by Hugues Soares on 2025-08-01.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/character_body3d.hpp>

class Player : public godot::CharacterBody3D 
{
    GDCLASS(Player, CharacterBody3D)

private:
    float _speed = 5.0f;
    float _fallAcceleration = 75;
    godot::Vector3 _targetVelocity = godot::Vector3();

protected:
    static void _bind_methods();

public:
    Player();
    ~Player();
    
    void _ready() override;
    void _physics_process(double delta) override;
};

#endif //PLAYER_H
