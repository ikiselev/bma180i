#include <Wire.h>
#include "bma180i.h"



void bma180i::BMA180_Init() {
    int id = BMA180_ReadId(address);

    if (id == BMA180_CHIP_ID) {
        //BMA180 Chip Detect Pass

        // Connect to the ctrl_reg1 register and set the ee_w bit to enable writing.
        if (BMA180_WriteByte(address, BMA180_CMD_CTRL_REG0, 0x10) == 0)
        {
            //debug("BMA180 Write Init Pass");
        }
        else
        {
            //debug("BMA180 Write Init Fail");
        }
    }
    else {
        //debug((char *)id, " <- BMA180 Chip Detect Fail");
    }
}

byte bma180i::BMA180_ReadId(byte address) {
    //get the contents of the chip id register.
    return BMA180_ReadByte(address, BMA180_CMD_CHIP_ID);
}

byte bma180i::BMA180_ReadTemperature() {
    return BMA180_ReadByte(address, BMA180_CMD_TEMP);
}

void bma180i::BMA180_SetRange(byte range) {
    //set g-divider to properly get measures in G
    g_divider = getDividerByRange(range);

    // Connect to the offset_lsb1 register and set the range
    byte last_value = BMA180_ReadByte(address, BMA180_CMD_OFFSET_LSB1);

    byte offset_lsb1 = ( last_value & 0xF1 ) | range << 1;
    BMA180_WriteByte(address, BMA180_CMD_OFFSET_LSB1, offset_lsb1);
}

void bma180i::BMA180_SetBandwidth(byte bandwidth) {
    // Connect to the bw_tcs register and set the filtering level
    BMA180_WriteByte(address, BMA180_CMD_BW_TCS, bandwidth << 4);
}


float bma180i::getDividerByRange(byte range) {
    switch (range)
    {
        case BMA180_RANGE_1G:
            return BMA180_RANGE_1G_G_DIVIDER;
        case BMA180_RANGE_1DOT5G:
            return BMA180_RANGE_1DOT5G_G_DIVIDER;
        case BMA180_RANGE_2G:
            return BMA180_RANGE_2G_G_DIVIDER;
        case BMA180_RANGE_3G:
            return BMA180_RANGE_3G_G_DIVIDER;
        case BMA180_RANGE_4G:
            return BMA180_RANGE_4G_G_DIVIDER;
        case BMA180_RANGE_8G:
            return BMA180_RANGE_8G_G_DIVIDER;
        case BMA180_RANGE_16G:
            return BMA180_RANGE_16G_G_DIVIDER;

        default:
            return BMA180_RANGE_2G_G_DIVIDER;
    }
}

int bma180i::BMA180_ReadX() {
    int data = 0;

    data = ((BMA180_ReadByte(address, BMA180_CMD_ACC_X_LSB) | BMA180_ReadByte(address, BMA180_CMD_ACC_X_MSB) << 8) >> 2);

    return data;
}

float bma180i::BMA180_ReadX_G() {
    return BMA180_ReadX() * g_divider;
}


int bma180i::BMA180_ReadY() {
    int data = 0;

    data = ((BMA180_ReadByte(address, BMA180_CMD_ACC_Y_LSB) | BMA180_ReadByte(address, BMA180_CMD_ACC_Y_MSB) << 8) >> 2);

    return data;
}

float bma180i::BMA180_ReadY_G() {
    return BMA180_ReadY() * g_divider;
}

int bma180i::BMA180_ReadZ() {
    int data = 0;

    data = ((BMA180_ReadByte(address, BMA180_CMD_ACC_Z_LSB) | BMA180_ReadByte(address, BMA180_CMD_ACC_Z_MSB) << 8) >> 2);

    return data;
}

float bma180i::BMA180_ReadZ_G() {
    return BMA180_ReadZ() * g_divider;
}



void bma180i::readAcc() {
    Wire.beginTransmission(address);
    Wire.write(BMA180_CMD_ACC_X_LSB);
    Wire.endTransmission();

    Wire.requestFrom(address, (byte)6);

    a.x = (Wire.read() | (Wire.read() << 8)) >> 2;
    a.y = (Wire.read() | (Wire.read() << 8)) >> 2;
    a.z = (Wire.read() | (Wire.read() << 8)) >> 2;
}


byte bma180i::BMA180_WriteByte(byte i2c_address, byte address, byte data) {
    Wire.beginTransmission(i2c_address);
    Wire.write(address);
    Wire.write(data);
    byte result = Wire.endTransmission();

    //do some error checking
    /*if (result > 0) {
        debug((char *)result, "PROBLEM..... Result code is ");
    }*/

    //the BMA180 has slow EEPROM.  take it easy.
    //delay(10);

    return result;
}


byte bma180i::BMA180_ReadByte(byte i2c_address, byte address)
{
    byte temp;
    Wire.beginTransmission(i2c_address);
    Wire.write(address);
    Wire.endTransmission();
    Wire.requestFrom(i2c_address, (byte) 1);
    while (Wire.available()) {
        temp = Wire.read();
    }
    Wire.endTransmission();
    return temp;
}

