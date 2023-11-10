/**
 * @file        TLV493D_P3I8.c
 * @author      Infineon Technologies AG
 * @brief       Contains the implementation of the complete sensor functionality
 * @copyright   Copyright (c) 2023
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// project c includes
// common to all sensors
#include "tlx493d_types.h"
#include "tlx493d_common_defines.h"
#include "tlx493d_common.h"

// common to same generation of sensors
#include "tlx493d_gen_3_common_defines.h"
#include "tlx493d_gen_3_common.h"

// sensor specific includes
#include "TLx493D_P3I8_defines.h"
#include "TLx493D_P3I8.h"


/*
  Listing of all register names for this sensor.
  Used to index "TLx493D_P3I8_regDef" defined below, so index values must match !
*/
typedef enum {
               BX_MSBS = 0,
               BX_LSBS,
               BY_MSBS,
               BY_LSBS,
               BZ_MSBS,
               BZ_LSBS,
               TEMP_MSBS,
               TEMP_LSBS,
               CRC,
               MEAS_FLG,
               TEST_FLG,
               FRAME_COUNTER,
               RST_FLG,
               WU_PAR_FLG,
               CRC_WR_FLG,
               FUSE_PAR_FLG,
               MODE_SEL,
               INT_DIS,
               WU_EN,
               TRIGGER_SEL,
               CRC_WR_EN,
               CHANNEL_SEL,
               F_UPDATE_SEL,
               XTR_SHORT_EN,
               SHORT_EN,
               WU_XH_MSBS,
               WU_XL_MSBS,
               WU_YH_MSBS,
               WU_YL_MSBS,
               WU_ZH_MSBS,
               WU_ZL_MSBS,
               WU_XH_LSBS,
               WU_XL_LSBS,
               WU_YH_LSBS,
               WU_YL_LSBS,
               WU_PAR,
               WU_EN_CP,
               WU_ZH_LSBS,
               WU_ZL_LSBS,
               RST_FLG_CLR,
               SOFT_RST,
               CHIP_ID_0,
               CHIP_ID_1,
               CHIP_ID_2,
               CHIP_ID_3,
               CHIP_ID_4,
               ID_PAR,
               CHIP_ID_5 } TLx493D_P3I8_registerNames_te;


TLx493D_Register_ts TLx493D_P3I8_regDef[] = {
    { BX_MSBS,       TLx493D_READ_MODE_e,       0x00, 0xFF, 0, 8 },
    { BX_LSBS,       TLx493D_READ_MODE_e,       0x01, 0x3F, 0, 6 },
    { BY_MSBS,       TLx493D_READ_MODE_e,       0x02, 0xFF, 0, 8 },
    { BY_LSBS,       TLx493D_READ_MODE_e,       0x03, 0x3F, 0, 6 },
    { BZ_MSBS,       TLx493D_READ_MODE_e,       0x04, 0xFF, 0, 8 },
    { BZ_LSBS,       TLx493D_READ_MODE_e,       0x05, 0x3F, 0, 6 },
    { TEMP_MSBS,     TLx493D_READ_MODE_e,       0x06, 0xFF, 0, 8 },
    { TEMP_LSBS,     TLx493D_READ_MODE_e,       0x07, 0x3F, 0, 6 },
    { CRC,           TLx493D_READ_MODE_e,       0x08, 0xFF, 0, 8 },
    { MEAS_FLG,      TLx493D_READ_MODE_e,       0x09, 0x80, 7, 1 },
    { TEST_FLG,      TLx493D_READ_MODE_e,       0x09, 0x40, 6, 1 },
    { FRAME_COUNTER, TLx493D_READ_MODE_e,       0x09, 0x30, 4, 2 },
    { RST_FLG,       TLx493D_READ_MODE_e,       0x09, 0x08, 3, 1 },
    { WU_PAR_FLG,    TLx493D_READ_MODE_e,       0x09, 0x04, 2, 1 },
    { CRC_WR_FLG,    TLx493D_READ_MODE_e,       0x09, 0x02, 1, 1 },
    { FUSE_PAR_FLG,  TLx493D_READ_MODE_e,       0x09, 0x01, 0, 1 },
    { MODE_SEL,      TLx493D_READ_WRITE_MODE_e, 0x0A, 0x80, 7, 1 },
    { INT_DIS,       TLx493D_READ_WRITE_MODE_e, 0x0A, 0x40, 6, 1 },
    { WU_EN,         TLx493D_READ_WRITE_MODE_e, 0x0A, 0x10, 4, 1 },
    { TRIGGER_SEL,   TLx493D_READ_WRITE_MODE_e, 0x0A, 0x0C, 2, 2 },
    { CRC_WR_EN,     TLx493D_READ_WRITE_MODE_e, 0x0A, 0x01, 0, 1 },
    { CHANNEL_SEL,   TLx493D_READ_WRITE_MODE_e, 0x0B, 0xF0, 4, 4 },
    { F_UPDATE_SEL,  TLx493D_READ_WRITE_MODE_e, 0x0B, 0x0C, 2, 2 },
    { XTR_SHORT_EN,  TLx493D_READ_WRITE_MODE_e, 0x0B, 0x02, 1, 1 },
    { SHORT_EN,      TLx493D_READ_WRITE_MODE_e, 0x0B, 0x01, 0, 1 },
    { WU_XH_MSBS,    TLx493D_READ_WRITE_MODE_e, 0x0C, 0xFF, 0, 8 },
    { WU_XL_MSBS,    TLx493D_READ_WRITE_MODE_e, 0x0D, 0xFF, 0, 8 },
    { WU_YH_MSBS,    TLx493D_READ_WRITE_MODE_e, 0x0E, 0xFF, 0, 8 },
    { WU_YL_MSBS,    TLx493D_READ_WRITE_MODE_e, 0x0F, 0xFF, 0, 8 },
    { WU_ZH_MSBS,    TLx493D_READ_WRITE_MODE_e, 0x10, 0xFF, 0, 8 },
    { WU_ZL_MSBS,    TLx493D_READ_WRITE_MODE_e, 0x11, 0xFF, 0, 8 },
    { WU_XH_LSBS,    TLx493D_READ_WRITE_MODE_e, 0x12, 0xC0, 6, 2 },
    { WU_XL_LSBS,    TLx493D_READ_WRITE_MODE_e, 0x12, 0x30, 4, 2 },
    { WU_YH_LSBS,    TLx493D_READ_WRITE_MODE_e, 0x12, 0x0C, 2, 2 },
    { WU_YL_LSBS,    TLx493D_READ_WRITE_MODE_e, 0x12, 0x03, 0, 2 },
    { WU_PAR,        TLx493D_READ_WRITE_MODE_e, 0x13, 0x20, 5, 1 },
    { WU_EN_CP,      TLx493D_WRITE_MODE_e,      0x13, 0x10, 4, 1 },
    { WU_ZH_LSBS,    TLx493D_READ_WRITE_MODE_e, 0x13, 0x0C, 2, 2 },
    { WU_ZL_LSBS,    TLx493D_READ_WRITE_MODE_e, 0x13, 0x03, 0, 2 },
    { RST_FLG_CLR,   TLx493D_WRITE_MODE_e,      0x14, 0x02, 1, 1 },
    { SOFT_RST,      TLx493D_WRITE_MODE_e,      0x14, 0x01, 0, 1 },
    { CHIP_ID_0,     TLx493D_READ_MODE_e,       0x15, 0xFF, 0, 8 },
    { CHIP_ID_1,     TLx493D_READ_MODE_e,       0x16, 0xFF, 0, 8 },
    { CHIP_ID_2,     TLx493D_READ_MODE_e,       0x17, 0xFF, 0, 8 },
    { CHIP_ID_3,     TLx493D_READ_MODE_e,       0x18, 0xFF, 0, 8 },
    { CHIP_ID_4,     TLx493D_READ_MODE_e,       0x19, 0xFF, 0, 8 },
    { ID_PAR,        TLx493D_READ_MODE_e,       0x1A, 0x40, 6, 1},
    { CHIP_ID_5,     TLx493D_READ_MODE_e,       0x1A, 0x3F, 0, 6 }
};


/***
 * 
*/
// typedef enum {
//                LOW_POWER_MODE         = 0x00,
//                MASTER_CONTROLLED_MODE = 0x01,
//                RESERVED_MODE          = 0x10,
//                FAST_MODE              = 0x11 } TLx493D_P3I8_modes_te;


/***
 * 
*/
// typedef enum { 
//                TEMP2_REG  = 0x05,
//                DIAG_REG   = 0x06,
//                CONFIG_REG = 0x10,
//                MOD1_REG   = 0x11,
//                MOD2_REG   = 0x13,
//                VER_REG    = 0x16 } SpecialRegisters_te;


TLx493D_CommonFunctions_ts TLx493D_P3I8_commonFunctions = {
                                .init                 = TLx493D_P3I8_init,
                                .deinit               = TLx493D_P3I8_deinit,

                                // .getTemperature       = TLx493D_P3I8_getTemperature,

                                .calculateMagneticField = TLx493D_P3I8_calculateMagneticField,
                                // .getFieldValues       = TLx493D_P3I8_getFieldValues,

                                .setDefaultConfig     = TLx493D_P3I8_setDefaultConfig,
                                .readRegisters        = tlx493d_gen_3_readRegistersSPI,
};


/***
 * TODO: add parameter IICAddress or ad function to set address.
*/
bool TLx493D_P3I8_init(TLx493D_ts *sensor) {
    sensor->regMap            = (uint8_t*) malloc(sizeof(uint8_t) * GEN_3_REG_MAP_SIZE);
    sensor->regDef            = TLx493D_P3I8_regDef;
    sensor->functions         = &TLx493D_P3I8_commonFunctions;
    sensor->regMapSize        = GEN_3_REG_MAP_SIZE;
    sensor->sensorType        = TLx493D_P3I8_e;
    sensor->comIFType         = TLx493D_SPI_e;
    sensor->comLibIF          = NULL;
    sensor->comLibObj.spi_obj = NULL;

    memset(sensor->regMap, 0, sensor->regMapSize);
   
    return true;
}


/***
 * 
*/
bool TLx493D_P3I8_deinit(TLx493D_ts *sensor) {
    free(sensor->regMap);
    free(sensor->comLibObj.spi_obj);

    sensor->regMap            = NULL;
    sensor->comLibObj.spi_obj = NULL;
    return true;
}


/***
 * 
*/
void TLx493D_P3I8_calculateRawTemperature(TLx493D_ts *sensor, double *temp) {
    int16_t value = 0;

    tlx493d_common_concatBytes(sensor, TEMP_MSBS, TEMP_LSBS, &value);
    *temp = (double) value;
}


/***
 * 
*/
void TLx493D_P3I8_calculateTemperature(TLx493D_ts *sensor, double *temp) {
    int16_t value = 0;

    tlx493d_common_concatBytes(sensor, TEMP_MSBS, TEMP_LSBS, &value);
    *temp = (((double) value - GEN_3_TEMP_OFFSET) / GEN_3_TEMP_MULT) + GEN_3_TEMP_REF;
}


/***
 * 
*/
bool TLx493D_P3I8_getTemperature(TLx493D_ts *sensor, double *temp) {
    if( tlx493d_gen_3_readRegistersSPI(sensor) ) {
        TLx493D_P3I8_calculateTemperature(sensor, temp);
        return true;
    }

    return false;
}


/***
 * 
*/
void TLx493D_P3I8_calculateMagneticField(TLx493D_ts *sensor, double *x, double *y, double *z) {
    int16_t valueX = 0, valueY = 0, valueZ = 0;

    tlx493d_common_concatBytes(sensor, BX_MSBS, BX_LSBS, &valueX);
    tlx493d_common_concatBytes(sensor, BY_MSBS, BY_LSBS, &valueY);
    tlx493d_common_concatBytes(sensor, BZ_MSBS, BZ_LSBS, &valueZ);

// TODO: temp unten in LSB format; x,y,z dann auch in LSB format => mittels sensitivity umrechnen in mT !
// TODO: TLx493D_P3I8_calculateTemperatureRaw hinzufügen um die LSB Werte für Temp zu bekommen !
double r    = 1.0; // TODO: r is range specific !
// double temp = 0.0;
double temp = 0.0;
double sensitivity = GEN_3_FULL_RANGE_FIELD_SENSITIVITY;  // TODO: r is range specific !
    
    TLx493D_P3I8_calculateRawTemperature(sensor, &temp);

    *x = (r * (GEN_3_O0x + temp * (GEN_3_O1x + temp * (GEN_3_O2x + GEN_3_O3x * temp)))
          + ((double) valueX) * (GEN_3_L0x + temp * (GEN_3_L1x + temp * (GEN_3_L2x + GEN_3_L3x * temp))))
       / sensitivity;

    *y = (r * (GEN_3_O0y + temp * (GEN_3_O1y + temp * (GEN_3_O2y + GEN_3_O3y * temp)))
          + ((double) valueY) * (GEN_3_L0y + temp * (GEN_3_L1y + temp * (GEN_3_L2y + GEN_3_L3y * temp))))
       / sensitivity;

    *z = (r * (GEN_3_O0z + temp * (GEN_3_O1z + temp * (GEN_3_O2z + GEN_3_O3z * temp)))
          + ((double) valueZ) * (GEN_3_L0z + temp * (GEN_3_L1z + temp * (GEN_3_L2z + GEN_3_L3z * temp))))
       / sensitivity;
}


/***
 * 
*/
bool TLx493D_P3I8_getMagneticField(TLx493D_ts *sensor, double *x, double *y, double *z) {
    if( tlx493d_gen_3_readRegistersSPI(sensor) ) {
        TLx493D_P3I8_calculateMagneticField(sensor, x, y, z);
        return true;
    }

    return false;
}


/***
 * TODO: set all options that must be set, eg MODE ?, reset all bits to defaults ?
*/
bool TLx493D_P3I8_setDefaultConfig(TLx493D_ts *sensor) {
    sensor->regMap[0x0A] = 0x02; // Bit 1 is set to constant 1 !

    tlx493d_common_setBitfield(sensor, MODE_SEL, 0);
    tlx493d_common_setBitfield(sensor, INT_DIS, 1);
    tlx493d_common_setBitfield(sensor, WU_EN, 0);
    tlx493d_common_setBitfield(sensor, CRC_WR_EN, 0);

    tlx493d_common_writeRegister(sensor, MODE_SEL);

    // Read registers in order to retrieve values in reserved register at 0x12 and in MOD2 in order to make sure we are not 
    // accidentally changing a preset values to 0.
    // if( tlx493d_gen_3_readRegistersSPI(sensor) )
    //     return TLx493D_P3I8_setLowUpdateRate(sensor);
 
    // tlx493d_common_setBitfield(sensor, CHANNEL_SEL, 0);

    return true;
}
