#include <stdio.h>
#include <stdlib.h>
//This kod has a big logic error amybe u can fix it!
struct TreeDugum{
    int veri;
    struct TreeDugum *left;
    struct TreeDugum *right;
};

struct TreeDugum* root = NULL;
struct TreeDugum* dugumOlustur(int veri) {
    struct TreeDugum* dugum = (struct TreeDugum*)malloc(sizeof(struct TreeDugum));
    dugum->veri = veri;
    dugum->left = NULL;
    dugum->right = NULL;
    return dugum;
};

void agacOlustur(int n) {
    if (n <= 0) printf("n 0'dan büyük olamilidr.");
    int veri = 1; // Kök düğümü oluştur
    root = dugumOlustur(veri++); // Kök düğümü oluştur ve bir sonraki veriye geç
    
    for (int i = 2; i <1<<n ; i++)//burada 2^n in 1<<n şeklinde yazıldığını gfg de gördüm ve kullandım 2^n yazınca çalışmıyordu kod
     {
        struct TreeDugum* temp = root;
        int veri = i;
        while (1) { 
            if (veri < temp->veri) {
                if (temp->left == NULL) {
                    temp->left = dugumOlustur(veri);
                    break;
                } else {
                    temp = temp->left;
                }
            } else {
                if (temp->right == NULL) {
                    temp->right = dugumOlustur(veri);
                    break;
                } else {
                    temp = temp->right;
                }
            }
        }
    }
}

void AgaciDiziyeAta(struct TreeDugum* root, int *dizi, int *index) {
    if (root != NULL) {
      dizi[*index] = root->veri;
        (*index)++;  
        AgaciDiziyeAta(root->left, dizi, index);
        AgaciDiziyeAta(root->right, dizi, index);
    }
}

void PreorderGezintiDizisi(struct TreeDugum* root, int *dizi, int boyut) {
    int index = 0;
    AgaciDiziyeAta(root, dizi, &index);
}

     
void DiziyiYazdir(int *dizi, int boyut) {
    printf("Dizi: ");
    for (int i = 0; i < boyut; i++) {
        printf("%d ", dizi[i]);
    }
    printf("\n");
}
    int AgacDugumSayisi(struct TreeDugum* root) 
    {
    if (root == NULL)
        return 0;
    else
        return 1 + AgacDugumSayisi(root->left) + AgacDugumSayisi(root->right);
    }


    //dizinin ortasındaki elemanı bul
    int ortaElaman(int *dizi, int n) 
    {
        int orta = dizi[(1<<n)-2]/2;
        return dizi[orta];
    }

    // orta elemanı kök kabul eden yeni bir ağaç yapmalıyım
struct TreeDugum* YeniAgac(int *dizi, int n) {
    int ortaIndis = (1 << n) / 2 - 1;
    int ortaEleman = ortaElaman(dizi, n);
    struct TreeDugum* root = dugumOlustur(ortaEleman);

    for (int i = 0; i < (1 << n) - 1; i++) {
        if (i == ortaIndis) continue;

        struct TreeDugum* temp = root;
        while (1) {
            if (dizi[i] < temp->veri) {
                if (temp->left == NULL) {
                    temp->left = dugumOlustur(dizi[i]);
                    break;
                } else {
                    temp = temp->left;
                }
            } else {
                if (temp->right == NULL) {
                    temp->right = dugumOlustur(dizi[i]);
                    break;
                } else {
                    temp = temp->right;
                }
            }
        }
    }
    return root;
}

    //yeniağacın doğru olup olmadığını inorder ile test etme
    void InorderGezinti(struct TreeDugum* root) 
    {
        if (root == NULL) return;
        InorderGezinti(root->left);
        printf("%d ", root->veri);
        InorderGezinti(root->right);

    }

    void agaciagacgibiYazdir(struct TreeDugum* root,int bosluk) {
    if (root == NULL) return;
    bosluk += 3;
    agaciagacgibiYazdir(root->right, bosluk);
    printf("\n");
    for (int i = 3; i < bosluk; i++) printf(" ");
    printf("%d\n", root->veri);
    agaciagacgibiYazdir(root->left, bosluk);
    }

    int yaprakSayisi(struct TreeDugum* root) {
    if (root == NULL) return 0;
    
    if (root->left == NULL && root->right == NULL) return 1;
   
    
    return yaprakSayisi(root->left) + yaprakSayisi(root->right);
     }
    


int main(){
    int n;
    printf("Agaciniz 2 uzeri n-1 e kadar olan tam sayilarla olusturulacaktir. Lutfen bir sayi giriniz: ");
    scanf("%d", &n);
    root = dugumOlustur(1);
    agacOlustur(n); 

    // Yeni ağacı oluştur
    int* dizi = malloc(AgacDugumSayisi(root) * sizeof(int));
    PreorderGezintiDizisi(root, dizi, AgacDugumSayisi(root));
    struct TreeDugum* yeni_root = YeniAgac(dizi, n);
    

    // Yeni ağacın inorder gezintisini yazdır rootun doğru olup olmadığını test etmek için
    printf("Yeni Agacin Elemanlari (Inorder): ");
    InorderGezinti(yeni_root);
    printf("\n");
    agaciagacgibiYazdir(yeni_root, 0);

    int yaprak_sayisi = yaprakSayisi(yeni_root);
    printf("Agacin yaprak sayisi: %d\n", yaprak_sayisi);
    return 0;
};
