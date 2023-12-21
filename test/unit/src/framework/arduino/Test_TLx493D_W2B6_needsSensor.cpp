// test includes
#include "Test_includes.hpp"


extern "C" {
    // project includes
    #include "Test_TLx493D_W2B6_needsSensor.h"
    #include "Test_tlx493d_commonFunctions_needsSensor.h"


    // Method invoked by Unity before a test suite is run 
    void TLx493D_W2B6_needsSensor_suiteSetup() {
        // deinit in TEAR_DOWN will cut communication link, so if deinit is called communication must be reinitialized !
        (void) TLx493D_W2B6_init(&dut);
        tlx493d_initCommunication(&dut, Wire, TLx493D_IIC_ADDR_A0_e);
        dut.functions->setDefaultConfig(&dut);
    }
    
    
    // Method invoked by Unity after a test suite is run 
    void TLx493D_W2B6_needsSensor_suiteTearDown() {
        // If deinitializing here make sure to reinit in 'TEST_SETUP' or communication will be lost !
        dut.functions->deinit(&dut);
    }
}
