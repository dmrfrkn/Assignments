#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BOYUT 101
#define HEDEF_SKOR 100
#define MAX_ATIS 9

typedef struct {
    int deger;
    int atis;
} KuyrukElemani;

typedef struct {
    KuyrukElemani *veri;
    int bas;
    int son;
} Kuyruk;

typedef struct {
    int deger;
} HeapElemani;

typedef struct {
    HeapElemani **kayitlar;
} Heap;

void kuyrukOlustur(Kuyruk *k) {
    k->veri = (KuyrukElemani *)malloc(MAX_BOYUT * sizeof(KuyrukElemani));
    k->bas = 0;
    k->son = -1;
}

void kuyrugaEkle(Kuyruk *k, int deger, int atis) {
    k->son++;
    k->veri[k->son].deger = deger;
    k->veri[k->son].atis = atis;
}

KuyrukElemani kuyruktanCikar(Kuyruk *k) {
    return k->veri[k->bas++];
}

int kuyrukBosmu(Kuyruk *k) {
    return k->bas > k->son;
}

void kuyrukTemizle(Kuyruk *k) {
    free(k->veri);
}

void heapOlustur(Heap *h) {
    h->kayitlar = (HeapElemani **)malloc(MAX_BOYUT * sizeof(HeapElemani *));
    for (int i = 0; i < MAX_BOYUT; i++) {
        h->kayitlar[i] = NULL;
    }
}

void heapEkle(Heap *h, int deger) {
    int indeks = deger;
    while (h->kayitlar[indeks] != NULL) {
        indeks = (indeks + 1) % MAX_BOYUT;
    }
    h->kayitlar[indeks] = (HeapElemani *)malloc(sizeof(HeapElemani));
    h->kayitlar[indeks]->deger = deger;
}

int heapVarMi(Heap *h, int deger) {
    int indeks = deger;
    while (h->kayitlar[indeks] != NULL) {
        if (h->kayitlar[indeks]->deger == deger) {
            return 1;
        }
        indeks = (indeks + 1) % MAX_BOYUT;
    }
    return 0;
}

void hedefTahtasiOyunu() {
    Kuyruk k;
    Heap h;
    int olasiSkorlar[] = {11, 21, 27, 33, 36};
    int olasiSkorSayisi = sizeof(olasiSkorlar) / sizeof(olasiSkorlar[0]);
    int toplamSkor = 0;

    kuyrukOlustur(&k);
    heapOlustur(&h);

    printf("Hedef tahtasi oyununa hos geldiniz!\n");

    srand(time(NULL)); 

    for (int i = 1; i <= MAX_ATIS; i++) {
        int skor = olasiSkorlar[rand() % olasiSkorSayisi];

        if (toplamSkor + skor > HEDEF_SKOR) {
            printf("Oyunu kaybettiniz, sonraki atislarla %d skoruna ulasamazsiniz.\n", HEDEF_SKOR);
            kuyrukTemizle(&k);
            return;
        }

        printf("Vurulan puan ({11, 21, 27, 33, 36}): %d\n", skor);

        toplamSkor += skor;
        printf("Toplam skor: %d\n", toplamSkor);

        if (toplamSkor == HEDEF_SKOR) {
            printf("Tebrikler! Oyunu kazandiniz!\n");
            kuyrukTemizle(&k);
            return;
        }

        if (!heapVarMi(&h, skor)) {
            heapEkle(&h, skor);
        }
    }

    printf("Maksimum atis sayisina ulasildi. Oyunu kazanamadiniz.\n");
    kuyrukTemizle(&k);
}

int main() {
    hedefTahtasiOyunu();
    return 0;
}
