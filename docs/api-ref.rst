.. _api-ref:

API Reference
=============

TLx493D 3D Magnetic Sensor API
------------------------------

The following section shows you the API of the TLx493D base class.

.. doxygenclass:: ifx::tlx493d::TLx493DBase
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
   :members:
   :protected-members:
   :undoc-members:

TLx493D 3D Magnetic Sensor Arduino API
--------------------------------------

The following sections shows you the specific implementation of the Tlx493d classes for Arduino. The classes are inheriting most of their functionality from the Tlx493Base class, but also define the necessary interfaces (SPI, I2C) depending on the sensor.

.. doxygenclass:: ifx::tlx493d::TLx493D
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
   :members:
   :protected-members:
   :undoc-members:
.. doxygenfunction:: TLx493D(BusType &busObj, TLx493D_IICAddressType_t iicAdr = TLx493D_IIC_ADDR_A0_e) : busWrapper(busObj), iicAddress(iicAdr)
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: ~TLx493D()
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: init(bool enablePower = true, bool enableSelect = false, bool enableExtendedAdress = false, bool executeInit = true)
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: begin(bool enablePower = true, bool enableSelect = false, bool enableExtendedAdress = false, bool executeInit = true)
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: deinit(bool executeDeinit = false)
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: end(bool executeDeinit = false)
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: setPowerPin(uint8_t pinNumber, uint8_t pinDriveDirection, uint8_t pinTristateDirection, uint8_t pinEnableValue, pinDisableValue, uint32_t delayAfterEnable = 0, uint32_t delayAfterDisable = 0)
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: unsetPowerPin()
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: setSelectPin(uint8_t pinNumber, uint8_t pinDriveDirection, uint8_t pinTristateDirection, uint8_t pinEnableValue, uint8_t pinDisableValue, uint32_t delayAfterEnable = 0, uint32_t delayAfterDisable = 0)
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: unsetSelectPin()
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: setAddressPin(uint8_t pinNumber, uint8_t pinDriveDirection, uint8_t pinTristateDirection,uint8_t,pinEnableValue, uint8_t pinDisableValue, uint32_t delayAfterEnable = 0, uint32_t delayAfterDisable = 0)
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: unsetAddressPin()
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: enablePower()
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: disablePower()
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: reset(bool executeInit = false, bool executeDeinit = false)
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: enableSelect()
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: disableSelect()
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: enableAddress()
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: disableAddress()
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: TLx493D(BusType &bus)
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: 
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: 
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library

Logger API
----------

The following section shows you all the available logger functions, which can be utilized for debugging or printing out important information of the sensors, for example the internal register map.

.. doxygenfunction:: logPrintRegisters
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: logPrintDouble
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: logPrint
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: logPrintln
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: logInfo
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: logWarn
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: logError
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: logFlush
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library

Communication Interface
-----------------------

The following section shows you the important high-level functions of the communication interface. The :code:`tlx493d_transfer()` function is implemented for every sensor depending on its available interface (I2C, SPI).

.. doxygenfunction:: tlx493d_transfer
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: tlx493d_setReadAddress
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: ifx::tlx493d::deinitCommunication
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library

Kit2GoBoardSupport
------------------

The following section shows you how you can utilize the board support class for your applications. The Kit2GoBoardSupport class eases the usage of Kit2Go boards by giving the opportunity define for example power pins, which can be used to power up and power down the sensor. Or by defining chip select pins in case of a SPI interface.

.. doxygenfile:: Kit2GoBoardSupport.hpp
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library

Common Defines
--------------

The following section shows you the common defines off the different, available sensors. These defines can be used to exclude specific sensors from the compilation.

.. doxygenfile:: tlx493d_common_defines.h
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library