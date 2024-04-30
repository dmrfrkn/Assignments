#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SKOR 99
#define HEDEF_BOYUTU 10

// Hedef tahtası yapısı
typedef struct {
    int skorlar[HEDEF_BOYUTU];
} Hedef;

// Hedef tahtasını başlat
void hedefiBaslat(Hedef *hedef) {
    for (int i = 0; i < HEDEF_BOYUTU; i++) {
        hedef->skorlar[i] = i + 1;
    }
}

// Hedef tahtasını ekrana yazdır
void hedefiGoster(Hedef hedef) {
    printf("Hedef Tahtasi:\n");
    for (int i = 0; i < HEDEF_BOYUTU; i++) {
        printf("%d ", hedef.skorlar[i]);
    }
    printf("\n\n");
}

// Atış sonucunu kontrol et ve bilgilendir
void atisSonucunuKontrolEt(int atis, int toplamSkor) {
    if (toplamSkor == MAX_SKOR) {
        printf("Tebrikler! 99 puanli hedefe ulastiniz.\n");
    } else if (toplamSkor > MAX_SKOR) {
        printf("Toplam skor 100'u gecti, oyunu kaybettiniz.\n");
    } else {
        printf("Toplam skor: %d\n", toplamSkor);
    }
}

int main() {
    srand(time(NULL)); // Rastgelelik için zamanı kullan
    Hedef hedef;
    hedefiBaslat(&hedef);
    hedefiGoster(hedef);
    int toplamSkor = 0;
    int atisSayisi = 0;
    while (toplamSkor < MAX_SKOR) {
        int atis = rand() % HEDEF_BOYUTU; // Rastgele bir hedef seç
        int atisSkoru = hedef.skorlar[atis];
        toplamSkor += atisSkoru;
        atisSayisi++;
        printf("Atis %d: %d puan\n", atisSayisi, atisSkoru);
        atisSonucunuKontrolEt(atisSkoru, toplamSkor);
        
        if (toplamSkor >= MAX_SKOR || toplamSkor > 100) {
            break;
        }
    }

    return 0;
}
