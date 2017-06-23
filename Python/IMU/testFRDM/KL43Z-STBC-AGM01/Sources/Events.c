/* ###################################################################
**     Filename    : Events.c
**     Project     : KL43Z-STBC-AGM01
**     Processor   : MKL43Z256VLH4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-09-22, 11:22, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif 


extern bool FXAS21002C_DataReady;
extern bool FXOS8700CQ_DataReady;

unsigned char flag_but1=0, flag_but2=1;
unsigned int i=0;

/* User includes (#include below this line is not maintained by Processor Expert) */

void PORTA_IRQHandler(void)
{
  /* Clear interrupt flag.*/
  PORT_HAL_ClearPortIntFlag(PORTA_BASE_PTR);
  /* Write your code here ... */
  PORT_HAL_ClearPinIntFlag(PORTA_BASE_PTR, 5);
   /* Write your code here ... */
   FXAS21002C_DataReady = 1;
}

void PORTCD_IRQHandler(void)
{
  //PORT_HAL_ClearPortIntFlag(PORTD_BASE_PTR);
  /* Write your code here ... */
  //FXOS8700 interrupt
    if(PORT_HAL_IsPinIntPending(PORTD_BASE_PTR, 3)) {
    	//PORT_HAL_ClearPortIntFlag(PORTD_BASE_PTR);
  	    PORT_HAL_ClearPinIntFlag(PORTD_BASE_PTR, 3);

    	  FXOS8700CQ_DataReady = 1;
    }

    //switch-1 interface

    else if(PORT_HAL_IsPinIntPending(PORTC_BASE_PTR, 3)) {
   	  PORT_HAL_ClearPinIntFlag(PORTC_BASE_PTR, 3);
   	// PORT_HAL_ClearPortIntFlag(PORTC_BASE_PTR);
   	  flag_but1 = 1;
   	  i=i+1;
     }
   // FXOS8700CQ_DataReady = 1;
}

/*! i2cCom1 IRQ handler */
void I2C1_IRQHandler(void)
{
  I2C_DRV_IRQHandler(FSL_I2CCOM1);
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
