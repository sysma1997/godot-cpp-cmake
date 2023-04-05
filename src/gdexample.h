#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <Input.hpp>

namespace godot
{
    class GDExample : public Sprite
    {
        GODOT_CLASS(GDExample, Sprite)

    private:
        float time_passed;
        float time_emit;
        float amplitude;
        float speed;

        Input *_input;

    public:
        static void _register_methods();

        GDExample();
        ~GDExample();

        void _init();
        void _ready();
        void _process(float delta);

        void set_speed(float speed);
        float get_speed();
    };
}

#endif