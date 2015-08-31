/*! \file    base64.c
   \brief    base64������뺯����ʵ���ļ�
   \author   zl
 */

#include "base64.h"


static char basis_64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";	


#define CHAR64(c)  (((c) < 0 || (c) > 127) ? -1 : index_64[(c)])
	
static signed char index_64[128] = {	
	    -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,	
	    -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,	
	    -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,62, -1,-1,-1,63,	
	    52,53,54,55, 56,57,58,59, 60,61,-1,-1, -1,-1,-1,-1,	
	    -1, 0, 1, 2,  3, 4, 5, 6,  7, 8, 9,10, 11,12,13,14,	
	    15,16,17,18, 19,20,21,22, 23,24,25,-1, -1,-1,-1,-1,	
	    -1,26,27,28, 29,30,31,32, 33,34,35,36, 37,38,39,40,	
	    41,42,43,44, 45,46,47,48, 49,50,51,-1, -1,-1,-1,-1	
} ;


void Base64_Encode_2(unsigned char *buf, int vlen) 
{
    char *out;	
    char *offset = buf+vlen-1;	
    unsigned char oval = 0 ; 	
	int base64_len=0;
	int x=0;
	unsigned char tmpbuf[3];
	
	base64_len = vlen / 3;
	x = vlen % 3;
	if (x != 0)
	{
		base64_len++;
	}
	base64_len *= 4;
	
	out = buf + base64_len + 1;
	*out-- = '\0';

	if (x != 0)
	{
		out -= 4;
		if (x == 2)
			tmpbuf[1] = *offset--;
		tmpbuf[0] = *offset--;

	    *out++ = basis_64[tmpbuf[0] >> 2];	
	    oval = (tmpbuf[0] << 4) & 0x30 ;	
	    if (x > 1) oval |= tmpbuf[1] >> 4;	
	    *out++ = basis_64[oval];	
	    *out++ = (x < 2) ? '=' : basis_64[(tmpbuf[1] << 2) & 0x3C];	
	    *out++ = '=';	
		out -= 4;
	}
	

	out -= 4;
	while (out >= buf)
	{
		tmpbuf[2] = *offset--;
		tmpbuf[1] = *offset--;
		tmpbuf[0] = *offset--;

		
        *out++ = basis_64[tmpbuf[0] >> 2];	
        *out++ = basis_64[((tmpbuf[0] << 4) & 0x30) | (tmpbuf[1] >> 4)];	
        *out++ = basis_64[((tmpbuf[1] << 2) & 0x3C) | (tmpbuf[2] >> 6)];	
        *out++ = basis_64[tmpbuf[2] & 0x3F];	

		out -= 8;
	}
	

}	

void Base64_Decode_2(char *value, int *rlen)	
{		
    int c1, c2, c3, c4;	        	
    int vlen = strlen(value);	
    char *out = value;	

    *rlen = 0;

    while (1) 
    {	
		if (value[0]==0) {
            *out = '\0' ; 
            return;	
		}
        c1 = value[0];	
        if (CHAR64(c1) == -1) goto base64_decode_error;
	    c2 = value[1];	
	    if (CHAR64(c2) == -1) goto base64_decode_error;
	    c3 = value[2];	
	    if ((c3 != '=') && (CHAR64(c3) == -1)) goto base64_decode_error;
	    c4 = value[3];	
	    if ((c4 != '=') && (CHAR64(c4) == -1)) goto base64_decode_error;	
        value += 4;	
	    *out++ = (CHAR64(c1) << 2) | (CHAR64(c2) >> 4);	
	    *rlen += 1;	
	    if (c3 != '=') 
        {	
	        *out++ = ((CHAR64(c2) << 4) & 0xf0) | (CHAR64(c3) >> 2);	
	        *rlen += 1;	
	        if (c4 != '=') 
            {	
	            *out++ = ((CHAR64(c3) << 6) & 0xc0) | CHAR64(c4);	
	                *rlen += 1;	
	        }
	    }	
	}	
base64_decode_error:	
	printf("base64_decode_error!!!\n");
    *rlen = 0;	

}



void Base64_Encode(unsigned char *value, int vlen, char *pcBase64Value) 
{
    unsigned char oval = 0 ; 	
//    char *result = (char *)malloc((vlen * 4) / 3 + 5) ;	
    char *out = pcBase64Value;	

	while (vlen >= 3) 
    {	
        	*out++ = basis_64[value[0] >> 2];	
        	*out++ = basis_64[((value[0] << 4) & 0x30) | (value[1] >> 4)];	
        	*out++ = basis_64[((value[1] << 2) & 0x3C) | (value[2] >> 6)];	
        	*out++ = basis_64[value[2] & 0x3F];	
        	value += 3;	
       		vlen -= 3;	
    }

	if (vlen > 0) 
    {	
	        *out++ = basis_64[value[0] >> 2];	
	        oval = (value[0] << 4) & 0x30 ;	
	        if (vlen > 1) oval |= value[1] >> 4;	
	        *out++ = basis_64[oval];	
	        *out++ = (vlen < 2) ? '=' : basis_64[(value[1] << 2) & 0x3C];	
	        *out++ = '=';	
	}	
	*out = '\0';		

}	

void Base64_Decode(char *value, unsigned char *result, int *rlen)	
{		
    int c1, c2, c3, c4;	        	
    int vlen = strlen(value);	
    //unsigned char *result =(unsigned char *)malloc((vlen * 3) / 4 + 1);	
    unsigned char *out = result;	

    *rlen = 0;

    while (1) 
    {	
		if (value[0]==0) {
            *out = '\0' ; 
            return;	
		}
        c1 = value[0];	
        if (CHAR64(c1) == -1) goto base64_decode_error;
	    c2 = value[1];	
	    if (CHAR64(c2) == -1) goto base64_decode_error;
	    c3 = value[2];	
	    if ((c3 != '=') && (CHAR64(c3) == -1)) goto base64_decode_error;
	    c4 = value[3];	
	    if ((c4 != '=') && (CHAR64(c4) == -1)) goto base64_decode_error;	
        value += 4;	
	    *out++ = (CHAR64(c1) << 2) | (CHAR64(c2) >> 4);	
	    *rlen += 1;	
	    if (c3 != '=') 
        {	
	        *out++ = ((CHAR64(c2) << 4) & 0xf0) | (CHAR64(c3) >> 2);	
	        *rlen += 1;	
	        if (c4 != '=') 
            {	
	            *out++ = ((CHAR64(c3) << 6) & 0xc0) | CHAR64(c4);	
	                *rlen += 1;	
	        }
	    }	
	}	
base64_decode_error:	
    *rlen = 0;	

}


