#ifndef SMEM_H
#define SMEM_H

#include <inttypes.h>

enum {
    MVMEMORY = 1,
    MVTOOFAR,
    MVEMPTY,
    MVNULL
};    

#ifdef SOURCE

struct memptr {
    uint32_t flags;
    char *pname;
    uint32_t length;
    void *ptr;
};    

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

#endif
