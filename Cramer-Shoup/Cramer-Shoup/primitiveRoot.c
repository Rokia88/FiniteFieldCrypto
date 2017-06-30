//
//  primitiveRoot.c
//  Cramer-Shoup
//
//  Created by Rokia on 6/6/17.
//  Copyright © 2017 Rokia. All rights reserved.
//

#include "primitiveRoot.h"
#include "RandomGenerator.h"
#include <gmp.h>

void primitiveRoot_g(mpz_t p,mpz_t g1, mpz_t g2,unsigned int bitLength)
{
 
    mpz_t p2,G,val;
    mpz_inits(p2,G,val,NULL);
    mpz_sub_ui(p2,p,1);
    mpz_div_ui(p2,p2,2);
    
    gmp_printf("p2 :%Zu \n",p2);
    
    generate(g1,p,0, 3);
    mpz_powm(G,g1,p2,p);
    
    if(mpz_cmp_ui(G,1)== 0)
    {
        //-g1 is a generator
        mpz_sub(g1,p,g1);
        
    }
    
    do{
        generate(g2,p,0, 3);
        mpz_powm(G,g2,p2,p);
        if(mpz_cmp_ui(G,1)== 0)
        {
            //-g2 is a generator
            mpz_sub(g2,p,g2);
        }
        
    }while(mpz_cmp(g1,g2)==0);
    
    gmp_printf("g1 :%Zu \n",g1);
    gmp_printf("g2 :%Zu \n",g2);
    
    mpz_clears(p2,G,val,NULL);

}
