#include "main.h"
#include "pca9685.h"

uint8_t PCA9685_Init(PCA9685_dev* dev,uint8_t DevAddress, uint8_t mode1, uint8_t mode2)
{
	if ((dev->i2c_write == NULL) || (dev->OEn_pin == NULL))
		return 0;
	dev->OEn_pin(0);
	//HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET);
	uint8_t data[2];
	data[0] = 0;	//вибирамо мод
	data[1] = mode1;//параметри мода

	dev->DevAddress = 0x80|(DevAddress<<1);
	dev->mode1 = data[1];
	for(uint8_t i = 0; i < 16; i++)
	{
		dev->led[i].address = 0x06+i*4;
	}
	dev->all_led.address = 0xFA;
	dev->i2c_write(dev->DevAddress,data,2);
	//HAL_I2C_Master_Transmit(hi2c,dev->DevAddress,data,2,1000);

	data[0] = 0x01;	//вибирамо мод
	data[1] = mode2;//параметри мода

	dev->mode2 = data[1];
	dev->i2c_write(dev->DevAddress,data,2);
	//HAL_I2C_Master_Transmit(hi2c,dev->DevAddress,data,2,1000);
	return 1;
}

void PCA9685_SET_Led(PCA9685_dev* dev,  uint8_t num, uint16_t on, uint16_t off)
{
	if(num<16)
	{
		dev->led[num].on = on;
		dev->led[num].off = off;
		dev->i2c_write(dev->DevAddress,(uint8_t*) &dev->led[num],(uint16_t) sizeof(dev->led[num]));
		//HAL_I2C_Master_Transmit(hi2c,dev->DevAddress,(uint8_t*) &dev->led[num],(uint16_t) sizeof(dev->led[num]),100);
	}

}

void PCA9685_SET_AllLed(PCA9685_dev* dev,  uint16_t on, uint16_t off)
{
	dev->all_led.on = on;
	dev->all_led.off = off;
	dev->i2c_write(dev->DevAddress,(uint8_t*) &dev->all_led,(uint16_t) sizeof(dev->all_led));
	//HAL_I2C_Master_Transmit(hi2c,dev->DevAddress,(uint8_t*) &dev->all_led,(uint16_t) sizeof(dev->all_led),100);
}

void PCA9685_SET_PWMfrequency(PCA9685_dev* dev, uint16_t frq)
{
	 unsigned char data[2];
	 data[0] = 254; //номер регістра
	 data[1] = (((uint16_t)48828/frq)>>3)-1;
	 dev->PWM_presc = data[1];
	 dev->i2c_write(dev->DevAddress,data,2);
	 //HAL_I2C_Master_Transmit(hi2c,dev->DevAddress,data,2,1000);

}


void PCA9685_GO_SleepMode(PCA9685_dev* dev)
{
	uint8_t data[2];
	data[0] = 0;	//вибирамо мод
	data[1] = dev->mode1 | SLEEP_MODE;		//параметри мода
	dev->i2c_write(dev->DevAddress,data,2);
	//HAL_I2C_Master_Transmit(hi2c,dev->DevAddress,data,2,1000);
}

void PCA9685_OUT_SleepMode(PCA9685_dev* dev)
{
	uint8_t data[2];
	data[0] = 0;	//вибирамо мод
	data[1] = dev->mode1;		//параметри мода
	dev->i2c_write(dev->DevAddress,data,2);
	//HAL_I2C_Master_Transmit(hi2c,dev->DevAddress,data,2,1000);
}


