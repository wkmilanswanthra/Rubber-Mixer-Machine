cmake_minimum_required(VERSION 3.20)
project(test2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(test2
        adc.h
        cust_lcd4.c
        cust_lcd4.h
        dc.h
        flowsensor.h
        i2c.h
        IRSensor.h
        keypad.c
        keypad.h
        lcd_func.h
        LCD_I2C.h
        lcd_lib.c
        lcd_lib.h
        main.c
        relayEx.c
        sensor.h
        Stepper_motors.h
        ToRelay.h)
