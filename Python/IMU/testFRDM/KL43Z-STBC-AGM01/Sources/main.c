/* #############################################################################
**     Filename    : main.c
**     Project     : FRDM-KL25Z FRDM-STBC-AGM01
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-07-23, 11:21, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
********************************************************************************
* This code has been written for the Freescale FRDM-KL25Z + FRDM-STBC-AGM01
* boards using KDS3.0.0 and Processor Expert and demonstrates how to read
* the acceleration + magnetic data from the FXOS8700CQ and angular rate
* + temperature from the FXAS21002C gyroscope using an interrupt technique.
*
* Both sensors are controlled via I2C by default.
*
* I2C slave addresses:
* FXOS8700 -> 0x1E
* FXAS21002 -> 0x20
*
* J5 selects the 21002 reset:
*   2:3 -> uses MCU reset
*
* J6 selects MCU I2C bus for SCL1_SCLK:
*   2:3 -> I2C_SCL1 (PTC1)
*
* J7 selects MCU I2C bus for SDA1_MOSI:
*    2:3 -> I2C_SDA1 (PTC2)
*
* INT1_8700 connected to PTD4 pin, INT1_21002 connected to PTA5 pin
*
* A detailed description of this example is available on the sensors community
* web page at https://community.freescale.com/docs/DOC-101192
** ############################################################################*/

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "clockMan1.h"
#include "pin_init.h"
#include "osa1.h"
#include "i2cCom1.h"
#include "gpio1.h"
#include "WAIT1.h"
#include "DbgCs1.h"
#if CPU_INIT_CONFIG
  #include "Init_Config.h"
#endif

#include "FXAS21002C.h"					// Include declarations of FXAS21002C registers
#include "FXOS8700CQ.h"					// Include declarations of FXAS21002C registers

/******************************************************************************
* Global variables and constants
******************************************************************************/

uint8_t AccelMagData[12];
int16_t Xout_Accel_14_bit, Yout_Accel_14_bit, Zout_Accel_14_bit;
float Xout_g, Yout_g, Zout_g;
int16_t Xout_Mag_16_bit, Yout_Mag_16_bit, Zout_Mag_16_bit;
float Xout_uT, Yout_uT, Zout_uT;

uint8_t GyroData[6];
int16_t Xout_Gyro_16_bit, Yout_Gyro_16_bit, Zout_Gyro_16_bit;
float Roll, Pitch, Yaw;
int8_t Temp;

bool FXOS8700CQ_DataReady, FXAS21002C_DataReady;

/******************************************************************************
* Functions
******************************************************************************/

void FXOS8700CQ_Init(void);
void FXAS21002C_Init(void);

/******************************************************************************
* Main
******************************************************************************/
extern unsigned char flag_but1, flag_but2;
extern unsigned int i;
unsigned int but1 = 0, but2 = 0;

int main(void)
{
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  FXOS8700CQ_DataReady = 1;
  FXAS21002C_DataReady = 1;

  FXOS8700CQ_Init();
  FXAS21002C_Init();


  for(;;)	//if(flag_but1==1)
  {
	 but1 = i%2;
	 but2 = i%5;

		//  if (FXOS8700CQ_DataReady && (flag_but1==1))		// Is a new set of accel+mag data ready?


	if(but2 == 0){
		 debug_printf("press button-1 to start Accel press again for Magnetometer and Gyro data\r\n");
		 //debug_getchar();
		 WAIT1_Waitms(50);
	}

	if (FXOS8700CQ_DataReady ) //&& (but2==1)
			if (but2 == 1)
				{
						  //FXOS8700CQ_DataReady = 0;
						 // FXAS21002C_DataReady = 1;

						  FXOS8700CQ_ReadRegisters(OUT_X_MSB_REG, 12, AccelMagData);		// Read FXOS8700CQ data output registers 0x01-0x06 and 0x33 - 0x38

						  // 14-bit accelerometer data
						  Xout_Accel_14_bit = ((int16_t) (AccelMagData[0]<<8 | AccelMagData[1])) >> 2;		// Compute 14-bit X-axis acceleration output value
						  Yout_Accel_14_bit = ((int16_t) (AccelMagData[2]<<8 | AccelMagData[3])) >> 2;		// Compute 14-bit Y-axis acceleration output value
						  Zout_Accel_14_bit = ((int16_t) (AccelMagData[4]<<8 | AccelMagData[5])) >> 2;		// Compute 14-bit Z-axis acceleration output value

						  FXOS8700CQ_DataReady = 0;
						  debug_printf("Accelerometer 14-bit data 	X:%d		Y:%d		Z:%d \r\n",Xout_Accel_14_bit, Yout_Accel_14_bit, Zout_Accel_14_bit);

				  }

				else if(but2==2){
							  FXOS8700CQ_ReadRegisters(OUT_X_MSB_REG, 12, AccelMagData);

							  Xout_Mag_16_bit = (int16_t) (AccelMagData[6]<<8 | AccelMagData[7]);		// Compute 16-bit X-axis magnetic output value
							  Yout_Mag_16_bit = (int16_t) (AccelMagData[8]<<8 | AccelMagData[9]);		// Compute 16-bit Y-axis magnetic output value
							  Zout_Mag_16_bit = (int16_t) (AccelMagData[10]<<8 | AccelMagData[11]);		// Compute 16-bit Z-axis magnetic output value

							  FXOS8700CQ_DataReady = 0;
							  debug_printf(" Magnetometer 16-bit data 		X:%d		Y:%d		Z:%d \r\n",Xout_Mag_16_bit, Yout_Mag_16_bit, Zout_Mag_16_bit);
						  }


		 if (FXAS21002C_DataReady )		// Is a new set of gyro data ready? //&& (but1==1)
				  if((but2==3))
						{
						  //FXAS21002C_DataReady = 0;
						  //FXOS8700CQ_DataReady = 1;
						  //WAIT1_Waitms(5);
						  FXAS21002C_ReadRegisters(GYRO_OUT_X_MSB_REG, 6, GyroData);		// Read FXAS21002C data output registers 0x01-0x06

						  // 16-bit gyro data
						  Xout_Gyro_16_bit = (int16_t) (GyroData[0]<<8 | GyroData[1]);		// Compute 16-bit X-axis output value
						  Yout_Gyro_16_bit = (int16_t) (GyroData[2]<<8 | GyroData[3]);		// Compute 16-bit Y-axis output value
						  Zout_Gyro_16_bit = (int16_t) (GyroData[4]<<8 | GyroData[5]);		// Compute 16-bit Z-axis output value

						  // Gyro data converted to dps
						  Roll = (float) (Xout_Gyro_16_bit) / SENSITIVITY_250;			// Compute X-axis output value in dps
						  Pitch = (float) (Yout_Gyro_16_bit) / SENSITIVITY_250;			// Compute Y-axis output value in dps
						  Yaw = (float) (Zout_Gyro_16_bit) / SENSITIVITY_250;			// Compute Z-axis output value in dps

						  FXAS21002C_DataReady = 0;

						  debug_printf("Gyro 16-bit data 	X axis:	%d		Y axis:	%d		Z axis:	%d \r\n",Xout_Gyro_16_bit, Yout_Gyro_16_bit, Zout_Gyro_16_bit);

					   }
				  	else if((but2==4)) //temperature
					  {
						  FXAS21002C_ReadRegisters(GYRO_TEMP_REG, 1, GyroData);
						  Temp = (int8_t) (GyroData[0]);
						  debug_printf("Temperature value is: 	%d degC\r\n",Temp);

					  }
	  }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/******************************************************************************
* FXOS8700CQ initialization function
******************************************************************************/

void FXOS8700CQ_Init (void)
{
	FXOS8700CQ_WriteRegister(CTRL_REG2, 0x40);          // Reset all registers to POR values
	WAIT1_Waitms(1);

	//WAIT1_Waitms(5);

	FXOS8700CQ_WriteRegister(XYZ_DATA_CFG_REG, 0x00);		// +/-2g range with 0.244mg/LSB

	FXOS8700CQ_WriteRegister(M_CTRL_REG1, 0x1F);		// Hybrid mode (accelerometer + magnetometer), max OSR
	FXOS8700CQ_WriteRegister(M_CTRL_REG2, 0x20);		// M_OUT_X_MSB register 0x33 follows the OUT_Z_LSB register 0x06 (used for burst read)

	FXOS8700CQ_WriteRegister(CTRL_REG2, 0x02);      // High Resolution mode
	FXOS8700CQ_WriteRegister(CTRL_REG3, 0x00);		// Push-pull, active low interrupt
	FXOS8700CQ_WriteRegister(CTRL_REG4, 0x01);		// Enable DRDY interrupt
	FXOS8700CQ_WriteRegister(CTRL_REG5, 0x01);		// DRDY interrupt routed to INT1 - PTD4
	FXOS8700CQ_WriteRegister(CTRL_REG1, 0x25);		// ODR = 25Hz, Reduced noise, Active mode
}

/******************************************************************************
* FXAS21002C initialization function
******************************************************************************/

void FXAS21002C_Init (void)
{
	FXAS21002C_WriteRegister(GYRO_CTRL_REG1, 0x40);			// Reset all registers to POR values
	WAIT1_Waitms(1);

	FXAS21002C_WriteRegister(GYRO_CTRL_REG0, 0x03);			// High-pass filter disabled, +/-250 dps range -> 7.8125 mdps/LSB = 128 LSB/dps
	FXAS21002C_WriteRegister(GYRO_CTRL_REG2, 0x0C);			// Enable DRDY interrupt, mapped to INT1 - PTA5, push-pull, active low interrupt
	FXAS21002C_WriteRegister(GYRO_CTRL_REG1, 0x16);			// ODR = 25Hz, Active mode
}

/******************************************************************************
* Write the specified register of FXAS21002C.
* The reading process is through I2C.
******************************************************************************/

FXAS_status_t FXAS21002C_WriteRegister(uint8_t reg, uint8_t val)
{
	uint8_t cmd[1], buff[1];
	uint8_t retval = 0;

	cmd[0] = reg;
	buff[0] = val;

	retval = I2C_DRV_MasterSendDataBlocking (FSL_I2CCOM1, &i2cCom1_MasterConfig0, cmd, 1, buff, 1, 500);

	if(retval != kStatus_I2C_Success)
	{
		return kStatus_FXOS_I2CFail;
	}
	return kStatus_FXOS_Success;
}

/******************************************************************************
* Read the specified register value of FXAS21002C.
* The reading process is through I2C.
******************************************************************************/

FXAS_status_t FXAS21002C_ReadRegisters(uint8_t reg, uint8_t n, uint8_t *val)
{
	uint8_t cmd[1];
	uint8_t retval = 0;

	cmd[0] = reg;

    retval = I2C_DRV_MasterReceiveDataBlocking(FSL_I2CCOM1, &i2cCom1_MasterConfig0, cmd, 1, val, n, 700); //500

    if(retval != kStatus_I2C_Success)
    {
    	return kStatus_FXOS_I2CFail;
    }
    return kStatus_FXOS_Success;
}

/******************************************************************************
* Write the specified register of FXOS8700CQ.
* The reading process is through I2C.
******************************************************************************/

FXOS_status_t FXOS8700CQ_WriteRegister(uint8_t reg, uint8_t val)
{
	uint8_t cmd[1], buff[1];
	uint8_t retval = 0;

	cmd[0] = reg;
	buff[0] = val;

	retval = I2C_DRV_MasterSendDataBlocking (FSL_I2CCOM1, &i2cCom1_MasterConfig1, cmd, 1, buff, 1, 500);

	if(retval != kStatus_I2C_Success)
	{
		return kStatus_FXOS_I2CFail;
	}
	return kStatus_FXOS_Success;
}

/******************************************************************************
* Read the specified register value of FXOS8700CQ.
* The reading process is through I2C.
******************************************************************************/

FXOS_status_t FXOS8700CQ_ReadRegisters(uint8_t reg, uint8_t n, uint8_t *val)
{
	uint8_t cmd[1];
	uint8_t retval = 0;

	cmd[0] = reg;

    retval = I2C_DRV_MasterReceiveDataBlocking(FSL_I2CCOM1, &i2cCom1_MasterConfig1, cmd, 1, val, n, 700); //500

    if(retval != kStatus_I2C_Success)
    {
    	return kStatus_FXOS_I2CFail;
    }
    return kStatus_FXOS_Success;
}

/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
