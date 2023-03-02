#ifndef _AT24C02_H_
#define _AT24C02_H_

#include <Arduino.h>
#include <Wire.h>

#define EEPROM_DELAY 3

#define DEFAULT_EEPROM_SdaPin 21
#define DEFAULT_EEPROM_SclPin 22

#define DEFAULT_EEPROM_i2C_ADDRESS 0x50

#define BUFFER_LENGTH 32
#define EEPROM__PAGE_SIZE 8
#define EEPROM__RD_BUFFER_SIZE    BUFFER_LENGTH
#define EEPROM__WR_BUFFER_SIZE    (BUFFER_LENGTH - 1)

class AT24C02
{
  public:
    AT24C02(byte _addressI2C);
    AT24C02();

    int SdaPin;
    int SclPin;
    void AttachI2CPins(int _sdaPin, int _sclPin);
    void SetAddressI2C(byte _addressI2C);

    void Init();
    void Init(int _sdaPin, int _sclPin, byte _addressI2C);

    void Write(byte _address, byte _data); //write single byte to EEPROM
    byte Read(byte _address); //read single byte from EEPROM

    void WriteBytes(byte _address, byte _length, byte* _ptr_data);
    void ReadBytes(byte _address, byte _length, byte* _ptr_data);

  private:
    byte addressI2C;
    void writePage(byte _address, byte _length, byte* _ptr_data);
    void writeBuffer(byte _address, byte _length, byte* _ptr_data);
    void readBuffer(byte _address, byte _length, byte* _ptr_data);
};

#endif
