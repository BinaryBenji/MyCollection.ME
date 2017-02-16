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

int             ft_strlen(char *str);
void            disp_all_fiches(char **tab);
char            *ft_strclr(char *str);
static int      cmpdecroiss(void const *a, void const *b);
static int      cmpcroiss(void const *a, void const *b);
char            **sort_fiches(char **tab);
char            **load_fiche();
void            echo_to_fichier(char **tab);
int             add_fiche(char** tab);
char            **del_fiche(char **tab);
int             cpt_fiches(char **tab);

#endif // MY_COLLECTION_H_INCLUDED
