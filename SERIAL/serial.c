#include <sys/timeb.h>
#include "DataTypeDesign.h"
#include "serial.h"

volatile int devfd = -2;

int openPort(char* path, int baudrate) {
	unsigned char temp;
	int ret=0;
	devfd = port_open(path, baudrate);
	if (devfd < 0) {
		printf("open serial %s %d failed!\n", path, baudrate);
		return -1;
	}

	do {
		ret = read(devfd, &temp, 1);
	}while(ret!=0 && ret!=-1);

	return devfd;
}

void closePort() {
	if (0 < devfd) {
		close(devfd);
	}
	return;
}

void cleanSerial() {
	unsigned char temp;
	while(read(devfd, &temp, 1));
}

int sendBytes(unsigned char* sendData, int sendLen) {
	if (0 > devfd)
	{
		return -1;
	}
	int size = write(devfd, sendData, sendLen);
	if (size != sendLen) {
		return size;
	}
	return 0;
}

int readBytes(unsigned char* revData, int revLen) {
	int size = 0;

	if (0 > devfd)
	{
		printf("serial is not open correctly\n");
		return -1;
	}
	size = read(devfd, revData, revLen);

	if (size < 0)
		size=0;

	return size;
}

void set_speed(int fd, int speed) {
	int i;
	int status;
	struct termios Opt;
	int speed_arr[] = { B115200, B57600, B38400, B19200, B9600, B4800, B2400, B1200, B300 };
	int name_arr[] = { 115200, 57600, 38400, 19200, 9600, 4800, 2400, 1200, 300 };

	tcgetattr(fd, &Opt);
	for (i = 0; i < sizeof(speed_arr) / sizeof(int); i++) {
		if (speed == name_arr[i]) {
			tcflush(fd, TCIOFLUSH);
			cfsetispeed(&Opt, speed_arr[i]);
			cfsetospeed(&Opt, speed_arr[i]);
			status = tcsetattr(fd, TCSANOW, &Opt);
			if (status != 0) {
				perror("tcsetattr fd");
				return;
			}
			tcflush(fd, TCIOFLUSH);
		}
	}
}

int set_property(int fd, int databits, int stopbits, int parity) {
	struct termios options;

	if (tcgetattr(fd, &options) != 0) {
		perror("SetupSerial 1");
		return -1;
	}

	/* set databits */				//数据位长度
	options.c_cflag &= ~CSIZE;
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); /*Input*/
	options.c_oflag &= ~OPOST; /*Output*/

	switch (databits) {
	case 7:
		options.c_cflag |= CS7;
		break;
	case 8:
		options.c_cflag |= CS8;
		break;
	default:
		return -1;
	}
	//设置校验位
	switch (parity) {
	case 'n':
	case 'N':
		options.c_cflag &= ~PARENB; /* Clear parity enable */
		options.c_iflag &= ~INPCK; /* Disable parity checking */
		break;
	case 'o':
	case 'O':
		options.c_cflag |= (PARODD | PARENB); /* Odd parity */
		options.c_iflag |= INPCK; /* Enable parity checking */
		break;
	case 'e':
	case 'E':
		options.c_cflag |= PARENB; /* Enable parity */
		options.c_cflag &= ~PARODD; /* Even parity */
		options.c_iflag |= INPCK; /* Enable parity checking */
		break;
	case 'S':
	case 's': /*as no parity*/
		options.c_cflag &= ~PARENB;
		options.c_cflag &= ~CSTOPB;
		break;
	default:
		return -1;
	}
	//设置停止位
	/* set stopbits */
	switch (stopbits) {
	case 1:
		options.c_cflag &= ~CSTOPB;
		break;
	case 2:
		options.c_cflag |= CSTOPB;
		break;
	default:
		return -1;
	}

	tcflush(fd, TCIFLUSH);

	// Update the options and do it NOW
	if (tcsetattr(fd, TCSANOW, &options) != 0) {
		perror("SetupSerial 3");
		return -1;
	}
	return 1;
}

void setTermios(struct termios * pNewtio, int uBaudRate) {
	bzero(pNewtio, sizeof(struct termios));

	//8N1
	pNewtio->c_cflag = uBaudRate | CS8 | CREAD | CLOCAL;
	pNewtio->c_iflag = IGNPAR;
	pNewtio->c_oflag = 0;
	pNewtio->c_lflag = 0; //non ICANON

	pNewtio->c_cc[VINTR] = 0;
	pNewtio->c_cc[VQUIT] = 0;
	pNewtio->c_cc[VERASE] = 0;
	pNewtio->c_cc[VKILL] = 0;
	pNewtio->c_cc[VEOF] = 4;
	pNewtio->c_cc[VTIME] = 5;
	pNewtio->c_cc[VMIN] = 0;
	pNewtio->c_cc[VSWTC] = 0;
	pNewtio->c_cc[VSTART] = 0;
	pNewtio->c_cc[VSTOP] = 0;
	pNewtio->c_cc[VSUSP] = 0;
	pNewtio->c_cc[VEOL] = 0;
	pNewtio->c_cc[VREPRINT] = 0;
	pNewtio->c_cc[VDISCARD] = 0;
	pNewtio->c_cc[VWERASE] = 0;
	pNewtio->c_cc[VLNEXT] = 0;
	pNewtio->c_cc[VEOL2] = 0;
}

int port_open(char *dev, int baudrate) {
	int fd;
	struct termios options;
	/* open the port */
	fd = open(dev, O_RDWR | O_NOCTTY | O_NDELAY);
	if (-1 == fd) {
		perror("Can''t Open Serial Port");
		return -1;
	}
	/* get the current options */
	tcgetattr(fd, &options);
	/* set raw input, 1 second timeout */
	options.c_cflag |= (CLOCAL | CREAD);
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	options.c_oflag &= ~OPOST;
	/* disable software flow control and CR NL map */
	options.c_iflag &= ~(IXON | IXOFF | INLCR | ICRNL);
	options.c_cc[VMIN] = 0;
	options.c_lflag &= ~ICANON;
	options.c_cc[VTIME] = 3;				// timeout(1/10s)
	/* set the options */
	tcsetattr(fd, TCSANOW, &options);
	//set baudrate
	set_speed(fd, baudrate);
	// 设置串口数据帧格式 数据位8,停止位1,校验位 无。
	if (set_property(fd, 8, 1, 'N') == -1) {
		return -1;
	}
	return fd;
}

#if COMMUNICATE_VERSION==BLUETOOTH_VERSION || PROJECT_TYPE_MODE == PROJECT_TYPE_A5_YTJ
volatile int printerfd = -2;
int openPrinterPort(char* path, int baudrate)
{
	unsigned char temp;
	printerfd = port_open(path, baudrate);
	if (printerfd < 0) {
		printf("open printer serial %s %d failed!\n", path, baudrate);
		return -1;
	}

	while(read(printerfd, &temp, 1));

	return printerfd;
}
void closePrinterPort()
{
	if (0 < printerfd) {
		close(printerfd);
	}
	return;
}
int printLine(unsigned char* sendData, int sendLen)
{
	printf("printLine printerfd=%d\n", printerfd);
	if (0 > printerfd)
	{
		return -1;
	}
	printf("sendLen=%d\n", sendLen);
	int size = write(printerfd, sendData, sendLen);
	printf("size=%d\n", size);
	if (size != sendLen) {
		return size;
	}
	return 0;
}
#endif


