#include <Wire.h>

#include "AT24C02.h"

AT24C02::AT24C02(byte _addressI2C)
{
  this->addressI2C = _addressI2C;

  this->SdaPin = DEFAULT_EEPROM_SdaPin;   
  this->SclPin = DEFAULT_EEPROM_SclPin;
}

AT24C02::AT24C02()
{
  this->addressI2C = DEFAULT_EEPROM_i2C_ADDRESS;

  this->SdaPin = DEFAULT_EEPROM_SdaPin;   
  this->SclPin = DEFAULT_EEPROM_SclPin;
}

void AT24C02::AttachI2CPins(int _sdaPin, int _sclPin)
{    
  this->SdaPin = _sdaPin;   
  this->SclPin = _sclPin;      
}
 
void AT24C02::SetAddressI2C(byte _addressI2C)
{
  this->addressI2C = _addressI2C;
}

void AT24C02::Init()
{
  Wire.begin(this->SdaPin, this->SclPin);
}

void AT24C02::Init(int _sdaPin, int _sclPin, byte _address)
{
  this->SdaPin = _sdaPin;   
  this->SclPin = _sclPin; 

  this->addressI2C = _address;

  Wire.begin(this->SdaPin, this->SclPin);
}

void AT24C02::Write(byte _address, byte _data)
{
  Wire.beginTransmission(this->addressI2C);

  Wire.write(_address);

  Wire.write(_data);
  Wire.endTransmission();

  delay(EEPROM_DELAY);
}

void AT24C02::writePage(byte _address, byte _length, byte* _ptr_data)
{
    // Write complete buffers.
    byte bufferCount = _length / EEPROM__WR_BUFFER_SIZE;
    for (byte i = 0; i < bufferCount; i++)
    {
        byte offset = i * EEPROM__WR_BUFFER_SIZE;
        writeBuffer(_address + offset, EEPROM__WR_BUFFER_SIZE, _ptr_data + offset);
    }

    // Write remaining bytes.
    byte remainingBytes = _length % EEPROM__WR_BUFFER_SIZE;
    byte offset = _length - remainingBytes;
    writeBuffer(_address + offset, remainingBytes, _ptr_data + offset);
}

void AT24C02::WriteBytes(byte _address, byte _length, byte* _ptr_data)
{

  // Write first page if not aligned.
  byte notAlignedLength = 0;
  byte pageOffset = _address % EEPROM__PAGE_SIZE;
  if (pageOffset > 0)
  {
      notAlignedLength = EEPROM__PAGE_SIZE - pageOffset;
      if (_length < notAlignedLength)
      {
          notAlignedLength = _length;
      }
      writePage(_address, notAlignedLength, _ptr_data);
      _length -= notAlignedLength;
  }

  if (_length > 0)
  {
      _address += notAlignedLength;
      _ptr_data += notAlignedLength;

      // Write complete and aligned pages.
      byte pageCount = _length / EEPROM__PAGE_SIZE;
      for (byte i = 0; i < pageCount; i++)
      {
          writePage(_address, EEPROM__PAGE_SIZE, _ptr_data);
          _address += EEPROM__PAGE_SIZE;
          _ptr_data += EEPROM__PAGE_SIZE;
          _length -= EEPROM__PAGE_SIZE;
      }

      if (_length > 0)
      {
          // Write remaining uncomplete page.
          writePage(_address, _length, _ptr_data);
      }
  }
}

void AT24C02::writeBuffer(byte _address, byte _length, byte* _ptr_data)
{
    Wire.beginTransmission(this->addressI2C);
    Wire.write(_address);
    for (byte i = 0; i < _length; i++)
    {
        Wire.write(_ptr_data[i]);
    }
    Wire.endTransmission();
    
    delay(EEPROM_DELAY);
}


byte AT24C02::Read(byte _address)
{
  Wire.beginTransmission(this->addressI2C);
  Wire.write(_address);
  Wire.endTransmission();

  Wire.requestFrom((int)this->addressI2C, (int)1);
  
  byte data = 0;
  if (Wire.available())
  {
      data = Wire.read();
  }

  delay(EEPROM_DELAY);
  return data;
}

void AT24C02::ReadBytes(byte _address, byte _length, byte* _ptr_data)
{
    byte bufferCount = _length / EEPROM__RD_BUFFER_SIZE;
    for (byte i = 0; i < bufferCount; i++)
    {
        byte offset = i * EEPROM__RD_BUFFER_SIZE;
        readBuffer(_address + offset, EEPROM__RD_BUFFER_SIZE, _ptr_data + offset);
    }

    byte remainingBytes = _length % EEPROM__RD_BUFFER_SIZE;
    byte offset = _length - remainingBytes;

    if(remainingBytes > 0)
    {
      readBuffer(_address + offset, remainingBytes, _ptr_data + offset);
    }
}

void AT24C02::readBuffer(byte _address, byte _length, byte* _ptr_data)
{
    Wire.beginTransmission(this->addressI2C);
    Wire.write(_address);
    Wire.endTransmission();

    Wire.requestFrom(this->addressI2C, _length);
    for (byte i = 0; i < _length; i++)
    {
        if (Wire.available())
        {
            _ptr_data[i] = Wire.read();
        }
    }
}