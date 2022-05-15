/*
 * solenoid.h
 *
 * Created: 4/16/2021 8:35:36 AM
 *  Author: Achintha
 */ 


#ifndef SOLENOID_H_
#define SOLENOID_H_

#ifndef F_CPU
#define F_CPU 800000UL
#endif

#include <avr/io.h>

#define pHMax 7.00
#define pHMIn 6.00

void init_solenoid_ports();         //initialize ports
void operate_solenoid(float pH);    //operate solenoid valve



#endif /* SOLENOID_H_ */