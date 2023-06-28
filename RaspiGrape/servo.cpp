#include "servo.h"

pthread_t servoThreadHandle;
int servoSerial;
char servoRecvBuff[1024];
int servoRecvOffset;


volatile struct ServoInfo servoInfo;


void Servo_Init()
{

}

uint8_t CheckSum(uint8_t startNum, uint8_t endNum, uint8_t *inData)
{
    uint8_t count;
    uint16_t checkSum = 0;
    for (count = startNum; count < endNum + 1; ++count)
    {
        checkSum += inData[count];
    }
    return ((~checkSum) & 0xFF);
}

uint16_t SwapInt16(uint16_t value)
{
    uint16_t ret = ((value >> 8) & 0xff) | ((value << 8) & 0xff00);
    return ret;
}

bool HandleServoPackage(uint8_t* data, int packageLen)
{
    if (packageLen != 8) return false;
    if (data[7] != CheckSum(2, 6, data)) return false;

    SERVO_TAG tag = (SERVO_TAG)data[2];
    uint8_t dataLen = data[3];
    uint16_t pos = (data[6] << 8) | data[5];

    // std::cout << tag << " " << pos << std::endl;

    switch (tag) {
        case SERVO_TAG_YUNTAI:
            servoInfo.yuntaiPos = pos;
            break;
        case SERVO_TAG_L1:
            servoInfo.l1Pos = pos;
            break;
        case SERVO_TAG_L2:
            servoInfo.l2Pos = pos;
            break;
        case SERVO_TAG_L3:
            servoInfo.l3Pos = pos;
            break;
        case SERVO_TAG_ClawL:
            servoInfo.clawLPos = SwapInt16(pos);
            break;
        case SERVO_TAG_ClawR:
            servoInfo.clawRPos = SwapInt16(pos);
            break;
    }

    return true;
}

//检查舵机数据包
void CheckServoTransmitPackage(uint8_t* data, int& offset)
{
    if (offset < 4) return ;
    if (data[0] != 0xff || data[1] != 0xff) { //不是帧头，则左移一字节
        for (int i = 0; i < offset - 1; ++i) {
            data[i] = data[i + 1];
        }
        offset -= 1;
        return ;
    }
    //是帧头
    int dataLen = data[3];
    if (offset >= dataLen + 4) {
        HandleServoPackage(data, offset);
        offset = 0;
    }
}

void UartTransmit(uint8_t* data, int len)
{
    for (int i = 0; i < len; ++i) {
        serialPutchar(servoSerial, data[i]);
    }
}

void SetServoPos(enum SERVO_TAG servoTag, uint16_t pos, uint16_t speed)
{

    if (servoTag == SERVO_TAG_ClawL || servoTag == SERVO_TAG_ClawR) {
        pos = SwapInt16(pos);
        speed = SwapInt16(speed);
    }
    uint8_t writeTempCmd[] = {0xFF, 0xFF, 0x00, 0x09, 0x04, 0x2A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    writeTempCmd[2] = servoTag;
    writeTempCmd[6] = pos & 0xff;
    writeTempCmd[7] = (pos >> 8) & 0xff;
    writeTempCmd[10] = speed & 0xff;
    writeTempCmd[11] = (speed >> 8) & 0xff;
    writeTempCmd[12] = CheckSum(2, 11, writeTempCmd);

    UartTransmit(writeTempCmd, 13);
}

void GetServoPos(enum SERVO_TAG servoTag)
{
    uint8_t cmd[] = {0xFF, 0xFF, 0x00, 0x04, 0x02, 0x38, 0x02, 0x00};
    cmd[2] = servoTag;
    cmd[7] = CheckSum(2, 6, cmd);
    uint8_t rx[8] = {0};
    UartTransmit(cmd, 8);
    usleep(10000);
    return ;
}

void UpdateServoPos()
{
    
}

void* ServoThread(void*)
{
    servoSerial = serialOpen(SERVO_DEV_PATH, SERVO_BAUD);
    if (servoSerial < 0) {
        std::cout << "cannot open servo dev!" << std::endl;
        exit(0);
        return nullptr;
    }
    while (true) {
        if (servoRecvOffset >= 1024) servoRecvOffset = 0;
        servoRecvBuff[servoRecvOffset++] = serialGetchar(servoSerial);
        CheckServoTransmitPackage((uint8_t*)servoRecvBuff, servoRecvOffset);
    }
    return nullptr;
}

void Servo_Start()
{
    pthread_create(&servoThreadHandle, nullptr, ServoThread, nullptr);
}

