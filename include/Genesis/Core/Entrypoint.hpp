#pragma once
#include "Core/Core.hpp"
#include "Core/Application.hpp"
#include "Core/Log/Log.hpp"

extern Genesis::Application* Genesis::CreateApplication();

int main(int argc, char** argv)
{
    Genesis::Logger::init();
    auto* application = Genesis::CreateApplication();
    application->run();
    delete application;
    return 0;
}