#include <iostream>

#include<xarm/wrapper/xarm_api.h>
using namespace std;

class SomaticXArm {
public:
    SomaticXArm() : api() {}

    bool Execute(const string &cmd) {
        if (cmd == "connect") {
            api.connect("192.168.1.200");
        } else if (cmd == "enable") {
            api.motion_enable(true);
        } else if (cmd == "servo") {
            api.core->set_mode(XARM_MODE::SERVO);
            api.core->set_state(0);
        } else if (cmd == "manual") {
            api.core->set_mode(XARM_MODE::TEACH_JOINT);
            api.core->set_state(0);
        } else if (cmd == "start") {
            api.core->set_state(0);
        } else if (cmd == "disconnect") {
            api.disconnect();
        } else if (cmd == "exit") {
            return false;
        }
        return true;
    }

private:
    XArmAPI api;
};

int main() {
    auto xarm = SomaticXArm();
    string c;
    while (true) {
        cout << "Input command:";
        cin >> c;
        if (!xarm.Execute(c)) break;
    }
    cout << "Disconnected\n";
    return 0;
}
