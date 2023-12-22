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

/**
 * @brief Specialization of the template class `TLx493D` for the IIC interface
 * 
 * @tparam BoardSupport A helper class, which takes care of needed power pins as well user defined pins.
 * @tparam sensorType   Specific sensor type of the used sensor.
 */
template<typename BoardSupport, TLx493D_SupportedSensorType_t sensorType>
    class TLx493D<BoardSupport, TwoWireWrapper, sensorType> : public TLx493DBase {

    public:

        typedef BoardSupport                      BoardSupportType;
        typedef TwoWireWrapper                    BusWrapperType;
        typedef typename TwoWireWrapper::BusType  BusType;

        /**
         * @brief The function `TLx493D` is the constructor of the template class.
         * It is calling the corresponding common initialization function of the sensor, depending
         * on the chosen parameters in the constructor.
         * 
         * @param[in] bus       Bus type of the used sensor
         * @param[in] iicAdr    I2C Address of the sensor, by default address A0 is chosen.
         */
        TLx493D(BusType &bus, TLx493D_IICAddressType_t iicAdr = TLx493D_IIC_ADDR_A0_e) : bsc(), busWrapper(bus), iicAddress(iicAdr) {
            tlx493d_init(&sensor, sensorType);
        }

        /**
         * @brief The function `~TLx493D` is the destructor of the template class.
         * 
         */
        ~TLx493D() {
        }

        /**
         * @brief The function `init` initializes all necessary peripherals of the chosen sensor board.
         * It initializes the BoardSupportClass, the communication interface and calls the `setDefaultConfig`
         * function in order to disable the interrupt of the sensor and putting it into 1-Byte-Read-Mode.
         * 
         * @param[in] enablePower           Tells the BoardSupportClass, whether it should turn the power pins on
         * or keep them off at initialization. 
         * @param[in] enableSelect          Tells the BoardSupportClass, whether it should turn the select pins on
         * or keep them off at initialization.
         * @param[in] enableExtendedAddr    Enable or disable the extended address feature of the sensor.
         */
        void init(bool enablePower = true, bool enableSelect = false, bool enableExtendedAddr = false) {
            bsc.init(enablePower, enableSelect, enableExtendedAddr);
            tlx493d_initBoardSupport(&sensor, bsc);
            tlx493d_initCommunication(&sensor, busWrapper, iicAddress); // includes call to busWrapper.init();
            setDefaultConfig();
        }

        /**
         * @brief The function `begin` calls the `init` function with the corresponding parameters.
         * Detailed description see `init`function.
         * 
         * @param[in] enablePower           Tells the BoardSupportClass, whether it should turn the power pins on
         * or keep them off at initialization. True - by default.
         * @param[in] enableSelect          Tells the BoardSupportClass, whether it should turn the select pins on
         * or keep them off at initialization. False - by default.
         * @param[in] enableExtendedAddr    Enable or disable the extended address feature of the sensor.
         * False - by default.
         */
        void begin(bool enablePower = true, bool enableSelect = false, bool enableExtendedAddr = false) {
            init(enablePower, enableSelect, enableExtendedAddr);
        }

        /**
         * @brief The function `deinit` de-initializes the sensor and its peripherals.
         * It de-initializes the communication interface, the BoardSupportClass as well as
         * all allocated memory (free the memory to be precise).
         */
        void deinit() {
            tlx493d_deinitCommunication(&sensor); // includes call to busWrapper.deinit();
            tlx493d_deinit(&sensor);
            bsc.deinit();
        }

        /**
         * @brief The function `end` calls the `deinit` function.
         * For details take a look at the `deinit` function.
         * 
         */
        void end() {
            deinit();
        }

        /**
         * @brief The function `setPowerPin` defines a power pin, which can be used to power up the sensor.
         * 
         * @param[in] pinNumber             Pin number of the desired pin.
         * @param[in] pinDirection          Pin direction of the pin (OUTPUT, INPUT, INPUT-PULLUP).
         * @param[in] pinEnableValue        Value to enable the power pin, depends on the pin (Active high or low).
         * @param[in] pinDisableValue       Value to disable the power pin, depends on the pin (Active high or low).
         * @param[in] delayAfterDisable     Delay after disabling the power pin in [ms].
         * @param[in] delayAfterEnable      Delay after enabling the power pin in [ms].
         */
        void setPowerPin(uint8_t pinNumber, uint8_t pinDirection, uint8_t pinEnableValue, uint8_t pinDisableValue,
                         uint8_t delayAfterDisable = 0, uint8_t  delayAfterEnable = 0) {
            bsc.setPowerPin(pinNumber, pinDirection, pinEnableValue, pinDisableValue, delayAfterDisable, delayAfterEnable);
        }

        /**
         * @brief The function `unsetPowerPin` does remove the power pin from the BoardSupportClass.
         * 
         */
        void unsetPowerPin() {
            bsc.unsetPowerPin();
        }

        /**
         * @brief The function `setSelectPin` defines a select pin, which can be used as chip select for
         * the SPI communication.
         * 
         * @param[in] pinNumber             Pin number of the desired pin.
         * @param[in] pinDirection          Pin direction of the pin (OUTPUT, INPUT, INPUT-PULLUP).
         * @param[in] pinEnableValue        Value to enable the power pin, depends on the pin (Active high or low).
         * @param[in] pinDisableValue       Value to disable the power pin, depends on the pin (Active high or low).
         * @param[in] delayAfterDisable     Delay after disabling the power pin in [ms].
         * @param[in] delayAfterEnable      Delay after enabling the power pin in [ms]. 
         */
        void setSelectPin(uint8_t pinNumber, uint8_t pinDirection, uint8_t pinEnableValue, uint8_t pinDisableValue,
                          uint8_t delayAfterDisable = 0, uint8_t  delayAfterEnable = 0) {
            bsc.setSelectPin(pinNumber, pinDirection, pinEnableValue, pinDisableValue, delayAfterDisable, delayAfterEnable);
        }

        /**
         * @brief The function `unsetSelectPin` does remove the select pin from the BoardSupportClass.
         * 
         */
        void unsetSelectPin() {
            bsc.unsetSelectPin();
        }

        /**
         * @brief The function `setAddrPin` defines a pin, which can be used for the extended address feature of the first
         * sensor generation. Here the SDA-line of the I2C bus has to be pulled low in order to use
         * the second half of addresses.
         * 
         * @param[in] pinNumber             Pin number of the desired pin.
         * @param[in] pinDirection          Pin direction of the pin (OUTPUT, INPUT, INPUT-PULLUP).
         * @param[in] pinEnableValue        Value to enable the power pin, depends on the pin (Active high or low).
         * @param[in] pinDisableValue       Value to disable the power pin, depends on the pin (Active high or low).
         * @param[in] delayAfterDisable     Delay after disabling the power pin in [ms].
         * @param[in] delayAfterEnable      Delay after enabling the power pin in [ms]. 
         */
        void setAddrPin(uint8_t pinNumber, uint8_t pinDirection, uint8_t pinEnableValue, uint8_t pinDisableValue,
                         uint8_t delayAfterDisable = 0, uint8_t  delayAfterEnable = 0) {
            bsc.setAddrPin(pinNumber, pinDirection, pinEnableValue, pinDisableValue, delayAfterDisable, delayAfterEnable);
        }

        /**
         * @brief The function `unsetAddrPin` does remove the address pin from the BoardSupportClass.
         * 
         */
        void unsetAddrPin() {
            bsc.unsetAddrPin();
        }

        /**
         * @brief The function `enablePower` enables the defined power pin.
         * 
         */
        void enablePower() {
            bsc.controlPower(true);
        }

        /**
         * @brief The function `disablePower` disables the defined power pin.
         * 
         */
        void disablePower() {
            bsc.controlPower(false);
        }

        /**
         * @brief The function `enableSelect` enables the defined select pin.
         * 
         */
        void enableSelect() {
            bsc.controlSelect(true);
        }

        /**
         * @brief The function `disableSelect` disables the defined select pin.
         * 
         */
        void disableSelect() {
            bsc.controlSelect(false);
        }

        /**
         * @brief The function `enableAddr` enables the defined address pin.
         * 
         */
        void enableAddr() {
            bsc.controlAddr(true);
        }

        /**
         * @brief The function `disableAddr` disables the defined address pin.
         * 
         */
        void disableAddr() {
            bsc.controlAddr(false);
        }


    private:

        /**
         * @brief The function `TLx493D` is the overloaded constructor of the template class.
         * 
         * @param[in] bus Bus type of the chose sensor board.
         */
        TLx493D(BusType &bus);


        BoardSupportType          bsc;          /**< BoardSupportClass */
        BusWrapperType            busWrapper;   /**< BusWrapperClass */
        TLx493D_IICAddressType_t  iicAddress;   /**< I2C-Address of the sensor */
};


/**
 * @brief Specialization of the template class `TLx493D` for the SPI interface
 * 
 * @tparam BoardSupport A helper class, which takes care of needed power pins as well user defined pins.
 * @tparam sensorType   Specific sensor type of the used sensor.
 */
template<typename BoardSupport, TLx493D_SupportedSensorType_t sensorType>
    class TLx493D<BoardSupport, SPIClassWrapper, sensorType> : public TLx493DBase {

    public:

        typedef BoardSupport                       BoardSupportType;
        typedef SPIClassWrapper                    BusWrapperType;
        typedef typename SPIClassWrapper::BusType  BusType;

        /**
         * @brief The function `TLx493D` is the constructor of the template class.
         * 
         * @param[in] bus Bus type of the chosen sensor.
         */
        TLx493D(BusType &bus) : bsc(), busWrapper(bus) {
            tlx493d_init(&sensor, sensorType);
        }

        /**
         * @brief The function `~TLx493D` is the constructor of the template class.
         * 
         */
        ~TLx493D() {
        }

        /**
         * @brief The function `init` initializes all necessary peripherals of the chosen sensor board.
         * It initializes the BoardSupportClass, the communication interface and calls the `setDefaultConfig`
         * function
         *
         */
        void init() {
            bsc.init(true);
            tlx493d_initBoardSupport(&sensor, bsc);
            tlx493d_initCommunication(&sensor, busWrapper); // includes call to busWrapper.init();
            setDefaultConfig();
        }

        /**
         * @brief The function `begin` calls the `init` function.
         * For details see `init` function.
         * 
         */
        void begin() {
            init();
        }


        /**
         * @brief The function `deinit` de-initializes the sensor and its peripherals.
         * It de-initializes the communication interface, the BoardSupportClass as well as
         * all allocated memory (free the memory to be precise).
         * 
         */
        void deinit() {
            tlx493d_deinitCommunication(&sensor); // includes call to busWrapper.deinit();
            tlx493d_deinit(&sensor);
            bsc.deinit();
        }

        /**
         * @brief The function `end` calls the `deinit` function.
         * For details see `deinit`function.
         * 
         */
        void end() {
            deinit();
        }

        /**
         * @brief The function `setPowerPin` defines a power pin, which can be used to power up the sensor.
         * 
         * @param[in] pinNumber             Pin number of the desired pin.
         * @param[in] pinDirection          Pin direction of the pin (OUTPUT, INPUT, INPUT-PULLUP).
         * @param[in] pinEnableValue        Value to enable the power pin, depends on the pin (Active high or low).
         * @param[in] pinDisableValue       Value to disable the power pin, depends on the pin (Active high or low).
         * @param[in] delayAfterDisable     Delay after disabling the power pin in [ms].
         * @param[in] delayAfterEnable      Delay after enabling the power pin in [ms].
         */
        void setPowerPin(uint8_t pinNumber, uint8_t pinDirection, uint8_t pinEnableValue, uint8_t pinDisableValue,
                         uint8_t delayAfterDisable = 0, uint8_t  delayAfterEnable = 0) {
            bsc.setPowerPin(pinNumber, pinDirection, pinEnableValue, pinDisableValue, delayAfterDisable, delayAfterEnable);
        }

        /**
         * @brief The function `unsetPowerPin` does remove the power pin from the BoardSupportClass.
         * 
         */
        void unsetPowerPin() {
            bsc.unsetPowerPin();
        }

        /**
         * @brief The function `setSelectPin` defines a select pin, which can be used as chip select for
         * the SPI communication.
         * 
         * @param[in] pinNumber             Pin number of the desired pin.
         * @param[in] pinDirection          Pin direction of the pin (OUTPUT, INPUT, INPUT-PULLUP).
         * @param[in] pinEnableValue        Value to enable the power pin, depends on the pin (Active high or low).
         * @param[in] pinDisableValue       Value to disable the power pin, depends on the pin (Active high or low).
         * @param[in] delayAfterDisable     Delay after disabling the power pin in [ms].
         * @param[in] delayAfterEnable      Delay after enabling the power pin in [ms]. 
         */
        void setSelectPin(uint8_t pinNumber, uint8_t pinDirection, uint8_t pinEnableValue, uint8_t pinDisableValue,
                          uint8_t delayAfterDisable = 0, uint8_t  delayAfterEnable = 0) {
            bsc.setSelectPin(pinNumber, pinDirection, pinEnableValue, pinDisableValue, delayAfterDisable, delayAfterEnable);
        }

        /**
         * @brief The function `unsetSelectPin` does remove the select pin from the BoardSupportClass.
         * 
         */
        void unsetSelectPin() {
            bsc.unsetSelectPin();
        }

        /**
         * @brief The function `enablePower` enables the defined power pin.
         * 
         */
        void enablePower() {
            bsc.controlPower(true);
        }

        /**
         * @brief The function `disablePower` disables the defined power pin.
         * 
         */
        void disablePower() {
            bsc.controlPower(false);
        }

        /**
         * @brief The function `enableSelect` enables the defined select pin.
         * 
         */
        void enableSelect() {
            bsc.controlSelect(true);
        }

        /**
         * @brief The function `disableSelect` disables the defined select pin.
         * 
         */
        void disableSelect() {
            bsc.controlSelect(false);
        }


    private:

        BoardSupportType  bsc;          /**< BoardSupportClass */
        BusWrapperType    busWrapper;   /**< BusWrapperClass */
};


#endif // TLX493D_HPP
