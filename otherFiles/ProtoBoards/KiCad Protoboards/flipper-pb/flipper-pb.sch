EESchema Schematic File Version 4
LIBS:flipper-bb-cache
EELAYER 26 0
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
L lomalkin_kicad_symbols:SolderPad X1
U 1 1 5FE7B9E9
P 1650 3600
F 0 "X1" H 1718 3698 50  0000 C CNN
F 1 "SolderPad" H 1700 3550 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 1650 3600 50  0001 C CNN
F 3 "" H 1650 3600 50  0001 C CNN
	1    1650 3600
	-1   0    0    1   
$EndComp
Text Label 1700 1850 0    50   ~ 0
3.3V
Text Label 1700 950  0    50   ~ 0
5V
Text Label 1700 1650 0    50   ~ 0
GND
Wire Wire Line
	1600 950  1700 950 
Wire Wire Line
	1600 1650 1700 1650
Wire Wire Line
	1600 1850 1700 1850
Wire Wire Line
	1600 2750 1700 2750
Text Label 1700 2050 0    50   ~ 0
GND
Wire Wire Line
	1600 2050 1700 2050
$Comp
L lomalkin_kicad_symbols:FlipperZero U1
U 1 1 5FE856CF
P 1200 1900
F 0 "U1" H 1231 3115 50  0000 C CNN
F 1 "FlipperZero" H 1231 3024 50  0000 C CNN
F 2 "lomalkin_kicad_footprints:FlipperZero" H 1150 2000 50  0001 C CNN
F 3 "" H 1150 2000 50  0001 C CNN
	1    1200 1900
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 5FE85C71
P 3750 1450
F 0 "D1" V 3788 1333 50  0000 R CNN
F 1 "LED0603" V 3697 1333 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 3750 1450 50  0001 C CNN
F 3 "~" H 3750 1450 50  0001 C CNN
	1    3750 1450
	0    -1   -1   0   
$EndComp
Text Label 3750 800  2    50   ~ 0
5V
Text Label 4300 800  2    50   ~ 0
3.3V
$Comp
L Device:R R1
U 1 1 5FE85EB1
P 3750 1050
F 0 "R1" H 3820 1096 50  0000 L CNN
F 1 "1K" H 3820 1005 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 3680 1050 50  0001 C CNN
F 3 "~" H 3750 1050 50  0001 C CNN
	1    3750 1050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5FE86052
P 1700 2800
F 0 "#PWR0101" H 1700 2550 50  0001 C CNN
F 1 "GND" H 1705 2627 50  0000 C CNN
F 2 "" H 1700 2800 50  0001 C CNN
F 3 "" H 1700 2800 50  0001 C CNN
	1    1700 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 2750 1700 2800
$Comp
L power:GND #PWR0102
U 1 1 5FE860EB
P 3750 1700
F 0 "#PWR0102" H 3750 1450 50  0001 C CNN
F 1 "GND" H 3755 1527 50  0000 C CNN
F 2 "" H 3750 1700 50  0001 C CNN
F 3 "" H 3750 1700 50  0001 C CNN
	1    3750 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 1600 3750 1700
Wire Wire Line
	3750 1200 3750 1300
Wire Wire Line
	3750 800  3750 900 
$Comp
L Device:LED D2
U 1 1 5FE8651E
P 4300 1450
F 0 "D2" V 4338 1333 50  0000 R CNN
F 1 "LED0603" V 4247 1333 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4300 1450 50  0001 C CNN
F 3 "~" H 4300 1450 50  0001 C CNN
	1    4300 1450
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R2
U 1 1 5FE86526
P 4300 1050
F 0 "R2" H 4370 1096 50  0000 L CNN
F 1 "1K" H 4370 1005 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 4230 1050 50  0001 C CNN
F 3 "~" H 4300 1050 50  0001 C CNN
	1    4300 1050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5FE8652D
P 4300 1700
F 0 "#PWR0103" H 4300 1450 50  0001 C CNN
F 1 "GND" H 4305 1527 50  0000 C CNN
F 2 "" H 4300 1700 50  0001 C CNN
F 3 "" H 4300 1700 50  0001 C CNN
	1    4300 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 1600 4300 1700
Wire Wire Line
	4300 1200 4300 1300
Wire Wire Line
	4300 800  4300 900 
$Comp
L Connector_Generic:Conn_01x06 J1
U 1 1 5FE86AF8
P 8600 1250
F 0 "J1" H 8600 1650 50  0000 L CNN
F 1 "SWD" H 8550 1550 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 8600 1250 50  0001 C CNN
F 3 "~" H 8600 1250 50  0001 C CNN
	1    8600 1250
	1    0    0    -1  
$EndComp
Text Notes 8750 1550 0    50   ~ 0
SWD (discovery):\n\n3.3V (Target)\nSWCLK\nGND\nSWDIO\nNRST\nSWO
$Comp
L Connector_Generic:Conn_01x04 J2
U 1 1 5FE86BC6
P 8600 2650
F 0 "J2" H 8680 2642 50  0000 L CNN
F 1 "UART" H 8680 2551 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 8600 2650 50  0001 C CNN
F 3 "~" H 8600 2650 50  0001 C CNN
	1    8600 2650
	1    0    0    1   
$EndComp
Text Label 8300 1050 2    50   ~ 0
3.3V
Text Label 1700 1950 0    50   ~ 0
SWCLK
Text Label 8300 1150 2    50   ~ 0
SWCLK
Text Label 1700 2150 0    50   ~ 0
SWDIO
Text Label 8300 1350 2    50   ~ 0
SWDIO
$Comp
L power:GND #PWR0104
U 1 1 5FE86E53
P 7950 1300
F 0 "#PWR0104" H 7950 1050 50  0001 C CNN
F 1 "GND" H 7800 1250 50  0000 C CNN
F 2 "" H 7950 1300 50  0001 C CNN
F 3 "" H 7950 1300 50  0001 C CNN
	1    7950 1300
	1    0    0    -1  
$EndComp
$Comp
L lomalkin_kicad_symbols:TestPoint TP1
U 1 1 5FE86ECC
P 7700 1450
F 0 "TP1" H 7950 1450 50  0000 C CNN
F 1 "TestPoint" H 7750 1400 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:TestPoint_Pad_D2.0mm" H 7700 1450 50  0001 C CNN
F 3 "" H 7700 1450 50  0001 C CNN
	1    7700 1450
	-1   0    0    1   
$EndComp
Text Label 1700 1350 0    50   ~ 0
SWO
Text Label 8300 1550 2    50   ~ 0
SWO
Wire Wire Line
	8300 1550 8400 1550
Wire Wire Line
	8400 1450 7700 1450
Wire Wire Line
	8300 1350 8400 1350
Wire Wire Line
	8400 1250 7950 1250
Wire Wire Line
	7950 1250 7950 1300
Wire Wire Line
	8400 1150 8300 1150
Wire Wire Line
	8300 1050 8400 1050
$Comp
L power:GND #PWR0105
U 1 1 5FE87A70
P 8250 2800
F 0 "#PWR0105" H 8250 2550 50  0001 C CNN
F 1 "GND" H 8255 2627 50  0000 C CNN
F 2 "" H 8250 2800 50  0001 C CNN
F 3 "" H 8250 2800 50  0001 C CNN
	1    8250 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 2750 8250 2750
Wire Wire Line
	8250 2750 8250 2800
Wire Wire Line
	1700 1350 1600 1350
Wire Wire Line
	1700 1950 1600 1950
Wire Wire Line
	1700 2150 1600 2150
Text Label 1700 2250 0    50   ~ 0
UART_TX
Text Label 1700 2350 0    50   ~ 0
UART_RX
Wire Wire Line
	1700 2350 1600 2350
Wire Wire Line
	1600 2250 1700 2250
Text Label 8300 2550 2    50   ~ 0
UART_TX
Text Label 8300 2650 2    50   ~ 0
UART_RX
Wire Wire Line
	8400 2550 8300 2550
Wire Wire Line
	8300 2650 8400 2650
Wire Wire Line
	8350 2450 8400 2450
Text Label 1800 1050 0    50   ~ 0
PA7
Text Label 1800 1150 0    50   ~ 0
PA6
Text Label 1800 1250 0    50   ~ 0
PA4
Text Label 1800 1450 0    50   ~ 0
PB2
Text Label 1800 1550 0    50   ~ 0
PC3
Text Label 1800 2450 0    50   ~ 0
PC1
Text Label 1800 2550 0    50   ~ 0
PC0
Wire Wire Line
	1800 2450 1600 2450
Wire Wire Line
	1600 2550 1800 2550
Wire Wire Line
	1600 1450 1800 1450
Wire Wire Line
	1800 1550 1600 1550
Wire Wire Line
	1800 1250 1600 1250
Wire Wire Line
	1600 1150 1800 1150
Wire Wire Line
	1800 1050 1600 1050
Text Label 3750 3800 2    50   ~ 0
PA7
Text Label 3750 3900 2    50   ~ 0
PA6
Text Label 3750 4000 2    50   ~ 0
PA4
Text Label 3750 4200 2    50   ~ 0
PB2
Text Label 3750 4300 2    50   ~ 0
PC3
Text Label 3750 4100 2    50   ~ 0
SWO
Text Label 3750 4450 2    50   ~ 0
PC1
Text Label 3750 4550 2    50   ~ 0
PC0
Text Label 1700 2650 0    50   ~ 0
PB14
Wire Wire Line
	1700 2650 1600 2650
Text Label 1800 2750 0    50   ~ 0
GND
Wire Wire Line
	1800 2750 1700 2750
Connection ~ 1700 2750
$Comp
L Device:C_Small C1
U 1 1 5FE9195A
P 5000 1100
F 0 "C1" H 5092 1146 50  0000 L CNN
F 1 "C0603" H 5092 1055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 5038 950 50  0001 C CNN
F 3 "~" H 5000 1100 50  0001 C CNN
	1    5000 1100
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C2
U 1 1 5FE91DD4
P 5450 1100
F 0 "C2" H 5538 1146 50  0000 L CNN
F 1 "C_Tantal_D" H 5538 1055 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-7343-31_Kemet-D_Pad2.25x2.55mm_HandSolder" H 5450 1100 50  0001 C CNN
F 3 "~" H 5450 1100 50  0001 C CNN
	1    5450 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 1200 5000 1250
Wire Wire Line
	5000 1250 5450 1250
Wire Wire Line
	5450 1250 5450 1200
$Comp
L power:GND #PWR0106
U 1 1 5FE92B0B
P 5450 1300
F 0 "#PWR0106" H 5450 1050 50  0001 C CNN
F 1 "GND" H 5455 1127 50  0000 C CNN
F 2 "" H 5450 1300 50  0001 C CNN
F 3 "" H 5450 1300 50  0001 C CNN
	1    5450 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 1250 5450 1300
Connection ~ 5450 1250
Wire Wire Line
	5000 950  5450 950 
Wire Wire Line
	5450 950  5450 1000
Wire Wire Line
	5000 1000 5000 950 
Wire Wire Line
	5000 900  5000 950 
Connection ~ 5000 950 
$Comp
L Device:C_Small C3
U 1 1 5FE981AE
P 6100 1100
F 0 "C3" H 6192 1146 50  0000 L CNN
F 1 "C0603" H 6192 1055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 6138 950 50  0001 C CNN
F 3 "~" H 6100 1100 50  0001 C CNN
	1    6100 1100
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C4
U 1 1 5FE981B5
P 6550 1100
F 0 "C4" H 6638 1146 50  0000 L CNN
F 1 "C_Tantal_D" H 6638 1055 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-7343-31_Kemet-D_Pad2.25x2.55mm_HandSolder" H 6550 1100 50  0001 C CNN
F 3 "~" H 6550 1100 50  0001 C CNN
	1    6550 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 1200 6100 1250
Wire Wire Line
	6100 1250 6550 1250
Wire Wire Line
	6550 1250 6550 1200
$Comp
L power:GND #PWR0107
U 1 1 5FE981BF
P 6550 1300
F 0 "#PWR0107" H 6550 1050 50  0001 C CNN
F 1 "GND" H 6555 1127 50  0000 C CNN
F 2 "" H 6550 1300 50  0001 C CNN
F 3 "" H 6550 1300 50  0001 C CNN
	1    6550 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 1250 6550 1300
Connection ~ 6550 1250
Wire Wire Line
	6100 950  6550 950 
Wire Wire Line
	6550 950  6550 1000
Wire Wire Line
	6100 1000 6100 950 
Wire Wire Line
	6100 900  6100 950 
Connection ~ 6100 950 
Text Label 5000 900  2    50   ~ 0
5V
Text Label 6100 900  2    50   ~ 0
3.3V
$Comp
L Device:LED D3
U 1 1 5FEA70EF
P 3900 3500
F 0 "D3" V 3938 3383 50  0000 R CNN
F 1 "LED" V 3847 3383 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 3900 3500 50  0001 C CNN
F 3 "~" H 3900 3500 50  0001 C CNN
	1    3900 3500
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R3
U 1 1 5FEA70F6
P 3900 3100
F 0 "R3" H 3970 3146 50  0000 L CNN
F 1 "1K" H 3970 3055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 3830 3100 50  0001 C CNN
F 3 "~" H 3900 3100 50  0001 C CNN
	1    3900 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 3250 3900 3350
$Comp
L Device:LED D4
U 1 1 5FEA9B17
P 4250 3500
F 0 "D4" V 4288 3383 50  0000 R CNN
F 1 "LED" V 4197 3383 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4250 3500 50  0001 C CNN
F 3 "~" H 4250 3500 50  0001 C CNN
	1    4250 3500
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R4
U 1 1 5FEA9B1E
P 4250 3100
F 0 "R4" H 4320 3146 50  0000 L CNN
F 1 "1K" H 4320 3055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 4180 3100 50  0001 C CNN
F 3 "~" H 4250 3100 50  0001 C CNN
	1    4250 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 3250 4250 3350
$Comp
L Device:LED D5
U 1 1 5FEAB196
P 4600 3500
F 0 "D5" V 4638 3383 50  0000 R CNN
F 1 "LED" V 4547 3383 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4600 3500 50  0001 C CNN
F 3 "~" H 4600 3500 50  0001 C CNN
	1    4600 3500
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R5
U 1 1 5FEAB19D
P 4600 3100
F 0 "R5" H 4670 3146 50  0000 L CNN
F 1 "1K" H 4670 3055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 4530 3100 50  0001 C CNN
F 3 "~" H 4600 3100 50  0001 C CNN
	1    4600 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 3250 4600 3350
$Comp
L Device:LED D6
U 1 1 5FEAB1A6
P 4950 3500
F 0 "D6" V 4988 3383 50  0000 R CNN
F 1 "LED" V 4897 3383 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4950 3500 50  0001 C CNN
F 3 "~" H 4950 3500 50  0001 C CNN
	1    4950 3500
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R6
U 1 1 5FEAB1AD
P 4950 3100
F 0 "R6" H 5020 3146 50  0000 L CNN
F 1 "1K" H 5020 3055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 4880 3100 50  0001 C CNN
F 3 "~" H 4950 3100 50  0001 C CNN
	1    4950 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 3250 4950 3350
$Comp
L Device:LED D7
U 1 1 5FEACB0D
P 5300 3500
F 0 "D7" V 5338 3383 50  0000 R CNN
F 1 "LED" V 5247 3383 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 5300 3500 50  0001 C CNN
F 3 "~" H 5300 3500 50  0001 C CNN
	1    5300 3500
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R7
U 1 1 5FEACB14
P 5300 3100
F 0 "R7" H 5370 3146 50  0000 L CNN
F 1 "1K" H 5370 3055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 5230 3100 50  0001 C CNN
F 3 "~" H 5300 3100 50  0001 C CNN
	1    5300 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 3250 5300 3350
$Comp
L Device:LED D8
U 1 1 5FEACB1D
P 5650 3500
F 0 "D8" V 5688 3383 50  0000 R CNN
F 1 "LED" V 5597 3383 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 5650 3500 50  0001 C CNN
F 3 "~" H 5650 3500 50  0001 C CNN
	1    5650 3500
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R8
U 1 1 5FEACB24
P 5650 3100
F 0 "R8" H 5720 3146 50  0000 L CNN
F 1 "1K" H 5720 3055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 5580 3100 50  0001 C CNN
F 3 "~" H 5650 3100 50  0001 C CNN
	1    5650 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 3250 5650 3350
$Comp
L Device:LED D9
U 1 1 5FEACB2D
P 6000 3500
F 0 "D9" V 6038 3383 50  0000 R CNN
F 1 "LED" V 5947 3383 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 6000 3500 50  0001 C CNN
F 3 "~" H 6000 3500 50  0001 C CNN
	1    6000 3500
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R9
U 1 1 5FEACB34
P 6000 3100
F 0 "R9" H 6070 3146 50  0000 L CNN
F 1 "1K" H 6070 3055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 5930 3100 50  0001 C CNN
F 3 "~" H 6000 3100 50  0001 C CNN
	1    6000 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 3250 6000 3350
$Comp
L Device:LED D10
U 1 1 5FEACB3D
P 6350 3500
F 0 "D10" V 6388 3383 50  0000 R CNN
F 1 "LED" V 6297 3383 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 6350 3500 50  0001 C CNN
F 3 "~" H 6350 3500 50  0001 C CNN
	1    6350 3500
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R10
U 1 1 5FEACB44
P 6350 3100
F 0 "R10" H 6420 3146 50  0000 L CNN
F 1 "1K" H 6420 3055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 6280 3100 50  0001 C CNN
F 3 "~" H 6350 3100 50  0001 C CNN
	1    6350 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 3250 6350 3350
Wire Wire Line
	3750 3800 3900 3800
Wire Wire Line
	3900 3650 3900 3800
Wire Wire Line
	3750 3900 4250 3900
Wire Wire Line
	4250 3650 4250 3900
Wire Wire Line
	3750 4000 4600 4000
Wire Wire Line
	4600 3650 4600 4000
Wire Wire Line
	3750 4100 4950 4100
Wire Wire Line
	4950 3650 4950 4100
Wire Wire Line
	3750 4200 5300 4200
Wire Wire Line
	5300 3650 5300 4200
Wire Wire Line
	3750 4300 5650 4300
Wire Wire Line
	5650 3650 5650 4300
Wire Wire Line
	3750 4450 6000 4450
Wire Wire Line
	6000 3650 6000 4450
Wire Wire Line
	3750 4550 6350 4550
Wire Wire Line
	6350 3650 6350 4550
Wire Wire Line
	6350 2900 6350 2950
Wire Wire Line
	6000 2950 6000 2900
Connection ~ 6000 2900
Wire Wire Line
	6000 2900 6350 2900
Wire Wire Line
	5650 2950 5650 2900
Connection ~ 5650 2900
Wire Wire Line
	5650 2900 6000 2900
Wire Wire Line
	5300 2900 5300 2950
Connection ~ 5300 2900
Wire Wire Line
	5300 2900 5650 2900
Wire Wire Line
	4950 2950 4950 2900
Connection ~ 4950 2900
Wire Wire Line
	4950 2900 5300 2900
Wire Wire Line
	3900 2950 3900 2900
Connection ~ 3900 2900
Wire Wire Line
	3900 2900 4250 2900
Wire Wire Line
	4250 2950 4250 2900
Connection ~ 4250 2900
Wire Wire Line
	4250 2900 4600 2900
Wire Wire Line
	4600 2950 4600 2900
Connection ~ 4600 2900
Wire Wire Line
	4600 2900 4950 2900
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 5FEDAEF8
P 1300 4350
F 0 "H1" V 1254 4500 50  0000 L CNN
F 1 "MountingHole_Pad" V 1345 4500 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 1300 4350 50  0001 C CNN
F 3 "~" H 1300 4350 50  0001 C CNN
	1    1300 4350
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 5FEDB181
P 1100 5050
F 0 "#PWR0108" H 1100 4800 50  0001 C CNN
F 1 "GND" H 1105 4877 50  0000 C CNN
F 2 "" H 1100 5050 50  0001 C CNN
F 3 "" H 1100 5050 50  0001 C CNN
	1    1100 5050
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 5FEDB309
P 1300 4550
F 0 "H2" V 1254 4700 50  0000 L CNN
F 1 "MountingHole_Pad" V 1345 4700 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 1300 4550 50  0001 C CNN
F 3 "~" H 1300 4550 50  0001 C CNN
	1    1300 4550
	0    1    1    0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H3
U 1 1 5FEDB365
P 1300 4750
F 0 "H3" V 1254 4900 50  0000 L CNN
F 1 "MountingHole_Pad" V 1345 4900 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 1300 4750 50  0001 C CNN
F 3 "~" H 1300 4750 50  0001 C CNN
	1    1300 4750
	0    1    1    0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 5FEDB3C5
P 1300 4950
F 0 "H4" V 1254 5100 50  0000 L CNN
F 1 "MountingHole_Pad" V 1345 5100 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 1300 4950 50  0001 C CNN
F 3 "~" H 1300 4950 50  0001 C CNN
	1    1300 4950
	0    1    1    0   
$EndComp
Wire Wire Line
	1200 4350 1100 4350
Wire Wire Line
	1100 4350 1100 4550
Wire Wire Line
	1200 4950 1100 4950
Connection ~ 1100 4950
Wire Wire Line
	1100 4950 1100 5050
Wire Wire Line
	1200 4750 1100 4750
Connection ~ 1100 4750
Wire Wire Line
	1100 4750 1100 4950
Wire Wire Line
	1200 4550 1100 4550
Connection ~ 1100 4550
Wire Wire Line
	1100 4550 1100 4750
$Comp
L Connector_Generic:Conn_01x03 J4
U 1 1 5FEE8E6B
P 8600 2100
F 0 "J4" H 8680 2142 50  0000 L CNN
F 1 "UART_PWR" H 8680 2051 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 8600 2100 50  0001 C CNN
F 3 "~" H 8600 2100 50  0001 C CNN
	1    8600 2100
	1    0    0    -1  
$EndComp
Text Label 8300 2000 2    50   ~ 0
5V
Text Label 8300 2200 2    50   ~ 0
3.3V
Wire Wire Line
	8300 2000 8400 2000
Wire Wire Line
	8400 2200 8300 2200
Wire Wire Line
	8400 2100 8350 2100
Wire Wire Line
	8350 2100 8350 2450
$Comp
L Connector_Generic:Conn_01x03 J3
U 1 1 5FF00C0D
P 4150 2550
F 0 "J3" H 4230 2592 50  0000 L CNN
F 1 "LEDS_PWR" H 4230 2501 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 4150 2550 50  0001 C CNN
F 3 "~" H 4150 2550 50  0001 C CNN
	1    4150 2550
	1    0    0    -1  
$EndComp
Text Label 3850 2450 2    50   ~ 0
5V
Text Label 3850 2650 2    50   ~ 0
3.3V
Wire Wire Line
	3850 2450 3950 2450
Wire Wire Line
	3950 2650 3850 2650
Wire Wire Line
	3950 2550 3900 2550
Wire Wire Line
	3900 2550 3900 2900
Text Label 2950 1850 0    50   ~ 0
3.3V
Text Label 2950 950  0    50   ~ 0
5V
Text Label 2950 1650 0    50   ~ 0
GND
Wire Wire Line
	2850 950  2950 950 
Wire Wire Line
	2850 1650 2950 1650
Wire Wire Line
	2850 1850 2950 1850
Wire Wire Line
	2850 2750 2950 2750
Text Label 2950 2050 0    50   ~ 0
GND
Wire Wire Line
	2850 2050 2950 2050
$Comp
L lomalkin_kicad_symbols:FlipperZero U2
U 1 1 5FF1BC21
P 2450 1900
F 0 "U2" H 2481 3115 50  0000 C CNN
F 1 "FlipperZero" H 2481 3024 50  0000 C CNN
F 2 "lomalkin_kicad_footprints:FlipperZero" H 2400 2000 50  0001 C CNN
F 3 "" H 2400 2000 50  0001 C CNN
	1    2450 1900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 5FF1BC28
P 2950 2800
F 0 "#PWR0109" H 2950 2550 50  0001 C CNN
F 1 "GND" H 2955 2627 50  0000 C CNN
F 2 "" H 2950 2800 50  0001 C CNN
F 3 "" H 2950 2800 50  0001 C CNN
	1    2950 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 2750 2950 2800
Text Label 2950 1950 0    50   ~ 0
SWCLK
Text Label 2950 2150 0    50   ~ 0
SWDIO
Text Label 2950 1350 0    50   ~ 0
SWO
Wire Wire Line
	2950 1350 2850 1350
Wire Wire Line
	2950 1950 2850 1950
Wire Wire Line
	2950 2150 2850 2150
Text Label 2950 2250 0    50   ~ 0
UART_TX
Text Label 2950 2350 0    50   ~ 0
UART_RX
Wire Wire Line
	2950 2350 2850 2350
Wire Wire Line
	2850 2250 2950 2250
Text Label 3050 1050 0    50   ~ 0
PA7
Text Label 3050 1150 0    50   ~ 0
PA6
Text Label 3050 1250 0    50   ~ 0
PA4
Text Label 3050 1450 0    50   ~ 0
PB2
Text Label 3050 1550 0    50   ~ 0
PC3
Text Label 3050 2450 0    50   ~ 0
PC1
Text Label 3050 2550 0    50   ~ 0
PC0
Wire Wire Line
	3050 2450 2850 2450
Wire Wire Line
	2850 2550 3050 2550
Wire Wire Line
	2850 1450 3050 1450
Wire Wire Line
	3050 1550 2850 1550
Wire Wire Line
	3050 1250 2850 1250
Wire Wire Line
	2850 1150 3050 1150
Wire Wire Line
	3050 1050 2850 1050
Text Label 2950 2650 0    50   ~ 0
PB14
Wire Wire Line
	2950 2650 2850 2650
Text Label 3050 2750 0    50   ~ 0
GND
Wire Wire Line
	3050 2750 2950 2750
Connection ~ 2950 2750
Text Label 3150 3800 0    50   ~ 0
PA7
Text Label 3150 3900 0    50   ~ 0
PA6
Text Label 3150 4000 0    50   ~ 0
PA4
Text Label 3150 4200 0    50   ~ 0
PB2
Text Label 3150 4300 0    50   ~ 0
PC3
Text Label 3150 4100 0    50   ~ 0
SWO
Text Label 3150 4450 0    50   ~ 0
PC1
Text Label 3150 4550 0    50   ~ 0
PC0
$Comp
L lomalkin_kicad_symbols:SolderPad X2
U 1 1 5FF34920
P 3050 3800
F 0 "X2" H 3300 3800 50  0000 C CNN
F 1 "SolderPad" H 3100 3750 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 3050 3800 50  0001 C CNN
F 3 "" H 3050 3800 50  0001 C CNN
	1    3050 3800
	-1   0    0    1   
$EndComp
$Comp
L lomalkin_kicad_symbols:SolderPad X3
U 1 1 5FF34B3B
P 3050 3900
F 0 "X3" H 3300 3900 50  0000 C CNN
F 1 "SolderPad" H 3100 3850 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 3050 3900 50  0001 C CNN
F 3 "" H 3050 3900 50  0001 C CNN
	1    3050 3900
	-1   0    0    1   
$EndComp
$Comp
L lomalkin_kicad_symbols:SolderPad X4
U 1 1 5FF34B9B
P 3050 4000
F 0 "X4" H 3300 4000 50  0000 C CNN
F 1 "SolderPad" H 3100 3950 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 3050 4000 50  0001 C CNN
F 3 "" H 3050 4000 50  0001 C CNN
	1    3050 4000
	-1   0    0    1   
$EndComp
$Comp
L lomalkin_kicad_symbols:SolderPad X5
U 1 1 5FF34BFD
P 3050 4100
F 0 "X5" H 3300 4100 50  0000 C CNN
F 1 "SolderPad" H 3100 4050 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 3050 4100 50  0001 C CNN
F 3 "" H 3050 4100 50  0001 C CNN
	1    3050 4100
	-1   0    0    1   
$EndComp
$Comp
L lomalkin_kicad_symbols:SolderPad X6
U 1 1 5FF34C5D
P 3050 4200
F 0 "X6" H 3300 4200 50  0000 C CNN
F 1 "SolderPad" H 3100 4150 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 3050 4200 50  0001 C CNN
F 3 "" H 3050 4200 50  0001 C CNN
	1    3050 4200
	-1   0    0    1   
$EndComp
$Comp
L lomalkin_kicad_symbols:SolderPad X7
U 1 1 5FF34CBF
P 3050 4300
F 0 "X7" H 3300 4300 50  0000 C CNN
F 1 "SolderPad" H 3100 4250 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 3050 4300 50  0001 C CNN
F 3 "" H 3050 4300 50  0001 C CNN
	1    3050 4300
	-1   0    0    1   
$EndComp
$Comp
L lomalkin_kicad_symbols:SolderPad X8
U 1 1 5FF34D23
P 3050 4450
F 0 "X8" H 3300 4450 50  0000 C CNN
F 1 "SolderPad" H 3100 4400 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 3050 4450 50  0001 C CNN
F 3 "" H 3050 4450 50  0001 C CNN
	1    3050 4450
	-1   0    0    1   
$EndComp
$Comp
L lomalkin_kicad_symbols:SolderPad X9
U 1 1 5FF34D8F
P 3050 4550
F 0 "X9" H 3300 4550 50  0000 C CNN
F 1 "SolderPad" H 3100 4500 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 3050 4550 50  0001 C CNN
F 3 "" H 3050 4550 50  0001 C CNN
	1    3050 4550
	-1   0    0    1   
$EndComp
Wire Wire Line
	3050 3800 3150 3800
Wire Wire Line
	3150 3900 3050 3900
Wire Wire Line
	3050 4000 3150 4000
Wire Wire Line
	3150 4100 3050 4100
Wire Wire Line
	3050 4200 3150 4200
Wire Wire Line
	3150 4300 3050 4300
Wire Wire Line
	3050 4450 3150 4450
Wire Wire Line
	3150 4550 3050 4550
$Comp
L lomalkin_kicad_symbols:SolderPad X10
U 1 1 5FF633C7
P 3050 4800
F 0 "X10" H 3300 4800 50  0000 C CNN
F 1 "SolderPad" H 3100 4750 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 3050 4800 50  0001 C CNN
F 3 "" H 3050 4800 50  0001 C CNN
	1    3050 4800
	-1   0    0    1   
$EndComp
Text Label 3150 4800 0    50   ~ 0
5V
Wire Wire Line
	3050 4800 3150 4800
$Comp
L lomalkin_kicad_symbols:SolderPad X11
U 1 1 5FF690BF
P 3050 4900
F 0 "X11" H 3300 4900 50  0000 C CNN
F 1 "SolderPad" H 3100 4850 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 3050 4900 50  0001 C CNN
F 3 "" H 3050 4900 50  0001 C CNN
	1    3050 4900
	-1   0    0    1   
$EndComp
Text Label 3150 4900 0    50   ~ 0
5V
Wire Wire Line
	3050 4900 3150 4900
$Comp
L lomalkin_kicad_symbols:SolderPad X12
U 1 1 5FF6EAEE
P 3050 5000
F 0 "X12" H 3300 5000 50  0000 C CNN
F 1 "SolderPad" H 3100 4950 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 3050 5000 50  0001 C CNN
F 3 "" H 3050 5000 50  0001 C CNN
	1    3050 5000
	-1   0    0    1   
$EndComp
Text Label 3150 5000 0    50   ~ 0
5V
Wire Wire Line
	3050 5000 3150 5000
$Comp
L lomalkin_kicad_symbols:SolderPad X13
U 1 1 5FF7468C
P 3050 5100
F 0 "X13" H 3300 5100 50  0000 C CNN
F 1 "SolderPad" H 3100 5050 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 3050 5100 50  0001 C CNN
F 3 "" H 3050 5100 50  0001 C CNN
	1    3050 5100
	-1   0    0    1   
$EndComp
Text Label 3150 5100 0    50   ~ 0
5V
Wire Wire Line
	3050 5100 3150 5100
$Comp
L lomalkin_kicad_symbols:SolderPad X14
U 1 1 5FF7A39C
P 3050 5200
F 0 "X14" H 3300 5200 50  0000 C CNN
F 1 "SolderPad" H 3100 5150 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 3050 5200 50  0001 C CNN
F 3 "" H 3050 5200 50  0001 C CNN
	1    3050 5200
	-1   0    0    1   
$EndComp
Text Label 3150 5200 0    50   ~ 0
5V
Wire Wire Line
	3050 5200 3150 5200
$Comp
L lomalkin_kicad_symbols:SolderPad X15
U 1 1 5FF80864
P 3700 4800
F 0 "X15" H 3950 4800 50  0000 C CNN
F 1 "SolderPad" H 3750 4750 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 3700 4800 50  0001 C CNN
F 3 "" H 3700 4800 50  0001 C CNN
	1    3700 4800
	-1   0    0    1   
$EndComp
Wire Wire Line
	3700 4800 3800 4800
$Comp
L lomalkin_kicad_symbols:SolderPad X16
U 1 1 5FF8086D
P 3700 4900
F 0 "X16" H 3950 4900 50  0000 C CNN
F 1 "SolderPad" H 3750 4850 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 3700 4900 50  0001 C CNN
F 3 "" H 3700 4900 50  0001 C CNN
	1    3700 4900
	-1   0    0    1   
$EndComp
Wire Wire Line
	3700 4900 3800 4900
$Comp
L lomalkin_kicad_symbols:SolderPad X17
U 1 1 5FF80876
P 3700 5000
F 0 "X17" H 3950 5000 50  0000 C CNN
F 1 "SolderPad" H 3750 4950 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 3700 5000 50  0001 C CNN
F 3 "" H 3700 5000 50  0001 C CNN
	1    3700 5000
	-1   0    0    1   
$EndComp
Wire Wire Line
	3700 5000 3800 5000
$Comp
L lomalkin_kicad_symbols:SolderPad X18
U 1 1 5FF8087F
P 3700 5100
F 0 "X18" H 3950 5100 50  0000 C CNN
F 1 "SolderPad" H 3750 5050 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 3700 5100 50  0001 C CNN
F 3 "" H 3700 5100 50  0001 C CNN
	1    3700 5100
	-1   0    0    1   
$EndComp
Wire Wire Line
	3700 5100 3800 5100
$Comp
L lomalkin_kicad_symbols:SolderPad X19
U 1 1 5FF80888
P 3700 5200
F 0 "X19" H 3950 5200 50  0000 C CNN
F 1 "SolderPad" H 3750 5150 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 3700 5200 50  0001 C CNN
F 3 "" H 3700 5200 50  0001 C CNN
	1    3700 5200
	-1   0    0    1   
$EndComp
Wire Wire Line
	3700 5200 3800 5200
$Comp
L lomalkin_kicad_symbols:SolderPad X20
U 1 1 5FF86E7D
P 3700 5300
F 0 "X20" H 3950 5300 50  0000 C CNN
F 1 "SolderPad" H 3750 5250 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 3700 5300 50  0001 C CNN
F 3 "" H 3700 5300 50  0001 C CNN
	1    3700 5300
	-1   0    0    1   
$EndComp
Text Label 3800 4800 0    50   ~ 0
3.3V
Text Label 3800 4900 0    50   ~ 0
3.3V
Text Label 3800 5000 0    50   ~ 0
3.3V
Text Label 3800 5100 0    50   ~ 0
3.3V
Text Label 3800 5200 0    50   ~ 0
3.3V
Text Label 3800 5300 0    50   ~ 0
3.3V
Wire Wire Line
	3800 5300 3700 5300
$Comp
L lomalkin_kicad_symbols:SolderPad X21
U 1 1 5FF94A52
P 4450 4800
F 0 "X21" H 4700 4800 50  0000 C CNN
F 1 "SolderPad" H 4500 4750 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 4450 4800 50  0001 C CNN
F 3 "" H 4450 4800 50  0001 C CNN
	1    4450 4800
	-1   0    0    1   
$EndComp
Wire Wire Line
	4450 4800 4550 4800
$Comp
L lomalkin_kicad_symbols:SolderPad X22
U 1 1 5FF94A5B
P 4450 4900
F 0 "X22" H 4700 4900 50  0000 C CNN
F 1 "SolderPad" H 4500 4850 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 4450 4900 50  0001 C CNN
F 3 "" H 4450 4900 50  0001 C CNN
	1    4450 4900
	-1   0    0    1   
$EndComp
Wire Wire Line
	4450 4900 4550 4900
$Comp
L lomalkin_kicad_symbols:SolderPad X23
U 1 1 5FF94A64
P 4450 5000
F 0 "X23" H 4700 5000 50  0000 C CNN
F 1 "SolderPad" H 4500 4950 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 4450 5000 50  0001 C CNN
F 3 "" H 4450 5000 50  0001 C CNN
	1    4450 5000
	-1   0    0    1   
$EndComp
Wire Wire Line
	4450 5000 4550 5000
$Comp
L lomalkin_kicad_symbols:SolderPad X24
U 1 1 5FF94A6D
P 4450 5100
F 0 "X24" H 4700 5100 50  0000 C CNN
F 1 "SolderPad" H 4500 5050 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 4450 5100 50  0001 C CNN
F 3 "" H 4450 5100 50  0001 C CNN
	1    4450 5100
	-1   0    0    1   
$EndComp
Wire Wire Line
	4450 5100 4550 5100
$Comp
L lomalkin_kicad_symbols:SolderPad X25
U 1 1 5FF94A76
P 4450 5200
F 0 "X25" H 4700 5200 50  0000 C CNN
F 1 "SolderPad" H 4500 5150 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 4450 5200 50  0001 C CNN
F 3 "" H 4450 5200 50  0001 C CNN
	1    4450 5200
	-1   0    0    1   
$EndComp
Wire Wire Line
	4450 5200 4550 5200
Text Label 4550 4800 0    50   ~ 0
GND
Text Label 4550 4900 0    50   ~ 0
GND
Text Label 4550 5000 0    50   ~ 0
GND
Text Label 4550 5100 0    50   ~ 0
GND
Text Label 4550 5200 0    50   ~ 0
GND
$Comp
L lomalkin_kicad_symbols:SolderPad X26
U 1 1 5FFA31B5
P 4450 5300
F 0 "X26" H 4700 5300 50  0000 C CNN
F 1 "SolderPad" H 4500 5250 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 4450 5300 50  0001 C CNN
F 3 "" H 4450 5300 50  0001 C CNN
	1    4450 5300
	-1   0    0    1   
$EndComp
Wire Wire Line
	4450 5300 4550 5300
Text Label 4550 5300 0    50   ~ 0
GND
$Comp
L lomalkin_kicad_symbols:SolderPad X27
U 1 1 5FFAA54C
P 5150 4800
F 0 "X27" H 5400 4800 50  0000 C CNN
F 1 "SolderPad" H 5200 4750 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 5150 4800 50  0001 C CNN
F 3 "" H 5150 4800 50  0001 C CNN
	1    5150 4800
	-1   0    0    1   
$EndComp
Wire Wire Line
	5150 4800 5250 4800
$Comp
L lomalkin_kicad_symbols:SolderPad X28
U 1 1 5FFAA554
P 5150 4900
F 0 "X28" H 5400 4900 50  0000 C CNN
F 1 "SolderPad" H 5200 4850 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 5150 4900 50  0001 C CNN
F 3 "" H 5150 4900 50  0001 C CNN
	1    5150 4900
	-1   0    0    1   
$EndComp
Wire Wire Line
	5150 4900 5250 4900
$Comp
L lomalkin_kicad_symbols:SolderPad X29
U 1 1 5FFAA55C
P 5150 5000
F 0 "X29" H 5400 5000 50  0000 C CNN
F 1 "SolderPad" H 5200 4950 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 5150 5000 50  0001 C CNN
F 3 "" H 5150 5000 50  0001 C CNN
	1    5150 5000
	-1   0    0    1   
$EndComp
Wire Wire Line
	5150 5000 5250 5000
$Comp
L lomalkin_kicad_symbols:SolderPad X30
U 1 1 5FFAA564
P 5150 5100
F 0 "X30" H 5400 5100 50  0000 C CNN
F 1 "SolderPad" H 5200 5050 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 5150 5100 50  0001 C CNN
F 3 "" H 5150 5100 50  0001 C CNN
	1    5150 5100
	-1   0    0    1   
$EndComp
Wire Wire Line
	5150 5100 5250 5100
$Comp
L lomalkin_kicad_symbols:SolderPad X31
U 1 1 5FFAA56C
P 5150 5200
F 0 "X31" H 5400 5200 50  0000 C CNN
F 1 "SolderPad" H 5200 5150 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 5150 5200 50  0001 C CNN
F 3 "" H 5150 5200 50  0001 C CNN
	1    5150 5200
	-1   0    0    1   
$EndComp
Wire Wire Line
	5150 5200 5250 5200
Text Label 5250 4800 0    50   ~ 0
GND
Text Label 5250 4900 0    50   ~ 0
GND
Text Label 5250 5000 0    50   ~ 0
GND
Text Label 5250 5100 0    50   ~ 0
GND
Text Label 5250 5200 0    50   ~ 0
GND
$EndSCHEMATC
