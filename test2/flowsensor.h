#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <util/delay.h>

void pump_w();
void pump_l();
void pump_a(int vol);
void timer_1();

void initUS();
uint8_t ultrasonic1();
uint8_t ultrasonic2();
uint8_t ultrasonic3();
void trigPulse();
uint8_t retDistance(double distance);


