#include "./player.h"

using namespace godot;

void Player::_register_methods()
{
    register_method("_ready", &Player::_ready);
    register_method("_physics_process", &Player::_physics_process);

    register_property<Player, int>("gravity", &Player::gravity, 60);
    register_property<Player, int>("speed", &Player::speed, 60);
}
Player::Player() {}
Player::~Player() {}

void Player::_init()
{
    gravity = 60;
    speed = 60;
}
void Player::_ready()
{
    animation = get_node<AnimatedSprite>("Animation");
    collision = get_node<CollisionShape2D>("Collision");

    input = Input::get_singleton();
}
void Player::_physics_process(float delta)
{
    Vector2 velocity = Vector2::ZERO;

    if (is_on_floor())
        velocity.y += gravity * delta;

    velocity.x = input->get_action_strength("ui_right") - input->get_action_strength("ui_left");

    move_and_collide(velocity.normalized());
}