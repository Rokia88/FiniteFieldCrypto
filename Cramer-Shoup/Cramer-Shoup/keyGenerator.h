//
//  keyGenerator.h
//  Cramer-Shoup
//
//  Created by Rokia on 6/6/17.
//  Copyright © 2017 Rokia. All rights reserved.
//

#ifndef keyGenerator_h
#define keyGenerator_h

#include <stdio.h>
#include "keys.h"

void keyGenerator(secretK *sk,publicK *pk,Cgroup *g, unsigned int bitLength,unsigned int bitLengthK);

#endif /* keyGenerator_h */
