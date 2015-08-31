#ifndef SERIAL_H
#define SERIAL_H

#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "SerialConfig.h"

#ifdef __cplusplus
extern "C" {
#endif

int openPort(char* path, int baudrate);
void closePort();
int sendBytes(unsigned char* sendData, int sendLen);
int readBytes(unsigned char* revData, int revLen);
void cleanSerial();

#if COMMUNICATE_VERSION==BLUETOOTH_VERSION || PROJECT_TYPE_MODE == PROJECT_TYPE_A5_YTJ
int openPrinterPort(char* path, int baudrate);
void closePrinterPort();
int printLine(unsigned char* sendData, int sendLen);
#endif

#ifdef __cplusplus
}
#endif

#endif