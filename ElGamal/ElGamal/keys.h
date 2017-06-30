//
//  keys.h
//  ElGamal
//
//  Created by Rokia on 6/7/17.
//  Copyright © 2017 Rokia. All rights reserved.
//

#ifndef keys_h
#define keys_h
#include <gmp.h>

struct secretK {
    mpz_t a;

};

typedef struct secretK secretK;

struct publicK {
    mpz_t beta;
};

typedef struct publicK publicK;


struct Cgroup{
    mpz_t p;
    mpz_t alpha;
};

typedef struct Cgroup Cgroup;

struct CipherT{
    mpz_t r;
    mpz_t t;

};

typedef struct CipherT CipherT;

#endif /* keys_h */
