#define SOURCE
#include <stdlib.h>
#include <smem/smem.h>



int mv_push(struct memvect *im, struct memptr *id) {
    struct memptr *nw;
    
    if (im == NULL) return MVNULL;
    
    if (im->vect == NULL) {
        im->vect = malloc(sizeof(struct memptr));
    }
    else {
        nw = realloc(im->vect, (im->length+1)*sizeof(struct memptr));
        if (nw == NULL) return MVMEMORY;
        im->vect = nw;
        im->length += 1;
        if (id != NULL) {
                (*(im->vect+((im->length-1)*sizeof(struct memptr)))) = *id;
        }    
    }    
    
    return 0;
}    


int mv_delete(struct memvect *im, unsigned int p) {
    struct memptr *nw;
    
    if (im == NULL) return MVNULL;
    if (p >= im->length) return MVTOOFAR;
    if (im->length == 0 && im->vect == NULL) return MVEMPTY;
    
    if (p < im->length-1) {
        memmove(im->vect+(p*sizeof(struct memptr)), im->vect+(p*sizeof(struct memptr))+sizeof(struct memptr), im->length-p-1);
    }
    
    im->length--;
    
    nw = realloc(im->vect, im->length);    
    if (nw != NULL) im->vect = nw;
    return 0;
}
    
int mv_insert(struct memvect *im, unsigned int p, struct memptr *id) {
    struct memptr *np;
    int nl, ret;
    
    if (im == NULL) return MVNULL;
    
    if (im->length < p) return MVTOOFAR;
    if (im->length == p) {
        return mv_push(im, id);
    }
    if (p < im->length) {
        ret = mv_resize(im, im->length+1);
        if (ret != 0) return ret;
        ret = (int)memmove(im->vect+(sizeof(struct memptr)*p)+sizeof(struct memptr), im->vect+(sizeof(struct memptr)*p), sizeof(struct memptr) * (im->length-p-1));
        *(im->vect+p) = *id;
        return 0;
    }    
    
    
    return 0;
}
    

int mv_size(struct memvect *id) {
    return id->length;
}    

int mv_resize(struct memvect *id, int ns) {
    struct memptr *np;
    if (id == NULL) return MVNULL;
    if (ns == 0 && id->vect != NULL && id->length > 0) {
        free(id->vect);
        id->length = 0;
    }
    else if (ns == 0 && id->length == 0) {
        return 0;
    }    
    else if (id->length > 0 && id->vect != NULL && ns > 0) {
        np = realloc(id->vect, ns*sizeof(struct memptr));
        if (np == NULL) return MVMEMORY;
        else {
            id->vect = np;
            id->length = ns;
            return 0;
        }    
    }
    else if (id->length == 0 && id->vect == NULL && ns > 0) {
        np = malloc(ns*sizeof(struct memptr));
        if (np == NULL) return MVMEMORY;
        else {
            id->vect = np;
            id->length = ns;
            return 0;
        }    
    }    
    return 0;
}    

int mv_destroy(struct memvect *od) {
    if (od == NULL) return MVNULL;
    mv_resize(od, 0);
    od ? free(od) : 0;
    return 0;
}    

struct memvect *mv_create() {
    struct memvect *nw;
    nw = malloc(sizeof(struct memvect));
    if (nw == NULL) return 0;
    
    memset(nw, 0, sizeof(struct memvect));
    
    return nw;
}



