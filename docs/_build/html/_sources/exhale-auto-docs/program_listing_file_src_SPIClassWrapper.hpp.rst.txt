
.. _program_listing_file_src_SPIClassWrapper.hpp:

Program Listing for File SPIClassWrapper.hpp
============================================

|exhale_lsh| :ref:`Return to documentation for file <file_src_SPIClassWrapper.hpp>` (``src\SPIClassWrapper.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #ifndef TLX493D_SPICLASS_WRAPPER_HPP
   #define TLX493D_SPICLASS_WRAPPER_HPP
   
   
   // std includes
   
   // Arduino includes
   #include <Arduino.h>
   #include <SPI.h>
   
   
   namespace ifx {
       namespace tlx493d {
           class SPIClassWrapper {
   
               public:
   
                   using BusType = SPIClass;
   
                   // static constexpr uint8_t TLX493D_SPI_READ_BIT         = 0x80;
                   static constexpr uint8_t TLX493D_SPI_READ_BIT_ON      = 0x80;
                   // static constexpr uint8_t TLX493D_SPI_READ_BIT_OFF     = 0x00;
   
                   // static constexpr uint8_t TLX493D_SPI_AUTO_INC_BIT     = 0x60;
                   // static constexpr uint8_t TLX493D_SPI_AUTO_INC_BIT_ON  = 0x60;
                   // static constexpr uint8_t TLX493D_SPI_AUTO_INC_BIT_OFF = 0x00;
   
                   explicit SPIClassWrapper() : spi(nullptr) {
                   }
   
                   explicit SPIClassWrapper(SPIClass &bus) : spi(&bus) {
                   }
   
                   ~SPIClassWrapper() {
                   }
   
   
                   void init(const SPISettings &settings) {
                   // void init(uint32_t clockFreq, uint8_t bitOrder, uint8_t dataMode) {
                       // SPISettings settings(clockFreq, bitOrder, dataMode);
                       spi->beginTransaction(settings);
                       // spi.beginTransaction(settings);
   
                       // spi.begin();
                   }
   
                   void deinit() {
                       spi->end();
                       // spi.end();
                   }
   
                   bool transfer(uint8_t *txBuffer, uint8_t txLen, uint8_t *rxBuffer, uint8_t rxLen, uint8_t readAddress) {
                       if( (txLen > 0) && (txBuffer != NULL) ) {
                           uint8_t bytesWritten = 0;
   
                           for(; bytesWritten < txLen; ++bytesWritten) {
                               spi->transfer(txBuffer[bytesWritten]);
                               // spi.transfer(txBuffer[bytesWritten]);
                           }
   
                           if( bytesWritten != txLen ) {
                               return false;
                           }
                       }
   
                       if( (rxLen > 0)  && (rxBuffer != NULL) ) {
                           uint16_t bytesRead = 0;
                           spi->transfer(TLX493D_SPI_READ_BIT_ON | readAddress);
                           // spi.transfer(TLX493D_SPI_READ_BIT_ON | readAddress);
   
                           for(; bytesRead < rxLen; ++bytesRead) {
                               rxBuffer[bytesRead] = spi->transfer(TLX493D_SPI_READ_BIT_ON | readAddress);
                               // rxBuffer[bytesRead] = spi.transfer(TLX493D_SPI_READ_BIT_ON | readAddress);
                           }
   
                           if( bytesRead != rxLen ) {
                               return false;
                           }
                       }
   
                       return true;
                   }
   
                   SPIClass &getBus() {
                       return *spi;
                   }
   
                   void setBus(SPIClass &spiObj) {
                       spi = &spiObj;
                   }
   
   
               private:
                   SPIClass *spi;
           };
       }
   }
   
   #endif // TLX493D_SPICLASS_WRAPPER_HPP
