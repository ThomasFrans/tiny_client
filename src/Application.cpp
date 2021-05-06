#include "Application.h"
#include "Window.h"
#include <thread>
#include <iostream>

Tiny::Application::Application(/* args */)
{

    Glib::RefPtr<Gtk::Builder> b = Gtk::Builder::create_from_file("/home/thomas/Documents/Programming/tiny_chat/tiny_server/res/Window.glade");
    window = new Tiny::Window(b);
    client = new Client("localhost", 18550);
    client->set_callback(this, &Application::message_callback);
    client->start();
    this->window->set_callback(this, &Application::window_callback);
    run(*window);
    exit(EXIT_SUCCESS);
}

Tiny::Application::~Application()
{
    delete window;
    delete client;
}

void Tiny::Application::message_callback(Tiny::Application *app, json req)
{
    if (req["command"].get<std::string>() == std::string("members"))
    {
        spdlog::info("Got members");
        std::vector<std::string> members = req["body"].get<std::vector<std::string>>();
        std::vector<std::string>::iterator it;
        for (it = members.begin(); it < members.end(); it++)
        {
            app->window->display_message(*it);
        }
    }
    else
    {
        app->window->display_message(req.dump()); // TODO fix the bug that results from changing textbuffer from different thread with this: https://developer.gnome.org/gtkmm-tutorial/stable/sec-multithread-example.html.en
    }
}

void Tiny::Application::window_callback(Tiny::Application *app, std::string message)
{
    json req;
    std::size_t find;
    req["name"] = message;
    find = message.find(" ");
    if (message.find("!connect") != std::string::npos)
    {
        req["command"] = "connect";
    }
    else if (message.find("!disconnect") != std::string::npos)
    {
        req["command"] = "disconnect";
    }
    else if (message.find("!list") != std::string::npos)
    {
        req["command"] = "list";
    }

    app->client->write(req);
    app->window->display_message(message); // TODO fix the bug that results from changing textbuffer from different thread with this: https://developer.gnome.org/gtkmm-tutorial/stable/sec-multithread-example.html.en
}