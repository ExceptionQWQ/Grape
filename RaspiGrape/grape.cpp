#include "grape.h"
#include "robot.h"


int main()
{
    Robot_Init();
    Robot_Start();

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