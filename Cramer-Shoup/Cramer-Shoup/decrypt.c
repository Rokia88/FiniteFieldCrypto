//
//  decrypt.c
//  Cramer-Shoup
//
//  Created by Rokia on 6/6/17.
//  Copyright © 2017 Rokia. All rights reserved.
//

#include "decrypt.h"


#include "keys.h"
#include "hashF.h"
#include <gmp.h>

void decrypt_(mpz_t plainT, secretK sk, Cgroup gr, CipherT cipherT)
{
    mpz_t alpha, val1, val2, val3;
    mpz_inits(alpha, val1, val2,val3, NULL);
    hashF_(alpha, cipherT.u1, cipherT.u2, cipherT.e);
    mpz_powm(val1,cipherT.u1,sk.x1,gr.p);
    mpz_powm(val2,cipherT.u2,sk.x2,gr.p);
    mpz_mul(val1, val1, val2);
    mpz_mod(val1, val1, gr.p);
    
    mpz_powm(val3,cipherT.u1,sk.y1,gr.p);
    mpz_powm(val2,cipherT.u2,sk.y2,gr.p);
    mpz_mul(val2, val3, val2);
    mpz_mod(val2, val2, gr.p);
    mpz_powm(val3,val2,alpha,gr.p);
    
    mpz_mul(val1, val3, val1);
    mpz_mod(val1, val1, gr.p);
    
    if(mpz_cmp(val1,cipherT.v) == 0)
    {
        gmp_printf("val1 :%Zu \n",val1);
        gmp_printf("v :%Zu \n",cipherT.v);
        mpz_powm(val3,cipherT.u1,sk.z,gr.p);
        mpz_invert(val3, val3,gr.p);
        mpz_mul(plainT,cipherT.e,val3);
        mpz_mod(plainT, plainT, gr.p);
    }
    
    else
    {
        printf("decryption is aborted\n");
    }
    
    
    mpz_clears(alpha, val1, val2,val3, NULL);

}
