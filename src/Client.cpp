#include "Client.h"

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <thread>
#include <string>
#include <iostream>

Tiny::Client::Client(const char* address, int port)
{
    struct sockaddr_in serv_addr;
    const char *hello = "Hello from client";
    if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "192.168.68.139", &serv_addr.sin_addr)<=0) 
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
   
    if (connect(_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
}

Tiny::Client::~Client()
{
    read_thread->join();
    delete read_thread;
}

void Tiny::Client::read()
{
    int valread;
    while (true)
    {
        char buffer[1024] = {0};
        valread = recv( _socket , buffer, 1024, 0);
        if (valread == 0) {exit(EXIT_SUCCESS);};
        _callback_fun(_app, std::string(buffer));
        // spdlog::info(buffer);
    }
}

void Tiny::Client::start()
{
    read_thread = new std::thread(&Client::read, *this);
}

void Tiny::Client::write(std::string message)
{
    const char* message_m = message.c_str();
    send(_socket, message_m, strlen(message_m), 0);
}

void Tiny::Client::set_callback(Tiny::Application* s, void (*fp)(Tiny::Application*, std::string))
{
    _app = s;
    _callback_fun = fp;
}