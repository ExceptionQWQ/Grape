#include "grape.h"
#include "robot.h"
#include "servo.h"

int main()
{
    Robot_Init();
    Robot_Start();
    Servo_Init();
    Servo_Start();

    sleep(1);

    while (true) {
        sleep(1);
        GetServoPos(SERVO_TAG_YUNTAI);
        GetServoPos(SERVO_TAG_L1);
        GetServoPos(SERVO_TAG_L2);
        GetServoPos(SERVO_TAG_L3);
        GetServoPos(SERVO_TAG_ClawL);
        GetServoPos(SERVO_TAG_ClawR);

        std::cout << "yuntai: " << servoInfo.yuntaiPos << std::endl;
        std::cout << "l1: " << servoInfo.l1Pos << std::endl;
        std::cout << "l2: " << servoInfo.l2Pos << std::endl;
        std::cout << "l3: " << servoInfo.l3Pos << std::endl;
        std::cout << "clawL: " << servoInfo.clawLPos << std::endl;
        std::cout << "clawR: " << servoInfo.clawRPos << std::endl;
        std::cout << "#############################################" << std::endl;
    }
    

    while (true) {
        char ch;
        std::cin >> ch;
        double speed;
        switch (ch) {
            case 'x':
                std::cin >> speed;
                Robot_MoveX(speed);
            break;
            case 'y':
                std::cin >> speed;
                Robot_MoveY(speed);
            break;
            case 'z':
                std::cin >> speed;
                Robot_MoveZ(speed);
            break;
            case 's':
                Robot_Stop();
            break;


            default:

            break;
        }
    }

    return 0;
}