#include <Wire.h>
#include "bma180i.h"


byte bma180i::BMA180_ReadTemperature() {
    return BMA180_ReadByte(address, BMA180_CMD_TEMP);
}

void bma180i::BMA180_SetRange(byte address, byte range) {
    // Connect to the offset_lsb1 register and set the range
    BMA180_WriteByte(address, 0x35, range << 1);
}

void bma180i::BMA180_SetBandwidth(byte address, byte bandwidth) {
    // Connect to the bw_tcs register and set the filtering level
    BMA180_WriteByte(address, BMA180_CMD_BW_TCS, bandwidth << 4);
}

byte bma180i::BMA180_WriteByte(byte i2c_address, byte address, byte data) {
    Wire.beginTransmission(i2c_address);
    Wire.write(address);
    Wire.write(data);
    byte result = Wire.endTransmission();

    //do some error checking
    if (result > 0) {
        Serial.print("PROBLEM..... Result code is ");
        Serial.println(result);
    }
    else {
        Serial.println("Read/Write success");
    }

    //the BMA180 has slow EEPROM.  take it easy.
    delay(10);

    return result;
}


void bma180i::BMA180_Init() {
    int id = BMA180_ReadId(address);

    if (id == BMA180_CHIP_ID) {
        Serial.println("BMA180 Chip Detect Pass");

        // Connect to the ctrl_reg1 register and set the ee_w bit to enable writing.
        if (BMA180_WriteByte(address, BMA180_CMD_CTRL_REG0, 0x01) == 0)
            Serial.println("BMA180 Write Init Pass. ");
        else
            Serial.println("BMA180 Write Init Fail :(");
    }
    else {
        Serial.print(id);
        Serial.println(" <- BMA180 Chip Detect Fail :(");
    }
}

byte bma180i::BMA180_ReadByte(byte i2c_address, byte address) {

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

byte bma180i::BMA180_ReadId(byte address) {
    //get the contents of the chip id register.
    return BMA180_ReadByte(address, BMA180_CMD_CHIP_ID);
}