#ifndef SMEM_H
#define SMEM_H

#include <inttypes.h>

enum {
    MVMEMORY = 1,
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
    struct memptr *vec;
};

int mv_push(struct memvect *, struct memptr *);
int mv_pop(struct memvect *, struct memptr *);
int mv_delete(struct memvect *, int);
int mv_insert(struct memvect *, int, struct memptr *);
inline int mv_size(struct memvect *, );
int mv_resize(struct memvect *, int);
int mv_destroy(struct memvect *);
struct memvect *mv_create();

#endif

#endif
