#include <stdio.h>

int main() {

    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int allocation[n][m];
    int max[n][m];
    int need[n][m];
    int available[m];

    printf("\nEnter Allocation Matrix:\n");

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("\nEnter Max Matrix:\n");

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");

    for(int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    printf("\nNeed Matrix:\n");

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    int finish[n];
    int safeSequence[n];

    for(int i = 0; i < n; i++) {
        finish[i] = 0;
    }

    int count = 0;

    while(count < n) {

        int found = 0;

        for(int i = 0; i < n; i++) {

            if(finish[i] == 0) {

                int possible = 1;

                for(int j = 0; j < m; j++) {

                    if(need[i][j] > available[j]) {
                        possible = 0;
                        break;
                    }
                }

                if(possible == 1) {

                    for(int j = 0; j < m; j++) {
                        available[j] += allocation[i][j];
                    }

                    safeSequence[count] = i;
                    count++;

                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0) {
            break;
        }
    }

    if(count == n) {

        printf("\nSystem is in SAFE STATE\n");

        printf("Safe Sequence: ");

        for(int i = 0; i < n; i++) {
            printf("P%d ", safeSequence[i]);
        }

        printf("\n");

    } else {

        printf("\nSystem is in UNSAFE STATE\n");
    }

    return 0;
}
