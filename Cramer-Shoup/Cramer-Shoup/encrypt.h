//
//  encrypt.h
//  Cramer-Shoup
//
//  Created by Rokia on 6/6/17.
//  Copyright © 2017 Rokia. All rights reserved.
//

#ifndef encrypt_h
#define encrypt_h

#include <stdio.h>
#include <gmp.h>
#include "keys.h"

void encrypt_(CipherT *cipher, publicK pk, Cgroup gr,mpz_t msg);
#endif /* encrypt_h */
