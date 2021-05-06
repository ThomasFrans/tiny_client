#pragma once

#include "Tiny.h"
#include <string>
#include "Application.h"
#include "Window.h"
#include "Client.h"
#include <thread>
#include <cereal/archives/json.hpp>

namespace Tiny
{
    class Application;

    class Window;

    struct Command
    {
        std::string command;
        std::string argument;

        template <class Archive>
        void serialize(Archive &archive)
        {
            archive(command, argument); // serialize things by passing them to the archive
        }
    };

    class Client
    {
    private:
        int _socket;
        Tiny::Application *_app;
        const char *address;
        int port;
        void (*_callback_fun)(Tiny::Application*, json);
        std::thread *read_thread;

    public:
        Client(const char *address, int port);
        ~Client();
        void read();
        void write(json req);
        void set_callback(Tiny::Application* s, void (*fp)(Tiny::Application*, json));
        void start();
    };
} // namespace Tiny