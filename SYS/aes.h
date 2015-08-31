#ifndef __LIB_AES_H
#define __LIB_AES_H

#include <stdio.h>
#include "comdatatype.h"
#include "SYSModuleHeader.h"

#if (USE_AES_FUNC!=0)

#define IN
#define OUT


typedef struct
{
    UINT32 erk[64];     /* encryption round keys */
    UINT32 drk[64];     /* decryption round keys */
    int nr;             /* number of rounds */
}
aes_context;

int  aes_set_key( IN aes_context *ctx, IN UINT8 *key, IN int nbits );

void aes_encrypt( aes_context *ctx, UINT8 input[16], UINT8 output[16] );
void aes_decrypt( aes_context *ctx, UINT8 input[16], UINT8 output[16] );

//
void aes_encrypt_cbc( IN UINT8 aeskey[16], IN UINT8 Iv[16], IN UINT8 *input, IN UINT32 inLen, OUT UINT8 *output, OUT UINT32 *outLen);
void aes_decrypt_cbc( IN UINT8 aeskey[16], IN UINT8 Iv[16], IN UINT8 *input, IN UINT32 inLen, OUT UINT8 *output, OUT UINT32 *outLen);

void XorData(IN UINT8 *factor, IN OUT UINT8 *input, IN UINT32 inLen);


#endif	//USE_AES_FUNC

#endif /* aes.h */

 
