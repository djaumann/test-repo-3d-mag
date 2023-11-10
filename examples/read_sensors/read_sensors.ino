
// std includes

// Arduino includes
// #include <Arduino.h>

// project cpp includes
#include "TLx493D.h"

// #include "arduino_defines.h"
// #include "TLx493D.hpp"
// #include "S2GoTemplateArduino.hpp"
// #include "SPI_Lib.hpp"
// #include "TwoWire_Lib.hpp"
// #include "Logger.h"


// SPI chip
#define POWER_PIN_LOW 3


// extern "C" {
//     #include "tlx493d_types.h"
//     // #include "tlx493d_gen_2_common_defines.h"
//     // #include "tlx493d_gen_2_common.h"
//     // #include "tlx493d_gen_3_common_defines.h"
//     // #include "tlx493d_gen_3_common.h"
//     // #include "tlx493d_common.h"

//     #include "TLx493D_A1B6.h"

//     #include "TLx493D_A2B6.h"
//     #include "TLx493D_P2B6.h"
//     #include "TLx493D_W2B6.h"
//     #include "TLx493D_W2BW.h"

//     #include "TLx493D_P3B6.h"
//     #include "TLx493D_P3I8.h"

//     #include "Logger.h"
// }


// TLx493D_A1B6 dut(Wire);

TLx493D_A2B6 dut(Wire);
// TLx493D_P2B6 dut(Wire);
// TLx493D_W2B6 dut(Wire);
// TLx493D_W2BW dut(Wire);

// TLx493D_P3B6 dut(Wire);
// TLx493D_P3I8 dut(Wire);


TLx493D_A1B6 a1b6(Wire);

TLx493D_A2B6 a2b6(Wire);
TLx493D_P2B6 p2b6(Wire);
TLx493D_W2B6 w2b6(Wire);
TLx493D_W2BW w2bw(Wire);

TLx493D_P3B6 p3b6(Wire);
TLx493D_P3I8 p3i8(SPI);


void setup() {
    pinMode(POWER_PIN_LOW, OUTPUT);
    digitalWrite(POWER_PIN_LOW, HIGH);

    delay(3000);
    Serial.begin(115200);
    delay(100);

    dut.begin();

    // a1b6.begin();
    a2b6.begin();
    // p2b6.begin();
    w2b6.begin();
    // w2bw.begin();
    // p3b6.begin();
    // p3i8.begin();

    delay(100);
    Serial.print("setup done.\n");
}

void loop() {
    double temp = 0.0;
    double valX = 0, valY = 0, valZ = 0;

    digitalWrite(POWER_PIN_LOW, LOW);
    Serial.print(true == dut.getTemperature(&temp) ? "getTemperature ok\n" : "getTemperature error\n");
    digitalWrite(POWER_PIN_LOW, HIGH);

    Serial.print("Temperature is: ");
    Serial.print(temp);
    Serial.println("°C");

    digitalWrite(POWER_PIN_LOW, LOW);
    Serial.print(true == dut.getMagneticField(&valX, &valY, &valZ) ? "getMagneticField ok\n" : "getMagneticField error\n");
    digitalWrite(POWER_PIN_LOW, HIGH);

    Serial.print("Value X is: ");
    Serial.print(valX);
    Serial.println(" mT");
    Serial.print("Value Y is: ");
    Serial.print(valY);
    Serial.println(" mT");
    Serial.print("Value Z is: ");
    Serial.print(valZ);
    Serial.println(" mT");

    printRegisters(dut.getRegisterMap(), dut.getRegisterMapSize());
    Serial.print("\n");

    delay(1000);
}
