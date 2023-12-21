/** Project CPP includes */
#include "TLx493D_inc.hpp"

/** Definition of the sensor object with the default address of the sensor.
 *  If you want to use any other sensor variant, just comment the active line
 *  and uncomment the desired sensor type.
 */
// TLx493D_A1B6 dut(Wire, TLx493D_IIC_ADDR_A0_e);

TLx493D_A2B6 dut(Wire, TLx493D_IIC_ADDR_A0_e);
// TLx493D_P2B6 dut(Wire, TLx493D_IIC_ADDR_A0_e);
// TLx493D_W2B6 dut(Wire, TLx493D_IIC_ADDR_A0_e);
// TLx493D_W2BW dut(Wire, TLx493D_IIC_ADDR_A0_e);

// TLx493D_P3B6 dut(Wire, TLx493D_IIC_ADDR_A0_e);
// TLx493D_P3B6 dut(Wire, TLx493D_IIC_ADDR_A1_e);


void setup() {
    delay(3000);
    Serial.begin(115200);

    /** Definition of the power pin to power up the sensor. */
    dut.setPowerPin(LED2, OUTPUT, HIGH, LOW, 50, 50);
    dut.begin();

    Serial.print("setup done.\n");
}

/** In the loop we continuously reading the temperature value as well as the
 *  magnetic values in X, Y, Z-direction of the sensor and printing them to
 *  the serial monitor
 */
void loop() {
    double temp = 0.0;
    double valX = 0, valY = 0, valZ = 0;

    Serial.print(true == dut.getTemperature(&temp) ? "getTemperature ok\n" : "getTemperature error\n");

    Serial.print("Temperature is: ");
    Serial.print(temp);
    Serial.println("°C");

    Serial.print(true == dut.getMagneticField(&valX, &valY, &valZ) ? "getMagneticField ok\n" : "getMagneticField error\n");

    Serial.print("Value X is: ");
    Serial.print(valX);
    Serial.println(" mT");
    Serial.print("Value Y is: ");
    Serial.print(valY);
    Serial.println(" mT");
    Serial.print("Value Z is: ");
    Serial.print(valZ);
    Serial.println(" mT");

    printRegisters(dut.getSensor());
    Serial.print("\n");

    delay(1000);
}