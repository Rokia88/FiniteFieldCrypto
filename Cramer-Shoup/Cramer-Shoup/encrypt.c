//
//  encrypt.c
//  Cramer-Shoup
//
//  Created by Rokia on 6/6/17.
//  Copyright © 2017 Rokia. All rights reserved.
//

#include "encrypt.h"
#include "keys.h"
#include "hashF.h"
#include "RandomGenerator.h"
#include <gmp.h>

void encrypt_(CipherT *cipher, publicK pk, Cgroup gr,mpz_t msg)
{
    mpz_t k, val1, val2, val3, alpha;
    mpz_inits(k, val1, val2, alpha, val3, NULL);
    generate(k,gr.p,0, 3);
    mpz_powm(cipher->u1,gr.g1,k,gr.p); //u1
    mpz_powm(cipher->u2,gr.g2,k,gr.p); //u2
    mpz_powm(val1,pk.h,k,gr.p);
    mpz_mul(cipher->e,val1,msg);
    mpz_mod(cipher->e, cipher->e, gr.p); //e
    hashF_(alpha, cipher->u1, cipher->u2, cipher->e);
    mpz_powm(val1,pk.c,k,gr.p);
    mpz_mul(val2,k,alpha);
    //mpz_mod(val2,val2, gr.p);
    mpz_powm(val3,pk.d,val2,gr.p);
    mpz_mul(cipher->v,val3,val1);
    mpz_mod(cipher->v,cipher->v, gr.p); //v
    
    mpz_clears(k, val1, val2, alpha, val3, NULL);
}
