#include "HumanBridge.h"
#include <iostream>

void HappyHumanBridgeImpl::greet()
{
    std::cout << "Hello" << std::endl;
}

void AngryHumanBridgeImpl::greet()
{
    std::cout << "Fuck you!" << std::endl;
}


HumanBridge::HumanBridge(HumanInterface& imp)
    : impl { imp }
{}

HumanBridge::~HumanBridge()
{}

void HumanBridge::greet()
{
    impl.greet();
}
