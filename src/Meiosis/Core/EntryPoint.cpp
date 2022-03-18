#include "Core/Entrypoint.hpp"

int main(int argc, char** argv)
{
    Meiosis::Logger::init();
    auto* application = Meiosis::CreateApplication();
    application->run();
    delete application;
    return 0;
}