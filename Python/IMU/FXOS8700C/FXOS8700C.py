#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  =================================================
# registers for the FXOS8700CQ
#   - Author jouke hijlkema <jouke.hijlkema@onera.fr>
#   - lun. mai 21:46 2017
#   - Initial Version 1.0
#  =================================================

STATUS_REG  = 0x00 ## STATUS Register 

OUT_X_MSB_REG  = 0x01 ## [7:0] are 8 MSBs of 14-bit acceleration data for X-axis 
OUT_X_LSB_REG  = 0x02 ## [7:2] are the 6 LSB of 14-bit acceleration data for X-axis
OUT_Y_MSB_REG  = 0x03 ## [7:0] are 8 MSBs of 14-bit acceleration data for Y-axis 
OUT_Y_LSB_REG  = 0x04 ## [7:2] are the 6 LSB of 14-bit acceleration data for Y-axis 
OUT_Z_MSB_REG  = 0x05 ## [7:0] are 8 MSBs of 14-bit acceleration data for Z-axis 
OUT_Z_LSB_REG  = 0x06 ## [7:2] are the 6 LSB of 14-bit acceleration data for Z-axis 

F_SETUP_REG           = 0x09 ## F_SETUP FIFO Setup Register 
TRIG_CFG_REG          = 0x0A ## TRIG_CFG Map of FIFO data capture events 
SYSMOD_REG            = 0x0B ## SYSMOD System Mode Register 
INT_SOURCE_REG        = 0x0C ## INT_SOURCE System Interrupt Status Register 
WHO_AM_I_REG          = 0x0D ## WHO_AM_I Device ID Register 
XYZ_DATA_CFG_REG      = 0x0E ## XYZ_DATA_CFG Sensor Data Configuration Register 
HP_FILTER_CUTOFF_REG  = 0x0F ## HP_FILTER_CUTOFF High Pass Filter Register 

PL_STATUS_REG    = 0x10 ## PL_STATUS Portrait/Landscape Status Register 
PL_CFG_REG       = 0x11 ## PL_CFG Portrait/Landscape Configuration Register 
PL_COUNT_REG     = 0x12 ## PL_COUNT Portrait/Landscape Debounce Register 
PL_BF_ZCOMP_REG  = 0x13 ## PL_BF_ZCOMP Back/Front and Z Compensation Register 
P_L_THS_REG      = 0x14 ## P_L_THS Portrait to Landscape Threshold Register 

FF_MT_CFG_REG    = 0x15 ## FF_MT_CFG Freefall and Motion Configuration Register 
FF_MT_SRC_REG    = 0x16 ## FF_MT_SRC Freefall and Motion Source Register 
FT_MT_THS_REG    = 0x17 ## FF_MT_THS Freefall and Motion Threshold Register 
FF_MT_COUNT_REG  = 0x18 ## FF_MT_COUNT Freefall Motion Count Register 

TRANSIENT_CFG_REG    = 0x1D ## TRANSIENT_CFG Transient Configuration Register 
TRANSIENT_SRC_REG    = 0x1E ## TRANSIENT_SRC Transient Source Register 
TRANSIENT_THS_REG    = 0x1F ## TRANSIENT_THS Transient Threshold Register 
TRANSIENT_COUNT_REG  = 0x20 ## TRANSIENT_COUNT Transient Debounce Counter Register 

PULSE_CFG_REG   = 0x21 ## PULSE_CFG Pulse Configuration Register 
PULSE_SRC_REG   = 0x22 ## PULSE_SRC Pulse Source Register 
PULSE_THSX_REG  = 0x23 ## PULSE_THS XYZ Pulse Threshold Registers 
PULSE_THSY_REG  = 0x24
PULSE_THSZ_REG  = 0x25
PULSE_TMLT_REG  = 0x26 ## PULSE_TMLT Pulse Time Window Register 
PULSE_LTCY_REG  = 0x27 ## PULSE_LTCY Pulse Latency Timer Register 
PULSE_WIND_REG  = 0x28 ## PULSE_WIND Second Pulse Time Window Register 

ASLP_COUNT_REG  = 0x29 ## ASLP_COUNT Auto Sleep Inactivity Timer Register 

CTRL_REG1  = 0x2A ## CTRL_REG1 System Control 1 Register 
CTRL_REG2  = 0x2B ## CTRL_REG2 System Control 2 Register 
CTRL_REG3  = 0x2C ## CTRL_REG3 Interrupt Control Register 
CTRL_REG4  = 0x2D ## CTRL_REG4 Interrupt Enable Register 
CTRL_REG5  = 0x2E ## CTRL_REG5 Interrupt Configuration Register 

OFF_X_REG  = 0x2F ## XYZ Offset Correction Registers 
OFF_Y_REG  = 0x30
OFF_Z_REG  = 0x31

M_DR_STATUS_REG  = 0x32 ## M_DR_STATUS Magnetic data-ready status register 	

MOUT_X_MSB_REG  = 0x33 ## MSB of 16-bit magnetic data for X-axis
MOUT_X_LSB_REG  = 0x34 ## LSB of 16-bit magnetic data for X-axis
MOUT_Y_MSB_REG  = 0x35 ## MSB of 16-bit magnetic data for Y-axis
MOUT_Y_LSB_REG  = 0x36 ## LSB of 16-bit magnetic data for Y-axis
MOUT_Z_MSB_REG  = 0x37 ## MSB of 16-bit magnetic data for Z-axis
MOUT_Z_LSB_REG  = 0x38 ## LSB of 16-bit magnetic data for Z-axis

CMP_X_MSB_REG  = 0x39  ## Bits [13:8] of integrated X-axis acceleration data
CMP_X_LSB_REG  = 0x3A  ## Bits [7:0] of integrated X-axis acceleration data
CMP_Y_MSB_REG  = 0x3B  ## Bits [13:8] of integrated Y-axis acceleration data
CMP_Y_LSB_REG  = 0x3C  ## Bits [7:0] of integrated Y-axis acceleration data
CMP_Z_MSB_REG  = 0x3D  ## Bits [13:8] of integrated Z-axis acceleration data
CMP_Z_LSB_REG  = 0x3E  ## Bits [7:0] of integrated Z-axis acceleration data

MOFF_X_MSB_REG  = 0x3F ## MSB of magnetometer of X-axis offset
MOFF_X_LSB_REG  = 0x40 ## LSB of magnetometer of X-axis offset
MOFF_Y_MSB_REG  = 0x41 ## MSB of magnetometer of Y-axis offset
MOFF_Y_LSB_REG  = 0x42 ## LSB of magnetometer of Y-axis offset
MOFF_Z_MSB_REG  = 0x43 ## MSB of magnetometer of Z-axis offset
MOFF_Z_LSB_REG  = 0x44 ## LSB of magnetometer of Z-axis offset

MAX_X_MSB_REG  = 0x45  ## Magnetometer X-axis maximum value MSB
MAX_X_LSB_REG  = 0x46  ## Magnetometer X-axis maximum value LSB
MAX_Y_MSB_REG  = 0x47  ## Magnetometer Y-axis maximum value MSB
MAX_Y_LSB_REG  = 0x48  ## Magnetometer Y-axis maximum value LSB
MAX_Z_MSB_REG  = 0x49  ## Magnetometer Z-axis maximum value MSB
MAX_Z_LSB_REG  = 0x4A  ## Magnetometer Z-axis maximum value LSB

MIN_X_MSB_REG  = 0x4B  ## Magnetometer X-axis minimum value MSB
MIN_X_LSB_REG  = 0x4C  ## Magnetometer X-axis minimum value LSB
MIN_Y_MSB_REG  = 0x4D  ## Magnetometer Y-axis minimum value MSB
MIN_Y_LSB_REG  = 0x4E  ## Magnetometer Y-axis minimum value LSB
MIN_Z_MSB_REG  = 0x4F  ## Magnetometer Z-axis minimum value MSB
MIN_Z_LSB_REG  = 0x50  ## Magnetometer Z-axis minimum value LSB

TEMP_REG       = 0x51  ## Device temperature
M_THS_CFG_REG  = 0x52  ## Magnetic threshold detection function configuration register
M_THS_SRC_REG  = 0x53  ## Magnetic threshold event source register

M_THS_X_MSB_REG  = 0x54	## X-axis magnetic threshold MSB
M_THS_X_LSB_REG  = 0x55	## X-axis magnetic threshold LSB
M_THS_Y_MSB_REG  = 0x56	## Y-axis magnetic threshold MSB
M_THS_Y_LSB_REG  = 0x57	## Y-axis magnetic threshold LSB
M_THS_Z_MSB_REG  = 0x58	## Z-axis magnetic threshold MSB
M_THS_Z_LSB_REG  = 0x59	## Z-axis magnetic threshold LSB

M_THS_COUNT_REG  = 0x5A	## Magnetic threshold debounce counter

M_CTRL_REG1  = 0x5B
M_CTRL_REG2  = 0x5C
M_CTRL_REG3  = 0x5D

M_INT_SRaC_REG  = 0x5E ## Magnetic interrupt source

A_VECM_CFG_REG      = 0x5F ## Acceleration vector-magnitude configuration register
A_VECM_THS_MSB_REG  = 0x60 ## Acceleration vector-magnitude threshold MSB
A_VECM_THS_LSB_REG  = 0x61 ## Acceleration vector-magnitude threshold LSB
A_VECM_CNT_REG      = 0x62 ## Acceleration vector-magnitude debounce count

A_VECM_INITX_MSB_REG  = 0x63 ## Acceleration vector-magnitude X-axis reference value MSB
A_VECM_INITX_LSB_REG  = 0x64 ## Acceleration vector-magnitude X-axis reference value LSB
A_VECM_INITY_MSB_REG  = 0x65 ## Acceleration vector-magnitude Y-axis reference value MSB
A_VECM_INITY_LSB_REG  = 0x66 ## Acceleration vector-magnitude Y-axis reference value LSB
A_VECM_INITZ_MSB_REG  = 0x67 ## Acceleration vector-magnitude Z-axis reference value MSB
A_VECM_INITZ_LSB_REG  = 0x68 ## Acceleration vector-magnitude Z-axis reference value LSB

M_VECM_CFG_REG  = 0x69 ## Magnetic vector-magnitude configuration register
M_VECM_THS_MSB  = 0x6A ## Magnetic vector-magnitude threshold MSB
M_VECM_THS_LSB  = 0x6B ## Magnetic vector-magnitude threshold LSB
M_VECM_CNT_REG  = 0x6C ## Magnetic vector-magnitude debounce count

M_VECM_INITX_MSB_REG  = 0x6D ## Magnetic vector-magnitude X-axis reference value MSB
M_VECM_INITX_LSB_REG  = 0x6E ## Magnetic vector-magnitude X-axis reference value LSB
M_VECM_INITY_MSB_REG  = 0x6F ## Magnetic vector-magnitude Y-axis reference value MSB
M_VECM_INITY_LSB_REG  = 0x70 ## Magnetic vector-magnitude Y-axis reference value LSB
M_VECM_INITZ_MSB_REG  = 0x71 ## Magnetic vector-magnitude Z-axis reference value MSB
M_VECM_INITZ_LSB_REG  = 0x72 ## Magnetic vector-magnitude Z-axis reference value LSB

A_FFMT_THSX_MSB_REG  = 0x73 ## X-axis FMT threshold MSB
A_FFMT_THSX_LSB_REG  = 0x74 ## X-axis FMT threshold LSB
A_FFMT_THSY_MSB_REG  = 0x75 ## Y-axis FMT threshold MSB
A_FFMT_THSY_LSB_REG  = 0x76 ## Y-axis FMT threshold LSB
A_FFMT_THSZ_MSB_REG  = 0x77 ## Z-axis FMT threshold MSB
A_FFMT_THSZ_LSB_REG  = 0x78 ## Z-axis FMT threshold LSB

##FXOS8700CQ Sensitivity 

#define SENSITIVITY_2G		  	4096
#define SENSITIVITY_4G		  	2048
#define SENSITIVITY_8G		  	1024
#define SENSITIVITY_MAG		  	10

# typedef enum _FXOS8700CQ_status
# {
#     kStatus_FXOS_Success = 0x0, /*!< success */
#     kStatus_FXOS_I2CFail = 0x1, /*!< I2C failure */
#     kStatus_FXOS_Fail = 0x2     /*!< fail */
# } FXOS_status_t;

# FXOS_status_t FXOS8700CQ_WriteRegister(uint8_t reg, uint8_t val);
# FXOS_status_t FXOS8700CQ_ReadRegisters(uint8_t reg, uint8_t n, uint8_t *val);

