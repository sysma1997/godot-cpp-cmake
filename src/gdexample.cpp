#include "gdexample.h"

using namespace godot;

void GDExample::_register_methods()
{
    register_method("_process", &GDExample::_process);
    register_method("_ready", &GDExample::_ready);

    register_property<GDExample, float>("amplitude", &GDExample::amplitude, 10.0f);
    register_property<GDExample, float>("speed", &GDExample::set_speed, &GDExample::get_speed, 1.0f);

    register_signal<GDExample>((char *)"position_changed",
                               "node", GODOT_VARIANT_TYPE_OBJECT,
                               "new_pos", GODOT_VARIANT_TYPE_VECTOR2);
}

GDExample::GDExample() {}
GDExample::~GDExample() {}

void GDExample::_init()
{
    time_passed = 0.0f;
    amplitude = 10.0f;
}
void GDExample::_ready()
{
    _input = Input::get_singleton();
}
void GDExample::_process(float delta)
{
    time_passed += speed * delta;

    Vector2 new_position(
        amplitude + (amplitude * sin(time_passed * 2.0f)),
        amplitude + (amplitude * cos(time_passed * 1.5f)));

    set_position(new_position);

    time_emit += delta;
    if (time_emit > 1.0f)
    {
        emit_signal("position_changed", this, new_position);

        time_emit = 0.0f;
    }

    if (_input->is_action_just_pressed("ui_accept"))
    {
        Godot::print("Action");
    }
}

void GDExample::set_speed(float speed)
{
    this->speed = speed;
}
float GDExample::get_speed()
{
    return speed;
}
