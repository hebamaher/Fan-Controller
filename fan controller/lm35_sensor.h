/*
 * lm35_sensor.h
 *
 *  Created on: Oct 9, 2023
 *      Author: Eng Heba
 */

#ifndef LM35_SENSOR_H_
#define LM35_SENSOR_H_

#include "std_types.h"

#define SENSOR_CHANNEL_ID         2
#define SENSOR_MAX_TEMPERATURE    150
#define SENSOR_MAX_VOLT           1.5

uint8 LM35_getTemperature(void);


#endif /* LM35_SENSOR_H_ */
