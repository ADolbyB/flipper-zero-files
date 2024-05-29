EESchema Schematic File Version 4
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
P 4200 2200
F 0 "X1" H 4268 2298 50  0000 C CNN
F 1 "SolderPad" H 4250 2150 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 4200 2200 50  0001 C CNN
F 3 "" H 4200 2200 50  0001 C CNN
	1    4200 2200
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
Text Label 1700 1950 0    50   ~ 0
SWCLK
Text Label 1700 2150 0    50   ~ 0
SWDIO
Text Label 1700 1350 0    50   ~ 0
SWO
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
Text Label 1700 2650 0    50   ~ 0
PB14
Wire Wire Line
	1700 2650 1600 2650
Text Label 1800 2750 0    50   ~ 0
GND
Wire Wire Line
	1800 2750 1700 2750
Connection ~ 1700 2750
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
Text Label 4350 850  0    50   ~ 0
PA7
Text Label 4350 950  0    50   ~ 0
PA6
Text Label 4350 1050 0    50   ~ 0
PA4
Text Label 4350 1250 0    50   ~ 0
PB2
Text Label 4350 1350 0    50   ~ 0
PC3
Text Label 4350 1150 0    50   ~ 0
SWO
Text Label 4350 1500 0    50   ~ 0
PC1
Text Label 4350 1600 0    50   ~ 0
PC0
$Comp
L lomalkin_kicad_symbols:SolderPad X2
U 1 1 5FF34920
P 4250 850
F 0 "X2" H 4500 850 50  0000 C CNN
F 1 "SolderPad" H 4300 800 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 4250 850 50  0001 C CNN
F 3 "" H 4250 850 50  0001 C CNN
	1    4250 850 
	-1   0    0    1   
$EndComp
$Comp
L lomalkin_kicad_symbols:SolderPad X3
U 1 1 5FF34B3B
P 4250 950
F 0 "X3" H 4500 950 50  0000 C CNN
F 1 "SolderPad" H 4300 900 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 4250 950 50  0001 C CNN
F 3 "" H 4250 950 50  0001 C CNN
	1    4250 950 
	-1   0    0    1   
$EndComp
$Comp
L lomalkin_kicad_symbols:SolderPad X4
U 1 1 5FF34B9B
P 4250 1050
F 0 "X4" H 4500 1050 50  0000 C CNN
F 1 "SolderPad" H 4300 1000 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 4250 1050 50  0001 C CNN
F 3 "" H 4250 1050 50  0001 C CNN
	1    4250 1050
	-1   0    0    1   
$EndComp
$Comp
L lomalkin_kicad_symbols:SolderPad X5
U 1 1 5FF34BFD
P 4250 1150
F 0 "X5" H 4500 1150 50  0000 C CNN
F 1 "SolderPad" H 4300 1100 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 4250 1150 50  0001 C CNN
F 3 "" H 4250 1150 50  0001 C CNN
	1    4250 1150
	-1   0    0    1   
$EndComp
$Comp
L lomalkin_kicad_symbols:SolderPad X6
U 1 1 5FF34C5D
P 4250 1250
F 0 "X6" H 4500 1250 50  0000 C CNN
F 1 "SolderPad" H 4300 1200 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 4250 1250 50  0001 C CNN
F 3 "" H 4250 1250 50  0001 C CNN
	1    4250 1250
	-1   0    0    1   
$EndComp
$Comp
L lomalkin_kicad_symbols:SolderPad X7
U 1 1 5FF34CBF
P 4250 1350
F 0 "X7" H 4500 1350 50  0000 C CNN
F 1 "SolderPad" H 4300 1300 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 4250 1350 50  0001 C CNN
F 3 "" H 4250 1350 50  0001 C CNN
	1    4250 1350
	-1   0    0    1   
$EndComp
$Comp
L lomalkin_kicad_symbols:SolderPad X8
U 1 1 5FF34D23
P 4250 1500
F 0 "X8" H 4500 1500 50  0000 C CNN
F 1 "SolderPad" H 4300 1450 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 4250 1500 50  0001 C CNN
F 3 "" H 4250 1500 50  0001 C CNN
	1    4250 1500
	-1   0    0    1   
$EndComp
$Comp
L lomalkin_kicad_symbols:SolderPad X9
U 1 1 5FF34D8F
P 4250 1600
F 0 "X9" H 4500 1600 50  0000 C CNN
F 1 "SolderPad" H 4300 1550 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 4250 1600 50  0001 C CNN
F 3 "" H 4250 1600 50  0001 C CNN
	1    4250 1600
	-1   0    0    1   
$EndComp
Wire Wire Line
	4250 850  4350 850 
Wire Wire Line
	4350 950  4250 950 
Wire Wire Line
	4250 1050 4350 1050
Wire Wire Line
	4350 1150 4250 1150
Wire Wire Line
	4250 1250 4350 1250
Wire Wire Line
	4350 1350 4250 1350
Wire Wire Line
	4250 1500 4350 1500
Wire Wire Line
	4350 1600 4250 1600
$Comp
L lomalkin_kicad_symbols:SolderPad X10
U 1 1 5FF633C7
P 5300 850
F 0 "X10" H 5550 850 50  0000 C CNN
F 1 "SolderPad" H 5350 800 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 5300 850 50  0001 C CNN
F 3 "" H 5300 850 50  0001 C CNN
	1    5300 850 
	-1   0    0    1   
$EndComp
Text Label 5400 850  0    50   ~ 0
5V
Wire Wire Line
	5300 850  5400 850 
$Comp
L lomalkin_kicad_symbols:SolderPad X11
U 1 1 5FF690BF
P 5300 950
F 0 "X11" H 5550 950 50  0000 C CNN
F 1 "SolderPad" H 5350 900 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 5300 950 50  0001 C CNN
F 3 "" H 5300 950 50  0001 C CNN
	1    5300 950 
	-1   0    0    1   
$EndComp
Text Label 5400 950  0    50   ~ 0
5V
Wire Wire Line
	5300 950  5400 950 
$Comp
L lomalkin_kicad_symbols:SolderPad X12
U 1 1 5FF6EAEE
P 5300 1050
F 0 "X12" H 5550 1050 50  0000 C CNN
F 1 "SolderPad" H 5350 1000 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 5300 1050 50  0001 C CNN
F 3 "" H 5300 1050 50  0001 C CNN
	1    5300 1050
	-1   0    0    1   
$EndComp
Text Label 5400 1050 0    50   ~ 0
5V
Wire Wire Line
	5300 1050 5400 1050
$Comp
L lomalkin_kicad_symbols:SolderPad X13
U 1 1 5FF7468C
P 5300 1150
F 0 "X13" H 5550 1150 50  0000 C CNN
F 1 "SolderPad" H 5350 1100 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 5300 1150 50  0001 C CNN
F 3 "" H 5300 1150 50  0001 C CNN
	1    5300 1150
	-1   0    0    1   
$EndComp
Text Label 5400 1150 0    50   ~ 0
5V
Wire Wire Line
	5300 1150 5400 1150
$Comp
L lomalkin_kicad_symbols:SolderPad X14
U 1 1 5FF7A39C
P 5300 1250
F 0 "X14" H 5550 1250 50  0000 C CNN
F 1 "SolderPad" H 5350 1200 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 5300 1250 50  0001 C CNN
F 3 "" H 5300 1250 50  0001 C CNN
	1    5300 1250
	-1   0    0    1   
$EndComp
Text Label 5400 1250 0    50   ~ 0
5V
Wire Wire Line
	5300 1250 5400 1250
$Comp
L lomalkin_kicad_symbols:SolderPad X15
U 1 1 5FF80864
P 5950 850
F 0 "X15" H 6200 850 50  0000 C CNN
F 1 "SolderPad" H 6000 800 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 5950 850 50  0001 C CNN
F 3 "" H 5950 850 50  0001 C CNN
	1    5950 850 
	-1   0    0    1   
$EndComp
Wire Wire Line
	5950 850  6050 850 
$Comp
L lomalkin_kicad_symbols:SolderPad X16
U 1 1 5FF8086D
P 5950 950
F 0 "X16" H 6200 950 50  0000 C CNN
F 1 "SolderPad" H 6000 900 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 5950 950 50  0001 C CNN
F 3 "" H 5950 950 50  0001 C CNN
	1    5950 950 
	-1   0    0    1   
$EndComp
Wire Wire Line
	5950 950  6050 950 
$Comp
L lomalkin_kicad_symbols:SolderPad X17
U 1 1 5FF80876
P 5950 1050
F 0 "X17" H 6200 1050 50  0000 C CNN
F 1 "SolderPad" H 6000 1000 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 5950 1050 50  0001 C CNN
F 3 "" H 5950 1050 50  0001 C CNN
	1    5950 1050
	-1   0    0    1   
$EndComp
Wire Wire Line
	5950 1050 6050 1050
$Comp
L lomalkin_kicad_symbols:SolderPad X18
U 1 1 5FF8087F
P 5950 1150
F 0 "X18" H 6200 1150 50  0000 C CNN
F 1 "SolderPad" H 6000 1100 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 5950 1150 50  0001 C CNN
F 3 "" H 5950 1150 50  0001 C CNN
	1    5950 1150
	-1   0    0    1   
$EndComp
Wire Wire Line
	5950 1150 6050 1150
$Comp
L lomalkin_kicad_symbols:SolderPad X19
U 1 1 5FF80888
P 5950 1250
F 0 "X19" H 6200 1250 50  0000 C CNN
F 1 "SolderPad" H 6000 1200 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 5950 1250 50  0001 C CNN
F 3 "" H 5950 1250 50  0001 C CNN
	1    5950 1250
	-1   0    0    1   
$EndComp
Wire Wire Line
	5950 1250 6050 1250
Text Label 6050 850  0    50   ~ 0
3.3V
Text Label 6050 950  0    50   ~ 0
3.3V
Text Label 6050 1050 0    50   ~ 0
3.3V
Text Label 6050 1150 0    50   ~ 0
3.3V
Text Label 6050 1250 0    50   ~ 0
3.3V
$Comp
L lomalkin_kicad_symbols:SolderPad X21
U 1 1 5FF94A52
P 6700 850
F 0 "X21" H 6950 850 50  0000 C CNN
F 1 "SolderPad" H 6750 800 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 6700 850 50  0001 C CNN
F 3 "" H 6700 850 50  0001 C CNN
	1    6700 850 
	-1   0    0    1   
$EndComp
Wire Wire Line
	6700 850  6800 850 
$Comp
L lomalkin_kicad_symbols:SolderPad X22
U 1 1 5FF94A5B
P 6700 950
F 0 "X22" H 6950 950 50  0000 C CNN
F 1 "SolderPad" H 6750 900 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 6700 950 50  0001 C CNN
F 3 "" H 6700 950 50  0001 C CNN
	1    6700 950 
	-1   0    0    1   
$EndComp
Wire Wire Line
	6700 950  6800 950 
$Comp
L lomalkin_kicad_symbols:SolderPad X23
U 1 1 5FF94A64
P 6700 1050
F 0 "X23" H 6950 1050 50  0000 C CNN
F 1 "SolderPad" H 6750 1000 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 6700 1050 50  0001 C CNN
F 3 "" H 6700 1050 50  0001 C CNN
	1    6700 1050
	-1   0    0    1   
$EndComp
Wire Wire Line
	6700 1050 6800 1050
$Comp
L lomalkin_kicad_symbols:SolderPad X24
U 1 1 5FF94A6D
P 6700 1150
F 0 "X24" H 6950 1150 50  0000 C CNN
F 1 "SolderPad" H 6750 1100 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 6700 1150 50  0001 C CNN
F 3 "" H 6700 1150 50  0001 C CNN
	1    6700 1150
	-1   0    0    1   
$EndComp
Wire Wire Line
	6700 1150 6800 1150
$Comp
L lomalkin_kicad_symbols:SolderPad X25
U 1 1 5FF94A76
P 6700 1250
F 0 "X25" H 6950 1250 50  0000 C CNN
F 1 "SolderPad" H 6750 1200 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 6700 1250 50  0001 C CNN
F 3 "" H 6700 1250 50  0001 C CNN
	1    6700 1250
	-1   0    0    1   
$EndComp
Wire Wire Line
	6700 1250 6800 1250
Text Label 6800 850  0    50   ~ 0
GND
Text Label 6800 950  0    50   ~ 0
GND
Text Label 6800 1050 0    50   ~ 0
GND
Text Label 6800 1150 0    50   ~ 0
GND
Text Label 6800 1250 0    50   ~ 0
GND
$Comp
L lomalkin_kicad_symbols:SolderPad X27
U 1 1 5FFAA54C
P 7400 850
F 0 "X27" H 7650 850 50  0000 C CNN
F 1 "SolderPad" H 7450 800 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 7400 850 50  0001 C CNN
F 3 "" H 7400 850 50  0001 C CNN
	1    7400 850 
	-1   0    0    1   
$EndComp
Wire Wire Line
	7400 850  7500 850 
$Comp
L lomalkin_kicad_symbols:SolderPad X28
U 1 1 5FFAA554
P 7400 950
F 0 "X28" H 7650 950 50  0000 C CNN
F 1 "SolderPad" H 7450 900 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 7400 950 50  0001 C CNN
F 3 "" H 7400 950 50  0001 C CNN
	1    7400 950 
	-1   0    0    1   
$EndComp
Wire Wire Line
	7400 950  7500 950 
$Comp
L lomalkin_kicad_symbols:SolderPad X29
U 1 1 5FFAA55C
P 7400 1050
F 0 "X29" H 7650 1050 50  0000 C CNN
F 1 "SolderPad" H 7450 1000 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 7400 1050 50  0001 C CNN
F 3 "" H 7400 1050 50  0001 C CNN
	1    7400 1050
	-1   0    0    1   
$EndComp
Wire Wire Line
	7400 1050 7500 1050
$Comp
L lomalkin_kicad_symbols:SolderPad X30
U 1 1 5FFAA564
P 7400 1150
F 0 "X30" H 7650 1150 50  0000 C CNN
F 1 "SolderPad" H 7450 1100 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 7400 1150 50  0001 C CNN
F 3 "" H 7400 1150 50  0001 C CNN
	1    7400 1150
	-1   0    0    1   
$EndComp
Wire Wire Line
	7400 1150 7500 1150
$Comp
L lomalkin_kicad_symbols:SolderPad X31
U 1 1 5FFAA56C
P 7400 1250
F 0 "X31" H 7650 1250 50  0000 C CNN
F 1 "SolderPad" H 7450 1200 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 7400 1250 50  0001 C CNN
F 3 "" H 7400 1250 50  0001 C CNN
	1    7400 1250
	-1   0    0    1   
$EndComp
Wire Wire Line
	7400 1250 7500 1250
Text Label 7500 850  0    50   ~ 0
GND
Text Label 7500 950  0    50   ~ 0
GND
Text Label 7500 1050 0    50   ~ 0
GND
Text Label 7500 1150 0    50   ~ 0
GND
Text Label 7500 1250 0    50   ~ 0
GND
Text Notes 4000 2150 0    50   ~ 0
Макетка
Text Label 4850 2050 0    50   ~ 0
UART_TX
Text Label 4850 2150 0    50   ~ 0
UART_RX
Text Label 4850 1950 0    50   ~ 0
SWCLK
Text Label 4850 1850 0    50   ~ 0
SWDIO
$Comp
L lomalkin_kicad_symbols:SolderPad X20
U 1 1 5FED9A41
P 4750 1850
F 0 "X20" H 5000 1850 50  0000 C CNN
F 1 "SolderPad" H 4800 1800 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 4750 1850 50  0001 C CNN
F 3 "" H 4750 1850 50  0001 C CNN
	1    4750 1850
	-1   0    0    1   
$EndComp
$Comp
L lomalkin_kicad_symbols:SolderPad X26
U 1 1 5FED9AB3
P 4750 1950
F 0 "X26" H 5000 1950 50  0000 C CNN
F 1 "SolderPad" H 4800 1900 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 4750 1950 50  0001 C CNN
F 3 "" H 4750 1950 50  0001 C CNN
	1    4750 1950
	-1   0    0    1   
$EndComp
$Comp
L lomalkin_kicad_symbols:SolderPad X32
U 1 1 5FED9B09
P 4750 2050
F 0 "X32" H 5000 2050 50  0000 C CNN
F 1 "SolderPad" H 4800 2000 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 4750 2050 50  0001 C CNN
F 3 "" H 4750 2050 50  0001 C CNN
	1    4750 2050
	-1   0    0    1   
$EndComp
$Comp
L lomalkin_kicad_symbols:SolderPad X33
U 1 1 5FED9B5D
P 4750 2150
F 0 "X33" H 5000 2150 50  0000 C CNN
F 1 "SolderPad" H 4800 2100 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 4750 2150 50  0001 C CNN
F 3 "" H 4750 2150 50  0001 C CNN
	1    4750 2150
	-1   0    0    1   
$EndComp
Wire Wire Line
	4750 1850 4850 1850
Wire Wire Line
	4850 1950 4750 1950
Wire Wire Line
	4750 2050 4850 2050
Wire Wire Line
	4850 2150 4750 2150
Text Label 4850 2250 0    50   ~ 0
PB14
$Comp
L lomalkin_kicad_symbols:SolderPad X34
U 1 1 5FEE15D0
P 4750 2250
F 0 "X34" H 5000 2250 50  0000 C CNN
F 1 "SolderPad" H 4800 2200 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 4750 2250 50  0001 C CNN
F 3 "" H 4750 2250 50  0001 C CNN
	1    4750 2250
	-1   0    0    1   
$EndComp
$Comp
L lomalkin_kicad_symbols:SolderPad X35
U 1 1 5FEE176D
P 8050 850
F 0 "X35" H 8300 850 50  0000 C CNN
F 1 "SolderPad" H 8100 800 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 8050 850 50  0001 C CNN
F 3 "" H 8050 850 50  0001 C CNN
	1    8050 850 
	-1   0    0    1   
$EndComp
Wire Wire Line
	8050 850  8150 850 
$Comp
L lomalkin_kicad_symbols:SolderPad X36
U 1 1 5FEE1775
P 8050 950
F 0 "X36" H 8300 950 50  0000 C CNN
F 1 "SolderPad" H 8100 900 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 8050 950 50  0001 C CNN
F 3 "" H 8050 950 50  0001 C CNN
	1    8050 950 
	-1   0    0    1   
$EndComp
Wire Wire Line
	8050 950  8150 950 
$Comp
L lomalkin_kicad_symbols:SolderPad X37
U 1 1 5FEE177D
P 8050 1050
F 0 "X37" H 8300 1050 50  0000 C CNN
F 1 "SolderPad" H 8100 1000 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 8050 1050 50  0001 C CNN
F 3 "" H 8050 1050 50  0001 C CNN
	1    8050 1050
	-1   0    0    1   
$EndComp
Wire Wire Line
	8050 1050 8150 1050
$Comp
L lomalkin_kicad_symbols:SolderPad X38
U 1 1 5FEE1785
P 8050 1150
F 0 "X38" H 8300 1150 50  0000 C CNN
F 1 "SolderPad" H 8100 1100 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 8050 1150 50  0001 C CNN
F 3 "" H 8050 1150 50  0001 C CNN
	1    8050 1150
	-1   0    0    1   
$EndComp
Wire Wire Line
	8050 1150 8150 1150
$Comp
L lomalkin_kicad_symbols:SolderPad X39
U 1 1 5FEE178D
P 8050 1250
F 0 "X39" H 8300 1250 50  0000 C CNN
F 1 "SolderPad" H 8100 1200 50  0001 C CNN
F 2 "lomalkin_kicad_footprints:Flipper-SolderPad" H 8050 1250 50  0001 C CNN
F 3 "" H 8050 1250 50  0001 C CNN
	1    8050 1250
	-1   0    0    1   
$EndComp
Wire Wire Line
	8050 1250 8150 1250
Text Label 8150 850  0    50   ~ 0
GND
Text Label 8150 950  0    50   ~ 0
GND
Text Label 8150 1050 0    50   ~ 0
GND
Text Label 8150 1150 0    50   ~ 0
GND
Text Label 8150 1250 0    50   ~ 0
GND
Wire Wire Line
	4850 2250 4750 2250
$EndSCHEMATC
