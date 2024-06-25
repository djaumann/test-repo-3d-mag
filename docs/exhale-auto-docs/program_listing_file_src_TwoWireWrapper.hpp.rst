
.. _program_listing_file_src_TwoWireWrapper.hpp:

Program Listing for File TwoWireWrapper.hpp
===========================================

|exhale_lsh| :ref:`Return to documentation for file <file_src_TwoWireWrapper.hpp>` (``src\TwoWireWrapper.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #ifndef TLX493D_TWOWIRE_WRAPPER_HPP
   #define TLX493D_TWOWIRE_WRAPPER_HPP
   
   
   #include <Arduino.h>
   #include <Wire.h>
   
   
   namespace ifx {
       namespace tlx493d {
           class TwoWireWrapper {
   
               public:
   
                   using BusType = TwoWire;
   
                   explicit TwoWireWrapper() : iic(nullptr) {
                   }
   
                   explicit TwoWireWrapper(TwoWire &bus) : iic(&bus) {
                   }
   
                   ~TwoWireWrapper() {
                   }
   
                   void init() {
                       iic->begin();
                       // iic.begin();
                   }
   
                   void deinit() {
                       iic->end();
                       // iic.end();
                   }
   
                   bool transfer(uint8_t iicAddress, uint8_t *txBuffer, uint8_t txLen, uint8_t *rxBuffer, uint8_t rxLen) {
                       if( (txLen > 0) && (txBuffer != NULL) ) {
                           iic->beginTransmission(iicAddress);
                           // iic.beginTransmission(iicAddress);
   
                           uint8_t bytesWritten = iic->write(txBuffer, txLen);
                           iic->endTransmission(true);
                           // uint8_t bytesWritten = iic.write(txBuffer, txLen);
                           // iic.endTransmission(true);
   
                           if( bytesWritten != txLen ) {
                               return false;
                           }
                       }
   
                       if( (rxLen > 0)  && (rxBuffer != NULL) ) {
                           uint8_t bytesRead = iic->requestFrom(iicAddress, rxLen);
   
                           for(uint16_t i = 0; (i < rxLen) && (iic->available() > 0); ++i) {
                               rxBuffer[i] = iic->read();
                           }
   
                           // uint8_t bytesRead = iic.requestFrom(iicAddress, rxLen);
   
                           // for(uint16_t i = 0; (i < rxLen) && (iic.available() > 0); ++i) {
                           //     rxBuffer[i] = iic.read();
                           // }
   
                           // iic.endTransmission(true);
   
                           if( bytesRead != rxLen ) {
                               return false;
                           }
                       }
   
                       return true;
                   }
   
                   TwoWire &getBus() {
                       return *iic;
                   }
   
                   void setBus(BusType &iicObj) {
                       iic = &iicObj;
                   }
   
   
               private:
                   
                   TwoWire *iic; 
           };
       }
   }
   
   
   #endif // TLX493D_TWOWIRE_WRAPPER_HPP
