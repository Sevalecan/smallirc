#define SOURCE
#include <stdlib.h>
#include <smem/smem.h>



int mv_push(struct memvect *im, struct memptr *id) {
    struct memptr *nw;
    
    if (im == NULL) return MVNULL;
    
    if (im->vect == NULL) {
        im->vect = malloc(sizeof(struct memptr));
        if (im->vect == NULL) return MVMEMORY; 
        im->length = 1;
        if (id != NULL) im->vect[0] = *id;
        else MVSHIT;
    }
    else {
        nw = realloc(im->vect, (im->length+1)*sizeof(struct memptr));
        if (nw == NULL) return MVMEMORY;
        im->vect = nw;
        im->length += 1;
        if (id != NULL) {
                im->vect[im->length-1] = *id;
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
        memmove(&im->vect[p], &im->vect[p+1], im->length-1-p);
    }
    
    //im->length--;
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



int sminit() {
    lvect = mv_create();
    if (lvect == NULL) return MVMEMORY;
    return 0;
}
    
void smfini() {
    int i;
    
    for (i=0;i<lvect->length;i++) {
        free(lvect->vect[i].ptr);
    }    
    
    if (lvect) mv_destroy(lvect);
}    



void *salloc(unsigned int size) {
    int ret;
    void *nv;
    struct memptr np;
    memset(&np, 0, sizeof(struct memptr));
    
    nv = malloc(size);
    if (nv == NULL) return NULL;
    
    np.length = size;
    np.ptr = nv;
    
    ret = mv_push(lvect, &np);
    if (ret != 0) {
        free(nv);
        return 0;
    }    
    
    return nv;
}
    
void sfree(void *ip) {
    int i;
    
    free(ip);
    
    for (i=0;i<lvect->length;i++) {
        if (lvect->vect[i].ptr == ip) {
            mv_delete(lvect, i);
            return;
        }    
    }    
    
    return;
}
    
void *srealloc(void *iv, unsigned int size) {\
    struct memptr ic;
    int i;
    void *nv;
    
    if (iv != NULL && size == 0) {
        sfree(iv);
        return 0;
    }
    /*
    if (iv == NULL && size > 0) {
        return salloc(size);
    }    
    */
    nv = realloc(iv, size);
    for (i=0;i<lvect->length;i++) {
        if (lvect->vect[i].ptr == iv) {
            lvect->vect[i].ptr = nv;
            lvect->vect[i].length = size;
            return nv;
        }    
    }
    // well fuck, reallocing something that maybe wasnt alloced with salloc in the first place? fuck you....
    ic.length = size;
    ic.ptr = nv;
    mv_push(lvect, &ic);
    
    return nv;
}
    
void *scalloc(unsigned int a, unsigned int b) {
    int ret;
    void *nv;
    struct memptr np;
    memset(&np, 0, sizeof(struct memptr));
    
    nv = calloc(a, b);
    if (nv == NULL) return NULL;
    
    np.length = a*b;
    np.ptr = nv;
    
    ret = mv_push(lvect, &np);
    if (ret != 0) {
        free(nv);
        return 0;
    }    
    
    return nv;
}    


