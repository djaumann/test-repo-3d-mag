
.. _program_listing_file_src_IICUsingTwoWire.hpp:

Program Listing for File IICUsingTwoWire.hpp
============================================

|exhale_lsh| :ref:`Return to documentation for file <file_src_IICUsingTwoWire.hpp>` (``src\IICUsingTwoWire.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #ifndef TLX493D_IIC_USING_TWOWIRE_HPP
   #define TLX493D_IIC_USING_TWOWIRE_HPP
   
   
   #include <cstdbool>
   
   #include <Arduino.h>
   
   #include "TwoWireWrapper.hpp"
   
   #include "tlx493d_types.h"
   
   namespace ifx {
       namespace tlx493d {
           bool initCommunication(TLx493D_t *sensor, TwoWire &tw, TLx493D_IICAddressType_t iicAdr, bool executeInit = false);
       }
   }
   
   
   #endif // TLX493D_IIC_USING_TWOWIRE_HPP
