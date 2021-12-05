
#ifndef INC_PCA9685_H_
#define INC_PCA9685_H_

#include "main.h"

#define LED0 0
#define LED1 1
#define LED2 2
#define LED3 3
#define LED4 4
#define LED5 5
#define LED6 6
#define LED7 7
#define LED8 8
#define LED9 9
#define LED10 10
#define LED11 11
#define LED12 12
#define LED13 13
#define LED14 14
#define LED15 15
#define SLEEP_MODE 0x10
#define START 0x01
#define AUTO_INC 0x20
#define INVRT 0x10
#define OCH 0x08
#define TOTEM 0x04
#define LED_HZ 0x02
#define LED_OUTDRV 0x01



#pragma pack(push, 1)
typedef struct
	{
		uint8_t address;
		uint16_t on;
		uint16_t off;
	}LEDt;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
	{
		LEDt led[16];
		LEDt all_led;
		uint8_t mode1;
		uint8_t mode2;
		uint8_t PWM_presc;
		uint8_t DevAddress;
		void (*i2c_write)(uint8_t DevAddress,uint8_t *pData, uint16_t num);
		void (*OEn_pin)(uint8_t value);

	}PCA9685_dev;
#pragma pack(pop)

uint8_t PCA9685_Init(PCA9685_dev* dev,uint8_t DevAddress, uint8_t mode1, uint8_t mode2);

void PCA9685_SET_Led(PCA9685_dev* dev,  uint8_t num, uint16_t on, uint16_t off);

void PCA9685_SET_AllLed(PCA9685_dev* dev,  uint16_t on, uint16_t off);

void PCA9685_SET_PWMfrequency(PCA9685_dev* dev, uint16_t frq);

void PCA9685_GO_SleepMode(PCA9685_dev* dev);

void PCA9685_OUT_SleepMode(PCA9685_dev* dev);

#endif /* INC_PCA9685_H_ */
