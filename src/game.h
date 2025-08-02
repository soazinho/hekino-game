//
// Created by Hugues Soares on 2025-08-01.
//

#ifndef GAME_H
#define GAME_H

#include <godot_cpp/classes/sprite2d.hpp>

namespace godot {

    class Game : public Sprite2D {
        GDCLASS(Game, Sprite2D);

    private:
        double time_passed;
        double time_emit;
        double amplitude;
        double speed;

    protected:
        static void _bind_methods();

    public:
        Game();
        ~Game();

        void _process(double delta) override;

        void set_amplitude(const double p_amplitude);
        double get_amplitude() const;
        void set_speed(const double p_speed);
        double get_speed() const;
        void _on_sprite2d_position_changed(godot::Node* node, godot::Vector2 new_pos);
    };

}

#endif //GAME_H
