#include <Arduino.h>
#include <Wire.h>
#include <EasyPCF8575.h>

EasyPCF8575 pcf;

void setup(){
    Serial.begin(9600);

    pcf.startI2C(21,22,SEARCH); //Only SEARCH, if using normal pins in Arduino

    if (!pcf.check(SEARCH)){
        Serial.println("Device not found. Try to specify the address");
        Serial.println(pcf.whichAddr());
        while (true);
    }


    uint8_t to_bits;
    uint8_t *to_bytes;
    uint16_t to_int;

    pcf.setNewBytesValue(65535); //OK
    Serial.println(" ");
    delay(500);

    Serial.print("setNewBytesValue: ");
    Serial.println(pcf.getBytesValueAsInt());
    delay(500);

    pcf.setAllBitsDown();
    Serial.print("setAllBitsDown: ");
    Serial.println(pcf.getBytesValueAsInt());
    delay(500);

    pcf.setAllBitsUp();
    Serial.print("setAllBitsUp: ");
    Serial.println(pcf.getBytesValueAsInt());
    delay(500);

    pcf.setBitDown(0);
    Serial.print("setBitDown (0): ");
    Serial.println(pcf.getBytesValueAsInt());
    delay(500);

    pcf.setBitDown(15);
    Serial.print("setBitDown (15): ");
    Serial.println(pcf.getBytesValueAsInt());
    delay(500);

    pcf.setInvertBit(15);
    Serial.print("setInvertBit (15): ");
    Serial.println(pcf.getBytesValueAsInt());
    delay(500);

    pcf.setLeftBitDown(7);
    Serial.print("setLeftBitDown(7): ");
    Serial.println(pcf.getBytesValueAsInt());
    delay(500);

    pcf.setLeftBitUp(7);
    Serial.print("setLeftBitUp(7): ");
    Serial.println(pcf.getBytesValueAsInt());
    delay(500);

    pcf.setNewBytesValue(383);
    Serial.print("setNewBytesValue(383): ");
    to_bytes = pcf.getBytesValueAsBytes();
    Serial.println(to_bytes[0]);
    Serial.println(to_bytes[1]);
    delay(500);

    to_bytes[0] = 128;
    to_bytes[1] = 1;
    pcf.setNewBytesValue(to_bytes);
    Serial.print("setNewBytesValue(to_bytes): ");
    Serial.println(pcf.getBytesValueAsInt());
    delay(500);

    pcf.setNewRightByteValue(0);
    Serial.print("setNewRightByteValue(0): ");
    Serial.println(pcf.getBytesValueAsInt());
    delay(500);

    pcf.setNewLeftByteValue(1);
    Serial.print("setNewLeftByteValue(1): ");
    Serial.println(pcf.getBytesValueAsInt());
    delay(500);

    pcf.setLeftBitDown(0);
    Serial.print("setLeftBitDown(0): ");
    Serial.println(pcf.getBytesValueAsInt());
    delay(500);

    pcf.setRightBitUp(0);
    Serial.print("setRightBitUp(0): ");
    Serial.println(pcf.getBytesValueAsInt());
    delay(500);

    //gets
    Serial.println("getBitValue(0)");
    Serial.println(pcf.getBitValue(0));

    pcf.setNewBytesValue(383);
    Serial.print("[383] getLeftBitValue(0): ");
    Serial.println(pcf.getLeftBitValue(0));
    delay(500);

    Serial.print("[383] getRightByteValue()");
    Serial.println(pcf.getRightByteValue());
}

void loop(){

}
