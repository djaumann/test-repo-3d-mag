
.. _namespace_ifx:

Namespace ifx
=============


The ``initBoardSupport`` function initializes the board support class. It can be used to define power, address and select pins and makes the handling with Kit2GOs easier for the user. 




.. contents:: Contents
   :local:
   :backlinks: none




Detailed Description
--------------------

The function ``initCommunication`` initializes the communication interface of the sensor. In this case it initializes the I2C-interface. The initialized interfaces depends on the chosen sensor and is determined automatically.

std includes. project c includes. project cpp includes.

std includes. Arduino includes. project cpp includes. project c includes. 



sensor


A pointer to a :ref:`exhale_struct_struct_t_lx493_d__t` struct, which represents the TLx493D sensor. 




bsc


A pointer to a board support class instance.



The function ``initBoardSupport`` returns a bool value to indicate if the execution was successful. 



0


Error. 




1


Successful.



std includes. Arduino includes. project cpp includes. project c includes. 



sensor


A pointer to a :ref:`exhale_struct_struct_t_lx493_d__t` struct, which represents the TLx493D sensor. 




tw


A reference to an instance of the TwoWire object. 




iicAdr


The I2C address of the sensor. See ``TLx493D_IICAddressType_t`` for the available ones. 




executeInit


A boolean flag which determines if the initialization is executed or not.



Returns a boolean to indicate if the function execution was successful or not. 



0


Error. 




1


Success.



std includes project cpp includes project c includes

Arduino includes 





Namespaces
----------


- :ref:`namespace_ifx__tlx493d`
