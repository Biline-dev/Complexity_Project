## Description de l'objéctif de l'algorithme
<<<<<<< HEAD
Le but de l'algorithme est de traiter la somme des éléments entre deux tableaux
>Exemple
**T1:** 
|4 	|8 	|7 	|9 	|1 	|5 	|4 	|6|
|---|---|---|---|---|---|---|-|

**T2:** 
|7 	|6 	|0 	|2 	|1 	|3 	|7 	|4|
|---|---|---|---|---|---|---|-|

**T3 à constituer:**
|11 |14 |12 |11 |2 	|8 	|11 |10|
|---|---|---|---|---|---|---|--|

=======
|4 	|8 	|7 	|9 	|1 	|5 	|4 	|6|
|---|---|---|---|---|---|---|-|
>>>>>>> 6474d4b2940c5751e26c81209520ecd581847f2d
## Comment fonctionne l'algorithme

J'ai crée une fonction `Somme` qui accepte en entrée 2 tableaux dynamique de type réel ainsi que la taille de chacun, et en sortie on aura un tableau contenant la somme des éléments des deux tableaux mis en entrée.

- On verifie la taille de chaque tableau, si les deux sont inférieur ou égale à 0, la fonction retourne null et le résultat au test sera null.
- Si la taille d'un des tableaux est null, T3 va contenir les éléments du tableau dont la taille est non null.
- Si les deux tailles sont non nulles et egale on fait un parcours mutuelle des deux tableaux.
-sinon si la taille d'un des tableau est inférieur à l'autre, on parcours les deux tableau mutuellement jusqu'à la plus fin du tableau avec la plus petite taille en sommant les éléments, à partir de cette taille on entre dans une autre boucle en séquentiel pour finir le tableau avec la plus grande taille.
- En testant, nous aurons besoin de d'autres boucles pour afficher les différent éléments de T3.

### pseudo code

```
Procédure Somme_tebleau(E/ T1[], T2[] : tableau de réel, size_T1, size_T2: entiers, S/T3[]: tableau de réel)
debut
    // Verifier si la taille des tableaux données est nulle ou inférieur à 0
    Var i: entier;

    Si size_T2<=0 et size_T1<=0 Alors
       retourner null;
    Fsi;

    Si size_T1==0 et size_T2=/=0 Alors
        pour i<--0 à size_T2-1 faire
          T3[i] <-- T2[i];
          i<--1+i;
        Fait;
        retourner T3;
    Fsi;

    Si size_T1=/=0 et size_T2==0 Alors
        pour i<--0 à size_T1-1 faire
          T3[i] <-- T1[i];
          i<--1+i;
        Fait;
        retourner T3;
    Fsi;

    // Si les tableaux sont non vides
    Si size_T2==size_T1 Alors
        pour i<--0 à size_T2-1 faire
            T3[i] <-- T1[i] + T2[i];
            i<--1+i;
        Fait;
        retourner T3;
    Sinon Si size_T1>size_T2 Alors
            pour i<--0 à size_T2-1 faire
                T3[i] <-- T1[i] + T2[i];
                i<--1+i;
            Fait;
            pour i<--size_T2 à size_T1-1 faire
                T3[i] <-- T1[i];
                i<--1+i;
            Fait;
            retourner T3;
          Sinon 
            pour i<--0 à size_T1-1 faire
                T3[i] <-- T1[i] + T2[i];
                i<--1+i;
            Fait;
            pour i<--size_T1 à size_T2-1 faire
                T3[i] <--T2[i];
                i<--1+i;
            Fait;
            retourner T3;
          Fsi;
    Fsi;
fin

Algorithme Test_Somme_Tableau;
var size_T1, size_T2, i : entiers;
    T1[], T2[], T3[]: tableau de reels;

Début

    // Declaration de la taille des tableaux

    Ecrire(‘Donner un entier pour lequel la taille size_T1>0’) ;
    Répéter Lire(size_T1) ; Jusqu’à size_T1>0 ;

    Ecrire(‘Donner un entier pour lequel la taille size_T2>0’) ;
    Répéter Lire(size_T2) ; Jusqu’à size_T2>0 ;


    // Initialiser T1 ET T2

    pour i<--0 à size_T1-1 faire
        Ecrire(‘Donner une valeur à', T1[i]);
        Lire(size_T1);
        i<--1+i;
    Fait;

    pour i<--0 à size_T2-1 faire
        Ecrire(‘Donner une valeur à', T2[i]);
        Lire(size_T2);
        i<--1+i;
    Fait;

    //Testing
    Ecrire('le resultat est');
    Si T3==NULL
       Ecrire('NULL');
    Sinon Si size_T1>=size_T2 Alors
            Pour i<--0 à size_T1
                Ecrire(T3[i]);
                i<--1+i;
            Fait;
          Sinon
            Pour i<--0 à size_T2
                    Ecrire(T3[i]);
                    i<--1+i;
                Fait;
          Fsi;
    Fsi;

```
## Le calcul détaillé de la complexité théorique temporelle et spatiale

L'algorithme contient 7 boucles imbriqués dans des conditions `if..else`, des boucles en dehors de celle utilisé dans la partie `Test`. La compléxité de l'algorithme va dépendre des éléments mis en entrée.
- Dans un 1er cas, si la taille d'un des tableau est null, il y'aura qu'un seul parcour d'un des tableaux, **m** ou **n **
- Dans un 2eme cas, si la taille d'un des tableau est supérieur ou egale à l'autre, il y'aura 2 parcours , **m** et **n**
   * Si m=n alors le nombre d'intstruction est égale à **2m** ou **2n**
   * Si m>n ou n>m alors le nombre d'intstruction est égale à **m+n**
Donc la complexité de cette algorithme est égale à **o(max(m,n)**)
### Expérimentation (test unitaires?)
## Conclusion


