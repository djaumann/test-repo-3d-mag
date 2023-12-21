/*********************************************************************
 * @file  Kit2GoBoardSupport.hpp
 * 
 * @brief Implementation of the class Kit2GoBoardSupport for custom sensor/board bring up.
 * This can be used to power cycle the sensor device, help with setting/resetting the SPI
 * slave select lines for multiple devices and also setting/resetting addressing lines 
 * for enabling extended addresses for certain devices.  
 *********************************************************************/

#ifndef TLX493D_KIT2GO_BOARD_SUPPORT_HPP
#define TLX493D_KIT2GO_BOARD_SUPPORT_HPP


// std include

// Arduino includes
#include <Arduino.h>

// project cpp includes
// #include "Logger.h"

/**
 * @brief The Kit2GoBoardSupport class used for custom board bring up, for control of SPI slave select lines 
 * and for controlling address lines for extended addressing of certain devices.
 */
class Kit2GoBoardSupport {

    public:
        /**
         * Create a new Kit2GoBoardSupport object with initialised datastructures of type PinCtrl to hold parameters for powerPins, selectPins
         * and addrPins.
         * @brief Default constructor with no parameters.
         */
        Kit2GoBoardSupport() : powerPins{false, 0, 0, 0, 0, 0, 0}, selectPins{false, 0, 0, 0, 0, 0, 0}, addrPins{false, 0, 0, 0, 0, 0, 0} {
        }
        /**
         * @brief The function `init` sets/resets the board pin modes and/or values based on the values of the datastructures set in the main code.  
         * 
         * @param[in] enablePower Whether to power up the board using this class. In this case the board 3V3 is routed through a GPIO of the host MCU.
         * @param[in] enableSelect Whether SPI slaves SELECT lines need to be controlled using this class. A particular slave is selected by pulling its 
         * corresponding SELECT line low.
         * @param[in] enableExtendedAddr (Only relevant for Generation 1, A1B6 devices) Whether to use extended addressing feature. In this case, the pin
         *  stored in addrPins structure is activated and later isolated in a prescribed way to enable the 4 extended addresses of the said device.        
         */
        void init(bool enablePower = true, bool enableSelect = false, bool enableExtendedAddr = false) {
            
            if(enableExtendedAddr){
                for(auto &p : addrPins){
                    if(p.isSet){
                        initPin(p, true);
                    }
                }
            }
            
            for(auto &p : powerPins) {
                initPin(p, enablePower);
            }

            if(enableExtendedAddr){
                controlAddr(false);
                for(auto &p : addrPins){
                    if(p.isSet){
                        pinMode(p.pinNumber, INPUT);
                    }
                }
            }

            for(auto &p : selectPins) {
                initPin(p, enableSelect);
            }
        }
        
        /**
         * @brief The `begin` function recursively calls the `init` function of the same class.
         * 
         * @param[in] enablePower Whether to power up the board using this class. In this case the board 3V3 is routed through a GPIO of the host MCU.
         * @param[in] enableSelect Whether SPI slaves SELECT lines need to be controlled using this class. A particular slave is selected by pulling its 
         * corresponding SELECT line low.
         * @param[in] enableExtendedAddr (Only relevant for Generation 1, A1B6 devices) Whether to use extended addressing feature. In this case, the pin
         *  stored in addrPins structure is activated and later isolated in a prescribed way to enable the 4 extended addresses of the said device.   
         */
        void begin(bool enablePower = true, bool enableSelect = false) {
            init(enablePower, enableSelect);
        }

        /**
         * @brief The `deinit` function sets all the pins to their disableValue.
         */
        void deinit() {
            for(auto &p : powerPins) {
                controlPin(p, false);
            }

            for(auto &p : selectPins) {
                controlPin(p, false);
            }
        }

        /**
         * @brief The `end` function recursively calls the `deinit` function of the same class.
         */
        void end() {
            deinit();
        }

        /**
         * @brief The `setPowerPin` function is setter function to route pin parameters from the main code into the datastructures/variables of this class.
         * 
         * @param[in] pinNumber Arduino pin number of the GPIO to be used as 3V3 POWER pin for the sensor.
         * @param[in] pinDirection Direction of the Arduino pin to be used as the 3V3 POWER pin.
         * @param[in] pinEnableValue Value of the pin in enabled state.
         * @param[in] pinDisableValue Value of the pin in disabled state.
         * @param[in] delayAfterDisable delay in ms after the pin is disabled. Needed to meet settling time constraints.
         * @param[in] delayAfterEnable delay in ms after the pin is enabled. Needed to meet settling time constraints.  
         */
        void setPowerPin(uint8_t pinNumber, uint8_t pinDirection, uint8_t pinEnableValue, uint8_t pinDisableValue,
                         uint8_t delayAfterDisable = 0, uint8_t  delayAfterEnable = 0) {
            powerPins[0] = { true, pinNumber, pinDirection, pinEnableValue, pinDisableValue, delayAfterDisable, delayAfterEnable };
        }

        /**
         * @brief The `unsetPowerPin` function disables all actions on the pins set in powerPins that would otherwise be performed by the `init` function.
         */
        void unsetPowerPin() {
            powerPins[0].isSet = false;
        }

        /**
         * @brief The `setSelectPin` function is setter function to route pin parameters from the main code into the datastructures/variables of this class.
         * @param[in] pinNumber Arduino pin number of the GPIO to be used as SELECT pin for the sensor used as SPI slave.
         * @param[in] pinDirection Direction of the Arduino pin to be used as the select pin for the sensor used as SPI slave.
         * @param[in] pinEnableValue Value of the pin in enabled state.
         * @param[in] pinDisableValue Value of the pin in disabled state.
         * @param[in] delayAfterDisable delay in ms after the pin is disabled. Needed to meet settling time constraints.
         * @param[in] delayAfterEnable delay in ms after the pin is enabled. Needed to meet settling time constraints.
         */
        void setSelectPin(uint8_t pinNumber, uint8_t pinDirection, uint8_t pinEnableValue, uint8_t pinDisableValue,
                          uint8_t delayAfterDisable = 0, uint8_t  delayAfterEnable = 0) {
            selectPins[0] = { true, pinNumber, pinDirection, pinEnableValue, pinDisableValue, delayAfterDisable, delayAfterEnable };
        }

        /**
         * @brief The `unsetSelectPin` function disables all actions on the pins set in selectPins that would otherwise be performed by the `init` function.
         */    
        void unsetSelectPin() {
            selectPins[0].isSet = false;
        }


        /**
         * @brief The `controlPower` function sets/resets the pins in powerPins based on argument.
         * 
         * @param[in] enable Sets pin to pinEnableValue if true, else to pinDisableValue.
         */
        void controlPower(bool enable) {
            for(auto &p : powerPins) {
                controlPin(p, enable);
            }
        }

        /**
         * @brief The `controlSelect` function sets/resets the pins in selectPins based on argument.
         * 
         * @param[in] enable Sets pin to pinEnableValue if true, else to pinDisableValue.
         */
        void controlSelect(bool enable) {
            for(auto &p : selectPins) {
                controlPin(p, enable);
            }
        }

        /**
         * @brief The `setAddrPin` function is setter function to route pin parameters from the main code into the datastructures/variables of this class.
         * 
         * @param[in] pinNumber Arduino pin number of the GPIO to be used as the ADDR pin for the sensor used as SPI slave.
         * @param[in] pinDirection Direction of the Arduino pin to be used as the ADDR pin for the sensor used as SPI slave.
         * @param[in] pinEnableValue Value of the pin in enabled state.
         * @param[in] pinDisableValue Value of the pin in disabled state.
         * @param[in] delayAfterDisable delay in ms after the pin is disabled. Needed to meet settling time constraints.
         * @param[in] delayAfterEnable delay in ms after the pin is enabled. Needed to meet settling time constraints.
         */
        void setAddrPin(uint8_t pinNumber, uint8_t pinDirection, uint8_t pinEnableValue, uint8_t pinDisableValue,
                         uint8_t delayAfterDisable = 0, uint8_t  delayAfterEnable = 0) {
            addrPins[0] = { true, pinNumber, pinDirection, pinEnableValue, pinDisableValue, delayAfterDisable, delayAfterEnable };
        }

        /**
         * @brief The `unsetAddrPin` function disables all actions on the pins set in selectPins that would otherwise be performed by the `init` function.
         */ 
        void unsetAddrPin() {
            addrPins[0].isSet = false;
        }

        /**
         * @brief The `controlAddr` function sets/resets the pins in selectPins based on argument.
         * 
         * @param enable Sets pin to pinEnableValue if true, else to pinDisableValue.
         */    
        void controlAddr(bool enable) {
            for(auto &p : addrPins) {
                controlPin(p, enable);
            }
        }


    private:
        /**
        * A structure to represent pins with all necessary parameters. 
        */
        typedef struct pinCtrl {
            /*@{*/
            bool     isSet;             /**< the state of the pin, to be activated at `init` or not. */
            uint8_t  pinNumber;         /**< the Arduino pin number of the pin. */
            uint8_t  direction;         /**< the direction for the Arduino pin. */
            uint8_t  enableValue;       /**< the value of the pin to be enabled or set by the `init` function. */
            uint8_t  disableValue;      /**< the value of the pin when the pin is disabled. */
            uint8_t  delayAfterDisable; /**< the delay in ms after the pin is disabled. */
            uint8_t  delayAfterEnable;  /**< the delay in ms after the pin is enabled. */
            /*@}*/
        } pinCtrl;

        /**
         * @brief The `controlPin` function sets/resets the pin on the basis of parameters in the structure `pinCtrl`.
         * 
         * @param[in] p Structure of type `pinCtrl`.
         * @param[in] enable Sets pin to pinEnableValue if true, else to pinDisableValue.
         */ 
        void controlPin(const pinCtrl &p, bool enable) {
            if( p.isSet ) {
                digitalWrite(p.pinNumber, enable ? p.enableValue : p.disableValue);
                // print("Setting select pin %d to %d\n", p.pinNumber, enable ? p.enableValue : p.disableValue);
                delay(enable ? p.delayAfterEnable : p.delayAfterDisable);
            }
        }

        /**
         * @brief The `initPin` function sets the direction and value of the pin on the basis of parameters in the structure `pinCtrl`.
         * 
         * @param[in] p Structure of type `pinCtrl`.
         * @param[in] enable Sets pin to pinEnableValue if true, else to pinDisableValue.
         */ 
        void initPin(const pinCtrl &p, bool enable) {
            pinMode(p.pinNumber, p.direction);
            controlPin(p, enable);
        }
    
        /**
        * Structure variables to hold parameters of powerPins, selectPins and addrPins.
        */ 
        pinCtrl powerPins[1];
        pinCtrl selectPins[1];
        pinCtrl addrPins[1];
};


#endif // TLX493D_KIT2GO_BOARD_SUPPORT_HPP
