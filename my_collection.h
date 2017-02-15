#ifndef MY_COLLECTION_H_INCLUDED
#define MY_COLLECTION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct fiche fiche;
struct fiche
{
    char *nom_film;
    int annee;
    char *realisateur[1];
};

int ft_strlen(char *str);
void disp_fiche(fiche *tmp);
int add_fiche();

#endif // MY_COLLECTION_H_INCLUDED
