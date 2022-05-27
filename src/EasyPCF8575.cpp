#include <EasyPCF8575.h>

EasyPCF8575::EasyPCF8575()
{
    this->pcf_address = 0;   //must be changed in setup() function
    this->i2c_exists  = false;
}

bool EasyPCF8575::check(uint8_t addr)
{
    if (addr > 126){
        return this->i2c_exists;
    }
    Wire.beginTransmission(addr);
    byte error = Wire.endTransmission();

    return error > 0 ? false : true;
}

uint8_t EasyPCF8575::findPCFaddr()
{
    byte error, address;

    for(address = 1; address < 127; address++ ) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
 
        if (error == 0){
            this->i2c_exists = true;
            return address;
        }
        else if (error==4){
            return 0;
        }    
    }
    if (this->i2c_exists == false){
        return 255;
    }
}

//Returns 0 if LOW, 1 if HIGH
uint8_t EasyPCF8575::getBitValue(uint8_t bit0UpTo15)
{
    Wire.requestFrom(this->pcf_address,2);
    if (Wire.available()){
        Wire.readBytes(localBuf,2);
    }

    uint16_t bothBytes = (localBuf[0] << 8) | (localBuf[1] << 0);
    return bothBytes&(1<<bit0UpTo15) > 0 ? 1 : 0;
}

uint8_t *EasyPCF8575::getBytesValueAsBytes()
{
    localBuf[0] = 0;
    localBuf[1] = 0;

    Wire.requestFrom(this->pcf_address,2);
    if (Wire.available()){
        Wire.readBytes(localBuf,2);
        return localBuf;
    }
    return localBuf;

}

uint16_t EasyPCF8575::getBytesValueAsInt()
{
    uint8_t localBuf[2];
    localBuf[0] = 0;
    localBuf[1] = 0;

    Wire.requestFrom(this->pcf_address,2);
    if (Wire.available()){
        Wire.readBytes(localBuf,2);
    }

    return (localBuf[0] << 8) | (localBuf[1] << 0);
}

uint8_t EasyPCF8575::getLeftBitValue(uint8_t bit0upTo7)
{
    localBuf[0] = 0;
    localBuf[1] = 0;

    Wire.requestFrom(this->pcf_address,2);
    if (Wire.available()){
        Wire.readBytes(localBuf,2);
        return localBuf[0]&(1<<bit0upTo7);
    }
    return 0;
}

uint8_t EasyPCF8575::getLSBbyteValue()
{
    localBuf[0] = 0;
    localBuf[1] = 0;

    Wire.requestFrom(this->pcf_address,2);
    if (Wire.available()){
        Wire.readBytes(localBuf,2);
        return localBuf[0];
    }
    return 0;
}

uint8_t EasyPCF8575::getRightBitValue(uint8_t bit0upTo7)
{
    localBuf[0] = 0;
    localBuf[1] = 0;

    Wire.requestFrom(this->pcf_address,2);
    if (Wire.available()){
        Wire.readBytes(localBuf,2);
        return localBuf[1]&(1<<bit0upTo7);
    }
    return 0;
}

uint8_t EasyPCF8575::getMSBbyteValue()
{
    localBuf[0] = 0;
    localBuf[1] = 0;

    Wire.requestFrom(this->pcf_address,2);
    if (Wire.available()){
        Wire.readBytes(localBuf,2);
        return localBuf[1];
    }
    return 0;
}

void EasyPCF8575::setAllBitsDown()
{
    localBuf[0] = 0;
    localBuf[1] = 0;

    Wire.beginTransmission(this->pcf_address);
    Wire.write(localBuf,2);
    Wire.endTransmission();
}

void EasyPCF8575::setAllBitsUp()
{
    localBuf[0] = 255;
    localBuf[1] = 255;

    Wire.beginTransmission(this->pcf_address);
    Wire.write(localBuf,2);
    Wire.endTransmission();
}

void EasyPCF8575::setBitDown(uint8_t bit0upTo15)
{
    localBuf[0] = 0;
    localBuf[1] = 0;

    Wire.requestFrom(this->pcf_address,2);
    if (Wire.available()){
        Wire.readBytes(localBuf,2);
    }

    uint16_t values = (localBuf[0]<<8) | (localBuf[1] <<0);
    values = values&~(1<<bit0upTo15);

    localBuf[1] = values &~(255 << 8);
    localBuf[0] = values >> 8;

    Wire.beginTransmission(this->pcf_address);
    Wire.write(localBuf,2);
    Wire.endTransmission();
}

void EasyPCF8575::setBitUp(uint8_t bit0upTo15)
{
    localBuf[0] = 0;
    localBuf[1] = 0;

    Wire.requestFrom(this->pcf_address,2);
    if (Wire.available()){
        Wire.readBytes(localBuf,2);
    }

    uint16_t values = (localBuf[0]<<8) | (localBuf[1] <<0);
    values = values|(1<<bit0upTo15);

    localBuf[1] = values &~(255 << 8);
    localBuf[0] = values >> 8;

    Wire.beginTransmission(this->pcf_address);
    Wire.write(localBuf,2);
    Wire.endTransmission();
}

void EasyPCF8575::setInvertBit(uint8_t bit0upTo15)
{
    localBuf[0] = 0;
    localBuf[1] = 0;

    Wire.requestFrom(this->pcf_address,2);
    if (Wire.available()){
        Wire.readBytes(localBuf,2);
    }

    uint16_t values = (localBuf[0]<<8) | (localBuf[1] <<0);
    values = values^(1<<bit0upTo15);

    localBuf[1] = values &~(255 << 8);
    localBuf[0] = values >> 8;

    Wire.beginTransmission(this->pcf_address);
    Wire.write(localBuf,2);
    Wire.endTransmission();
}

void EasyPCF8575::setLeftBitDown(uint8_t bit0upTo7)
{
    localBuf[0] = 0;
    localBuf[1] = 0;

    Wire.requestFrom(this->pcf_address,2);
    if (Wire.available()){
        Wire.readBytes(localBuf,2);
    }

    localBuf[0] = localBuf[0]&~(1<<bit0upTo7);

    Wire.beginTransmission(this->pcf_address);
    Wire.write(localBuf,2);
    Wire.endTransmission();
}

void EasyPCF8575::setLeftBitUp(uint8_t bit0upTo7)
{
    localBuf[0] = 0;
    localBuf[1] = 0;

    Wire.requestFrom(this->pcf_address,2);
    if (Wire.available()){
        Wire.readBytes(localBuf,2);
    }

    localBuf[0] = localBuf[0]|(1<<bit0upTo7);

    Wire.beginTransmission(this->pcf_address);
    Wire.write(localBuf,2);
    Wire.endTransmission();
}

void EasyPCF8575::setNewBytesValue(uint8_t *value)
{
    Wire.beginTransmission(this->pcf_address);
    Wire.write(value,2);
    Wire.endTransmission();
}

void EasyPCF8575::setNewBytesValue(uint16_t value)
{
    localBuf[1] = value &~ (255<<8);
    localBuf[0] = value >> 8;

    Wire.beginTransmission(this->pcf_address);
    Wire.write(localBuf,2);
    Wire.endTransmission();
}

void EasyPCF8575::setNewLeftByteValue(uint8_t value)
{
    Wire.requestFrom(this->pcf_address,2);
    if (Wire.available()){
        Wire.readBytes(localBuf,2);
    }

    localBuf[0] = value;

    Wire.beginTransmission(this->pcf_address);
    Wire.write(localBuf,2);
    Wire.endTransmission();
}

void EasyPCF8575::setNewRightByteValue(uint8_t value)
{
    Wire.requestFrom(this->pcf_address,2);
    if (Wire.available()){
        Wire.readBytes(localBuf,2);
    }

    localBuf[1] = value;

    Wire.beginTransmission(this->pcf_address);
    Wire.write(localBuf,2);
    Wire.endTransmission();
}

void EasyPCF8575::setRightBitDown(uint8_t bit0upTo7)
{
    localBuf[0] = 0;
    localBuf[1] = 0;

    Wire.requestFrom(this->pcf_address,2);
    if (Wire.available()){
        Wire.readBytes(localBuf,2);
    }

    localBuf[1] = localBuf[1]&~(1<<bit0upTo7);

    Wire.beginTransmission(this->pcf_address);
    Wire.write(localBuf,2);
    Wire.endTransmission();
}

void EasyPCF8575::setRightBitUp(uint8_t bit0upTo7)
{
    localBuf[0] = 0;
    localBuf[1] = 0;

    Wire.requestFrom(this->pcf_address,2);
    if (Wire.available()){
        Wire.readBytes(localBuf,2);
    }

    localBuf[1] = localBuf[1]|(1<<bit0upTo7);

    Wire.beginTransmission(this->pcf_address);
    Wire.write(localBuf,2);
    Wire.endTransmission();
}

void EasyPCF8575::startI2C(uint8_t sda_pin, uint8_t scl_pin, uint8_t pcf_addr)
{
    Wire.setPins(21,22);
    Wire.begin();
    uint8_t addr = this->findPCFaddr();
    this->pcf_address = pcf_addr >126 ? addr : pcf_addr;
    this->i2c_exists = this->pcf_address > 0 ? true : false;
}

void EasyPCF8575::startI2C(uint8_t pcf_addr)
{
    Wire.begin();
    this->pcf_address = pcf_addr >126 ? this->findPCFaddr() : pcf_addr;
    this->i2c_exists = this->pcf_address > 0 ? true : false;
}

uint8_t EasyPCF8575::whichAddr()
{
    return this->pcf_address;
}