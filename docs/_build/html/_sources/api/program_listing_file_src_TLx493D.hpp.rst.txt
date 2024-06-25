
.. _program_listing_file_src_TLx493D.hpp:

Program Listing for File TLx493D.hpp
====================================

|exhale_lsh| :ref:`Return to documentation for file <file_src_TLx493D.hpp>` (``src\TLx493D.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #ifndef TLX493D_HPP
   #define TLX493D_HPP
   
   
   // std includes
   #include <cstdbool>
   #include <cstdint>
   
   // project cpp includes
   #include "types.hpp"
   #include "BoardSupportUsingKit2Go.hpp"
   #include "IICUsingTwoWire.hpp"
   #include "SPIUsingSPIClass.hpp"
   #include "TLx493DBase.hpp"
   
   // project c includes
   #include "tlx493d_types.h"
   #include "tlx493d.h"
   
   
   namespace ifx {
       namespace tlx493d {
           template<typename BoardSupport, TLx493D_SupportedSensorType_t sensorType>
               class TLx493D<BoardSupport, TwoWireWrapper, sensorType> : public TLx493DBase {
   
               public:
   
                   typedef BoardSupport                                    BoardSupportType;
                   // typedef ifx::tlx493d::TwoWireWrapper                    BusWrapperType;
                   typedef typename ifx::tlx493d::TwoWireWrapper::BusType  BusType;
   
   
                   explicit TLx493D(BusType &busObj, TLx493D_IICAddressType_t iicAdr = TLx493D_IIC_ADDR_A0_e) : bsc(), bus(busObj), iicAddress(iicAdr) {
                   // explicit TLx493D(BusType &bus, TLx493D_IICAddressType_t iicAdr = TLx493D_IIC_ADDR_A0_e) : bsc(), busWrapper(bus), iicAddress(iicAdr) {
                       (void) tlx493d_init(&sensor, sensorType);
                   }
   
                   ~TLx493D() {
                   }
   
                   void init(bool enablePower = true, bool enableSelect = false, bool enableExtendedAdress = false) {
                       (void) initBoardSupport(&sensor, bsc);
                       bsc.init(enablePower, enableSelect, enableExtendedAdress);
                       initCommunication(&sensor, bus, iicAddress, false);
                       // initCommunication(&sensor, busWrapper, iicAddress, false);
                       setDefaultConfig();
                   }
   
                   void begin(bool enablePower = true, bool enableSelect = false, bool enableExtendedAdress = false) {
                       init(enablePower, enableSelect, enableExtendedAdress);
                   }
   
                   void deinit() {
                       deinitCommunication(&sensor, false);
                       bsc.deinit();
                       (void) tlx493d_deinit(&sensor);
                   }
   
                   void end() {
                       deinit();
                   }
   
                   void setPowerPin(uint8_t pinNumber, uint8_t pinDriveDirection, uint8_t pinTristateDirection,
                                    uint8_t pinEnableValue, uint8_t pinDisableValue,
                                    uint32_t delayAfterEnable = 0, uint32_t delayAfterDisable = 0) {
                       bsc.setPowerPin(pinNumber, pinDriveDirection, pinTristateDirection, pinEnableValue, pinDisableValue, delayAfterEnable, delayAfterDisable);
                   }
   
                   void unsetPowerPin() {
                       bsc.unsetPowerPin();
                   }
   
                   void setSelectPin(uint8_t pinNumber, uint8_t pinDriveDirection, uint8_t pinTristateDirection,
                                     uint8_t pinEnableValue, uint8_t pinDisableValue,
                                     uint32_t delayAfterEnable = 0, uint32_t delayAfterDisable = 0) {
                       bsc.setSelectPin(pinNumber, pinDriveDirection, pinTristateDirection, pinEnableValue, pinDisableValue, delayAfterEnable, delayAfterDisable);
                   }
   
                   void unsetSelectPin() {
                       bsc.unsetSelectPin();
                   }
   
                   void setAddressPin(uint8_t pinNumber, uint8_t pinDriveDirection, uint8_t pinTristateDirection,
                                      uint8_t pinEnableValue, uint8_t pinDisableValue,
                                      uint32_t delayAfterEnable = 0, uint32_t delayAfterDisable = 0) {
                       bsc.setAdressPin(pinNumber, pinDriveDirection, pinTristateDirection, pinEnableValue, pinDisableValue, delayAfterEnable, delayAfterDisable);
                   }
   
                   void unsetAddressPin() {
                       bsc.unsetAdressPin();
                   }
   
                   void enablePower() {
                       bsc.enablePower(true);
                   }
   
                   void disablePower() {
                       bsc.enablePower(false);
                   }
   
                   void reset() {
                       deinitCommunication(&sensor, true);
                       sensor.functions->setResetValues(&sensor);
                       bsc.reset();
                       initCommunication(&sensor, bus, iicAddress, true);
                       // initCommunication(&sensor, busWrapper, iicAddress, true);
                       setDefaultConfig();
                   }
   
                   void enableSelect() {
                       bsc.enableSelect(true);
                   }
   
                   void disableSelect() {
                       bsc.enableSelect(false);
                   }
   
                   void enableAddress() {
                       bsc.enableAddress(true);
                   }
   
                   void disableAddress() {
                       bsc.enableAddress(false);
                   }
   
   
               private:
   
                   TLx493D(BusType &bus);
   
   
                   BoardSupportType          bsc;          
                   // BusWrapperType            busWrapper;   /**< BusWrapperClass */
                   BusType                   bus;  
                   TLx493D_IICAddressType_t  iicAddress;   
           };
   
   
           template<typename BoardSupport, TLx493D_SupportedSensorType_t sensorType>
               class TLx493D<BoardSupport, SPIClassWrapper, sensorType> : public TLx493DBase {
   
               public:
   
                   typedef BoardSupport                                     BoardSupportType;
                   // typedef ifx::tlx493d::SPIClassWrapper                    BusWrapperType;
                   typedef typename ifx::tlx493d::SPIClassWrapper::BusType  BusType;
   
           
                   explicit TLx493D(BusType &busObj) : bsc(), bus(busObj) {
                   // explicit TLx493D(BusType &bus) : bsc(), busWrapper(bus) {
                       (void) tlx493d_init(&sensor, sensorType);
                   }
   
                   ~TLx493D() {
                   }
   
                   void init(bool enablePower = false, bool enableSelect = true) {
                       (void) initBoardSupport(&sensor, bsc);
                       bsc.init(enablePower, enableSelect, false);
                       // initCommunication(&sensor, busWrapper, true);
                       initCommunication(&sensor, bus, true);
                       setDefaultConfig();
                   }
   
                   void begin(bool enablePower = false, bool enableSelect = true) {
                       init(enablePower, enableSelect);
                   }
   
   
                   void deinit() {
                       deinitCommunication(&sensor, false);
                       bsc.deinit();
                       (void) tlx493d_deinit(&sensor);
                   }
   
                   void end() {
                       deinit();
                   }
   
                   void setPowerPin(uint8_t pinNumber, uint8_t pinDriveDirection, uint8_t pinTristateDirection,
                                    uint8_t pinEnableValue, uint8_t pinDisableValue,
                                    uint32_t delayAfterEnable = 0, uint32_t delayAfterDisable = 0) {
                       bsc.setPowerPin(pinNumber, pinDriveDirection, pinTristateDirection, pinEnableValue, pinDisableValue, delayAfterEnable, delayAfterDisable);
                   }
   
                   void unsetPowerPin() {
                       bsc.unsetPowerPin();
                   }
   
                   void setSelectPin(uint8_t pinNumber, uint8_t pinDriveDirection, uint8_t pinTristateDirection,
                                     uint8_t pinEnableValue, uint8_t pinDisableValue,
                                     uint32_t delayAfterEnable = 0, uint32_t delayAfterDisable = 0) {
                       bsc.setSelectPin(pinNumber, pinDriveDirection, pinTristateDirection, pinEnableValue, pinDisableValue, delayAfterEnable, delayAfterDisable);
                   }
   
                   void unsetSelectPin() {
                       bsc.unsetSelectPin();
                   }
   
                   void enablePower() {
                       bsc.enablePower(true);
                   }
   
                   void disablePower() {
                       bsc.enablePower(false);
                   }
   
                   void reset() {
                       deinitCommunication(&sensor, false);
                       sensor.functions->setResetValues(&sensor);
                       bsc.reset();
                       // initCommunication(&sensor, busWrapper, true);
                       initCommunication(&sensor, bus, true);
                       setDefaultConfig();
                   }
   
                   void enableSelect() {
                       bsc.enableSelect(true);
                   }
   
                   void disableSelect() {
                       bsc.enableSelect(false);
                   }
   
   
               private:
   
                   BoardSupportType  bsc;              
                   // BusWrapperType    busWrapper;    /**< BusWrapperClass */
                   BusType           bus;              
           };
       }
   }
   
   
   #endif // TLX493D_HPP
