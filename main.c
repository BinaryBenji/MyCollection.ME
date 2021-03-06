#include "my_collection.h"

int     ft_strlen(char *str) /// Compter le nb de caracteres par string
{
    int i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

char    *ft_strclr(char *str) /// Effacer une string en remplacant chaque caracteres par \0
{
    int i = 0;
    while(str[i])
    {
        str[i] = '\0';
        i++;
    }
    return (str);
}

static int     cmpdecroiss(void const *a, void const *b) /// Tri d�croissant
{
    char const *const *pa = a;
    char const *const *pb = b;
    return (-strcmp(*pa, *pb));
}

static int     cmpcroiss(void const *a, void const *b) /// Tri croissant
{
    char const *const *pa = a;
    char const *const *pb = b;
    return strcmp(*pa, *pb);
}

char    **sort_fiches(char **tab) /// Choix du tri avec qsort (tri a bulle)
{
    int choix;
    int len = cpt_fiches(tab);
    printf("\n 1 : Tri croissant \n");
    printf(" 2 : Tri decroissant \n\n Votre choix :\n\n >> ");
    scanf("%d", &choix);
    printf("\n");
    if (choix == 1)
    {
        qsort (tab, len, sizeof *tab, cmpcroiss);
    }
    else if (choix == 2)
    {
        qsort (tab, len, sizeof *tab, cmpdecroiss);
    }
    else
        printf("\n x Saisie invalide\n");
	return(tab);
}

char    **load_fiche() /// Transformer le fichier en tableau de string
{
    char **tab;
    int tmp;
    char ligne[100];
    int i = 0;
    int cpt_ln = 0;
    int prog = 0;
    int j = 0;
    int k = 0;
    FILE *fichier = NULL; // Pointeur sur struct dans stdio
    int tour = 0;
    fichier = fopen("fiches.txt", "r");
    if (fichier != NULL) // Si le fichier existe
    {
        while (i != EOF)
        {
            i = fgetc(fichier); // On lit un caractere
            if (i == '\n')
                cpt_ln++; /// Compteur du nombre de lignes
        }
    }
    else // Si le fichier existe pas
    {
            printf("Ficher non existant");
            return (NULL);
    }
    if(!(tab = (char **)malloc(cpt_ln * sizeof(char *))))
        return NULL;
    rewind(fichier); /// Remettre le curseur a zero
    while(tour < cpt_ln) // Tant que l'on a pas lu toutes les fiches
    {
        while(1) /// Copie une ligne dans "ligne"
        {
            tmp = fgetc(fichier);
            if (tmp == '\n')
                break;
            if ((tmp <= 57 && tmp >= 48) //Chiffres
                || (tmp >= 65 && tmp <= 90) // Majuscules
                || (tmp <= 122 && tmp >= 97) // Minuscules
                ||  tmp == 45) // tiret
            {
                 ligne[prog] = ((char)tmp);
            }
            else
                break;
            prog++;
        }
        ligne[prog] = '\0';
        if (!(tab[j] = (char*)malloc(ft_strlen(ligne) + 1 * sizeof(char))))
            return (NULL);
        tab[j + 1] = NULL;
        while(ligne[k]) /// Copie la ligne de "ligne" dans le tableau
        {
            tab[j][k] = ligne[k];
            k++;
        }
        tab[j][k] = '\0';
        if(fgetc(fichier) == EOF) // si on est a la fin du fichier
        {
            fclose(fichier);
            return (tab);
        }
        fseek(fichier, -1, SEEK_CUR); // retour au caractere precedent
        tour++;
        j++;
        k = 0;
        prog = 0;
    }
    //free(ligne);
    fclose(fichier);
    return (tab);
}

void    disp_all_fiches(char **tab) /// Afficher toutes les fiches a partir du tableau de string
{
    int i = 0;
    while(tab[i] != NULL)
    {
        printf(" > Fiche numero %d : %s \n", i, tab[i]);
        i++;
    }
}

void    echo_to_fichier(char **tab) /// Ecrire dans le fichier le tableau de string
{
    int i = 0;
    FILE *fichier = NULL;
    fichier = fopen("fiches.txt", "w+");
    while(tab[i] != NULL)
    {
        fputs(tab[i], fichier);
        fputc('\n', fichier);
        i++;
    }
    fclose(fichier);
}

int   add_fiche(char** tab) /// Ajouter une fiche. On utilise une structure, dont on prend les composants que l'on concat�ne dans une string
{
    struct fiche *tmp; /// Structure temporaire
    char film[100]; /// Variable temporaire de film
    int annee; /// Annee
    char nom_real[100]; /// Nom real
    char prenom_real[100]; /// Prenom real
    int nb; /// Nb de caracteres
    int j = 0;
    int prog = 0;
    int k = 0;
    char str[100];
    if(!(tmp = (struct fiche *)malloc(sizeof(struct fiche))))
    {
        printf("Allocation impossible");
        return (-1);
    }
    printf("\n Veuillez entrez le nom du film : "); /// FILM
    scanf("%s", film);
    nb = ft_strlen(film);
    if(!(tmp->nom_film = (char *) malloc((nb + 1)*sizeof(char))))
    {
        tmp->nom_film = NULL;
        printf("Allocation impossible");
        return (-1);
    }
    strcpy(tmp->nom_film, film);
    printf(" Veuillez entrer l'annee du film : "); /// ANNEE
    scanf("%d", &annee);
    if(!(tmp->annee = (int)malloc(sizeof(int))))
    {
        tmp->annee = 0;
        printf("Allocation impossible");
        return (-1);
    }
    tmp->annee = annee;
    printf(" Veuillez entrer le nom du realisateur : "); /// NOM REALISATEUR
    scanf("%s", nom_real);
    nb = ft_strlen(nom_real);
    if(!(tmp->realisateur[0] = (char *) malloc((nb + 1)*sizeof(char))))
    {
        tmp->realisateur[0] = NULL;
        printf("Allocation impossible");
        return (-1);
    }
    strcpy(tmp->realisateur[0], nom_real);
    printf(" Veuillez Entre le prenom du realisateur : "); /// PRENOM REALISATEUR
    scanf("%s", prenom_real);
    printf("\n");
    nb = ft_strlen(prenom_real);
    if(!(tmp->realisateur[1] = (char *) malloc((nb + 1)*sizeof(char))))
    {
        tmp->realisateur[1] = NULL;
        printf("Allocation impossible");
        return (-1);
    }
    strcpy(tmp->realisateur[1], prenom_real);
    while (tab[j] != NULL)
        j++;
    itoa(tmp->annee, str, 10);
    if (!(tab[j] = (char*)malloc(ft_strlen(tmp->nom_film) + ft_strlen(str) + ft_strlen(tmp->realisateur[0]) + ft_strlen(tmp->realisateur[1])) + 1 * sizeof(char)))
            return (0);
    while (tmp->nom_film[prog])
    {
        tab[j][k] = tmp->nom_film[prog];
        k++;
        prog++;
    }
    tab[j][k] = '-';
    k++;
    prog = 0;
    while (str[prog])
    {
        tab[j][k] = str[prog];
        k++;
        prog++;
    }
    tab[j][k] = '-';
    k++;
    prog = 0;
    while (tmp->realisateur[0][prog])
    {
        tab[j][k] = tmp->realisateur[0][prog];
        k++;
        prog++;
    }
    tab[j][k] = '-';
    k++;
    prog = 0;
    while (tmp->realisateur[1][prog])
    {
        tab[j][k] = tmp->realisateur[1][prog];
        k++;
        prog++;
    }
    tab[j][k] = '\0';
    tab[j+1] = NULL;
    free(tmp);
    echo_to_fichier(tab);
    return (1);
}

char **del_fiche(char **tab) /// Supprimer une fiches en effacant une fiche + d�calage des autres fiches
{
    int choix;
    int len = cpt_fiches(tab);
    printf("\n Voici vos fiches : \n\n");
    disp_all_fiches(tab);
    printf("\n Veuillez entrer le numero de la fiche que vous voulez supprimer : \n\n >> ");
    scanf("%d", &choix);
    if ((choix >= cpt_fiches(tab)) || (choix < 0))
    {
        printf("Fiche inexistante");
        return (NULL);
    }
    else
    {
        ft_strclr(tab[choix]);
        while(choix < len)
        {
            tab[choix] = tab[choix + 1];
            choix++;
        }
    }
    return(tab);
}

int cpt_fiches(char **tab) /// Permet de compter le nb de fiches, indispensable pour l'allocation dynamique
{
    int i = 0;
    while(tab[i] != NULL)
        i++;
    return(i);
}

int similarity(char *s1, char *s2) /// Voir si deux chaines sont similaires. Renvoie 1 si true, 0 si false
{
    int i = 0;
    while(s1[i] && s2[i])
    {
        if (s1[i] == s2[i])
            i++;
        else
            return(0);
    }
    return(1);
}

void search_fiche(char **tab) /// Recherche d'une fiche
{
    int i = 0;
    int j = 0;
    char entree[100]; /// String que nous cherchons
    char *tosearch; /// String que nous comparons a entree
    int tableau[100]; /// Tableau contenant les id des fiches a afficher
    int l = 0; /// Compte le nombre de fiches correspondant a la recherche

    printf("\n Veuillez entrer le nom du film que vous recherchez :\n\n >> ");
    scanf("%s", entree);
    while(tab[i] != NULL)
    {
        while(tab[i][j] != '-')
            j++;
        if(!(tosearch = (char *)malloc((j + 1) * sizeof(char))))
            printf("Allocation impossible");
        j = 0;
        while (tab[i][j] != '-')
        {
            tosearch[j] = tab[i][j];
            j++;
        }
        tosearch[j] = '\0';
        if (similarity(entree, tosearch)) /// Si les deux string sont similaires, on enregistre sa position dans tableau
        {
            tableau[l] = i;
            l++;
        }
        i++;
    }
    if(!l)
       printf("Aucune entree trouvee");
    else
        disp_all_fiches_from_search(tableau, tab, l);
}

void disp_all_fiches_from_search(int *tableau, char **tab, int l) /// Afficher les fiches correspondant a la recherche
{
    int i = 0;
    int tmp = 0;

    while(l)
    {
        tmp = tableau[i];
        printf("\nFiche correspondant a la recherche : %s \n", tab[tmp]);
        l--;
        i++;
    }
}

int main()
{
    int choix; /// Choix dans le menu
    int ok;
    int nbfiches;
    char **tab; /// Tableau des fiches charg�es
    printf(" Bonjour !\n\n Que voulez-vous faire ? \n \n 1 : Ajouter une fiche \n 2 : Afficher toutes les fiches \n 3 : Trier les fiches \n 4 : Supprimer une fiche \n 5 : Rechercher une fiche \n 6 : Quitter \n");
    tab = load_fiche();
    nbfiches = cpt_fiches(tab);
    printf("\n >> Vous avez %d fiches. Vous pouvez encore ajouter %d fiches.", nbfiches, 100-nbfiches);
    printf("\n\n >> Voici les fiches actuelles : \n\n");
    disp_all_fiches(tab);
    if (nbfiches < 100) /// On verifie que l'utilisateur a pas entre plus de 100 fiches
    {
        do
        {
            printf("\n Veuillez entrer votre choix : \n\n >> ");
            scanf("%d", &choix);
            switch(choix)
            {
                case 1 : /// Ajouter une fiche
                if ((ok = add_fiche(tab)) == -1)
                    printf(" Ajout impossible");
                disp_all_fiches(tab);
                break;

                case 2 : /// Afficher toutes les fiches
                printf("\n\n Voici les fiches : \n\n");
                disp_all_fiches(tab);
                break;

                case 3 : /// Trier les fiches par ordre decroissant ou croissant
                tab = sort_fiches(tab);
                disp_all_fiches(tab);
                echo_to_fichier(tab);
                printf("\n Fiches Triees\n");
                break;

                case 4: /// Supprimer une fiche
                del_fiche(tab);
                echo_to_fichier(tab);
                break;

                case 5 : /// Chercher une fiche sur le champ nom_film
                search_fiche(tab);
                break;

                case 6 : /// Quitter
                printf("\n Au revoir, A bientot! \n");
                return(1);


                default : /// invalide
                printf("\n Saisie invalide.");
                break;
            }
        } while(choix != 6);
    }
    else /// Cas ou il y a trop de fiches.
    {
        printf("\n x nombre maximal de fiche atteint. Veuillez en supprimer\n\n");
        del_fiche(tab);
        echo_to_fichier(tab);
    }
    return (1);
}
