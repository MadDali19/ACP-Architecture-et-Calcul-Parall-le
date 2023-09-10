#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <sys/wait.h>
#include <sys/types.h> 
#include <unistd.h> 
#include <math.h>
#define nb 18446

// Fonction exécutée par chaque thread pour rechercher les diviseurs
void *thread_carrefunction(void *i) 
{
    int j, k;
    j = *(int *)i;
    int debut, fin;
    register unsigned long long sqrt_nb; 
    sqrt_nb = sqrt(nb);
    debut = j * ((sqrt_nb) / 10);
    fin = (j + 1) * ((sqrt_nb) / 10);
    
    // Recherche des diviseurs dans la plage attribuée au thread
    for (k = debut; k < fin; k++) {
        if ((nb % k) == 0) {
            printf("%d\n", k);
            pthread_exit((void *)1); // Sortir du thread si un diviseur est trouvé
        }
    }
    pthread_exit((void *)0); // Terminer le thread sans avoir trouvé de diviseurs
}

int main(){	
    int i;
    int r;
    pthread_t tid[20];

    int tab[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (i = 0; i < 10; i++) {
        pthread_create(&tid[i], NULL, thread_carrefunction, &tab[i]);
        pthread_join(tid[i], (void **)&r);
        
        // Si un thread a trouvé un diviseur, le programme s'arrête
        if (r == 1) {
            exit(0);
        }
    }

    return 0; 
}
//execution: gcc -o diviseurs exo2.c -pthread -lm
//./diviseurs
