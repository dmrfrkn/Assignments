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
    KuyrukElemani veri[MAX_BOYUT];
    int bas;
    int son;
} Kuyruk;

typedef struct {
    int deger;
} KarmaTabloElemani;

typedef struct {
    KarmaTabloElemani *kayitlar[MAX_BOYUT];
} KarmaTablo;

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

void karmaTabloyuBas(KarmaTablo *kt) {
    printf("Karma Tablosu:\n");
    for (int i = 0; i < MAX_BOYUT; i++) {
        if (kt->kayitlar[i] != NULL) {
            printf("[%d] --> %d\n", i, kt->kayitlar[i]->deger);
        }
    }
}

void karmaTabloOlustur(KarmaTablo *kt) {
    for (int i = 0; i < MAX_BOYUT; i++) {
        kt->kayitlar[i] = NULL;
    }
}

int hashle(int deger) {
    return deger % MAX_BOYUT;
}

void karmaTabloyaEkle(KarmaTablo *kt, int deger) {
    int indeks = hashle(deger);
    while (kt->kayitlar[indeks] != NULL) {
        indeks = (indeks + 1) % MAX_BOYUT;
    }
    kt->kayitlar[indeks] = (KarmaTabloElemani *)malloc(sizeof(KarmaTabloElemani));
    kt->kayitlar[indeks]->deger = deger;
}

int karmaTablodaVarMi(KarmaTablo *kt, int deger) {
    int indeks = hashle(deger);
    while (kt->kayitlar[indeks] != NULL) {
        if (kt->kayitlar[indeks]->deger == deger) {
            return 1;
        }
        indeks = (indeks + 1) % MAX_BOYUT;
    }
    return 0;
}

void hedefTahtasiOyunu() {
    Kuyruk k;
    KarmaTablo kt;
    int olasiSkorlar[] = {11, 21, 27, 33, 36};
    int olasiSkorSayisi = sizeof(olasiSkorlar) / sizeof(olasiSkorlar[0]);
    int toplamSkor = 0;

    k.bas = 0;
    k.son = -1;
    karmaTabloOlustur(&kt);

    printf("Hedef tahtasi oyununa hos geldiniz!\n");

    srand(time(NULL)); // Başlangıç noktasını belirle

    for (int i = 1; i <= MAX_ATIS; i++) {
        int skor = olasiSkorlar[rand() % olasiSkorSayisi]; // Rastgele bir skor seç

        if (toplamSkor + skor > HEDEF_SKOR) {
            printf("Oyunu kaybettiniz, sonraki atislarla %d skoruna ulasamazsiniz.\n", HEDEF_SKOR);
            return;
        }

        printf("Vurulan puan ({11, 21, 27, 33, 36}): %d\n", skor);

        toplamSkor += skor;
        printf("Toplam skor: %d\n", toplamSkor);

        if (toplamSkor == HEDEF_SKOR) {
            printf("Tebrikler! Oyunu kazandiniz!\n");
            karmaTabloyuBas(&kt);
            return;
        }

        if (!karmaTablodaVarMi(&kt, skor)) {
            karmaTabloyaEkle(&kt, skor);
        }

        karmaTabloyuBas(&kt);
    }

    printf("Maksimum atis sayisina ulasildi. Oyunu kazanamadiniz.\n");
    karmaTabloyuBas(&kt);
}

int main() {
    hedefTahtasiOyunu();
    return 0;
}
