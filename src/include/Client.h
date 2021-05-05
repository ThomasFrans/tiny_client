#pragma once

#include "Tiny.h"
#include <string>
#include "Application.h"
#include "Window.h"
#include "Client.h"
#include <thread>

namespace Tiny
{
    class Application;

    class Window;

    class Client
    {
    private:
        int _socket;
        Tiny::Application *_app;
        const char *address;
        int port;
        void (*_callback_fun)(Tiny::Application*, std::string);
        std::thread *read_thread;

    public:
        Client(const char *address, int port);
        ~Client();
        void read();
        void write(std::string message);
        void set_callback(Tiny::Application* s, void (*fp)(Tiny::Application*, std::string));
        void start();
    };
} // namespace Tiny