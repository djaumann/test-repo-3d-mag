// std includes
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

// Arduino includes
#include <Arduino.h>


// project cpp includes
#include "Logger.h"


#define BUFFER_SIZE  512


extern "C" {
    void printRegisters(uint8_t *rm, uint8_t rmSize) {
        Serial.print("regMap :"); 

        for(uint8_t i = 0; i < rmSize; ++i) {
            Serial.print("  0x");
            Serial.print(rm[i], HEX);
        }

        Serial.println();
    }


    void print(double d) {
        Serial.print(d);
    }


    void logMessage(const char *prefix, const char *format, va_list vaList) {
        char buffer[BUFFER_SIZE];

        size_t prefixSize = strlen(prefix);
        memcpy(buffer, prefix, prefixSize);
        int ret = vsprintf(buffer + prefixSize, format, vaList);

        if( (ret + prefixSize) > BUFFER_SIZE ) {
            Serial.print("FATAL : Buffer overflow (> ");
            Serial.print(BUFFER_SIZE);
            Serial.println(" characters) because message too long !\n");
        }

        Serial.println(buffer);
    }


    void info(const char *format, ...) {
        va_list ap;
        va_start(ap, format);
        logMessage("INFO : ", format, ap);
        va_end(ap);
    }


    void warn(const char *format, ...) {
        va_list ap;
        va_start(ap, format);
        logMessage("WARNING : ", format, ap);
        va_end(ap);
    }


    void error(const char *format, ...) {
        va_list ap;
        va_start(ap, format);
        logMessage("ERROR : ", format, ap);
        va_end(ap);
    }


    void flush() {
        // USE WITH CAUTION ! DEVICE MAY HANGUP !
        // Serial.flush();
        Serial.println();

    }
}
