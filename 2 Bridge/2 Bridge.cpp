#include "Human.h"
#include "HumanBridge.h"


int main()
{

    HumanBridge p{AngryHumanBridgeImpl()};
    p.greet();

    return 0;
}

