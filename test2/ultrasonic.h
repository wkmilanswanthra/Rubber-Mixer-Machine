/*
 * toUltra.h
 *
 * Created: 5/22/2022 7:48:03 PM
 *  Author: Nishshanka
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <util/delay.h>

void initUS();
uint8_t ultrasonic1();
uint8_t ultrasonic2();
uint8_t ultrasonic3();
void trigPulse();
uint8_t retDistance(double distance);


