#include "ExampleTestLayer.hpp"


void ExampleLayer::onEvent(Meiosis::Event& e)
{
    ENGINE_INFO("{}", e);
}