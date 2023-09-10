/************* Programme pour résoudre l'équation de Laplace par la méthode des différences finies *************/

#include <stdio.h>

int main()
{
    int i, j, k, m, n, x, y;
    float a[20][20], at[20][20], l, r, t, b;
    FILE *fp;
    
    // Ouvrir un fichier pour stocker les résultats
    fp = fopen("c:\\laplace.dat", "w");
    printf("\t Programme pour résoudre l'équation de Laplace par la méthode des différences finies\n");
    
    // Entrer les conditions aux limites
    printf("\tEntrez la valeur sur le côté gauche : ");
    scanf("%f", &l);
    printf("\tEntrez la valeur sur le côté droit : ");
    scanf("%f", &r);
    printf("\tEntrez la valeur en haut : ");
    scanf("%f", &t);
    printf("\tEntrez la valeur en bas : ");
    scanf("%f", &b);
    
    // Entrer les dimensions et le nombre d'itérations
    printf("\tEntrez la longueur dans la direction x : ");
    scanf("%d", &x);
    printf("\tEntrez le nombre d'étapes dans la direction x : ");
    scanf("%d", &m);
    printf("\tEntrez la longueur dans la direction y : ");
    scanf("%d", &y);
    printf("\tEntrez le nombre d'étapes dans la direction y : ");
    scanf("%d", &n);
    
    // Incrémenter m et n (nombre de points du maillage est un de plus que le nombre d'étapes)
    m++;
    n++;
    
    // Initialisation des tableaux à zéro (maillage)
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            a[i][j] = 0.0;
            at[i][j] = 0.0;
        }
    }
    
    // Assigner les conditions aux limites
    for (i = 0; i < m; i++) {
        a[i][0] = b;
        a[i][n-1] = t;
    }
    
    for (i = 0; i < n; i++) {
        a[0][i] = l;
        a[m-1][i] = r;
    }
    
    // Calcul par la méthode de Gauss-Seidel
    for (k = 0; k < 100; k++) {
        for (i = 1; i < m - 1; i++) {
            for (j = 1; j < n - 1; j++) {
                at[i][j] = (a[i-1][j] + a[i+1][j] + a[i][j-1] + a[i][j+1]) / 4;
            }
        }
        
        // Échanger les tableaux a et at en utilisant un tableau temporaire
        for (i = 1; i < m - 1; i++) {
            for (j = 1; j < n - 1; j++) {
                float temp = a[i][j];
                a[i][j] = at[i][j];
                at[i][j] = temp;
            }
        }
    }
    
    // Écrire les résultats dans le fichier
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            fprintf(fp, "%.2f\t", a[i][j]);
        }
        fprintf(fp, "\n");
    }
    
    // Fermer le fichier
    fclose(fp);
    
    // Afficher un message de confirmation
    printf("\nDonnées enregistrées. Appuyez sur n'importe quelle touche pour quitter...");
    
    return 0;
}
//gcc -o laplace exo2.c -fopenmp
//./laplace
