
.. _program_listing_file_src_BoardSupportUsingKit2Go.cpp:

Program Listing for File BoardSupportUsingKit2Go.cpp
====================================================

|exhale_lsh| :ref:`Return to documentation for file <file_src_BoardSupportUsingKit2Go.cpp>` (``src\BoardSupportUsingKit2Go.cpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   
   #include <cstddef>
   #include <cstdlib>
   
   #include "tlx493d_types.h"
   
   #include "types.hpp"
   #include "BoardSupportUsingKit2Go.hpp"
   
   
   namespace ifx {
       namespace tlx493d {
           bool initBoardSupport(TLx493D_t *sensor, Kit2GoBoardSupport &bsc) {
               sensor->boardSupportInterface.boardSupportObj.k2go_obj       = (TLx493D_Kit2GoBoardSupportObject_t *) malloc(sizeof(TLx493D_Kit2GoBoardSupportObject_t));
               sensor->boardSupportInterface.boardSupportObj.k2go_obj->k2go = &bsc;
               return true;
           }
       }
   }
