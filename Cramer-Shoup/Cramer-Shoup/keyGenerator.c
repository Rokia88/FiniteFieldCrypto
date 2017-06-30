//
//  keyGenerator.c
//  Cramer-Shoup
//
//  Created by Rokia on 6/6/17.
//  Copyright © 2017 Rokia. All rights reserved.
//

#include "keyGenerator.h"
#include "RandomGenerator.h"
#include "primitiveRoot.h"
#include "keys.h"
#include <gmp.h>

void keyGenerator(secretK *sk,publicK *pk,Cgroup *g, unsigned int bitLength,unsigned int bitLengthK)
{
 
    //description of the group
    generate(g->p,NULL,bitLength, 1);
    primitiveRoot_g(g->p,g->g1,g->g2,bitLength);
    mpz_sub_ui(g->q,g->p,1);
    
    mpz_t c1, c2, d1, d2;
    mpz_inits(c1, c2, d1, d2, NULL);
    
    //secret key
    generate(sk->x1,g->p,bitLengthK, 0);
    generate(sk->x2,g->p,bitLengthK, 0);
    generate(sk->y1,g->p,bitLengthK, 0);
    generate(sk->y2,g->p,bitLengthK, 0);
    generate(sk->z,g->p,bitLengthK, 0);
    
    //public key
    mpz_powm(c1,g->g1,sk->x1,g->p);
    mpz_powm(c2,g->g2,sk->x2,g->p);
    mpz_mul(pk->c,c1,c2);
    mpz_mod(pk->c, pk->c, g->p);
    
    mpz_powm(d1,g->g1,sk->y1,g->p);
    mpz_powm(d2,g->g2,sk->y2,g->p);
    mpz_mul(pk->d,d1,d2);
    mpz_mod(pk->d, pk->d, g->p);
    
    mpz_powm(pk->h,g->g1,sk->z,g->p);
    
    mpz_clears(c1, c2, d1, d2, NULL);
}
