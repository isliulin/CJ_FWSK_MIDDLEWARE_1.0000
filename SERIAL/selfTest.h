
#ifndef SELFTEST_H
#define SELFTEST_H

#include     <stdio.h>
#include     <stdlib.h>
#include     <unistd.h> 
#include     <sys/types.h> 
#include     <sys/stat.h> 
#include     <fcntl.h> 
#include     <termios.h>  
#include     <errno.h>
#include     <string.h>
#include     <signal.h>
#include     <sys/ioctl.h>
#include     <scsi/sg.h>
#include     <scsi/scsi.h>
#include     "SerialConfig.h"

#define ME "SCSICMD: "

#define SENSE_BUFF_LEN 32
#define DEF_TIMEOUT 40000       /* 40,000 milliseconds */

#ifdef __cplusplus
extern "C" {
#endif

int netTest();
int udiskTest();
int  uartTest();
#ifdef __cplusplus
}
#endif

#endif