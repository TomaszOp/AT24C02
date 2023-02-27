#include <Wire.h>

#include "AT24C02.h"

AT24C02::AT24C02(byte _address)
{
  this->addressI2C = _address;

  this->SdaPin = DEFAULT_EEPROM_SdaPin;   
  this->SclPin = DEFAULT_EEPROM_SclPin;
}

void AT24C02::AttachI2CPins(int _sdaPin, int _sclPin)
{    
  this->SdaPin = _sdaPin;   
  this->SclPin = _sclPin;      
}
 
void AT24C02::Init()
{
  Wire.begin(this->SdaPin, this->SclPin);
}

void AT24C02::Write(unsigned int _offset, byte _data)
{
  Wire.beginTransmission(this->addressI2C);

  Wire.write((int)_offset);

  Wire.write(_data);
  Wire.endTransmission();

  delay(EEPROM_DELAY);
}

void AT24C02::WriteBuffer(unsigned int _offset, byte * _data, unsigned int _length)
{
  Wire.beginTransmission(this->addressI2C);
  Wire.write((int)_offset);

  for(byte i = 0; i < _length; i++)
  {
    Wire.write(_data[i]);
  }
  
  Wire.endTransmission();
  delay(EEPROM_DELAY);
}

byte AT24C02::Read(unsigned int _offset)
{
  Wire.beginTransmission(this->addressI2C);
  Wire.write((int)_offset);
  Wire.endTransmission();

  Wire.requestFrom(this->addressI2C, 1);
  
  byte data = 0;
  if (Wire.available())
  {
      data = Wire.read();
  }

  delay(EEPROM_DELAY);
  return data;
}

void AT24C02::ReadBuffer(unsigned int _offset, unsigned int _length, byte * _buffer)
{
  Wire.beginTransmission(this->addressI2C);
  Wire.write((int)_offset);
  Wire.endTransmission();

  Wire.write((int)_offset);
  Wire.requestFrom(this->addressI2C, _length);
  
  for (byte i = 0; i < _length; i++)
  {
      if (Wire.available())
      {
          _buffer[i] = Wire.read();
      }
  }

  delay(EEPROM_DELAY);
}
