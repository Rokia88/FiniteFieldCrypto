//
//  decrypt.h
//  Cramer-Shoup
//
//  Created by Rokia on 6/6/17.
//  Copyright © 2017 Rokia. All rights reserved.
//

#ifndef decrypt_h
#define decrypt_h

#include <stdio.h>
#include <gmp.h>
#include "keys.h"

void decrypt_(mpz_t plainT, secretK sk, Cgroup gr, CipherT cipherT);
#endif /* decrypt_h */
