#pragma once
#include "Core/Core.hpp"
#include "Core/Application.hpp"


extern Genesis::Application* Genesis::CreateApplication();

int main(int argc, char** argv)
{
    auto* application = Genesis::CreateApplication();
    application->run();
    delete application;
    return 0;
}