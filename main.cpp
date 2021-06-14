#include <iostream>

#include<xarm/wrapper/xarm_api.h>
#include <fstream>

using namespace std;

class SomaticXArm {
public:
    SomaticXArm() : api("", true) {}

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
        } else if (cmd == "initial") {
            float move1[7] = {-0.00015161, 0.261777,-3.14137,2.618,-1.25037e-05,1.30898,1.93239e-05};
            //api.set_servo_angle_j(move1, 1, 1, 0);
        } else if (cmd == "traj") {
            vector<float[7]> traj;
            ifstream myfile("/home/alex/development/bcr_ws/src/xArm-CPLUS-SDK/traj/test.traj");
            for (int i = 0; i < 54; i++) {
                float p[7] = {0};
                myfile >> p[0] >> p[1] >> p[2] >> p[3] >> p[4] >> p[5] >> p[6];
                api.set_servo_angle_j(p, 1, 1, 0);
                usleep(1000/20);
            }

        } else if (cmd == "pose") {
            float angles[7];
            api.get_servo_angle(angles);
            cout << angles[0] << '\n'
                << angles[1] << '\n'
                << angles[2] << '\n'
                << angles[3] << '\n'
                << angles[4] << '\n'
                << angles[5] << '\n'
                << angles[6] << '\n';
        } else if (cmd == "exit") {
            return false;
        } else {
            cout << "Failed to read command!\n";
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
