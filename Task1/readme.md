## Description de l'objéctif de l'algorithme
|4 	|8 	|7 	|9 	|1 	|5 	|4 	|6|
## Comment fonctionne l'algorithme
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
### Expérimentation (test unitaires?)
## Conclusion


