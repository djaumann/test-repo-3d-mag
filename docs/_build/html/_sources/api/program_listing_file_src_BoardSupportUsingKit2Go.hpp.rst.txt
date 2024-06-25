
.. _program_listing_file_src_BoardSupportUsingKit2Go.hpp:

Program Listing for File BoardSupportUsingKit2Go.hpp
====================================================

|exhale_lsh| :ref:`Return to documentation for file <file_src_BoardSupportUsingKit2Go.hpp>` (``src\BoardSupportUsingKit2Go.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #ifndef TLX493D_BOARD_SUPPORT_USING_KIT2GO_HPP
   #define TLX493D_BOARD_SUPPORT_USING_KIT2GO_HPP
   
   
   #include <cstdbool>
   
   #include <Arduino.h>
   
   #include "Kit2GoBoardSupport.hpp"
   
   #include "tlx493d_types.h"
   
   namespace ifx {
       namespace tlx493d {
           bool initBoardSupport(TLx493D_t *sensor, Kit2GoBoardSupport &bsc);
       }
   }
   
   
   #endif // TLX493D_BOARD_SUPPORT_USING_KIT2GO_HPP
