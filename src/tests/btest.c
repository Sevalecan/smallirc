#define FULL
#include <smem/smem.h>
#include <time.h>

int main()
{
  int i;
  clock_t starta, enda, startd, endd;
  void *crap[10000];
  sminit();
  
  starta = clock();
  for(i = 0; i < 10000; ++i)
    crap[i] = salloc(1);
  enda = clock();
  startd = clock();
  for (i=0;i<10000;i++) {
  sfree(crap[i]);
  }  
  endd = clock();
  
  printf("Allocation took %d clocks... Deallocation took %d clocks... Total time was %d clocks... Clocks per second: %d\n", enda - starta, endd - startd, (enda - starta) + (endd - startd), CLOCKS_PER_SEC);
  return 0;
}
