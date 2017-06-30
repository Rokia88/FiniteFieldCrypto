//
//  main.c
//  ElGamal
//
//  Created by Rokia on 6/6/17.
//  Copyright © 2017 Rokia. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "primitiveRoot.h"
#include "RandomGenerator.h"
#include "keyGenerator.h"
#include "keys.h"
#include "encrypt.h"
#include "decrypt.h"
#include <gmp.h>
#include <time.h>

#define MSGL  160
#define NbrTrials 200


long double cputime()
{
    struct rusage rus;
    
    getrusage (0, &rus);
    return rus.ru_utime.tv_sec * 1000 + rus.ru_utime.tv_usec / 1000;
}

int main(int argc, const char * argv[]) {
    
    // number of bits of security
    //unsigned int bs[] = {80,112,128,192,256};
    //key for FF, group for EC
    unsigned int k[] = {160,224,256,384,512};
    //group for FF
    unsigned int g[] = {1024,2048,3072,7680,15360};
    
    FILE* f = NULL;
    char *new_str;
    //char *new_str1;
    asprintf(&new_str,"%s","ExecutionTime.txt");
    f = fopen(new_str, "r");
    if (f == NULL)
    {
        f = fopen(new_str, "a+");
        fprintf(f,"%-15s  |%-15s  |%-15s  |\n\n","keyLength", "encrypt(ms)","decrypt(ms)");
        
    }
    else
    {
        fclose(f);
        f = fopen(new_str, "a+");
    }
    
    long double startT = 0;
    long double computationE,computationD  = -1;
    
    //msg to encrypt
    
    mpz_t msg, msgP;
    mpz_inits(msg, msgP, NULL);
    generate(msg, NULL,MSGL,0);
    gmp_printf("msg :%Zu \n",msg);
    
    //key generation
    secretK sk;
    publicK pk;
    Cgroup gr;
    CipherT ci;
    
    mpz_inits(sk.a,pk.beta,gr.alpha,gr.p,ci.r,ci.t,NULL);
    
for(int i = 0; i < 5; i++)
{
    
    //key generation
    keyGenerator(&sk,&pk,&gr,g[i],k[i]);
    
    gmp_printf("a :%Zu \n",sk.a);
    
    gmp_printf("beta :%Zu \n",pk.beta);
    
    gmp_printf("alpha :%Zu \n",gr.alpha);
    gmp_printf("p :%Zu \n",gr.p);
 
    
    for(int j = 0; j < NbrTrials; j++)
    {
        //encrypt
        startT = cputime();
        for(int j=0; j < 1000; j++)
        {
            encrypt_(&ci, pk, gr,k[i],msg);
        }
        computationE = (cputime() - startT)/1000;
        gmp_printf("r :%Zu \n",ci.r);
        gmp_printf("t :%Zu \n",ci.t);
    
    
        //decrypt
        startT = cputime();
        for(int j=0; j < 1000; j++)
        {
            decrypt_(msgP, sk,gr,ci);
        }
        computationD = (cputime() - startT)/1000;
    
        if(mpz_cmp(msg,msgP)==0)
        {
            printf("***********OK***************\n");
            fprintf(f, "%-15d  |%-15Lf  |%-15Lf  |\n", g[i],computationE,computationD);
        }
        else
        {
            fprintf(f, "%-15d  |%-45s  |\n", g[i],"computation error");
        }
    }

}
    fclose(f);
    mpz_clears(sk.a,pk.beta,gr.alpha,gr.p,ci.r,ci.t, msg, msgP, NULL);
    return 0;
}
