//
//  keys.h
//  Cramer-Shoup
//
//  Created by Rokia on 6/7/17.
//  Copyright © 2017 Rokia. All rights reserved.
//

#ifndef keys_h
#define keys_h
#include <gmp.h>

struct secretK {
    mpz_t x1;
    mpz_t x2;
    mpz_t y1;
    mpz_t y2;
    mpz_t z;
};

typedef struct secretK secretK;

struct publicK {
    mpz_t c;
    mpz_t d;
    mpz_t h;
};

typedef struct publicK publicK;


struct Cgroup{
    mpz_t p;
    mpz_t q;
    mpz_t g1;
    mpz_t g2;
};

typedef struct Cgroup Cgroup;

struct CipherT{
    mpz_t u1;
    mpz_t u2;
    mpz_t e;
    mpz_t v;
};

typedef struct CipherT CipherT;

#endif /* keys_h */
