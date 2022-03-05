#pragma once
#include "Core/Core.hpp"
#include "Core/Application.hpp"
#include "Core/Log.hpp"

extern Meiosis::Application* Meiosis::CreateApplication();

int main(int argc, char** argv)
{
    Meiosis::Logger::init();
    auto* application = Meiosis::CreateApplication();
    application->run();
    delete application;
    return 0;
}