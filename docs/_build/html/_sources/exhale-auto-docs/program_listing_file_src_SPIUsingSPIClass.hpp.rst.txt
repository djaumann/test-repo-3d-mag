
.. _program_listing_file_src_SPIUsingSPIClass.hpp:

Program Listing for File SPIUsingSPIClass.hpp
=============================================

|exhale_lsh| :ref:`Return to documentation for file <file_src_SPIUsingSPIClass.hpp>` (``src\SPIUsingSPIClass.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #ifndef TLX493D_SPI_USING_SPICLASS_HPP
   #define TLX493D_SPI_USING_SPICLASS_HPP
   
   
   // std includes
   #include <cstdbool>
   
   // Arduino includes
   #include <Arduino.h>
   
   // project cpp includes
   #include "SPIClassWrapper.hpp"
   
   // project c includes
   // common to all sensors
   #include "tlx493d_types.h"
   
   
   namespace ifx {
       namespace tlx493d {
           bool initCommunication(TLx493D_t *sensor, SPIClass &spi, bool executeInit = false, uint32_t clockFreq = 200000, uint8_t bitOrder = MSBFIRST, uint8_t dataMode = SPI_MODE2);
       }
   }
   
   
   #endif // TLX493D_SPI_USING_SPICLASS_HPP
