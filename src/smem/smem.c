#define SOURCE
#include <stdlib.h>
#include <smem/smem.h>



int mv_push(struct memvect *, struct memptr *);
int mv_pop(struct memvect *, struct memptr *);
int mv_delete(struct memvect *, int);
int mv_insert(struct memvect *im, int p, struct memptr *id) {
    
    return 0;
}
    

int mv_size(struct memvect *id) {
    return id->length;
}    

int mv_resize(struct memvect *id, int ns) {
    struct memptr *np;
    if (ns == 0 && id->vec != NULL && id->length > 0) {
        free(id->vec);
        id->length = 0;
    }
    else if (ns == 0 && id->length == 0) {
        return 0;
    }    
    else if (id->length > 0 && id->vec != NULL && ns > 0) {
        np = realloc(id->vec, ns*sizeof(struct memptr));
        if (np == NULL) return MVMEMORY;
        else {
            id->vec = np;
            id->length = ns;
            return 0;
        }    
    }
    else if (id->length == 0 && id->vec == NULL && ns > 0) {
        np = malloc(ns*sizeof(memptr));
        if (np == NULL) return MVMEMORY;
        else {
            id->vec = np;
            id->length = ns;
            return 0;
        }    
    }    
    return 0;
}    

int mv_destroy(struct memvect *od) {
    mv_resize(od, 0);
    od ? free(od) : 0;
    return 0;
}    

struct memvect *mv_create() {
    struct memvect *nw;
    nw = malloc(sizeof(struct memvect));
    if (nw == NULL) return MVMEMORY;
    
    memset(nw, 0, sizeof(struct memvect));
    
    return nw;
}



