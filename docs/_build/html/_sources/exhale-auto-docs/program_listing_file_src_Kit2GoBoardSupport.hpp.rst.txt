
.. _program_listing_file_src_Kit2GoBoardSupport.hpp:

Program Listing for File Kit2GoBoardSupport.hpp
===============================================

|exhale_lsh| :ref:`Return to documentation for file <file_src_Kit2GoBoardSupport.hpp>` (``src\Kit2GoBoardSupport.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   /*********************************************************************
    * @file  Kit2GoBoardSupport.hpp
    * 
    * @brief Implementation of the class Kit2GoBoardSupport for custom sensor/board bring up.
    * This can be used to power cycle the sensor device, help with setting/resetting the SPI
    * slave select lines for multiple devices and also setting/resetting addressing lines 
    * for enabling extended addresses for certain devices.  
    *********************************************************************/
   
   #ifndef TLX493D_KIT2GO_BOARD_SUPPORT_HPP
   #define TLX493D_KIT2GO_BOARD_SUPPORT_HPP
   
   
   // std include
   
   // Arduino includes
   #include <Arduino.h>
   
   // project cpp includes
   
   
   namespace ifx {
       namespace tlx493d {
           class Kit2GoBoardSupport {
   
               public:
               
                   Kit2GoBoardSupport() : powerPins{false, 0, 0, 0, 0, 0, 0, 0}, selectPins{false, 0, 0, 0, 0, 0, 0, 0}, addressPins{false, 0, 0, 0, 0, 0, 0, 0} {
                   }
   
                   ~Kit2GoBoardSupport() {
                   }
   
   
                   void init(bool isEnablePower = true, bool isEnableSelect = false, bool isEnableExtendedAddress = false) {
                       if( isEnableSelect ) {
                           for(const auto &p : selectPins) {
                               initPin(p);
                           }
   
                           this->enableSelect(false);
                       }
   
                       if( isEnableExtendedAddress ) {
                           for(const auto &p : addressPins){
                               initPin(p);
                           }
   
                           enableAddress(true);
                       }
   
                       if( isEnablePower ) {
                           for(const auto &p : powerPins) {
                               initPin(p);
                           }
   
                           reset();
                       }
   
                       if( isEnableExtendedAddress ) {
                           enableAddress(false);
   
                           for(auto &p : addressPins){
                               setPinDirectionToTristate(p);
                           }
                       }
                   }
                   
                   void begin(bool enablePower = true, bool enableSelect = false, bool enableExtendedAddress = false) {
                       init(enablePower, enableSelect, enableExtendedAddress);
                   }
   
                   void deinit() {
                       enablePower(false);
                       enableSelect(false);
                   }
   
                   void end() {
                       deinit();
                   }
   
                   void setPowerPin(uint8_t pinNumber, uint8_t pinDriveDirection, uint8_t pinTristateDirection,
                                    uint8_t pinEnableValue, uint8_t pinDisableValue,
                                    uint32_t delayAfterEnable = 0, uint32_t delayAfterDisable = 0) {
                       powerPins[0] = { true, pinNumber, pinDriveDirection, pinTristateDirection, pinEnableValue, pinDisableValue, delayAfterEnable, delayAfterDisable };
                   }
   
                   void unsetPowerPin() {
                       powerPins[0].isSet = false;
                   }
   
                   void setSelectPin(uint8_t pinNumber, uint8_t pinDriveDirection, uint8_t pinTristateDirection,
                                     uint8_t pinEnableValue, uint8_t pinDisableValue,
                                     uint32_t delayAfterEnable = 0, uint32_t delayAfterDisable = 0) {
                       selectPins[0] = { true, pinNumber, pinDriveDirection, pinTristateDirection, pinEnableValue, pinDisableValue, delayAfterEnable, delayAfterDisable };
                   }
   
                   void unsetSelectPin() {
                       selectPins[0].isSet = false;
                   }
   
                   void setAddressPin(uint8_t pinNumber, uint8_t pinDriveDirection, uint8_t pinTristateDirection,
                                      uint8_t pinEnableValue, uint8_t pinDisableValue,
                                      uint32_t delayAfterEnable = 0, uint32_t delayAfterDisable = 0) {
                       addressPins[0] = { true, pinNumber, pinDriveDirection, pinTristateDirection, pinEnableValue, pinDisableValue, delayAfterEnable, delayAfterDisable };
                   }
   
                   void unsetAddressPin() {
                       addressPins[0].isSet = false;
                   }
   
   
                   void enablePower(bool enable) {
                       for(const auto &p : powerPins) {
                           enablePin(p, enable);
                       }
                   }
   
                   void enableSelect(bool enable) {
                       for(const auto &p : selectPins) {
                           enablePin(p, enable);
                       }
                   }
   
                   void enableAddress(bool enable) {
                       for(const auto &p : addressPins) {
                           enablePin(p, enable);
                       }
                   }
   
                   void reset() {
                       enablePower(false);
                       enablePower(true);
                   }
   
   
               private:
   
                   typedef struct pinCtrl {
                       bool     isSet;             
                       uint8_t  pinNumber;         
                       uint8_t  driveDirection;    
                       uint8_t  tristateDirection; 
                       uint8_t  enableValue;       
                       uint8_t  disableValue;      
                       uint32_t delayAfterEnable;  
                       uint32_t delayAfterDisable; 
                   } pinCtrl;
   
                   void enablePin(const pinCtrl &p, bool enable) {
                       if( p.isSet ) {
                           digitalWrite(p.pinNumber, enable ? p.enableValue : p.disableValue);
                           delayMicroseconds(enable ? p.delayAfterEnable : p.delayAfterDisable);
                       }
                   }
   
                   void initPin(const pinCtrl &p) {
                       if( p.isSet ) {
                           pinMode(p.pinNumber, p.driveDirection);
                       }
                   }
   
                   void setPinDirectionToDrive(pinCtrl &p) {
                       if( p.isSet ) {
                           pinMode(p.pinNumber, p.driveDirection);
                       }
                   }
   
                   void setPinDirectionToTristate(pinCtrl &p) {
                       if( p.isSet ) {
                           pinMode(p.pinNumber, p.tristateDirection);
                       }
                   }
   
                   pinCtrl powerPins[1];
                   pinCtrl selectPins[1];
                   pinCtrl addressPins[1];
           };
       }
   }
   
   
   #endif // TLX493D_KIT2GO_BOARD_SUPPORT_HPP
