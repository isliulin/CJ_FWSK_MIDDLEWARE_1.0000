 
/****************************************************************************
 * 
 * FILENAME
 *     selfTest.c
 *
 * VERSION
 *     1.0
 *
 * DESCRIPTION
 *     This is the test program used to test the UARTs,net and uhost on NUC970
 *
 ****************************************************************************/

#include  "selfTest.h"


char sg_file_name[64] = "/dev/sda";

int fd;

//char buff[101];

char *dev=USB_SERIAL_DEVICE;

static struct termios newtios,oldtios; /*termianal settings */
static int saved_portfd=-1;            /*serial port fd */


int netTest(void)
{
   int ret=0;
   ret=system("./ether.sh");
   return ret;
}


void show_data(struct sg_io_hdr * hdr)
{

	unsigned char * buffer = hdr->dxferp;
	int i;

	printf("\nreceive data:");
	for (i = 0; i < hdr->dxfer_len; ++i) {
		printf(" %02x", *(buffer + i));

	}
	printf("\n");

}

unsigned char data_buffer_zhq[2048];

unsigned char testCmd[][10] = {{0x12, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00},
				{}};


/* Returns 0 if everything ok */
static int sg_cmd(int sg_fd, int cmd, unsigned char * buff)
{

	unsigned char senseBuff[SENSE_BUFF_LEN];
	struct sg_io_hdr io_hdr;

	memset(&io_hdr, 0, sizeof(sg_io_hdr_t));
	io_hdr.interface_id = 'S';
	io_hdr.cmd_len = sizeof(testCmd[cmd]);
	io_hdr.cmdp = testCmd[cmd];
	io_hdr.dxfer_direction = SG_DXFER_FROM_DEV;
	io_hdr.dxfer_len = 256;
	io_hdr.dxferp = data_buffer_zhq;
	io_hdr.mx_sb_len = SENSE_BUFF_LEN;
	io_hdr.sbp = senseBuff;
	io_hdr.timeout = DEF_TIMEOUT;

	if (ioctl(sg_fd, SG_IO, &io_hdr)) {
		perror("reading (SG_IO) on sg device, error");
		return -1;
	}
	show_data(&io_hdr);
	return 0;
}

int udiskTest()
{
    int sg_fd,res;

    sg_fd = open(sg_file_name,O_RDONLY);
    if (sg_fd < 0)
    {
       perror(ME "sg device node open error");
       return -1;
    }
    res = sg_cmd(sg_fd,0, NULL);
    if (res < 0) {
          printf(ME "not a sg device, or driver prior to 3.x\n");
          return -1;
    }
    res = close(sg_fd);
    if (res < 0) {
         perror(ME "sg device close error");
         return -1;
    }
    return 0;
}


static void reset_tty_atexit(void)
{
	if(saved_portfd != -1)
	{
		tcsetattr(saved_portfd,TCSANOW,&oldtios);
	} 
}

static int open_port(const char *portname)
{
	int portfd;

	printf("\n Opening serial port:%s\n",portname);
	/*open serial port */
	if((portfd=open(portname,O_RDWR | O_NOCTTY)) < 0 )
	{
   		printf("open serial port %s fail \n ",portname);
   		return portfd;
	}

	/*get serial port parnms,save away */
	tcgetattr(portfd,&newtios);
	memcpy(&oldtios,&newtios,sizeof newtios);
	/* configure new values */
	cfmakeraw(&newtios); /*see man page */
	newtios.c_iflag |=IGNPAR; /*ignore parity on input */
	newtios.c_oflag &= ~(OPOST | ONLCR | OLCUC | OCRNL | ONOCR | ONLRET | OFILL); 
	newtios.c_cflag = CS8 | CLOCAL | CREAD;
	newtios.c_cc[VMIN]=1; /* block until 1 char received */
	newtios.c_cc[VTIME]=0; /*no inter-character timer */
	/* 115200 bps */
	cfsetospeed(&newtios,B115200);
	cfsetispeed(&newtios,B115200);
	/* register cleanup stuff */
	atexit(reset_tty_atexit);
	/*apply modified termios */
	saved_portfd=portfd;
	tcflush(portfd,TCIFLUSH);
	tcsetattr(portfd,TCSADRAIN,&newtios);
	return portfd;
}

/*
* FUNC: uart_test 
* DESCRIPTION:uart loop test func
* RETURN: 0 is success and -1 is failed.
*/
int  uartTest()
{/*****************
	unsigned char i, j;
	int rev1, rev2;
	char RxBuffer[101];	

	rev1 =0;
	rev2 =0;

        for(i = 0; i < 100; i++)
        {
                buff[i] = (i & 0xff);
        }
        if((fd = open_port(dev))<0)
        {
            printf("open uart device failed.\n");
            return -1;
        }
	while(rev2 < 100)
   	{
		rev1 = write(fd,(buff+rev2),100);
		rev2 += rev1;
   	}

	printf("\n %s send %d byts\n",dev, rev2);

	rev1 = 0;
	rev2 = 0;

	while(rev2 < 100)
	{
		rev1 = read(fd,(RxBuffer+rev2),100);
		rev2 += rev1;
	}
		
	printf("\n %s receive %d bytes\n",dev, rev2);

	for(j = 0; j < 100; j++)
	{
		if(j != RxBuffer[j])
		{
			printf("\n %s compare Error!!",dev);
						
			return  -1;
		}
	}
      printf("\n %s compare correct!!\n",dev); 
      printf("\n %s test done!!\n",dev);
	  **********************************/
       return  0;

}	
