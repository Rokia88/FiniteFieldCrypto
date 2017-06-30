//
//  encrypt.c
//  ElGamal
//
//  Created by Rokia on 6/6/17.
//  Copyright © 2017 Rokia. All rights reserved.
//

#include "encrypt.h"
#include "keys.h"
#include "RandomGenerator.h"
#include <gmp.h>

void encrypt_(CipherT *cipher, publicK pk, Cgroup gr,unsigned int bitLengthK, mpz_t msg)
{
    mpz_t k,val1;
    mpz_inits(k, val1, NULL);
    
    
    generate(k,gr.p,bitLengthK, 0);
    mpz_powm(cipher->r,gr.alpha,k,gr.p); //r
    
    mpz_powm(val1,pk.beta,k,gr.p);
    mpz_mul(cipher->t,val1,msg);
    mpz_mod(cipher->t, cipher->t, gr.p); //t
   
    
    mpz_clears(k, val1,NULL);
}
