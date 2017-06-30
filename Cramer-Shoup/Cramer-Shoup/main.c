//
//  main.c
//  Cramer-Shoup
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
    
    FILE* fichier = NULL;
    char *new_str;
    //char *new_str1;
    asprintf(&new_str,"%s","ExecutionTime.txt");
    fichier = fopen(new_str, "r");
    if (fichier == NULL)
    {
        fichier = fopen(new_str, "a+");
        fprintf(fichier,"%-15s  |%-15s  |%-15s  |\n\n","keyLength", "encrypt(ms)","decrypt(ms)");
        fflush(fichier);
    }
    else
    {
        fclose(fichier);
        fichier = fopen(new_str, "a+");
    }
    
    long double startT = 0;
    long double computationE=-1,computationD  = -1;
    
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
    
    mpz_inits(sk.x1,sk.x2,sk.y2,sk.y1,sk.z,pk.c,pk.d,pk.h,gr.g1,gr.g2,gr.p,gr.q,ci.e,ci.u1,ci.u2,ci.v,NULL);
    
for(int i = 0; i < 5; i++)
{
    
    //key generation
    keyGenerator(&sk,&pk,&gr,g[i],k[i]);
    
    gmp_printf("x1 :%Zu \n",sk.x1);
    gmp_printf("x2 :%Zu \n",sk.x2);
    gmp_printf("y2 :%Zu \n",sk.y2);
    gmp_printf("y1 :%Zu \n",sk.y1);
    gmp_printf("z :%Zu \n",sk.z);
    
    gmp_printf("c :%Zu \n",pk.c);
    gmp_printf("d :%Zu \n",pk.d);
    gmp_printf("h :%Zu \n",pk.h);
    
    gmp_printf("g1 :%Zu \n",gr.g1);
    gmp_printf("g2 :%Zu \n",gr.g2);
    gmp_printf("p :%Zu \n",gr.p);
    gmp_printf("q :%Zu \n",gr.q);
    
    for(int j = 0; j < NbrTrials; j++)
    {
        //encrypt
        if(i != 4)
        {
            startT = cputime();
            for(int l= 0; l < 1000 ; l++)
            {
                encrypt_(&ci, pk, gr,msg);
            }
            computationE = (cputime() - startT)/1000;
        }
        else if(i==4)
        {
            startT = cputime();
            encrypt_(&ci, pk, gr,msg);
            computationE = (cputime() - startT);
        }
        
        gmp_printf("e :%Zu \n",ci.e);
        gmp_printf("u1 :%Zu \n",ci.u1);
        gmp_printf("u2:%Zu \n",ci.u2);
        gmp_printf("v:%Zu \n",ci.v);
    
    
        //decrypt
        startT = cputime();
        for(int l= 0; l < 1000; l++)
        {
            decrypt_(msgP, sk,gr,ci);
        }
        computationD = (cputime() - startT)/1000;
    
        if(mpz_cmp(msg,msgP)==0)
        {
            printf("***********OK***************\n");
            fprintf(fichier, "%-15d  |%-15Lf  |%-15Lf  |\n", g[i],computationE,computationD);
            fflush(fichier);
        }
        else
        {
            fprintf(fichier, "%-15d  |%-45s  |\n", g[i],"computation error");
            fflush(fichier);
        }
    }

}
    fclose(fichier);
    mpz_clears(sk.x1,sk.x2,sk.y2,sk.y1,sk.z,pk.c,pk.d,pk.h,gr.g1,gr.g2,gr.p,gr.q,ci.e,ci.u1,ci.u2,ci.v, msg, msgP, NULL);
    return 0;
}
