//
//  keyGenerator.c
//  ElGamal
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
    primitiveRoot_g(g->p,g->alpha,bitLength);
    
    
    //secret key
    generate(sk->a,g->p,bitLengthK, 0);

    
    //public key
    mpz_powm(pk->beta,g->alpha,sk->a,g->p);
  

}
