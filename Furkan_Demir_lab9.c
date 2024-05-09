#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//ilk başta ana struct oluştur binary heap için array ile yapılyıor genelde
//ardından içine tek tek char frek şeklinde node oluşturup char olacak freakans olacak left olacak rigth olacak 
//bu ndoe da ardından binary heap oluşturup içine teker teker dizdikten sonra
//tabi her aşamada bu şu anda min heap da mı diye kontrl edecek
//ardından min heap da iken en küçük 2 taneyi alıp bunların freq toplayıp yeni bir node a atamak yeni node un da sağ ve solunu en üstten aldığımız ikiliyi yapmak
//aldığımız o en küçük 2 taneyi yeni ağaca insert edecez ve bu işlemi tekrarlayacağız 1 tane kalana kadar
//bu işlemi yaparken her seferinde min heap da mı diye kontrol edecez
//en sonunda ise ağacı yazdıracağız

struct node {
    char veri;
    unsigned frekans;
    struct node* left, *right;
};

struct Heap {
    unsigned size;
    unsigned capacity;
    struct node* *arr;
};

struct node* newNode(char veri, unsigned frekans) {
    struct node* temp = (struct node* )malloc(sizeof(struct node));
    temp->left = temp->right = NULL;
    temp->veri = veri;
    temp->frekans = frekans;
    return temp;
}

struct Heap *createMinHeap(unsigned capacity) {
    struct Heap *minHeap = (struct Heap *)malloc(sizeof(struct Heap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->arr = (struct node* *)malloc(minHeap->capacity * sizeof(struct node* ));
    return minHeap;
}

void swapNode(struct node* *a, struct node* *b) {
    struct node* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct Heap *minHeap, int idx) {
    int min = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    if (left < minHeap->size && minHeap->arr[left]->frekans < minHeap->arr[min]->frekans)
        min = left;
    if (right < minHeap->size && minHeap->arr[right]->frekans < minHeap->arr[min]->frekans)
        min = right;
    if (min != idx) {
        swapNode(&minHeap->arr[min], &minHeap->arr[idx]);
        minHeapify(minHeap, min);
    }
}

int isSizeOne(struct Heap *minHeap) {
    return (minHeap->size == 1);
}

struct node* removeMin(struct Heap *minHeap) {
    struct node* temp = minHeap->arr[0];
    minHeap->arr[0] = minHeap->arr[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void addHeap(struct Heap *minHeap, struct node* node) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && node->frekans < minHeap->arr[(i - 1) / 2]->frekans) {
        minHeap->arr[i] = minHeap->arr[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->arr[i] = node;
}

void createHeap(struct Heap *minHeap) {
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

void printArr(int arr[], int n) {
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);
    printf("\n");
}

int isLeaf(struct node* root) {
    return !(root->left) && !(root->right);
}

struct Heap *buildHeapFromFreq(char veri[], int freq[], int size) {
    struct Heap *minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->arr[i] = newNode(veri[i], freq[i]);
    minHeap->size = size;
    createHeap(minHeap);
    return minHeap;
}

struct node* addTree(char veri[], int freq[], int size) {
    struct node* left, *right, *top;
    struct Heap *minHeap = buildHeapFromFreq(veri, freq, size);
    while (!isSizeOne(minHeap)) {
        left = removeMin(minHeap);
        right = removeMin(minHeap);
        top = newNode('$', left->frekans + right->frekans);
        top->left = left;
        top->right = right;
        addHeap(minHeap, top);
    }
    return removeMin(minHeap);
}

void show(struct node* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        show(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        show(root->right, arr, top + 1);
    }
    if (isLeaf(root)) {
        printf("%c: ", root->veri);
        printArr(arr, top);
    }
}

void HuffmanCodes(char veri[], int freq[], int size) {
    struct node* root = addTree(veri, freq, size);
    int arr[100], top = 0;
    show(root, arr, top);
}

int main() {
    char str[100];
    printf("Bir string giriniz: ");
    scanf("%s", str);
    int freq[256] = {0}; 
    int length = strlen(str);
    for (int i = 0; i < length; ++i)
        freq[(int)str[i]]++; 
    int size = 0;
    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0)
            size++;
    }
    char veri[size];
    int j = 0;
    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) {
            veri[j] = (char)i;
            j++;
        }
    }

    HuffmanCodes(veri, freq, size);
    return 0;
}
