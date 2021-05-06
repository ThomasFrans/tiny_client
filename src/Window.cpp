#include "Window.h"
#include <iomanip>
#include <iostream>

bool Tiny::Window::send_message(Gdk::Event* event)
{
    spdlog::info("Key pressed");
    // Glib::RefPtr<Tiny::Application> app = get_application();
    // Tiny::Application *app_ptr = app.get();
    // _callback_fun(app_ptr, message);
    return true;
}

Tiny::Window::Window(Glib::RefPtr<Gtk::Builder> b)
{
    Gtk::Button *button;
    b->get_widget("button_send", button);
    button->signal_pressed().connect(sigc::mem_fun(*this, &Window::on_send_button_press));

    _builder = b;
    _builder->get_widget("box_layout", _layout);
    set_default_geometry(720, 480);
    add(*_layout);
    present();
}

Tiny::Window::~Window()
{
    delete _layout;
}

void Tiny::Window::display_message(std::string message)
{
    Gtk::TextView* view;
    _builder->get_widget("textview_messages", view);
    Glib::RefPtr<Gtk::TextBuffer> _textview_messages_buffer = view->get_buffer();
    std::string full_message("");
    full_message.append(message);
    full_message.append("\n");
    Glib::RefPtr<Gtk::TextMark> mark = _textview_messages_buffer->get_insert();
    _textview_messages_buffer->insert(mark->get_iter(), full_message.c_str());
}

void Tiny::Window::set_callback(Tiny::Application* app, void (*callback_fun)(Tiny::Application *app, std::string message))
{
    _app = app;
    _callback_fun = callback_fun;
}

bool Tiny::Window::on_key_press_event(GdkEventKey *event)
{
    Gtk::Entry* entry;
    _builder->get_widget("entry_message", entry);
    if (event->keyval == GDK_KEY_Return)
    {
        Glib::ustring text = entry->get_text();
        entry->set_text("");
        _callback_fun(_app, std::string(text));
        return true;    // Event handled
    }
    return Gtk::ApplicationWindow::on_key_press_event(event);
}

void Tiny::Window::on_send_button_press()
{
        Gtk::Entry* entry;
        _builder->get_widget("entry_message", entry);
        Glib::ustring text = entry->get_text();
        entry->set_text("");
        _callback_fun(_app, std::string(text));
}