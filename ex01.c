#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <sys/wait.h>
#include <sys/types.h> 
#include <unistd.h> 
#include <time.h>

// Fonction exécutée par le thread
void *thread_seqcarrefunction(int *var[]) 
{
    int i;
    int resultat[10];
    int val;

    // Boucle pour calculer les carrés des nombres
    for (i = 0; i < 10; i++) {
        val = var[i];
        resultat[i] = val * val;
        
        // Affichage des informations sur le thread
        printf("Je suis le thread de tid :%ld, mon pid est :%d\n", pthread_self(), getpid()) ; 
        printf("le carré de %d est %d\n", val, resultat[i]); 
    }

    // Terminer le thread en renvoyant le tableau résultant
    pthread_exit((void*)resultat); 
}

int main(){	
    int i;
    int resultat[10];
    pthread_t tid;

    // Tableau d'entiers à traiter
    int tab[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    float temps;
    clock_t t1, t2;
    t1 = clock();

    // Création du thread pour exécuter la fonction thread_seqcarrefunction
    pthread_create(&tid, NULL, thread_seqcarrefunction, &tab);

    // Attente de la fin du thread et récupération du résultat
    pthread_join(tid, (void **)&resultat);
    t2 = clock();

    // Calcul et affichage du temps d'exécution
    temps = (float)(t2 - t1) / CLOCKS_PER_SEC;
    printf("temps = %f\n", temps);

    return 0; 
}
