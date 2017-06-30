//
//  hashF.c
//  Cramer-Shoup
//
//  Created by Rokia on 6/7/17.
//  Copyright © 2017 Rokia. All rights reserved.
//

#include "hashF.h"
#include <openssl/sha.h>
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hashF_(mpz_t hsh, mpz_t elt1, mpz_t elt2, mpz_t elt3)
{
    SHA512_CTX c;
    SHA512_Init(&c);
    
    unsigned char hash[SHA512_DIGEST_LENGTH];
    char *h= (char*) malloc(8);
    char *h_f= (char*) malloc(SHA512_DIGEST_LENGTH*2 + 1);
    
    char *selt1 = (char*) malloc(2 + mpz_sizeinbase(elt1, 10));
    mpz_get_str(selt1, 10, elt1);
    printf("L1:%d %d \n", (int)mpz_sizeinbase(elt1, 10), (int)strlen(selt1));
    SHA512_Update(&c, selt1, (int)strlen(selt1));
    
    char *selt2 = (char*) malloc(2 + mpz_sizeinbase(elt2, 10));
    mpz_get_str(selt2, 10, elt2);
    printf("L2:%d %d \n", (int)mpz_sizeinbase(elt2, 10), (int)strlen(selt2));
    SHA512_Update(&c, selt2, (int) strlen(selt2));
    
    char *selt3 = (char*) malloc(2 + mpz_sizeinbase(elt3, 10));
    mpz_get_str(selt3, 10, elt3);
    printf("L3:%d %d \n", (int)mpz_sizeinbase(elt3, 10), (int)strlen(selt3));
    SHA512_Update(&c, selt3, (int)strlen(selt3));

    SHA512_Final(hash, &c);
    
    for (int i= 0; i< SHA512_DIGEST_LENGTH; ++i)
    {
        sprintf(h,"%x",hash[i]);
        if(i==0)
        {
            strcpy(h_f, h);
        }
        else
        {
            strncat(h_f, h,strlen(h));
        }
    }
    printf("hash:%s \n",h_f);
    
    mpz_set_str(hsh,h_f,16);

    free(h);
    free(h_f);
    free(selt1);
    free(selt2);
    free(selt3);

}
