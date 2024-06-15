#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct Dugum {
    char ad[10];
    int agirlik;
    struct Dugum* sonraki;
} Dugum;

typedef struct Graf {
    char ad[10];
    Dugum* komsular;
    struct Graf* sonraki;
} Graf;

typedef struct KuyrukDugumu {
    char ad[10];
    int maliyet;
    struct KuyrukDugumu* sonraki;
} KuyrukDugumu;

void kenar_ekle(Graf** graf, const char* kaynak, const char* hedef, int agirlik) {
    Graf* g = *graf;
    while (g && strcmp(g->ad, kaynak) != 0) {
        g = g->sonraki;
    }
    if (!g) {
        g = (Graf*)malloc(sizeof(Graf));
        strcpy(g->ad, kaynak);
        g->komsular = NULL;
        g->sonraki = *graf;
        *graf = g;
    }
    Dugum* n = (Dugum*)malloc(sizeof(Dugum));
    strcpy(n->ad, hedef);
    n->agirlik = agirlik;
    n->sonraki = g->komsular;
    g->komsular = n;
}

KuyrukDugumu* kuyruk_dugumu_olustur(const char* ad, int maliyet) {
    KuyrukDugumu* yeni_dugum = (KuyrukDugumu*)malloc(sizeof(KuyrukDugumu));
    strcpy(yeni_dugum->ad, ad);
    yeni_dugum->maliyet = maliyet;
    yeni_dugum->sonraki = NULL;
    return yeni_dugum;
}

void kuyruga_ekle(KuyrukDugumu** bas, KuyrukDugumu** son, const char* ad, int maliyet) {
    KuyrukDugumu* yeni_dugum = kuyruk_dugumu_olustur(ad, maliyet);
    if (!*bas) {
        *bas = *son = yeni_dugum;
    } else {
        KuyrukDugumu* temp = *bas;
        KuyrukDugumu* onceki = NULL;
        while (temp && (temp->maliyet < maliyet || (temp->maliyet == maliyet && strcmp(temp->ad, ad) < 0))) {
            onceki = temp;
            temp = temp->sonraki;
        }
        if (!onceki) {
            yeni_dugum->sonraki = *bas;
            *bas = yeni_dugum;
        } else {
            yeni_dugum->sonraki = onceki->sonraki;
            onceki->sonraki = yeni_dugum;
        }
        if (!yeni_dugum->sonraki) {
            *son = yeni_dugum;
        }
    }
}

KuyrukDugumu* kuyruktan_cikar(KuyrukDugumu** bas) {
    if (!*bas) {
        return NULL;
    }
    KuyrukDugumu* temp = *bas;
    *bas = (*bas)->sonraki;
    temp->sonraki = NULL;
    return temp;
}
 
int bos_mu(KuyrukDugumu* bas) {
    return bas == NULL;
}

void en_kisa_yolu_bul(Graf* graf, const char* baslangic, const char* hedef) {
    KuyrukDugumu* kuyruk_basi = NULL;
    KuyrukDugumu* kuyruk_sonu = NULL;
    Graf* g = graf;

    char ziyaret_edilenler[100][10];
    int ziyaret_edilen_sayisi = 0;

    char oncekiler[100][10];
    int maliyetler[100];
    for (int i = 0; i < 100; ++i) {
        maliyetler[i] = INT_MAX;
    }
    int baslangic_indeksi = -1;

    for (int i = 0; g; ++i) {
        if (strcmp(g->ad, baslangic) == 0) {
            baslangic_indeksi = i;
            maliyetler[i] = 0;
        }
        g = g->sonraki;
    }

    if (baslangic_indeksi == -1) {
        printf("Başlangıç düğümü grafiğin içinde bulunamadı\n");
        return;
    }

    kuyruga_ekle(&kuyruk_basi, &kuyruk_sonu, baslangic, 0);

    while (!bos_mu(kuyruk_basi)) {
        KuyrukDugumu* mevcut = kuyruktan_cikar(&kuyruk_basi);
        int mevcut_maliyet = mevcut->maliyet;
        char* mevcut_ad = mevcut->ad;

        int bulundu = 0;
        for (int i = 0; i < ziyaret_edilen_sayisi; ++i) {
            if (strcmp(ziyaret_edilenler[i], mevcut_ad) == 0) {
                bulundu = 1;
                break;
            }
        }
        if (bulundu) {
            free(mevcut);
            continue;
        }

        strcpy(ziyaret_edilenler[ziyaret_edilen_sayisi++], mevcut_ad);

        if (strcmp(mevcut_ad, hedef) == 0) {
            break;
        }

        Graf* g = graf;
        while (g && strcmp(g->ad, mevcut_ad) != 0) {
            g = g->sonraki;
        }

        if (!g) {
            continue;
        }

        Dugum* n = g->komsular;
        while (n) {
            int yeni_maliyet = mevcut_maliyet + n->agirlik;
            int dugum_indeksi = -1;

            for (int i = 0; i < ziyaret_edilen_sayisi; ++i) {
                if (strcmp(ziyaret_edilenler[i], n->ad) == 0) {
                    dugum_indeksi = i;
                    break;
                }
            }

            if (dugum_indeksi == -1) {
                dugum_indeksi = ziyaret_edilen_sayisi;
                strcpy(oncekiler[dugum_indeksi], mevcut_ad);
            }

            if (yeni_maliyet < maliyetler[dugum_indeksi]) {
                maliyetler[dugum_indeksi] = yeni_maliyet;
                strcpy(oncekiler[dugum_indeksi], mevcut_ad);
                kuyruga_ekle(&kuyruk_basi, &kuyruk_sonu, n->ad, yeni_maliyet);
            }
            n = n->sonraki;
        }
        free(mevcut);
    }

    char yol[100][10];
    int yol_indeksi = 0;
    strcpy(yol[yol_indeksi++], hedef);

    char guncel_ad[10];
    strcpy(guncel_ad, hedef);

    printf("Yol:\n");
    while (strcmp(guncel_ad, baslangic) != 0) {
        for (int i = 0; i < ziyaret_edilen_sayisi; ++i) {
            if (strcmp(guncel_ad, ziyaret_edilenler[i]) == 0) {
                printf("%s (%d) <- ", guncel_ad, maliyetler[i]);
                strcpy(guncel_ad, oncekiler[i]);
                break;
            }
        }
    }
    printf("%s (%d)\n", baslangic, 0);
}


int main() {
    Graf* graf = NULL;

    kenar_ekle(&graf, "s", "A", 1);
    kenar_ekle(&graf, "s", "D", 3);
    kenar_ekle(&graf, "s", "G", 4);
    kenar_ekle(&graf, "A", "B", 2);
    kenar_ekle(&graf, "A", "D", 2);
    kenar_ekle(&graf, "B", "C", 2);
    kenar_ekle(&graf, "C", "t", 4);
    kenar_ekle(&graf, "D", "C", 3);
    kenar_ekle(&graf, "D", "E", 1);
    kenar_ekle(&graf, "E", "F", 3);
    kenar_ekle(&graf, "E", "t", 3);
    kenar_ekle(&graf, "F", "t", 3);
    kenar_ekle(&graf, "G", "H", 6);
    kenar_ekle(&graf, "G", "I", 4);
    kenar_ekle(&graf, "H", "I", 6);
    kenar_ekle(&graf, "I", "E", 3);
    kenar_ekle(&graf, "I", "t", 4);

    en_kisa_yolu_bul(graf, "s", "t");

    return 0;
}

