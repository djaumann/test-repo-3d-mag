// test includes
#include "Test_includes.hpp"


#define POWER_PIN LED2 // 15


extern "C" {
    /***
      * Uses flags / defines to determine which groups of tests should be added to this test such that multiple tests can be executed in a single run.
      * Use the '--build-property option of the 'arduino_compile' target to add the flags by defining the respective targets in the makefile.
      * makefile : --build-property "compiler.cpp.extra_flags=\"-D<TEST_SPECIFIER>=1\"" build
    */
    void RunAllTests(void)
    {

// TLx493D_A1B6
#ifdef TEST_TLx493D_A1B6

    RUN_TEST_GROUP(TLx493D_A1B6);

#endif

#ifdef TEST_TLx493D_A1B6_NEEDS_SENSOR

    RUN_TEST_GROUP(TLx493D_A1B6_needsSensor);

#endif


// TLx493D_A2B6
#ifdef TEST_TLx493D_A2B6

    RUN_TEST_GROUP(TLx493D_A2B6);

#endif

#ifdef TEST_TLx493D_A2B6_NEEDS_SENSOR

    RUN_TEST_GROUP(TLx493D_A2B6_needsSensor);

#endif


// TLx493D_P2B6
#ifdef TEST_TLx493D_P2B6

    RUN_TEST_GROUP(TLx493D_P2B6);

#endif

#ifdef TEST_TLx493D_P2B6_NEEDS_SENSOR

    RUN_TEST_GROUP(TLx493D_P2B6_needsSensor);

#endif


// TLx493D_W2B6
#ifdef TEST_TLx493D_W2B6

    RUN_TEST_GROUP(TLx493D_W2B6);

#endif

#ifdef TEST_TLx493D_W2B6_NEEDS_SENSOR

    RUN_TEST_GROUP(TLx493D_W2B6_needsSensor);

#endif


// TLx493D_W2BW
#ifdef TEST_TLx493D_W2BW

    RUN_TEST_GROUP(TLx493D_W2BW);

#endif

#ifdef TEST_TLx493D_W2BW_NEEDS_SENSOR

    RUN_TEST_GROUP(TLx493D_W2BW_needsSensor);

#endif

    }
}


/***
 * 
*/
void setup() {
    Serial.begin(115200);
    delay(3000);

    // required for S2Go
    pinMode(POWER_PIN, OUTPUT);
    digitalWrite(POWER_PIN, HIGH);

    delay(500);
    Serial.print("setup done.\n");
}


/***
 *
*/
void loop() {
    Serial.println("\n");

    int         argc       = 2;
    const char *argv[argc] = { "", "-v" };

    (void) UnityMain(argc, argv, RunAllTests);
    delay(3000);
}