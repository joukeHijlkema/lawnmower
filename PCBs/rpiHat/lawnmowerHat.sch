EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:rpi_3_gpio
LIBS:lawnmowerHat-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L RPI_3_GPIO P1
U 1 1 58C535CE
P 5650 3600
F 0 "P1" H 5650 4650 50  0000 C CNN
F 1 "RPI_3_GPIO" V 5650 3600 50  0000 C CNN
F 2 "MyLibs:rpi3_gpio" H 5650 2650 50  0000 C CNN
F 3 "" H 5650 2650 50  0000 C CNN
	1    5650 3600
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X04 BERRY_IMU1
U 1 1 58C53A72
P 2700 2800
F 0 "BERRY_IMU1" V 2900 2800 50  0000 C CNN
F 1 "CONN_01X04" V 2800 2800 50  0000 C CNN
F 2 "MyLibs:berry_imu" H 2700 2800 50  0001 C CNN
F 3 "" H 2700 2800 50  0001 C CNN
	1    2700 2800
	-1   0    0    1   
$EndComp
Wire Wire Line
	2900 2950 2900 3050
Wire Wire Line
	2900 3050 4650 3050
Wire Wire Line
	2900 2650 4650 2650
Wire Wire Line
	2900 2850 4650 2850
Wire Wire Line
	2900 2750 4650 2750
$Comp
L +5VD #PWR01
U 1 1 58C54E36
P 7200 2750
F 0 "#PWR01" H 7200 2600 50  0001 C CNN
F 1 "+5VD" H 7200 2890 50  0000 C CNN
F 2 "" H 7200 2750 50  0001 C CNN
F 3 "" H 7200 2750 50  0001 C CNN
	1    7200 2750
	0    1    1    0   
$EndComp
$Comp
L GND #PWR02
U 1 1 58C54E62
P 7450 2850
F 0 "#PWR02" H 7450 2600 50  0001 C CNN
F 1 "GND" H 7450 2700 50  0000 C CNN
F 2 "" H 7450 2850 50  0001 C CNN
F 3 "" H 7450 2850 50  0001 C CNN
	1    7450 2850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6650 2850 7450 2850
Wire Wire Line
	6650 2750 7200 2750
NoConn ~ 6650 2650
NoConn ~ 6650 2950
NoConn ~ 6650 3050
NoConn ~ 6650 3150
NoConn ~ 6650 3250
NoConn ~ 6650 3350
NoConn ~ 6650 3450
NoConn ~ 6650 3550
NoConn ~ 6650 3650
NoConn ~ 6650 3750
NoConn ~ 6650 3850
NoConn ~ 6650 3950
NoConn ~ 6650 4050
NoConn ~ 6650 4150
NoConn ~ 6650 4250
NoConn ~ 6650 4350
NoConn ~ 6650 4450
NoConn ~ 6650 4550
NoConn ~ 4650 2950
NoConn ~ 4650 3150
NoConn ~ 4650 3250
NoConn ~ 4650 3350
NoConn ~ 4650 3450
NoConn ~ 4650 3550
NoConn ~ 4650 3650
NoConn ~ 4650 3750
NoConn ~ 4650 3850
NoConn ~ 4650 3950
NoConn ~ 4650 4050
NoConn ~ 4650 4150
NoConn ~ 4650 4250
NoConn ~ 4650 4350
NoConn ~ 4650 4450
NoConn ~ 4650 4550
$Comp
L PWR_FLAG #FLG03
U 1 1 58C55024
P 7200 2750
F 0 "#FLG03" H 7200 2825 50  0001 C CNN
F 1 "PWR_FLAG" V 7200 3050 50  0000 C CNN
F 2 "" H 7200 2750 50  0001 C CNN
F 3 "" H 7200 2750 50  0001 C CNN
	1    7200 2750
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG04
U 1 1 58C5503C
P 7450 2850
F 0 "#FLG04" H 7450 2925 50  0001 C CNN
F 1 "PWR_FLAG" V 7450 3150 50  0000 C CNN
F 2 "" H 7450 2850 50  0001 C CNN
F 3 "" H 7450 2850 50  0001 C CNN
	1    7450 2850
	1    0    0    -1  
$EndComp
$EndSCHEMATC