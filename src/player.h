//
// Created by Hugues Soares on 2025-08-01.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/input_event.hpp>

class Player : public godot::CharacterBody3D 
{
    GDCLASS(Player, CharacterBody3D)

private:
    godot::Camera3D* _camera3D;
    Node3D* _cameraPivot;

    
    float tilt_limit = godot::Math::deg_to_rad(75.0f);
    float _mouseSensitivity = 0.3f;
    
    float _fallAcceleration = 75.0f;
    float _speed = 5.0f;
    godot::Vector3 _targetVelocity = godot::Vector3();

protected:
    static void _bind_methods();

public:
    Player();
    ~Player();
    
    void _ready() override;
    void _physics_process(double delta) override;
    void _unhandled_input(const godot::Ref<godot::InputEvent> &event) override;

    float get_mouse_sensitivity() const;
    void set_mouse_sensitivity(float p_sensitivity);

    float get_tilt_limit() const;
    void set_tilt_limit(float p_limit);
};

#endif //PLAYER_H
