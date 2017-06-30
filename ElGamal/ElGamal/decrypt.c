//
//  decrypt.c
//  ElGamal
//
//  Created by Rokia on 6/6/17.
//  Copyright © 2017 Rokia. All rights reserved.
//

#include "decrypt.h"


#include "keys.h"
#include <gmp.h>

void decrypt_(mpz_t plainT, secretK sk, Cgroup gr, CipherT cipherT)
{
    mpz_t val1;
    mpz_init(val1);

    mpz_powm(val1,cipherT.r,sk.a,gr.p);
    mpz_invert(val1, val1,gr.p);
    
    
    mpz_mul(plainT, val1, cipherT.t);
    mpz_mod(plainT, plainT, gr.p);
    
    
    mpz_clear(val1);

}
