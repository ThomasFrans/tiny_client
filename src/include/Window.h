#pragma once

#include "Tiny.h"
#include "Application.h"
#include <string>

namespace Tiny
{
    class Application;

    class Window : public Gtk::ApplicationWindow
    {
    private:
        Tiny::Application *_app;
        Glib::RefPtr<Gtk::Builder> _builder;
        Gtk::Widget *_layout;
        void (*_callback_fun) (Tiny::Application* app, std::string message);
        bool on_key_press_event(GdkEventKey *event) override;
    public:
        bool send_message(Gdk::Event *event);
        Window(Glib::RefPtr<Gtk::Builder> b);
        ~Window();
        void display_message(std::string message);
        void set_callback(Tiny::Application* app, void (*callback_fun) (Tiny::Application* app, std::string message));
    };

} // namespace Tiny
