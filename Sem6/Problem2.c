#include <stdio.h>
#include <stdlib.h>

#define N 10

typedef int (*Compare)(int, int);

int my_sort (int* a, int n, Compare comparator);
int swap (int* fir, int* sec);
int comparator (int fir, int sec);

int main(){
    int a[N] = {};
    int i = 0;
    for(i = 0; i < N; i++)
        scanf("%d", &a[i]);
    my_sort (a, N, comparator);

    for(int i = 0; i < N; i++)
        printf ("%d  ", a[i]);
    return 0;
}

int my_sort(int* a, int n, Compare comp){
    for(int i = 0; i < n - 1; i++){
        for (int j = i + 1; j < n; j++){
            if (comp (a[i], a[j]))
                swap (&a[i], &a[j]);
        }
    }
}

int comparator(int fir, int sec){
    return fir > sec;
}

int swap(int* fir, int* sec){
    int temp = *fir;
    *fir = *sec;
    *sec = temp;
}
