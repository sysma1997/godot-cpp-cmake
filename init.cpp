#include "./src/gdexample.h"

/*
COMPILE GODOT CPP WITH CMAKE

https://aleksandrbazhin.github.io/godot/2021/06/25/GDNative-cpp-in-2k21.html
*/

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o)
{
    godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o)
{
    godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle)
{
    godot::Godot::nativescript_init(handle);

    godot::register_class<godot::GDExample>();
}