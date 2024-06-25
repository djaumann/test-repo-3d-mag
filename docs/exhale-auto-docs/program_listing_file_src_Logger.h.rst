
.. _program_listing_file_src_Logger.h:

Program Listing for File Logger.h
=================================

|exhale_lsh| :ref:`Return to documentation for file <file_src_Logger.h>` (``src\Logger.h``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #ifndef TLX493D_LOGGER_H
   #define TLX493D_LOGGER_H
   
   #ifdef __cplusplus
   
   #include <cstdarg>
   
   using TLx493D_t = struct TLx493D_t;
   
   extern "C" {
   
   #else
   
   #include <stdarg.h>
   
   typedef struct TLx493D_t  TLx493D_t;
   
   #endif
   
   
   void logPrintRegisters(const TLx493D_t *sensor, const char *headLine);
   
   void logPrintDouble(double d);
   
   void logPrint(const char *format, ...);
   
   void logPrintln(const char *format, ...);
   
   void logInfo(const char *format, ...);
   
   void logWarn(const char *format, ...);
   
   void logError(const char *format, ...);
   
   void logFlush(void);
   
   
   #ifdef __cplusplus
   
   }
   
   #endif
   
   
   #endif // TLX493D_LOGGER_H
