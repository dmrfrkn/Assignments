#include <stdio.h>
#include <stdlib.h>
struct Dugum {
    int veri;
    struct Dugum* sonraki;
};

struct Dugum* yeniDugum(int veri) {
    struct Dugum* gecici = (struct Dugum*)malloc(sizeof(struct Dugum));
    gecici->veri = veri;
    gecici->sonraki = NULL;
    return gecici;
}

void basaEkle(struct Dugum** bas, int veri) {
    struct Dugum* yeni = yeniDugum(veri);
    yeni->sonraki = *bas;
    *bas = yeni;
}

void sonaEkle(struct Dugum** bas, int veri) {
    struct Dugum* yeni = yeniDugum(veri);
    if (*bas == NULL) {
        *bas = yeni;
        return;
    }
    struct Dugum* gecici = *bas;
    while (gecici->sonraki != NULL) {
        gecici = gecici->sonraki;
    }
    gecici->sonraki = yeni;
}

void listeYazdir(struct Dugum* bas) {
    struct Dugum* suanki = bas;
    while (suanki != NULL) {
        printf("%d ", suanki->veri);
        suanki = suanki->sonraki;
    }
    printf("\n");
}

void tersYazdir(struct Dugum* bas) {
    if (bas == NULL) {
        printf("\n");
        return;
    }
    tersYazdir(bas->sonraki);
    printf("%d ", bas->veri);
}

int elemanAra(struct Dugum* bas, int anahtar) {
    int index = 0;
    struct Dugum* suanki = bas;
    while (suanki != NULL) {
        if (suanki->veri == anahtar) {
            return index;
        }
        index++;
        suanki = suanki->sonraki;
    }
    return -1;
}

int main() {
    int ogrenciNo = 32290051;

    struct Dugum* basdan = NULL;
    struct Dugum* sondan = NULL;

    while (ogrenciNo > 0) {
        int rakam = ogrenciNo % 10;
        basaEkle(&basdan, rakam);
        ogrenciNo /= 10;
    }

    ogrenciNo = 32290051; 

    while (ogrenciNo > 0) {
        int rakam = ogrenciNo % 10;
        sonaEkle(&sondan, rakam);
        ogrenciNo /= 10;
    }

    printf("Baştan Liste: ");
    listeYazdir(basdan);

    printf("Sondan Liste: ");
    tersYazdir(sondan);

    printf("\n");

    struct Dugum* birlestirilmis = basdan;
    while (basdan->sonraki != NULL) {
        basdan = basdan->sonraki;
    }
    basdan->sonraki = sondan;

    printf("Birleştirilmiş Liste: ");
    listeYazdir(birlestirilmis);

    int aranan = 9;
    int index = elemanAra(birlestirilmis, aranan);
    if (index != -1) {
        printf("%d bulundu, [%d] index.\n", aranan, index);
    } else {
        printf("%d bulunamadı.\n", aranan);
    }

    return 0;
}
