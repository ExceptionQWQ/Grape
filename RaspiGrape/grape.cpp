#include "grape.h"
#include "robot.h"
#include "servo.h"



struct ArmInfo
{
    double len;
    double radian;
};


using ArmList = std::vector<ArmInfo>;

ArmList SolveArm3DH(double len1, double len2, double len3, double xPos, double yPos)
{
    if (fabs(xPos) < 0.001) xPos = 0.001;
    double len = std::sqrt(std::pow(xPos, 2) + std::pow(yPos, 2));
    if (len > len1 + len2) return ArmList{}; //无解
    double r4 = std::acos((std::pow(len1, 2) + std::pow(len2, 2) - std::pow(len, 2)) / (2 * len1 * len2));
    double r5 = std::atan(yPos / xPos);
    if (xPos < 0 && yPos > 0) {
        r5 += PI;
    }
    std::cout << r4 << std::endl;
    double r2 = r4 - PI;
    double r3 = std::asin(len2 * std::sin(r4) / len);
    double r1 = r3 + r5;
    return ArmList{{len1, r1}, {len2, r2}, {len3, -(r1 + r2)}};
}

// SERVO_TAG_L1 = 2, //0-3050, 90-2050
//     SERVO_TAG_L2 = 3, //0-2150, 90-3150
//     SERVO_TAG_L3 = 4, //0-1950, 90-2950
//     SERVO_TAG_ClawL = 5, //0-, 90-
//     SERVO_TAG_ClawR = 6, //0-, 90-


void SetL1Angle(double angle)
{
    std::cout << "l1: " << angle << std::endl;
    if (angle < 0 || angle > 150) return ;
    int pos = 3050;
    double add = 1000.0 / 90.0 * angle;
    pos += -add;
    SetServoPos(SERVO_TAG_L1, pos, 800);
}

void SetL2Angle(double angle)
{
    std::cout << "l2: " << angle << std::endl;
    if (angle < -150 || angle > 90) return ;
    int pos = 2150;
    double add = 1000.0 / 90.0 * angle;
    pos += add;
    SetServoPos(SERVO_TAG_L2, pos, 800);
}

void SetL3Angle(double angle)
{
     std::cout << "l3: " << angle << std::endl;
    if (angle < -90 || angle > 90) return ;
    int pos = 1950;
    double add = 1000.0 / 90.0 * angle;
    pos += add;
    SetServoPos(SERVO_TAG_L3, pos, 800);
}


int main()
{
    Robot_Init();
    Robot_Start();
    Servo_Init();
    Servo_Start();

    sleep(1);

    SetL1Angle(0);
    SetL2Angle(0);
    SetL3Angle(0);
    UpdateServoPos();

    sleep(3);

    double len1 = 165, len2 = 185, len3 = 55;
    double xPos = 340, yPos = 0;
    for (int i = 0; i < 80; ++i) {
        xPos -= 1;
        ArmList armList = SolveArm3DH(len1, len2, len3, xPos, yPos);
        if (armList.size() != 0) {
            SetL1Angle(180 / PI * armList[0].radian);
            SetL2Angle(180 / PI * armList[1].radian);
            SetL3Angle(180 / PI * armList[2].radian);
            UpdateServoPos();
        }
        usleep(10000);
    }
    for (int i = 0; i < 160; ++i) {
        yPos += 1;
        ArmList armList = SolveArm3DH(len1, len2, len3, xPos, yPos);
        if (armList.size() != 0) {
            SetL1Angle(180 / PI * armList[0].radian);
            SetL2Angle(180 / PI * armList[1].radian);
            SetL3Angle(180 / PI * armList[2].radian);
            UpdateServoPos();
        }
        usleep(10000);
    }
    for (int i = 0; i < 130; ++i) {
        xPos -= 1;
        ArmList armList = SolveArm3DH(len1, len2, len3, xPos, yPos);
        if (armList.size() != 0) {
            SetL1Angle(180 / PI * armList[0].radian);
            SetL2Angle(180 / PI * armList[1].radian);
            SetL3Angle(180 / PI * armList[2].radian);
            UpdateServoPos();
        }
        usleep(10000);
    }


    // SetServoPos(SERVO_TAG_YUNTAI, 1450, 300);
    // SetServoPos(SERVO_TAG_L1, 3050, 300);
    // SetServoPos(SERVO_TAG_L2, 2150, 300);
    // SetServoPos(SERVO_TAG_L3, 1950, 300);
    // UpdateServoPos();

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