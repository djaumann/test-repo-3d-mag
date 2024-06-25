
.. _program_listing_file_src_tlx493d_types.h:

Program Listing for File tlx493d_types.h
========================================

|exhale_lsh| :ref:`Return to documentation for file <file_src_tlx493d_types.h>` (``src\tlx493d_types.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #ifndef TLX493D_TYPES_H
   #define TLX493D_TYPES_H
   
   
   #include <stdbool.h>
   #include <stdint.h>
   
   #include "pal.h"
   
   #ifdef __cplusplus
   
   extern "C" {
   
   #endif
   
   
   typedef enum {
                  TLx493D_A1B6_e = 0,
                  TLx493D_A2B6_e,
                  TLx493D_P2B6_e,
                  TLx493D_W2B6_e,
                  TLx493D_W2BW_e,
                  TLx493D_P3B6_e,
                  TLx493D_P3I8_e,
   } TLx493D_SupportedSensorType_t;
   
   
   typedef enum {
                  TLx493D_I2C_e = 0,
                  TLx493D_SPI_e,
   } TLx493D_SupportedComLibraryInterfaceType_t;
   
   
   typedef enum { TLx493D_READ_MODE_e = 0, 
                  TLx493D_WRITE_MODE_e,
                  TLx493D_READ_WRITE_MODE_e,
   } TLx493D_RegisterAccessModeType_t;
   
   
   typedef enum {
       TLx493D_IIC_ADDR_A0_e = 0,
       TLx493D_IIC_ADDR_A1_e,
       TLx493D_IIC_ADDR_A2_e,
       TLx493D_IIC_ADDR_A3_e,
       TLx493D_IIC_ADDR_A4_e,
       TLx493D_IIC_ADDR_A5_e,
       TLx493D_IIC_ADDR_A6_e,
       TLx493D_IIC_ADDR_A7_e,
   } TLx493D_IICAddressType_t;
   
   
   typedef enum {
       // 1st and 2nd generation
       TLx493D_BxByBz_e = 0,
       
       //  1st and 3rd generation
       TLx493D_BxByBzTemp_e,
   
       // 3rd generation
       TLx493D_VHall_Bias_e,
       TLx493D_Spintest_e,
       TLx493D_SAT_test_e,
       TLx493D_BxTemp_e,
       TLx493D_BxBy_e,
       TLx493D_BzTemp_e,
   } TLx493D_MeasurementType_t;
   
   
   typedef enum {
                  // 1st and 2nd gen.
                  TLx493D_NO_ADC_ON_READ_e = 0,
                  TLx493D_ADC_ON_READ_BEFORE_FIRST_MSB_e,
                  TLx493D_ADC_ON_READ_AFTER_REG_05_e,
   
                  // 3rd gen. only
                  TLx493D_NO_TRIGGER_e,
                  TLx493D_ADC_ON_READ_e,
                  TLx493D_ADC_ON_STOP_CONDITION_e,
   } TLx493D_TriggerType_t;
   
   
   typedef enum {
                  TLx493D_FULL_RANGE_e = 0, 
                  TLx493D_SHORT_RANGE_e,
                  TLx493D_EXTRA_SHORT_RANGE_e,
   } TLx493D_SensitivityType_t;
   
   
   typedef enum {
                  TLx493D_HAS_X1_e = 0, 
                  TLx493D_HAS_X2_e, 
                  TLx493D_HAS_X4_e,
   } TLx493D_AvailableSensitivityType_t;
   
   
   typedef enum {
                  TLx493D_POWER_DOWN_MODE_e = 0,
                  TLx493D_FAST_MODE_e,
                  TLx493D_LOW_POWER_MODE_e,
                  TLx493D_ULTRA_LOW_POWER_MODE_e,
                  TLx493D_MASTER_CONTROLLED_MODE_e,
   } TLx493D_PowerModeType_t;
   
   
   typedef enum {
                  // Generation 2
                  TLx493D_UPDATE_RATE_FAST_e = 0,
                  TLx493D_UPDATE_RATE_SLOW_e,
                  TLx493D_UPDATE_RATE_770_HZ_e,
                  TLx493D_UPDATE_RATE_97_HZ_e,
                  TLx493D_UPDATE_RATE_24_HZ_e,
                  TLx493D_UPDATE_RATE_12_HZ_e,
                  TLx493D_UPDATE_RATE_6_HZ_e,
                  TLx493D_UPDATE_RATE_3_HZ_e,
                  TLx493D_UPDATE_RATE_0_4_HZ_e,
                  TLx493D_UPDATE_RATE_0_05_HZ_e,
   
                  // Generation 3
                  TLx493D_UPDATE_RATE_1000_HZ_e,
                  TLx493D_UPDATE_RATE_125_HZ_e,
                  TLx493D_UPDATE_RATE_31_HZ_e,
                  TLx493D_UPDATE_RATE_16_HZ_e,
   } TLx493D_UpdateRateType_t;
   
   
   typedef struct TLx493D_Register_t {
       // uint8_t                           name;
       TLx493D_RegisterAccessModeType_t  accessMode;
       uint8_t                           address;
       uint8_t                           mask;
       uint8_t                           offset;
       uint8_t                           numBits;
   } TLx493D_Register_t;
   
   typedef bool (*TLx493D_OneParamsFuncPtr)(TLx493D_t *sensor);
   typedef void (*TLx493D_SetReadAddressFuncPtr)(TLx493D_t *sensor, uint8_t address);
   typedef bool (*TLx493D_TransferFuncPtr)(TLx493D_t *sensor, uint8_t *tx_buffer, uint8_t tx_len, uint8_t *rx_buffer, uint8_t rx_len);
   
   
   typedef struct TLx493D_SPIParameters_t {
       uint8_t dummy;
   } TLx493D_SPIParameters_t;
   
   
   typedef struct TLx493D_I2CParameters_t {
       uint8_t address;
   } TLx493D_I2CParameters_t;
   
   
   typedef struct TLx493D_ComLibraryFunctions_t {
       union {
           TLx493D_OneParamsFuncPtr  spi_init;
           TLx493D_OneParamsFuncPtr  iic_init;
       } init;
   
       union {
           TLx493D_OneParamsFuncPtr  spi_deinit;
           TLx493D_OneParamsFuncPtr  iic_deinit;
       } deinit;
   
       union {
           TLx493D_TransferFuncPtr  spi_transfer;
           TLx493D_TransferFuncPtr  iic_transfer;
       } transfer;
   
       union {
           TLx493D_SetReadAddressFuncPtr  spi_setReadAddress;
           TLx493D_SetReadAddressFuncPtr  iic_setReadAddress;
       } setReadAddress;
   } TLx493D_ComLibraryFunctions_t;
   
   
   typedef union TLx493D_ComLibraryParameters_t {
       TLx493D_SPIParameters_t  spi_params;
       TLx493D_I2CParameters_t  iic_params;
   } TLx493D_ComLibraryParameters_t;
   
   
   typedef union TLx493D_ComLibraryObject_t {
       TLx493D_SPIObject_t  *spi_obj;
       TLx493D_I2CObject_t  *iic_obj;
   } TLx493D_ComLibraryObject_t;
   
   
   typedef struct TLx493D_CommunicationInterface_t {
       TLx493D_ComLibraryFunctions_t   *comLibFuncs;
       TLx493D_ComLibraryParameters_t   comLibParams;
       TLx493D_ComLibraryObject_t       comLibObj;
   } TLx493D_CommunicationInterface_t;
   
   
   typedef union TLx493D_BoardSupportObject_t {
       TLx493D_Kit2GoBoardSupportObject_t  *k2go_obj;
   } TLx493D_BoardSupportObject_t;
   
   
   // TODO: Is this needed?
   typedef struct TLx493D_BoardSupportInterface_t {
       // TLx493D_BoardSupportFunctions_t   *boardSupportFuncs;
       // TLx493D_BoardSupportParameters_t   boardSupportParams;
       TLx493D_BoardSupportObject_t       boardSupportObj;
   } TLx493D_BoardSupportInterface_t;
   
   
   typedef bool (*TLx493D_InitFuncPtr)(TLx493D_t *);
   typedef bool (*TLx493D_DeinitFuncPtr)(TLx493D_t *);
   
   typedef bool (*TLx493D_ReadRegistersFuncPtr)(TLx493D_t *);
   typedef bool (*TLx493D_ReadRegistersAndCheckFuncPtr)(TLx493D_t *);
   
   typedef void (*TLx493D_CalculateRawTemperatureFuncPtr)(TLx493D_t *, int16_t *);
   typedef bool (*TLx493D_GetRawTemperatureFuncPtr)(TLx493D_t *, int16_t *);
   
   typedef void (*TLx493D_CalculateRawMagneticFieldFuncPtr)(TLx493D_t *, int16_t *, int16_t *, int16_t *);
   typedef bool (*TLx493D_GetRawMagneticFieldFuncPtr)(TLx493D_t *, int16_t *, int16_t *, int16_t *);
   
   typedef void (*TLx493D_CalculateRawMagneticFieldAndTemperatureFuncPtr)(TLx493D_t *, int16_t *, int16_t *, int16_t *, int16_t *);
   typedef bool (*TLx493D_GetRawMagneticFieldAndTemperatureFuncPtr)(TLx493D_t *, int16_t *, int16_t *, int16_t *, int16_t *);
   
   typedef void (*TLx493D_CalculateTemperatureFuncPtr)(TLx493D_t *, double *);
   typedef bool (*TLx493D_GetTemperatureFuncPtr)(TLx493D_t *, double *);
   
   typedef void (*TLx493D_CalculateMagneticFieldFuncPtr)(TLx493D_t *, double *, double *, double *);
   typedef bool (*TLx493D_GetMagneticFieldFuncPtr)(TLx493D_t *, double *, double *, double *);
   
   typedef void (*TLx493D_CalculateMagneticFieldAndTemperatureFuncPtr)(TLx493D_t *, double *, double *, double *, double *);
   typedef bool (*TLx493D_GetMagneticFieldAndTemperatureFuncPtr)(TLx493D_t *, double *, double *, double *, double *);
   
   
   typedef bool (*TLx493D_SetMeasurementFuncPtr)(TLx493D_t *, TLx493D_MeasurementType_t);
   typedef bool (*TLx493D_SetTriggerFuncPtr)(TLx493D_t *, TLx493D_TriggerType_t);
   typedef bool (*TLx493D_SetSetSensitivityFuncPtr)(TLx493D_t *, TLx493D_SensitivityType_t);
   
   
   typedef bool (*TLx493D_SetDefaultConfigFuncPtr)(TLx493D_t *);
   typedef bool (*TLx493D_SetIICAddressFuncPtr)(TLx493D_t *, TLx493D_IICAddressType_t);
   typedef bool (*TLx493D_Enable1ByteReadModeFuncPtr)(TLx493D_t *);
   
   typedef bool (*TLx493D_EnableInterruptFuncPtr)(TLx493D_t *);
   typedef bool (*TLx493D_DisableInterruptFuncPtr)(TLx493D_t *);
   
   typedef bool (*TLx493D_EnableCollisionAvoidanceFuncPtr)(TLx493D_t *);
   typedef bool (*TLx493D_DisableCollisionAvoidanceFuncPtr)(TLx493D_t *);
   
   typedef bool (*TLx493D_SetPowerModeFuncPtr)(TLx493D_t *, TLx493D_PowerModeType_t);
   typedef bool (*TLx493D_SetUpdateRateFuncPtr)(TLx493D_t *, TLx493D_UpdateRateType_t);
   
   typedef bool (*TLx493D_HasValidDataFuncPtr)(const TLx493D_t *);
   typedef bool (*TLx493D_IsFunctionalFuncPtr)(const TLx493D_t *);
   
   
   typedef bool (*TLx493D_HasWakeUpFuncPtr)(const TLx493D_t *);
   typedef bool (*TLx493D_IsWakeUpEnabledFuncPtr)(const TLx493D_t *);
   typedef bool (*TLx493D_EnableWakeUpModeFuncPtr)(TLx493D_t *);
   typedef bool (*TLx493D_DisableWakeUpModeFuncPtr)(TLx493D_t *);
   typedef bool (*TLx493D_SetWakeUpThresholdsAsIntegerFuncPtr)(TLx493D_t *, int16_t, int16_t, int16_t, int16_t, int16_t, int16_t);
   typedef bool (*TLx493D_SetWakeUpThresholdsFuncPtr)(TLx493D_t *, double, double, double, double, double, double, double);
   
   typedef bool (*TLx493D_SoftwareResetFuncPtr)(TLx493D_t *);
   
   
   typedef uint8_t (*TLx493D_CalculateFuseParityFuncPtr)(const TLx493D_t *);
   typedef uint8_t (*TLx493D_CalculateBusParityFuncPtr)(const TLx493D_t *);
   typedef uint8_t (*TLx493D_CalculateConfigParityFuncPtr)(TLx493D_t *);
   
   typedef bool (*TLx493D_HasValidFuseParityFuncPtr)(const TLx493D_t *);
   typedef bool (*TLx493D_HasValidBusParityFuncPtr)(const TLx493D_t *);
   typedef bool (*TLx493D_HasValidConfigParityFuncPtr)(const TLx493D_t *);
   typedef bool (*TLx493D_HasValidWakeUpParityFuncPtr)(const TLx493D_t *);
   
   typedef bool (*TLx493D_HasValidTBitFuncPtr)(const TLx493D_t *);
   typedef bool (*TLx493D_isInTestModeFuncPtr)(const TLx493D_t *);
   
   typedef void (*TLx493D_SetResetValuesFuncPtr)(TLx493D_t *);
   
   typedef void (*TLx493D_CalculateRawMagneticFieldAtTemperatureFuncPtr)(const TLx493D_t *, int16_t, TLx493D_SensitivityType_t,
                                                                         double, double, double,
                                                                         int16_t *, int16_t *, int16_t *);
   
   typedef double (*TLx493D_GetSensitivityScaleFactorFuncPtr)(const TLx493D_t *);
   
   typedef uint8_t (*TLx493D_SelectIICAddressFuncPtr)(const TLx493D_t *, TLx493D_IICAddressType_t);
   
   typedef void (*TLx493D_PrintRegistersFuncPtr)(const TLx493D_t *);
   
   
   typedef struct TLx493D_CommonFunctions_t {
       TLx493D_InitFuncPtr                         init;
       TLx493D_DeinitFuncPtr                       deinit;
   
       TLx493D_ReadRegistersFuncPtr                readRegisters;
       TLx493D_ReadRegistersAndCheckFuncPtr        readRegistersAndCheck;
   
       TLx493D_CalculateRawTemperatureFuncPtr      calculateRawTemperature;
       TLx493D_GetRawTemperatureFuncPtr            getRawTemperature;
   
       TLx493D_CalculateRawMagneticFieldFuncPtr    calculateRawMagneticField;
       TLx493D_GetRawMagneticFieldFuncPtr          getRawMagneticField;
   
       TLx493D_CalculateRawMagneticFieldAndTemperatureFuncPtr  calculateRawMagneticFieldAndTemperature;
       TLx493D_GetRawMagneticFieldAndTemperatureFuncPtr        getRawMagneticFieldAndTemperature;
   
       TLx493D_CalculateTemperatureFuncPtr         calculateTemperature;
       TLx493D_GetTemperatureFuncPtr               getTemperature;
   
       TLx493D_CalculateMagneticFieldFuncPtr       calculateMagneticField;
       TLx493D_GetMagneticFieldFuncPtr             getMagneticField;
       
       TLx493D_CalculateMagneticFieldAndTemperatureFuncPtr  calculateMagneticFieldAndTemperature;
       TLx493D_GetMagneticFieldAndTemperatureFuncPtr        getMagneticFieldAndTemperature;
   
       TLx493D_SetMeasurementFuncPtr               setMeasurement;
       TLx493D_SetTriggerFuncPtr                   setTrigger;
       TLx493D_SetSetSensitivityFuncPtr            setSensitivity;
   
       
       TLx493D_SetDefaultConfigFuncPtr             setDefaultConfig;
       TLx493D_SetIICAddressFuncPtr                setIICAddress;
       TLx493D_Enable1ByteReadModeFuncPtr          enable1ByteReadMode;
   
       TLx493D_EnableInterruptFuncPtr              enableInterrupt;
       TLx493D_DisableInterruptFuncPtr             disableInterrupt;
   
       TLx493D_EnableCollisionAvoidanceFuncPtr     enableCollisionAvoidance;
       TLx493D_DisableCollisionAvoidanceFuncPtr    disableCollisionAvoidance;
   
       TLx493D_SetPowerModeFuncPtr                 setPowerMode;
       TLx493D_SetUpdateRateFuncPtr                setUpdateRate;
   
       TLx493D_HasValidDataFuncPtr                 hasValidData;
       TLx493D_IsFunctionalFuncPtr                 isFunctional;
   
   
       TLx493D_HasWakeUpFuncPtr                    hasWakeUp;
       TLx493D_IsWakeUpEnabledFuncPtr              isWakeUpEnabled;
       TLx493D_EnableWakeUpModeFuncPtr             enableWakeUpMode;
       TLx493D_DisableWakeUpModeFuncPtr            disableWakeUpMode;
   
       TLx493D_SetWakeUpThresholdsAsIntegerFuncPtr setWakeUpThresholdsAsInteger;                
       TLx493D_SetWakeUpThresholdsFuncPtr          setWakeUpThresholds;                
   
       TLx493D_SoftwareResetFuncPtr                softwareReset;
       
   
       TLx493D_CalculateFuseParityFuncPtr          calculateFuseParity;
       TLx493D_CalculateBusParityFuncPtr           calculateBusParity;
       TLx493D_CalculateConfigParityFuncPtr        calculateConfigurationParity;
       
       TLx493D_HasValidFuseParityFuncPtr           hasValidFuseParity;
       TLx493D_HasValidBusParityFuncPtr            hasValidBusParity;
       TLx493D_HasValidConfigParityFuncPtr         hasValidConfigurationParity;
      
       TLx493D_HasValidWakeUpParityFuncPtr         hasValidWakeUpParity;
       TLx493D_isInTestModeFuncPtr                 isInTestMode;
   
       TLx493D_HasValidTBitFuncPtr                 hasValidTBit;
    
       TLx493D_SetResetValuesFuncPtr               setResetValues;
   
       TLx493D_SelectIICAddressFuncPtr             selectIICAddress;
   
       TLx493D_CalculateRawMagneticFieldAtTemperatureFuncPtr  calculateRawMagneticFieldAtTemperature;
   
       TLx493D_GetSensitivityScaleFactorFuncPtr    getSensitivityScaleFactor;
   
       TLx493D_PrintRegistersFuncPtr               printRegisters;
   } TLx493D_CommonFunctions_t;
   
   
   typedef struct TLx493D_t {
       uint8_t                         *regMap;
       TLx493D_Register_t              *regDef;
       TLx493D_CommonFunctions_t       *functions;
   
       TLx493D_CommunicationInterface_t  comInterface;
   
       TLx493D_BoardSupportInterface_t   boardSupportInterface;
   
       uint8_t                                     regMapSize;
       TLx493D_SupportedSensorType_t               sensorType;
       TLx493D_SupportedComLibraryInterfaceType_t  comIFType;
   } TLx493D_t;
   
   
   #ifdef __cplusplus
   
   }
   
   #endif
   
   
   #endif // TLX493D_TYPES_H
