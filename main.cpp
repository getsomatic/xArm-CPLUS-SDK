#include <iostream>

#include<xarm/wrapper/xarm_api.h>
using namespace std;
int main() {
    auto api = XArmAPI("192.168.1.200");
    api.core->set_mode(2);
    api.core->set_state(0);

    while (api.is_connected()) {
        int cmd;
        cout << "Cin command\n";
        cin >> cmd;
        api.core->set_mode(cmd);
        api.core->set_state(0);
    }
    cout << "Disconnected\n";

    return 0;
}
