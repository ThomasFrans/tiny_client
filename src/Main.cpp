#include "spdlog/spdlog.h"

#include "Client.h"
#include "Application.h"

int main(int argc, char* argv[])
{
#ifndef DEBUG
    spdlog::set_level(spdlog::level::off);
#endif
    Tiny::Application app;
    return 0;
}