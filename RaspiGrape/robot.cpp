#include "robot.h"



int robotSerial;
pthread_t robotThreadHandle;
char robotRecvBuff[1024] = {0};
int robotRecvOffset = 0;


volatile bool motionOK = false;


bool startsWith(const char* str1, const char* str2)
{
    int len1 = strlen(str1), len2 = strlen(str2);
    if (len1 < len2) return false;
    for (int i = 0; i < len2; ++i) {
        if (str1[i] != str2[i]) return false;
    }
    return true;
}

void Handle_Robot_Message(char* message, int len)
{
    message[len] = 0;

    // std::cout << message << std::endl;

    if (startsWith(message, "[Motion]OK")) {
        motionOK = true;
    }

}

void Robot_Init()
{
    
}


void* RobotThread(void*)
{
    robotSerial = serialOpen(ROBOT_DEV_PATH, ROBOT_BAUD);
    if ( robotSerial < 0) {
        std::cout << "cannot open robot dev!" << std::endl;
        exit(0);
        return nullptr;
    }
    while (true) {
        if (robotRecvOffset >= 1024) robotRecvOffset = 0;
        robotRecvBuff[robotRecvOffset] = serialGetchar(robotSerial);
        if (robotRecvBuff[robotRecvOffset] == '\n') {
            Handle_Robot_Message(robotRecvBuff, robotRecvOffset);
            robotRecvOffset = 0;
        } else {
            ++robotRecvOffset;
        }
    }
    return nullptr;
}

void Robot_Start()
{
    pthread_create(&robotThreadHandle, nullptr, RobotThread, nullptr);
}


void Robot_Test()
{
    serialPuts(robotSerial, "Hello WOrld\n");
}

void Robot_Move(double speed, double xDis, double yDis)
{
    motionOK = false;
    char command[128] = {};
    snprintf(command, 128, "[Move]speed=%.2f xDis=%.2f yDis=%.2f\n", speed, xDis, yDis);
    std::cout << command << std::endl;
    serialPuts(robotSerial, command);
    while (!motionOK) { }
}

void Robot_MoveX(double speed)
{
    char command[128] = {};
    snprintf(command, 128, "[MoveX]speed=%.2f\n", speed);
    std::cout << command << std::endl;
    serialPuts(robotSerial, command);
}

void Robot_MoveY(double speed)
{
    char command[128] = {};
    snprintf(command, 128, "[MoveY]speed=%.2f\n", speed);
    std::cout << command << std::endl;
    serialPuts(robotSerial, command);
}

void Robot_MoveZ(double speed)
{
    char command[128] = {};
    snprintf(command, 128, "[MoveZ]speed=%.2f\n", speed);
    std::cout << command << std::endl;
    serialPuts(robotSerial, command);
}

void Robot_Stop()
{
    serialPuts(robotSerial, "[Stop]\n");
}