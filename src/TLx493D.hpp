#ifndef TLX493D_HPP
#define TLX493D_HPP


// std includes
#include <stdbool.h>
#include <stdint.h>

// project cpp includes
#include "types.hpp"
#include "BoardSupportUsingKit2Go.hpp"
#include "IICUsingTwoWire.hpp"
#include "SPIUsingSPIClass.hpp"
#include "TLx493DBase.hpp"

// project c includes
#include "tlx493d_types.h"
#include "tlx493d.h"


/***
 * Specialization for IIC interface.
*/
template<typename BoardSupport, TLx493D_SupportedSensorType_t sensorType>
    class TLx493D<BoardSupport, TwoWireWrapper, sensorType> : public TLx493DBase {

    public:

        typedef BoardSupport                      BoardSupportType;
        typedef TwoWireWrapper                    BusWrapperType;
        typedef typename TwoWireWrapper::BusType  BusType;

 
        TLx493D(BusType &bus, TLx493D_IICAddressType_t iicAdr = TLx493D_IIC_ADDR_A0_e) : bsc(), busWrapper(bus), iicAddress(iicAdr) {
            tlx493d_init(&sensor, sensorType);
        }


        ~TLx493D() {
        }


        void init(bool enablePower = true, bool enableSelect = false, bool enableExtendedAddr = false) {
            bsc.init(enablePower, enableSelect, enableExtendedAddr);
            tlx493d_initBoardSupport(&sensor, bsc);
            tlx493d_initCommunication(&sensor, busWrapper, iicAddress); // includes call to busWrapper.init();
            setDefaultConfig();
        }


        void begin(bool enablePower = true, bool enableSelect = false, bool enableExtendedAddr = false) {
            init(enablePower, enableSelect, enableExtendedAddr);
        }


        void deinit() {
            tlx493d_deinitCommunication(&sensor); // includes call to busWrapper.deinit();
            tlx493d_deinit(&sensor);
            bsc.deinit();
        }


        void end() {
            deinit();
        }


        void setPowerPin(uint8_t pinNumber, uint8_t pinDirection, uint8_t pinEnableValue, uint8_t pinDisableValue,
                         uint8_t delayAfterDisable = 0, uint8_t  delayAfterEnable = 0) {
            bsc.setPowerPin(pinNumber, pinDirection, pinEnableValue, pinDisableValue, delayAfterDisable, delayAfterEnable);
        }


        void unsetPowerPin() {
            bsc.unsetPowerPin();
        }


        void setSelectPin(uint8_t pinNumber, uint8_t pinDirection, uint8_t pinEnableValue, uint8_t pinDisableValue,
                          uint8_t delayAfterDisable = 0, uint8_t  delayAfterEnable = 0) {
            bsc.setSelectPin(pinNumber, pinDirection, pinEnableValue, pinDisableValue, delayAfterDisable, delayAfterEnable);
        }

        void unsetSelectPin() {
            bsc.unsetSelectPin();
        }

        void setAddrPin(uint8_t pinNumber, uint8_t pinDirection, uint8_t pinEnableValue, uint8_t pinDisableValue,
                         uint8_t delayAfterDisable = 0, uint8_t  delayAfterEnable = 0) {
            bsc.setAddrPin(pinNumber, pinDirection, pinEnableValue, pinDisableValue, delayAfterDisable, delayAfterEnable);
        }

        void unsetAddrPin() {
            bsc.unsetAddrPin();
        }

        void enablePower() {
            bsc.controlPower(true);
        }


        void disablePower() {
            bsc.controlPower(false);
        }


        void enableSelect() {
            bsc.controlSelect(true);
        }


        void disableSelect() {
            bsc.controlSelect(false);
        }


        void enableAddr() {
            bsc.controlAddr(true);
        }


        void disableAddr() {
            bsc.controlAddr(false);
        }


    private:

        TLx493D(BusType &bus);


        BoardSupportType          bsc;
        BusWrapperType            busWrapper;
        TLx493D_IICAddressType_t  iicAddress;
};


/***
 * Specialization for SPI interface.
*/
template<typename BoardSupport, TLx493D_SupportedSensorType_t sensorType>
    class TLx493D<BoardSupport, SPIClassWrapper, sensorType> : public TLx493DBase {

    public:

        typedef BoardSupport                       BoardSupportType;
        typedef SPIClassWrapper                    BusWrapperType;
        typedef typename SPIClassWrapper::BusType  BusType;

 
        TLx493D(BusType &bus) : bsc(), busWrapper(bus) {
            tlx493d_init(&sensor, sensorType);
        }


        ~TLx493D() {
        }


        void init() {
            bsc.init(true);
            tlx493d_initBoardSupport(&sensor, bsc);
            tlx493d_initCommunication(&sensor, busWrapper); // includes call to busWrapper.init();
            setDefaultConfig();
        }


        void begin() {
            init();
        }


        void deinit() {
            tlx493d_deinitCommunication(&sensor); // includes call to busWrapper.deinit();
            tlx493d_deinit(&sensor);
            bsc.deinit();
        }


        void end() {
            deinit();
        }


        void setPowerPin(uint8_t pinNumber, uint8_t pinDirection, uint8_t pinEnableValue, uint8_t pinDisableValue,
                         uint8_t delayAfterDisable = 0, uint8_t  delayAfterEnable = 0) {
            bsc.setPowerPin(pinNumber, pinDirection, pinEnableValue, pinDisableValue, delayAfterDisable, delayAfterEnable);
        }


        void unsetPowerPin() {
            bsc.unsetPowerPin();
        }


        void setSelectPin(uint8_t pinNumber, uint8_t pinDirection, uint8_t pinEnableValue, uint8_t pinDisableValue,
                          uint8_t delayAfterDisable = 0, uint8_t  delayAfterEnable = 0) {
            bsc.setSelectPin(pinNumber, pinDirection, pinEnableValue, pinDisableValue, delayAfterDisable, delayAfterEnable);
        }


        void unsetSelectPin() {
            bsc.unsetSelectPin();
        }


        void enablePower() {
            bsc.controlPower(true);
        }


        void disablePower() {
            bsc.controlPower(false);
        }


        void enableSelect() {
            bsc.controlSelect(true);
        }


        void disableSelect() {
            bsc.controlSelect(false);
        }


    private:

        BoardSupportType  bsc;
        BusWrapperType    busWrapper;
};


#endif // TLX493D_HPP
