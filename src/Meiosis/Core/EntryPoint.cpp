#include "Core/Entrypoint.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
    Meiosis::Logger::init();
    auto* application = Meiosis::CreateApplication();
    application->run();
    delete application;
    return 0;
}