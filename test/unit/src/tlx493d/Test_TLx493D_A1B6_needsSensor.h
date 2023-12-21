// test includes
#include "Test_includes.h"


void TLx493D_A1B6_needsSensor_suiteSetup(void);
void TLx493D_A1B6_needsSensor_suiteTearDown(void);
void TLx493D_A1B6_atReset_suiteSetup(void);
void TLx493D_A1B6_atReset_suiteTearDown(void);


// variables used in the tests below that have to be accessed in the setup and tear down methods
static TLx493D_t dut;


#include "Test_tlx493d_commonFunctions_needsSensor.h"
#include "Test_tlx493d_common_needsSensor.h"
#include "Test_tlx493d_common.h"


// define test group name
TEST_GROUP(TLx493D_A1B6_needsSensor);


// Setup method called before every individual test defined for this test group
TEST_SETUP(TLx493D_A1B6_needsSensor)
{
}


// Tear down method called before every individual test defined for this test group
TEST_TEAR_DOWN(TLx493D_A1B6_needsSensor)
{
}


TEST(TLx493D_A1B6_needsSensor, readRegisters)
{
    TEST_ASSERT_EQUAL( true, TLx493D_A1B6_readRegisters(&dut) );
}

TEST(TLx493D_A1B6_needsSensor, getTemperature)
{
    double temperature = 0.0;

    TEST_ASSERT_EQUAL( true, dut.functions->getTemperature(&dut, &temperature));
    TEST_ASSERT_FLOAT_WITHIN( 8.0, 25.0, temperature ); // Environmental temp is around 20 - 30 deg C
}

TEST(TLx493D_A1B6_needsSensor, getMagneticField)
{
    double x = 0.0, y = 0.0, z = 0.0;

    TEST_ASSERT_EQUAL( true, dut.functions->getMagneticField(&dut, &x, &y, &z) );
    TEST_ASSERT_FLOAT_WITHIN( 1.0, 0.0, x ); // Residual mag field stays within 0-1 mT
    TEST_ASSERT_FLOAT_WITHIN( 1.0, 0.0, y );
    TEST_ASSERT_FLOAT_WITHIN( 1.0, 0.0, z );
}

/**
 * Define tests for supported common functionality.
 * Requires that the registers have been read once, in setDefaultConfig.
 */

TEST(TLx493D_A1B6_needsSensor, checkSupportedFunctionality)
{
    TEST_ASSERT( dut.functions->readRegisters(&dut) == true );
    TEST_ASSERT( dut.functions->isFunctional(&dut) == true );
    TEST_ASSERT( dut.functions->hasValidFuseParity(&dut) == true );
    TEST_ASSERT( dut.functions->hasValidTBit(&dut) == true );
}

// define test group name
TEST_GROUP(TLx493D_A1B6_TempDisable);

// Setup method called before every individual test defined for this test group
TEST_SETUP(TLx493D_A1B6_TempDisable)
{
    dut.functions->setMeasurement(&dut, TLx493D_BxByBz_e);
}


// Tear down method called before every individual test defined for this test group
TEST_TEAR_DOWN(TLx493D_A1B6_TempDisable)
{
    dut.functions->setMeasurement(&dut, TLx493D_BxByBzTemp_e);
}

TEST(TLx493D_A1B6_TempDisable, TempDisable)
{
    // CH cannot be 0b11 when temperature measurement is disabled
    TEST_ASSERT_NOT_EQUAL ( 0x3, ( dut.regMap[A1B6_CH_e] & dut.regDef[A1B6_CH_e].mask) >> dut.regDef[A1B6_CH_e].offset );
    
    double temperature = 0.0;
    TEST_ASSERT_EQUAL( true, dut.functions->getTemperature(&dut, &temperature));
    
    // When temperature measurement is disabled in runtime, the last measured value remains in the register
    // sample 50 values of temperature after temp disable and check if they are equal to the value measured above.
    double temp_sum = 0.0;

    for(uint8_t i=0; i<50; i++)
    {
        double temp_temp = 0.0;
        dut.functions->getTemperature(&dut, &temp_temp);
        temp_sum += temp_temp;
    }

    TEST_ASSERT_EQUAL_FLOAT(temp_sum/50, temperature);
}

// define test group name
TEST_GROUP(TLx493D_A1B6_ParityCheck);

// Setup method called before every individual test defined for this test group
TEST_SETUP(TLx493D_A1B6_ParityCheck)
{
}


// Tear down method called before every individual test defined for this test group
TEST_TEAR_DOWN(TLx493D_A1B6_ParityCheck)
{
}

TEST(TLx493D_A1B6_ParityCheck, SetWrongParity_ParityCheckDisabled)
{
    // first, disable Parity check.
    TEST_ASSERT_EQUAL( true, TLx493D_A1B6_disableParityTest(&dut) );
    
    // here, changine a Write Register bitField and not recalculating parity and not setting
    // it in the bitField.P, should give an error
    TLx493D_A1B6_setBitfield(&dut, A1B6_Temp_NEN_e, 1);
    TEST_ASSERT_EQUAL( true, TLx493D_A1B6_transferWriteRegisters(&dut));

    // the readRegisters() throws NO error due to wrong parity
    TEST_ASSERT_EQUAL( true, dut.functions->readRegisters(&dut) );
    
    // enable partity check at the end, to restore default state for other tests
    TEST_ASSERT_EQUAL( true, TLx493D_A1B6_enableParityTest(&dut) );
}


// define test group name
TEST_GROUP(TLx493D_A1B6_atReset);

// Setup method called before every individual test defined for this test group
TEST_SETUP(TLx493D_A1B6_atReset)
{
    dut.functions->readRegisters(&dut);
}


// Tear down method called before every individual test defined for this test group
TEST_TEAR_DOWN(TLx493D_A1B6_atReset)
{
}

TEST(TLx493D_A1B6_atReset, regMapatReset_MeasurementBitfields)
{
    TEST_ASSERT_EQUAL_UINT8 ( 0x00, ( dut.regMap[A1B6_BX_MSB_e] & dut.regDef[A1B6_BX_MSB_e].mask) >> dut.regDef[A1B6_BX_MSB_e].offset  );
    TEST_ASSERT_EQUAL_UINT8 ( 0x00, ( dut.regMap[A1B6_BY_MSB_e] & dut.regDef[A1B6_BY_MSB_e].mask) >> dut.regDef[A1B6_BY_MSB_e].offset  );
    TEST_ASSERT_EQUAL_UINT8 ( 0x00, ( dut.regMap[A1B6_BZ_MSB_e] & dut.regDef[A1B6_BZ_MSB_e].mask) >> dut.regDef[A1B6_BZ_MSB_e].offset  );
    TEST_ASSERT_EQUAL_UINT8 ( 0x01, ( dut.regMap[A1B6_TEMP_MSB_e] & dut.regDef[A1B6_TEMP_MSB_e].mask) >> dut.regDef[A1B6_TEMP_MSB_e].offset );
    
    TEST_ASSERT_EQUAL_UINT8 ( 0x5, ( dut.regMap[A1B6_BX_LSB_e] & dut.regDef[A1B6_BX_LSB_e].mask) >> dut.regDef[A1B6_BX_LSB_e].offset );
    TEST_ASSERT_EQUAL_UINT8 ( 0x3, ( dut.regMap[A1B6_BY_LSB_e] & dut.regDef[A1B6_BY_LSB_e].mask) >> dut.regDef[A1B6_BY_LSB_e].offset );

    TEST_ASSERT_EQUAL_UINT8 ( 0x3 , ( dut.regMap[A1B6_BZ_LSB_e] & dut.regDef[A1B6_BZ_LSB_e].mask) >> dut.regDef[A1B6_BZ_LSB_e].offset );
    TEST_ASSERT_EQUAL_UINT8 ( 0x0 , ( dut.regMap[A1B6_TEMP_LSB_e] & dut.regDef[A1B6_TEMP_LSB_e].mask) >> dut.regDef[A1B6_TEMP_LSB_e].offset );
}

TEST(TLx493D_A1B6_atReset, regMapatReset_nonMeasurementBitfields)
{
    TEST_ASSERT_EQUAL_UINT8  ( 0x0, ( dut.regMap[A1B6_FRM_e] & dut.regDef[A1B6_FRM_e].mask) >> dut.regDef[A1B6_FRM_e].offset );
    TEST_ASSERT_UINT8_WITHIN ( 0x3, 0x0, ( dut.regMap[A1B6_CH_e] & dut.regDef[A1B6_CH_e].mask) >> dut.regDef[A1B6_CH_e].offset );
    TEST_ASSERT_EQUAL_UINT8  ( 0x0, ( dut.regMap[A1B6_T_e] & dut.regDef[A1B6_T_e].mask) >> dut.regDef[A1B6_T_e].offset );
    TEST_ASSERT_EQUAL_UINT8  ( 0x1, ( dut.regMap[A1B6_FF_e] & dut.regDef[A1B6_FF_e].mask) >> dut.regDef[A1B6_FF_e].offset );
    TEST_ASSERT_EQUAL_UINT8  ( 0x0, ( dut.regMap[A1B6_PD_e] & dut.regDef[A1B6_PD_e].mask) >> dut.regDef[A1B6_PD_e].offset );
}

// Bundle all tests to be executed for this test group
TEST_GROUP_RUNNER(TLx493D_A1B6_needsSensor)
{
    TLx493D_A1B6_needsSensor_suiteSetup();

    RUN_TEST_CASE(TLx493D_A1B6_needsSensor, readRegisters);
    RUN_TEST_CASE(TLx493D_A1B6_needsSensor, getTemperature);
    RUN_TEST_CASE(TLx493D_A1B6_needsSensor, getMagneticField);
    RUN_TEST_CASE(TLx493D_A1B6_needsSensor, checkSupportedFunctionality);

    RUN_TEST_CASE(TLx493D_A1B6_TempDisable, TempDisable);
    RUN_TEST_CASE(TLx493D_A1B6_ParityCheck, SetWrongParity_ParityCheckDisabled);
    
    
    // run common functions tests
    RUN_TEST_GROUP(SensorsCommonFunctions);

    // run gen 1 common functions tests
    RUN_TEST_GROUP(SensorsCommon_needsSensor);
    RUN_TEST_GROUP(SensorsCommon);
    

    // This test is run at the end since the sensor cannot recover from a wrong parity error without hard reset
    // So tests will fail in the loop second time onwards. First time everything will pass. 
    //RUN_TEST_CASE(TLx493D_A1B6_ParityCheck, SetWrongParity_ParityCheckEnabled);
    TLx493D_A1B6_needsSensor_suiteTearDown();

    TLx493D_A1B6_atReset_suiteSetup();

    // This test is commented out since we dont check measurement bitfields (BX,BY,BZ,TEMP) at reset.
    //RUN_TEST_CASE(TLx493D_A1B6_atReset, regMapatReset_MeasurementBitfields);
    RUN_TEST_CASE(TLx493D_A1B6_atReset, regMapatReset_nonMeasurementBitfields);

    TLx493D_A1B6_atReset_suiteTearDown();

}
