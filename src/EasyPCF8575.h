/*
  EasyPCF8575 - The easiest library for PCF8575.
  Created by Djames Suhanko, May 5, 2022.
  Released into the public domain.
*/
#ifndef EasyPCF8575_h
#define EasyPCF8575_h
#include <Arduino.h>
#include <Wire.h>

#define SEARCH 255
/*! PCF8575 handler - by: Djames Suhanko - www.dobitaobyte.com.br */

class EasyPCF8575{
    public:
        EasyPCF8575();                               //! if SEARCH is passed to pcf_addr, the lib will try to discover address

        bool check(uint8_t addr);                    //! Just returns true if pcf found

        uint8_t findPCFaddr();                       //!find and return PCF address

        uint8_t getLeftByteValue();                  //! Returns value of left byte
        uint8_t getRightByteValue();                 //! Returns value of right byte

        uint8_t *getBytesValueAsBytes();             //! Returns an array of two bytes
        uint16_t getBytesValueAsInt();               //! Returns bytes value as int

        uint8_t getLeftBitValue(uint8_t bit0upTo7);  //! check if bit is HIGH or LOW
        uint8_t getRightBitValue(uint8_t bit0upTo7); //! check if bit is HIGH or LOW
        uint8_t getBitValue(uint8_t bit0UpTo15);     //! check if a bit is HIGH or LOW

        void setNewLeftByteValue(uint8_t value);     //! Set a new value, ignoring last value in left byte
        void setNewRightByteValue(uint8_t value);    //! Set a new value, ignoring last value in right byte

        void setNewBytesValue(uint8_t *value);       //! Set a new value, ignoring last two byte values. Here we need pass an array of 2 bytes like [16,5], representing left and right, respectively.
        void setNewBytesValue(uint16_t value);       //! Set a new value, ignoring last two byte values. Here we can pass a int like 512+128, but not 1+1, because this is equal 2, resulting in 1 byte: 00000010

        void setBitDown(uint8_t bit0upTo15);         //! Here you can down any bit using numerical position, from 0 to 15
        void setBitUp(uint8_t bit0upTo15);           //! Here you can up any bit using numerical position, from 0 to 15
        
        void setLeftBitDown(uint8_t bit0upTo7);      //! Here you can pass the position of any bit of left byte, from 0 to 7. Think as port B
        void setRightBitDown(uint8_t bit0upTo7);     //! Here you can pass the position of any bit of right byte, from 0 to 7. Think as port A

        void setLeftBitUp(uint8_t bit0upTo7);        //! Here you can pass the position of any bit of left byte, from 0 to 7. Think as port B
        void setRightBitUp(uint8_t bit0upTo7);       //! Here you can pass the position of any bit of right byte, from 0 to 7. Think as port A

        void setAllBitsDown();                       //! Put all bits in LOW
        void setAllBitsUp();                         //! Put all bits in HIGH

        void setInvertBit(uint8_t bit0upTo15);       //! Invert bit value

        void startI2C(uint8_t sda_pin, uint8_t scl_pin, uint8_t pcf_addr); //!Call it in setup() function. Instead pcf_addr, you can pass SEARCH as parameter to auto discovering
        void startI2C(uint8_t pcf_addr); //! Using default pins in Arduino, but other platforms may be needed to use sda, scl and addr.

        uint8_t whichAddr();

    private:
        uint8_t localBuf[2];
        uint8_t pcf_address;

        bool i2c_exists;
};
#endif