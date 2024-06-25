#ifndef TLX493D_ARDUINO_TYPES_H
#define TLX493D_ARDUINO_TYPES_H


/** Arduino includes. */
#include <Arduino.h>

/** project cpp includes. */
#include "baseTypes.hpp"
#include "TLx493D.hpp"


namespace ifx {
    namespace tlx493d {
        /** Definiton of the specific sensor constructors. This makes instantiation of the sensors easier for the user,
         *  since they can use a "regular" constructor call, instead of using the template notation. 
         */
        
        // typedef TLx493D<Kit2GoBoardSupport, TwoWireWrapper, TLx493D_A1B6_e>  TLx493D_A1B6;
        // typedef TLx493D<Kit2GoBoardSupport, TwoWireWrapper, TLx493D_A2B6_e>  TLx493D_A2B6;
        // typedef TLx493D<Kit2GoBoardSupport, TwoWireWrapper, TLx493D_P2B6_e>  TLx493D_P2B6;
        // typedef TLx493D<Kit2GoBoardSupport, TwoWireWrapper, TLx493D_W2B6_e>  TLx493D_W2B6;
        // typedef TLx493D<Kit2GoBoardSupport, TwoWireWrapper, TLx493D_W2BW_e>  TLx493D_W2BW;
        // typedef TLx493D<Kit2GoBoardSupport, TwoWireWrapper, TLx493D_P3B6_e>  TLx493D_P3B6;

        // typedef TLx493D<Kit2GoBoardSupport, SPIClassWrapper, TLx493D_P3I8_e>  TLx493D_P3I8;


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
