
.. _program_listing_file_src_CommunicationInterface.h:

Program Listing for File CommunicationInterface.h
=================================================

|exhale_lsh| :ref:`Return to documentation for file <file_src_CommunicationInterface.h>` (``src\CommunicationInterface.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #ifndef TLX493D_COMMUNICATION_INTERFACE_H
   #define TLX493D_COMMUNICATION_INTERFACE_H
   
   
   #include <stdbool.h>
   #include <stdint.h>
   
   
   #ifdef __cplusplus
   
   extern "C" {
   
   #endif
   
   typedef struct TLx493D_t  TLx493D_t;
   
   bool tlx493d_transfer(TLx493D_t *sensor, uint8_t *txBuffer, uint8_t txLen, uint8_t *rxBuffer, uint8_t rxLen);
   
   void tlx493d_setReadAddress(TLx493D_t *sensor, uint8_t address);
   
   
   #ifdef __cplusplus
   
   }
   
   #endif
   
   
   #ifdef __cplusplus
   
   namespace ifx {
       namespace tlx493d {
   
   #endif
   
   void deinitCommunication(TLx493D_t *sensor, bool executeDeinit);
   
   
   #ifdef __cplusplus
   
       }
   }
   
   #endif
   
   
   #endif // TLX493D_COMMUNICATION_INTERFACE_H
