#ifndef _AT24C02_H_
#define _AT24C02_H_

#include <Arduino.h>
#include <Wire.h>

#define EEPROM_DELAY 3

#define DEFAULT_EEPROM_SdaPin 21
#define DEFAULT_EEPROM_SclPin 22

class AT24C02
{
  public:
    AT24C02(byte _address);

    int SdaPin;
    int SclPin;
    void AttachI2CPins(int _sdaPin, int _sclPin);

    void Init();
    void Write(unsigned int _offset, byte _data); //write single byte to EEPROM
    void WriteBuffer(unsigned int _offset, byte* _buffer, unsigned int _length); //write multiple bytes to EEPROM
    byte Read(unsigned int _offset); //read single byte from EEPROM
    void ReadBuffer(unsigned int _offset, unsigned int _length, byte * _buffer); //read multiple bytes to EEPROM
  private:
    byte addressI2C;
};

#endif
