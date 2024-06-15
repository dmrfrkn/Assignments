#include <stdio.h>

int main() {
    int n; // Kare matrisin boyutunu kullanıcıdan alalım
    printf("Kare matrisin boyutunu girin: ");
    scanf("%d", &n);

    int matris[n][n]; // Kare matrisi tanımlayalım

    // Matrisi dolduralım (örneğin, i + j değeri ile)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matris[i][j] = i + j;
        }
    }

    // Matrisi yazdıralım
    printf("Kare Matris:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matris[i][j]);
        }
        printf("\n");
    }

    return 0;
}
