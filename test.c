#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#define SIZE 50

int *init_long(int from) {

    int i;    
    int *to = calloc(SIZE, sizeof(int));
    to[0] = 0;

    if (from == 0) {
        to[0] = 1;
        to[1] = 0;
        return to;
    }

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
                rem += add_res / 10;
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

int *multiply(int *fm, int *sm) {

    int *a, *b;
    if (fm[0] < sm[0]) {
        a = fm;
        b = sm;
    } else if ( fm[0] > sm[0] ) {
        a = sm;
        b = fm;
    } else {
        a = fm;
        b = sm;
    }


    printf("a: \n");
    print_long(a);
    printf("b: \n");
    print_long(b);

    int *res = init_long(0);
    int i = 0,
        tmp_mpl = 0,
        rem = 0,
        j = 0,
        tmp_add;

    if (a[0] == 1 && a[1] == 0) return res;
    if (b[0] == 1 && b[1] == 0) return res;

    for(i = 1; i <= a[0]; i++) {
        for( j = 1; j <= b[0]; j++ ) {
            tmp_mpl = a[i] * b[j] + rem;
            printf(" %d x %d + %d = %d\n", a[i], b[j], rem, tmp_mpl);
            if (tmp_mpl > 9) {
                rem = tmp_mpl / 10;
            }

            if (res[i + j - 1]) {
                tmp_add = res[i + j - 1] + (tmp_mpl % 10);
                if (tmp_add > 9) {
                    rem = tmp_add / 10;
                }
                printf("1 Wrinting %d to position %d rem %d\n", tmp_add % 10, i + j - 1, rem);
                res[i + j - 1] = tmp_add % 10;
                if(i + j - 1 > res[0]) res[0] = i + j - 1;

            } else {
                printf("2 Wrinting %d to pos %d rem %d \n", tmp_mpl % 10, i + j - 1, rem);
                if(i + j - 1 > res[0]) res[0] = i + j - 1;
                res[i + j - 1] = tmp_mpl % 10;
            }
        
        }
        if (rem) {
           res[0]++;
           printf("Writing reminder %d to pos %d\n", rem, res[0]);
           res[res[0]] = rem;
           rem = 0;
        }
    
        printf("End of digit: \n");
        print_long(res);
    }
    printf("Exiting\n");
    //print_long(res);
    return res;
}

    
int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    int A, B, N;
    scanf("%d", &A);
    scanf("%d", &B);
    //scanf("%d", &N);

    // First two members
    N -= 2;
    int *al = init_long(A);
    int *bl = init_long(B);
    int *tmpl = multiply(al, bl);
    printf("Mulit res: ");
    print_long(tmpl);
    /*
    int *cl, *tmpl;
    
    printf("al: ");
    print_long(al);
    printf("bl: ");
    print_long(bl);

    while (N--) {
        
        tmpl = multiply(bl, bl);
        printf("tmpl: ");
        print_long(tmpl);

        cl = add(tmpl, al);
        al = bl;
        bl = cl;
        printf("tmpl: ");
        print_long(tmpl);

        printf("cl: ");
        print_long(cl);
        
        printf("al: ");
        print_long(al);

        printf("bl: ");
        print_long(bl);
        break;
    }

    print_long(cl);

    if (al) free(al);
    if (bl) free(bl);
    if (cl) free(cl);
    if (tmpl) free(tmpl); 
    */
    return 0;
}
