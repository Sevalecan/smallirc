#ifndef SMEM_H
#define SMEM_H

#include <inttypes.h>

enum {
    MVMEMORY = 1,
    MVTOOFAR,
    MVEMPTY,
    MVNULL,
    MVSHIT
};    

#ifndef SOURCE
#define EXPORT extern
#else
#define EXPORT
#endif

#if defined(SOURCE) || defined(FULL)


struct memptr {
    //uint32_t flags;     // flags        :: unused
    //char *pname;        // pointer name :: unused
    uint32_t length;    // length
    void *ptr;          // pointer
} __attribute__((packed));    

struct memvect {
    uint32_t length;
    struct memptr *vect;
};



int mv_push(struct memvect *, struct memptr *);
int mv_delete(struct memvect *, unsigned int);
int mv_insert(struct memvect *, unsigned int, struct memptr *);
int mv_size(struct memvect *);
int mv_resize(struct memvect *, int);
int mv_destroy(struct memvect *);
struct memvect *mv_create();


#endif

EXPORT struct memvect *lvect;

EXPORT int sminit();
EXPORT void smfini();
EXPORT void *salloc(unsigned int);
EXPORT void sfree(void *);
EXPORT void *srealloc(void *, unsigned int);
EXPORT void *scalloc(unsigned int, unsigned int);

#undef EXPORT

#endif
