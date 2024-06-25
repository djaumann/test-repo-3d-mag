
.. _program_listing_file_src_pal.h:

Program Listing for File pal.h
==============================

|exhale_lsh| :ref:`Return to documentation for file <file_src_pal.h>` (``src\pal.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #ifndef TLX493D_PAL_H
   #define TLX493D_PAL_H
   
   
   // std includes
   #include <stdbool.h>
   #include <stdint.h>
   
   
   #include "CommunicationInterface.h"
   
   
   #ifdef __cplusplus
   
   extern "C" {
   
   #endif
   
   
   typedef union TLx493D_ComLibraryParameters_t TLx493D_ComLibraryParameters_t;
   
   typedef struct TLx493D_I2CObject_t           TLx493D_I2CObject_t;
   typedef struct TLx493D_SPIObject_t           TLx493D_SPIObject_t;
   
   
   typedef struct TLx493D_Kit2GoBoardSupportObject_t  TLx493D_Kit2GoBoardSupportObject_t;
   
   typedef struct TLx493D_t                     TLx493D_t;
   
   
   #ifdef __cplusplus
   
   }
   
   #endif
   
   
   #endif // TLX493D_PAL_H
