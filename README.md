# ADXL345 Accelerometer using STM32 Board

Details on I2C communication and code: https://aquila-dev.vercel.app/blog/logic-analyzer-i2c-adxl/

Board used: STM32F401RE

Note: Add the following line to the local `gcc-arm-none-eabi.cmake` file:
```cmake
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -u _printf_float")  # enable printing floats
```