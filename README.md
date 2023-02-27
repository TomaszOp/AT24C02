# AT24C02

Atmel AT24C02 eeprom library<br>

use<br>

#define EEPROM_i2C_ADDRESS 0x50<br>

AT24C02 memory(EEPROM_i2C_ADDRESS);<br>
<br>
  memory.AttachI2CPins(DEFAULT_SdaPin, DEFAULT_SclPin);<br>
  memory.Init();<br>
<br>
  for(int i = 0; i < 256; i++)<br>
  {<br>
    memory.Write(i, (byte)i);<br>
  }<br>
  <br>
  byte value;<br>
  for(int i = 0; i < 256; i++)<br>
  {<br>
    value = memory.Read(i);<br>
  }<br>
<br>
  char value1[50] = "Global variables";<br>
  memory.WriteBuffer(0, (byte*)value1, strlen(value1));<br>
  byte value2[50];<br>
  memory.ReadBuffer(0, strlen(value1), value2);<br>
