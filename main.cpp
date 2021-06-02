#include <iostream>

#include<xarm/wrapper/xarm_api.h>

int main() {
    std::cout << "Hello, World!" << std::endl;

    auto api = XArmAPI("192.168.1.200");
    api.core->set_mode(2);
    api.core->set_state(0);


    return 0;
}
