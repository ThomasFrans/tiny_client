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

void Tiny::Application::message_callback(Tiny::Application* app, std::string message)
{

    spdlog::info("here");
    app->window->display_message(message);
}

void Tiny::Application::window_callback(Tiny::Application* app, std::string message)
{
    spdlog::info("Message received");
    app->client->write(message);
    app->window->display_message(message);
}