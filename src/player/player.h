#ifndef PLAYER_H
#define PLAYER_H

#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <AnimatedSprite.hpp>
#include <CollisionShape2D.hpp>
#include <Input.hpp>

namespace godot
{
    class Player : public KinematicBody2D
    {
        GODOT_CLASS(Player, KinematicBody2D)

    private:
        AnimatedSprite *animation;
        CollisionShape2D *collision;
        Input *input;

        int gravity;
        int speed;

    public:
        static void _register_methods();

        Player();
        ~Player();

        void _init();
        void _ready();
        void _physics_process(float delta);
    };
}

#endif