#define FULL
#include <time.h>
#include <smem/smem.h>

int main() {
    void *x;
    int i, j, k;
    clock_t f,g;
    sminit();
    k = 10+(rand()%20);
    f = clock();
    for (j=0;j<5000;j++) {
        x = salloc(1000);
    }    
    g = clock();
    
    printf("Time: %u\r\nSecond: %f\r\n", g-f, (double)(g-f)/(double)CLOCKS_PER_SEC);
    /*
    for (i=0;i<lvect->length;i++) {
        printf("Address: %p Size: %10u\r\n", lvect->vect[i].ptr, lvect->vect[i].length);
    }    
    */
    smfini();
    return 0;
}
    
