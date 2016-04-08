#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 32000
#define BASE 100000000000

unsigned long long *init_long(int from) {

    int i;    
    unsigned long long *to = calloc(SIZE, sizeof( unsigned long long ));
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

void print_long( unsigned long long  *l ) {
    //printf("Length is: %d\n", l[0]);
    int i;
    for(i = l[0]; i > 0; i--) {
        printf("%d", l[i]);
    }
    printf("\n");
}


unsigned long long *add( unsigned long long  *a,  unsigned long long  *b) {
    int i;
    unsigned long long add_res, rem = 0;
    unsigned long long  *res = calloc(SIZE, sizeof( unsigned long long ));
    memcpy(res, a, (a[0] + 1) * sizeof( unsigned long long ));

    for(i = 1; rem || i <= b[0]; i++) {
        if (i <= res[0]) {
            add_res = res[i] + b[i] + rem;
            // printf("%d + %d + %d = %d\n", res[i], b[i], rem, add_res);
            
            if (add_res > BASE- 1) {
                rem = add_res / BASE;
            } else {
                rem = 0;
            }
            res[i] = add_res % BASE;
            // printf("0 Added %d, rem %d to pos %d\n", add_res % 10,  rem, i);

        } else {
            if (rem) {
                add_res = b[i] + rem;
                if (add_res > BASE - 1) {
                    rem = add_res / BASE;
                } else {
                    rem = 0;
                }
               // printf("1 Added %d, rem %d to pos %d\n", add_res % 10,  rem, i);
                res[i] = add_res % BASE;
            } else {
                //printf("1 Added %d, rem %d to pos %d\n", b[i],  rem, i);
                res[i] = b[i];
            }
            res[0]++;
        }
    }


    
    return res;
}

unsigned long long *multiply( unsigned long long  *fm,  unsigned long long  *sm) {

    unsigned long long  *a, *b;
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

    /*
    printf("a: \n");
    print_long(a);
    printf("b: \n");
    print_long(b);
    */

    unsigned long long  *res = init_long(0);
    int i = 0,
        j = 0;
    unsigned long long tmp_mpl = 0,
                       rem = 0,
                       tmp_add;

    if (a[0] == 1 && a[1] == 0) return res;
    if (b[0] == 1 && b[1] == 0) return res;

    for(i = 1; i <= a[0]; i++) {
        for( j = 1; j <= b[0]; j++ ) {
            tmp_mpl = a[i] * b[j] + rem;
           // printf(" %d x %d + %d = %d\n", a[i], b[j], rem, tmp_mpl);
            if (tmp_mpl > BASE - 1) {
             //   printf( "%d > 9, so reminder, %d\n", tmp_mpl, tmp_mpl / 10);
                rem = tmp_mpl / BASE;
            } else {
                rem = 0;
            }

            if (res[i + j - 1]) {
                tmp_add = res[i + j - 1] + (tmp_mpl % BASE);
                if (tmp_add > BASE - 1) {
                    rem += tmp_add / BASE;
                }
             //   printf("1 Wrinting %d to position %d rem %d\n", tmp_add % 10, i + j - 1, rem);
                res[i + j - 1] = tmp_add % BASE;
                if(i + j - 1 > res[0]) res[0] = i + j - 1;

            } else {
               // printf("2 Wrinting %d to pos %d rem %d \n", tmp_mpl % 10, i + j - 1, rem);
                if(i + j - 1 > res[0]) res[0] = i + j - 1;
                res[i + j - 1] = tmp_mpl % BASE;
            }
        
        }
        if (rem) {
           res[0]++;
           //printf("Writing reminder %d to pos %d\n", rem, res[0]);
           res[res[0]] = rem;
           rem = 0;
        }
    
        //printf("End of digit: \n");
        //print_long(res);
    }
    //printf("Exiting\n");
    //print_long(res);
    return res;
}

    
int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    int A, B, N;
    scanf("%d", &A);
    scanf("%d", &B);
    scanf("%d", &N);

    // First two members
    N -= 2;
    unsigned long long  *al = init_long(A);
    unsigned long long *bl = init_long(B);
    /*
    int *tmpl = multiply(al, bl);

    printf("Mulit res: ");
    print_long(tmpl);
   
    int *cl = add(al, bl);
    printf("Add res: ");
    print_long(cl);
    
    free(al);
    free(bl);
    //free(tmpl);
    free(cl);
    */
    
    unsigned long long  *cl, *tmpl;
    
    //printf("al: ");
    //print_long(al);
    //printf("bl: ");
    //print_long(bl);

    while (N--) {
        
        tmpl = multiply(bl, bl);
        //printf("tmpl: ");
        //print_long(tmpl);

        cl = add(tmpl, al);

        free(tmpl);
        free(al);

        al = bl;
        bl = cl;
        /*        
        printf("tmpl: ");
        print_long(tmpl);

        printf("cl: ");
        print_long(cl);
        
        printf("al: ");
        print_long(al);

        printf("bl: ");
        print_long(bl);
        */
    }

    //printf("Out of loop\n");
    print_long(bl);

    if (al) free(al);
    if (bl) free(bl);
    //if (cl) free(cl);
    // if (tmpl) free(tmpl); 

    return 0;
}
