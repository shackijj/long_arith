#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 50

int *init_long(int from) {

    int i;    
    int *to = calloc(SIZE, sizeof(int));
    to[0] = 0;


    for(i = 1; from > 0; i++) {
        to[i] = from % 10;
        to[0]++;
        from = from / 10;
    }

    return to;
}


int *add(int *a, int *b) {
    int i, 
        rem = 0;
    int *res = calloc(SIZE, sizeof(int));
    memcpy(&res, &a, sizeof(a[0]));
    
    for(i = 1; i < b[0]; i++) {
        if (i < res[0]) {
            int add_res = res[i] + b[i] + rem;
            if (add_res > 9) {
                rem = add_res / 10;
            } else {
                rem = 0;
            }
            res[i] = add_res % 10;
        } else {
            if (rem) {
                int add_res = b[i] + rem;
                if (add_res > 9) {
                    rem = add_res / 10;
                } else {
                    rem = 0;
                }
                res[i] = add_res % 10;
            } else {
                res[i] = b[i];
            }
            res[0]++;
        }
    } 

    if (rem) {
        res[0]++;
        res[res[0] - 1] = rem;
    }

    return res;
}

int main() {

    int *al;
    int *bl;
    int *res;
    int a, b;
    int i;

    scanf("%d", &a);
    scanf("%d", &b);

    al = init_long(a);
    bl = init_long(b);
    res = add(al, bl);
    
    for(i = 0; i < res[0]; i++) {
        printf("%d", res[i]);
    }

    printf("\n");

    free(al);
    free(bl);
    free(res);
    return 0;
}
