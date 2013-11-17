//
// Created by Alabay on 17.11.13.
//



#include "Arduino.h"

#ifndef __bma180i_H_
#define __bma180i_H_


class bma180i {

#define BMA180_ADDRESS 0x40
#define BMA180_CHIP_ID 0x03

    //bandwidth / filter mode constants
#define BMA180_BANDWIDTH_10HZ     0x00
#define BMA180_BANDWIDTH_20HZ     0x01
#define BMA180_BANDWIDTH_40HZ     0x02
#define BMA180_BANDWIDTH_75HZ     0x03
#define BMA180_BANDWIDTH_150HZ    0x04
#define BMA180_BANDWIDTH_300HZ    0x05
#define BMA180_BANDWIDTH_600HZ    0x06
#define BMA180_BANDWIDTH_1200HZ   0x07
#define BMA180_BANDWIDTH_HIGHPASS 0x08 // high-pass: 1 Hz
#define BMA180_BANDWIDTH_BANDPASS 0x09 // band-pass: 0.2 Hz ... 300 Hz

    //acceleration sensitivity range constants
#define BMA180_RANGE_1G     0x00
#define BMA180_RANGE_1DOT5G 0x01
#define BMA180_RANGE_2G     0x02
#define BMA180_RANGE_3G     0x03
#define BMA180_RANGE_4G     0x04
#define BMA180_RANGE_8G     0x05
#define BMA180_RANGE_16G    0x06

    //pick your mode
#define BMA180_MODE_LOW_NOISE 0x00
#define BMA180_MODE_LOW_POWER 0x03

#define BMA180_CMD_CHIP_ID          0x00
#define BMA180_CMD_VERSION          0x01
#define BMA180_CMD_ACC_X_LSB        0x02
#define BMA180_CMD_ACC_X_MSB        0x03
#define BMA180_CMD_ACC_Y_LSB        0x04
#define BMA180_CMD_ACC_Y_MSB        0x05
#define BMA180_CMD_ACC_Z_LSB        0x06
#define BMA180_CMD_ACC_Z_MSB        0x07
#define BMA180_CMD_TEMP             0x08
#define BMA180_CMD_STATUS_REG1      0x09
#define BMA180_CMD_STATUS_REG2      0x0A
#define BMA180_CMD_STATUS_REG3      0x0B
#define BMA180_CMD_STATUS_REG4      0x0C
#define BMA180_CMD_CTRL_REG0        0x0D
#define BMA180_CMD_CTRL_REG1        0x0E
#define BMA180_CMD_CTRL_REG2        0x0F
#define BMA180_CMD_RESET            0x10
#define BMA180_CMD_BW_TCS           0x20
#define BMA180_CMD_CTRL_REG3        0x21
    //#define BMA180_CMD_CTRL_REG3        0x22

    byte temp;
    byte address;
public:
    bma180i(): address(BMA180_ADDRESS) {}

    byte BMA180_WriteByte(byte i2c_address, byte address, byte data);
    byte BMA180_ReadByte(byte i2c_address, byte address);
    byte BMA180_ReadId(byte address);
    void BMA180_SetBandwidth(byte address, byte bandwidth);
    void BMA180_SetRange(byte address, byte range);
    byte BMA180_ReadTemperature();

    void BMA180_Init();
};


#endif //__bma180i_H_
