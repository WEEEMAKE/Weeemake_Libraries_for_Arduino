#include "TempOneWire.h"


TempOneWire::TempOneWire(void)
{
}

TempOneWire::TempOneWire(uint8_t pin)
{
   bitmask = WePIN_TO_BITMASK(pin);
   baseReg = WePIN_TO_BASEREG(pin);
}
void TempOneWire::reset(uint8_t pin)
{
  bitmask = WePIN_TO_BITMASK(pin);
  baseReg = WePIN_TO_BASEREG(pin);
}
bool TempOneWire::readIO(void)
{
  WeIO_REG_TYPE           mask = bitmask;
  volatile WeIO_REG_TYPE *reg WeIO_REG_ASM = baseReg;
  uint8_t r;
  WeDIRECT_MODE_INPUT(reg, mask);    // allow it to float
  delayMicroseconds(10);
  r = WeDIRECT_READ(reg, mask);
  return(r);
}
uint8_t TempOneWire::reset(void)
{
  WeIO_REG_TYPE mask = bitmask;
  volatile WeIO_REG_TYPE *reg WeIO_REG_ASM = baseReg;
  uint8_t r;
  uint8_t retries = 125;

  noInterrupts();
  WeDIRECT_MODE_INPUT(reg, mask);
  interrupts();
  /* wait until the wire is high... just in case */
  do
  {
    if (--retries == 0)
    {
      return(0);
    }
    delayMicroseconds(2);
  }
  while (!WeDIRECT_READ(reg, mask));

  noInterrupts();
  WeDIRECT_WRITE_LOW(reg, mask);
  WeDIRECT_MODE_OUTPUT(reg, mask);        /* drive output low */
  interrupts();
  delayMicroseconds(480);
  noInterrupts();
  WeDIRECT_MODE_INPUT(reg, mask);         /* allow it to float */
  delayMicroseconds(70);
  r = !WeDIRECT_READ(reg, mask);
  interrupts();
  delayMicroseconds(410);
  return(r);
}
void TempOneWire::write_bit(uint8_t v)
{
  WeIO_REG_TYPE mask = bitmask;
  volatile WeIO_REG_TYPE *reg WeIO_REG_ASM = baseReg;

  if (v & 1)
  {
    noInterrupts();
    WeDIRECT_WRITE_LOW(reg, mask);
    WeDIRECT_MODE_OUTPUT(reg, mask);        /* drive output low */
    delayMicroseconds(10);
    WeDIRECT_WRITE_HIGH(reg, mask);         /* drive output high */
    interrupts();
    delayMicroseconds(55);
  }
  else
  {
    noInterrupts();
    WeDIRECT_WRITE_LOW(reg, mask);
    WeDIRECT_MODE_OUTPUT(reg, mask);        /* drive output low */
    delayMicroseconds(65);
    WeDIRECT_WRITE_HIGH(reg, mask);         /* drive output high */
    interrupts();
    delayMicroseconds(5);
  }
}
uint8_t TempOneWire::read_bit(void)
{
  WeIO_REG_TYPE mask = bitmask;
  volatile WeIO_REG_TYPE *reg WeIO_REG_ASM = baseReg;
  uint8_t r;

  noInterrupts();
  WeDIRECT_MODE_OUTPUT(reg, mask);
  WeDIRECT_WRITE_LOW(reg, mask);
  delayMicroseconds(3);
  WeDIRECT_MODE_INPUT(reg, mask); /* let pin float, pull up will raise */
  delayMicroseconds(10);
  r = WeDIRECT_READ(reg, mask);
  interrupts();
  delayMicroseconds(53);
  return(r);
}
void TempOneWire::write(uint8_t v, uint8_t power)
{
  uint8_t bitMask;

  for (bitMask = 0x01; bitMask; bitMask <<= 1)
  {
    TempOneWire::write_bit((bitMask & v) ? 1 : 0);
  }
  if (!power)
  {
    noInterrupts();
    WeDIRECT_MODE_INPUT(baseReg, bitmask);
    WeDIRECT_WRITE_LOW(baseReg, bitmask);
    interrupts();
  }
}
void TempOneWire::write_bytes(const uint8_t *buf, uint16_t count, bool power)
{
  for (uint16_t i = 0; i < count; i++)
  {
    write(buf[i]);
  }
  if (!power)
  {
    noInterrupts();
    WeDIRECT_MODE_INPUT(baseReg, bitmask);
    WeDIRECT_WRITE_LOW(baseReg, bitmask);
    interrupts();
  }
}
uint8_t TempOneWire::read()
{
  uint8_t bitMask;
  uint8_t r = 0;

  for (bitMask = 0x01; bitMask; bitMask <<= 1)
  {
    if (TempOneWire::read_bit())
    {
      r |= bitMask;
    }
  }
  return(r);
}
void TempOneWire::read_bytes(uint8_t *buf, uint16_t count)
{
  for (uint16_t i = 0; i < count; i++)
  {
    buf[i] = read();
  }
}
void TempOneWire::select(const uint8_t rom[8])
{
  uint8_t i;

  write(0x55);       /* Choose ROM */

  for (i = 0; i < 8; i++)
  {
    write(rom[i]);
  }
}
void TempOneWire::skip(void)
{
  write(0xCC);       /* Skip ROM */
}
void TempOneWire::depower(void)
{
  noInterrupts();
  WeDIRECT_MODE_INPUT(baseReg, bitmask);
  interrupts();
}
void TempOneWire::reset_search(void)
{
  /* reset the search state */
  LastDiscrepancy = 0;
  LastDeviceFlag = false;
  LastFamilyDiscrepancy = 0;
  for (int16_t i = 7;; i--)
  {
    ROM_NO[i] = 0;
    if (i == 0)
    {
      break;
    }
  }
}
void TempOneWire::target_search(uint8_t family_code)
{
  /* set the search state to find SearchFamily type devices */
  ROM_NO[0] = family_code;
  for (uint8_t i = 1; i < 8; i++)
  {
    ROM_NO[i] = 0;
  }
  LastDiscrepancy = 64;
  LastFamilyDiscrepancy = 0;
  LastDeviceFlag = false;
}
uint8_t TempOneWire::search(uint8_t *newAddr)
{
  uint8_t id_bit_number;
  uint8_t last_zero, rom_byte_number, search_result;
  uint8_t id_bit, cmp_id_bit;

  uint8_t rom_byte_mask, search_direction;

  /* initialize for search */
  id_bit_number = 1;
  last_zero = 0;
  rom_byte_number = 0;
  rom_byte_mask = 1;
  search_result = 0;

  /* if the last call was not the last one */
  if (!LastDeviceFlag)
  {
    /* 1-Wire reset */
    if (!reset())
    {
      /* reset the search */
      LastDiscrepancy = 0;
      LastDeviceFlag = false;
      LastFamilyDiscrepancy = 0;
      return(false);
    }

    /* issue the search command */
    write(0xF0);

    /* loop to do the search */
    do
    {
      /* read a bit and its complement */
      id_bit = read_bit();
      cmp_id_bit = read_bit();

      /* check for no devices on 1-wire */
      if ((id_bit == 1) && (cmp_id_bit == 1))
      {
        break;
      }
      else
      {
        /* all devices coupled have 0 or 1 */
        if (id_bit != cmp_id_bit)
        {
          search_direction = id_bit; /* bit write value for search */
        }
        else
        {
          /*
             if this discrepancy if before the Last Discrepancy
             on a previous next then pick the same as last time
             */
          if (id_bit_number < LastDiscrepancy)
          {
            search_direction = ((ROM_NO[rom_byte_number] & rom_byte_mask) > 0);
          }
          else
          {
            /* if equal to last pick 1, if not then pick 0 */
            search_direction = (id_bit_number == LastDiscrepancy);
          }

          /* if 0 was picked then record its position in LastZero */
          if (search_direction == 0)
          {
            last_zero = id_bit_number;

            /* check for Last discrepancy in family */
            if (last_zero < 9)
            {
              LastFamilyDiscrepancy = last_zero;
            }
          }
        }

        /*
           set or clear the bit in the ROM byte rom_byte_number
           with mask rom_byte_mask
           */
        if (search_direction == 1)
        {
          ROM_NO[rom_byte_number] |= rom_byte_mask;
        }
        else
        {
          ROM_NO[rom_byte_number] &= ~rom_byte_mask;
        }

        /* serial number search direction write bit */
        write_bit(search_direction);

        /*
           increment the byte counter id_bit_number
           and shift the mask rom_byte_mask
           */
        id_bit_number++;
        rom_byte_mask <<= 1;

        /* if the mask is 0 then go to new SerialNum byte rom_byte_number and reset mask */
        if (rom_byte_mask == 0)
        {
          rom_byte_number++;
          rom_byte_mask = 1;
        }
      }
    }
    while (rom_byte_number < 8); /* loop until through all ROM bytes 0-7 */

    /* if the search was successful then */
    if (!(id_bit_number < 65))
    {
      /* search successful so set LastDiscrepancy,LastDeviceFlag,search_result */
      LastDiscrepancy = last_zero;

      /* check for last device */
      if (LastDiscrepancy == 0)
      {
        LastDeviceFlag = true;
      }

      search_result = true;
    }
  }

  /* if no device found then reset counters so next 'search' will be like a first */
  if (!search_result || !ROM_NO[0])
  {
    LastDiscrepancy = 0;
    LastDeviceFlag = false;
    LastFamilyDiscrepancy = 0;
    search_result = false;
  }
  for (int16_t i = 0; i < 8; i++)
  {
    newAddr[i] = ROM_NO[i];
  }
  return(search_result);
}





