#include <stdio.h>
#include <stdlib.h>

// Eleman yapısını tanımlama
typedef struct Eleman {
   int katsayi;
   int us;
   struct Eleman* ileri;
} Eleman;

// Yeni bir eleman oluşturma
Eleman* elemanOlustur(int katsayi, int us) {
    Eleman* yeniEleman = (Eleman*)malloc(sizeof(Eleman));
    yeniEleman->katsayi = katsayi;
    yeniEleman->us = us;
    yeniEleman->ileri = NULL;
    return yeniEleman;
}

// Yeni elemanı sonuca ekleme
Eleman* elemanEkle(Eleman* sonuc, int katsayi, int us) {
    Eleman* yeniEleman = elemanOlustur(katsayi, us);
    if (sonuc == NULL) {
        sonuc = yeniEleman;
    } else {
        Eleman* tmp = sonuc;
        while (tmp->ileri != NULL) {
            tmp = tmp->ileri;
        }
        tmp->ileri = yeniEleman;
    }
    return sonuc;
}

// Polinomları temsil eden bağlı listelerin çarpımını yapma
Eleman* polinomCarp(Eleman* polinom1, Eleman* polinom2) {
    Eleman* sonuc = NULL;
    Eleman* tmp1 = polinom1;
    
    while (tmp1 != NULL) {
        Eleman* tmp2 = polinom2;
        while (tmp2 != NULL) {
            int katsayi = tmp1->katsayi * tmp2->katsayi;
            int us = tmp1->us + tmp2->us;
            // Sonuç polinomuna eleman ekleme
            sonuc = elemanEkle(sonuc, katsayi, us);
            tmp2 = tmp2->ileri;
        }
        tmp1 = tmp1->ileri;
    }
    
    return sonuc;
}

// Bağlı listeyi yazdırma
void listeYazdir(Eleman* liste) {
    Eleman* tmp = liste;
    while (tmp != NULL) {
        printf("%dx^%d ", tmp->katsayi, tmp->us);
        tmp = tmp->ileri;
        if (tmp != NULL) {
            printf("+ ");
        }
    }
    printf("\n");
}

// Bağlı listeyi temizleme
void listeTemizle(Eleman* liste) {
    Eleman* tmp;
    while (liste != NULL) {
        tmp = liste;
        liste = liste->ileri;
        free(tmp);
    }
}

int main() {
    // İlk polinom: ( x^2 − 4x + 7 )
    Eleman* polinom1 = elemanOlustur(1, 2);
    polinom1->ileri = elemanOlustur(-4, 1);
    polinom1->ileri->ileri = elemanOlustur(7, 0);
    
    // İkinci polinom: ( x^2 − 2 )
    Eleman* polinom2 = elemanOlustur(1, 2);
    polinom2->ileri = elemanOlustur(-2, 0);
    
    printf("Polinom 1: ");
    listeYazdir(polinom1);
    printf("Polinom 2: ");
    listeYazdir(polinom2);
    
    Eleman* carpimSonucu = polinomCarp(polinom1, polinom2);
    printf("Çarpım Sonucu: ");
    listeYazdir(carpimSonucu);
    
    // Belleği temizleme
    listeTemizle(polinom1);
    listeTemizle(polinom2);
    listeTemizle(carpimSonucu);
    
    return 0;
}
