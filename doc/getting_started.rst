Getting Started
===============

In this quick tutorial we will go through one of the |TM| library examples, which is available for all the sensors supported by this Arduino library.
We will use the XMC 2Go as microcontroller, but you can choose any of the `supported platforms <link>`_ in order to get this example working.

Required Hardware
-----------------

.. list-table:: 
  :widths: 50 50
  :header-rows: 1

  * - Name
    - Picture
  * - `XENSIV™ 3D Magnetic Sensor TLE493D-W2B6 <https://www.infineon.com/cms/en/product/evaluation-boards/s2go_3d_tle493dw2b6-a0/>`_
    - .. image:: img/TLE493D_W2B6_2GO.jpg
          :height: 60
  * - `XMC 2Go <https://www.infineon.com/cms/de/product/evaluation-boards/kit_xmc_2go_xmc1100_v1/>`_ (only needed if you chose a shield 2Go)
    - .. image:: img/xmc2go.jpg
          :height: 60
  * - Magnet
    - .. image:: img/magnet.jpg
          :height: 60
          :target: https://www.digikey.de/de/products/detail/radial-magnets-inc/8170/5400486 
  * - Pin headers (included with the XMC 2Go)
    - .. image:: img/pin_headers.jpg
          :target: https://www.digikey.de/de/products/detail/te-connectivity-amp-connectors/5-146280-4/5008688
          :height: 60
  * - Micro-USB to USB-A cable
    - .. image:: img/usb_cable.jpg
          :height: 60
          :target: https://www.digikey.de/de/products/detail/molex/0687840002/1952431  

Required Software
-----------------

- `Segger J-Link <https://www.segger.com/downloads/jlink>`_
- `Arduino IDE <https://www.arduino.cc/en/main/software>`_
- `XMC-for-Arduino <https://github.com/Infineon/XMC-for-Arduino>`_
- `XENSIV™ 3D Magnetic Sensors TLx493D Arduino Library <test>`_

Software Installation
---------------------

0. **Install the Arduino IDE**. If you are new to Arduino, please `download <https://www.arduino.cc/en/Main/Software>`_
the program and install it first.

1. **Install the XMC Board**. The official Arduino boards are already available in the Arduino IDE, but other third party boards
,like the Infineon MCUs, need to be explicitly included in order to use them. Follow the instructions in the `link <>`_ to add the
XMC MCU family to the Arduino IDE. Do not forget to install the the J-Link-Software as well.


2. **Install the library**. In the Arduino IDE, go to the menu *Sketch > Include Library > Library Manager*. Type *XENSIV 3D Magnetic Sensor TLx493D*
and install the library.

.. image:: img/
  :width: 500

Hardware Setup
--------------

For this example we will use the SPI interface of the MCU.











.. |TM| replace:: XENSIV™ 3D Magnetic Sensors TLx493D
.. _TM: https:://infineon.com/