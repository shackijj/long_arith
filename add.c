#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000

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

void print_long( int *l ) {
    printf("Length is: %d\n", l[0]);
    int i;
    for(i = l[0]; i > 0; i--) {
        printf("%d", l[i]);
    }
    printf("\n");
}


int *add(int *a, int *b) {
    int i, add_res, rem = 0;
    int *res = calloc(SIZE, sizeof(int));
    memcpy(res, a, (a[0] + 1) * sizeof(int));
   
    for(i = 1; i <= b[0]; i++) {
        if (i <= res[0]) {
            add_res = res[i] + b[i] + rem;
            if (add_res > 9) {
                rem = add_res / 10;
            } else {
                rem = 0;
            }
            res[i] = add_res % 10;
            // pintf("Added %d, rem %d\n", add_res % 10,  rem);

        } else {
            if (rem) {
                add_res = b[i] + rem;
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
        res[res[0]] = rem;
    }

    return res;
}

int *multiply(int *a, int *b) {
    int *res = init_long(0);
    int i = 0,
        tmp_res = 0,
        rem = 0,
        j = 0,
        tmp_add;

    for(i = 1; i <= a[0]; i++) {
        for( j = 1; j <= b[0]; j++ ) {
            //printf("m %d x %d reminder at start %d\n", a[i], b[j], rem);

            tmp_res = (a[i] * b[j]) + rem;

            if (tmp_res > 9) {
                rem = tmp_res / 10;
            } else {
                rem = 0;
            }
            //printf("tmp_res %d, rem %d\n", tmp_res, rem);
 
            if (res[i + j - 1]) {
                tmp_add = res[i + j - 1] + (tmp_res % 10);
                if (tmp_add > 9) {
                    rem += tmp_add / 10;
                }
                // printf("Writing here %d rem %d\n", tmp_add % 10, rem);
                res[i + j - 1] = tmp_add % 10;
                
            } else {
                //printf("Writing there %d rem %d\n", tmp_res % 10,  rem);
                res[i + j - 1] = tmp_res % 10;
                rem = tmp_res / 10;
                res[0]++;
            }
        }
        //print_long(res);
        if (rem) {
            //printf("Writing reminer %d\n", rem);
            res[0]++;
            res[res[0]] = rem;
            rem = 0;
        }
        //printf("End of first %d digit\n", i);
        //print_long(res);
    }
    //print_long(res);
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

    res = multiply(al, bl);
    print_long(res); 
    if(al) free(al);
    if(bl) free(bl);
    if(res) free(res);
    return 0;
}
