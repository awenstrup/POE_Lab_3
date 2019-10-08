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
L power:VCC #PWR?
U 1 1 5D8E1217
P 1700 1950
F 0 "#PWR?" H 1700 1800 50  0001 C CNN
F 1 "VCC" H 1717 2123 50  0000 C CNN
F 2 "" H 1700 1950 50  0001 C CNN
F 3 "" H 1700 1950 50  0001 C CNN
	1    1700 1950
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery BT?
U 1 1 5D8E128D
P 1700 2150
F 0 "BT?" H 1808 2196 50  0000 L CNN
F 1 "12V Battery (8 x 1.5V)" H 1808 2105 50  0000 L CNN
F 2 "" V 1700 2210 50  0001 C CNN
F 3 "~" V 1700 2210 50  0001 C CNN
	1    1700 2150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D8E1331
P 1700 2900
F 0 "#PWR?" H 1700 2650 50  0001 C CNN
F 1 "GND" H 1705 2727 50  0000 C CNN
F 2 "" H 1700 2900 50  0001 C CNN
F 3 "" H 1700 2900 50  0001 C CNN
	1    1700 2900
	1    0    0    -1  
$EndComp
$Comp
L MCU_Module:Arduino_UNO_R3 A?
U 1 1 5D8E13D5
P 3950 2200
F 0 "A?" H 4450 3300 50  0000 C CNN
F 1 "Arduino_UNO_R3" H 4700 3200 50  0000 C CNN
F 2 "Module:Arduino_UNO_R3" H 4100 1150 50  0001 L CNN
F 3 "https://www.arduino.cc/en/Main/arduinoBoardUno" H 3750 3250 50  0001 C CNN
	1    3950 2200
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 5D8E14AC
P 3850 1200
F 0 "#PWR?" H 3850 1050 50  0001 C CNN
F 1 "VCC" H 3867 1373 50  0000 C CNN
F 2 "" H 3850 1200 50  0001 C CNN
F 3 "" H 3850 1200 50  0001 C CNN
	1    3850 1200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D8E155B
P 4050 3300
F 0 "#PWR?" H 4050 3050 50  0001 C CNN
F 1 "GND" H 4055 3127 50  0000 C CNN
F 2 "" H 4050 3300 50  0001 C CNN
F 3 "" H 4050 3300 50  0001 C CNN
	1    4050 3300
	1    0    0    -1  
$EndComp
$Comp
L Device:D D?
U 1 1 5D8E1600
P 1700 2750
F 0 "D?" V 1746 2671 50  0000 R CNN
F 1 "D" V 1655 2671 50  0000 R CNN
F 2 "" H 1700 2750 50  0001 C CNN
F 3 "~" H 1700 2750 50  0001 C CNN
	1    1700 2750
	0    1    1    0   
$EndComp
$Comp
L Device:LED D?
U 1 1 5D8E17DB
P 1200 2550
F 0 "D?" V 1145 2628 50  0000 L CNN
F 1 "LED" V 1236 2628 50  0000 L CNN
F 2 "" H 1200 2550 50  0001 C CNN
F 3 "~" H 1200 2550 50  0001 C CNN
	1    1200 2550
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5D8E1B46
P 1200 2250
F 0 "R?" H 1270 2296 50  0000 L CNN
F 1 "R" H 1270 2205 50  0000 L CNN
F 2 "" V 1130 2250 50  0001 C CNN
F 3 "~" H 1200 2250 50  0001 C CNN
	1    1200 2250
	1    0    0    -1  
$EndComp
$EndSCHEMATC