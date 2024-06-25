
.. _program_listing_file_src_types.hpp:

Program Listing for File types.hpp
==================================

|exhale_lsh| :ref:`Return to documentation for file <file_src_types.hpp>` (``src\types.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #ifndef TLX493D_ARDUINO_TYPES_H
   #define TLX493D_ARDUINO_TYPES_H
   
   #include <Arduino.h>
   #include <SPI.h>
   #include <Wire.h>
   
   #include "Kit2GoBoardSupport.hpp"
   #include "TLx493D.hpp"
   
   #include "tlx493d_types.h"
   
   using TLx493D_I2CObject_t = struct TLx493D_I2CObject_t {
       ifx::tlx493d::TwoWireWrapper wire;
   
       // ifx::tlx493d::TwoWireWrapper *wire;
       // bool                          isToBeDeleted;
   };
   
   using TLx493D_SPIObject_t = struct TLx493D_SPIObject_t {
       ifx::tlx493d::SPIClassWrapper spi;
   
       // ifx::tlx493d::SPIClassWrapper *spi;
       // bool                           isToBeDeleted;
   };
   
   using TLx493D_Kit2GoBoardSupportObject_t = struct TLx493D_Kit2GoBoardSupportObject_t {
       ifx::tlx493d::Kit2GoBoardSupport  *k2go;
       // bool                               isToBeDeleted;
   };
   
   
   namespace ifx {
       namespace tlx493d {
           using TLx493D_A1B6 = TLx493D<Kit2GoBoardSupport, TwoWireWrapper, TLx493D_A1B6_e>;
           using TLx493D_A2B6 = TLx493D<Kit2GoBoardSupport, TwoWireWrapper, TLx493D_A2B6_e>;
           using TLx493D_P2B6 = TLx493D<Kit2GoBoardSupport, TwoWireWrapper, TLx493D_P2B6_e>;
           using TLx493D_W2B6 = TLx493D<Kit2GoBoardSupport, TwoWireWrapper, TLx493D_W2B6_e>;
           using TLx493D_W2BW = TLx493D<Kit2GoBoardSupport, TwoWireWrapper, TLx493D_W2BW_e>;
           using TLx493D_P3B6 = TLx493D<Kit2GoBoardSupport, TwoWireWrapper, TLx493D_P3B6_e>;
   
           // using TLx493D_P3I8 = TLx493D<Kit2GoBoardSupport, SPIClass, TLx493D_P3I8_e>;
           using TLx493D_P3I8 = TLx493D<Kit2GoBoardSupport, SPIClassWrapper, TLx493D_P3I8_e>;
       }
   }
   
   #endif // TLX493D_ARDUINO_TYPES_H
