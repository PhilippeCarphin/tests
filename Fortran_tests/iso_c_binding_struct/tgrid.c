#include "tgrid.h"
#include <stdio.h>
#include <stdlib.h>

int print_tile(TTile *t){
    fprintf(stderr, "Tile at %p\n", t);
    fprintf(stderr, "    (I0,J0) = (%d,%d)\n", t->I0, t->J0);
    fprintf(stderr, "    (I1,J1) = (%d,%d)\n", t->I1, t->J1);
    fprintf(stderr, "    (HI,HJ) = (%d,%d)\n", t->HI, t->HJ);
    return 0;
}

// character(kind=C_CHAR, len=14) :: Id
// type(C_PTR)                    :: GRef (keep for later)
// integer(C_INT)                 :: NI, NJ, NK
// integer(C_INT)                 :: HI, HJ
// integer(C_INT)                 :: NbTiles
// type(C_PTR)                    :: Tiles
int print_grid(TGrid *g){
    fprintf(stderr, "Tile at %p\n", g);
    fprintf(stderr, "    Id = %s\n", g->Id);
    // fprintf(stderr, "    GRef (ptr) = %p\n", g->GRef);
    fprintf(stderr, "    (NI,NJ,NK) = (%d,%d,%d)\n", g->NI, g->NJ, g->NK);
    fprintf(stderr, "    (HI,HJ) = (%d,%d)\n", g->HI, g->HJ);
    fprintf(stderr, "    NbTiles = %d\n", g->NbTiles);
    for( int i = 0; i < g->NbTiles; i++ ){
        print_tile(&g->tiles[i]);
    }
    return 0;
}

int allocate_tiles(TGrid *g, int n){
    g->tiles = malloc(sizeof(*g->tiles) * n);
    if(g->tiles == NULL){
        fprintf(stderr, "MALLOC ERROR\n");
        return 1;
    }
    return 0;
}


TGrid *new_grid(int nb_tiles){
    TGrid *g = malloc(sizeof(*g));
    g->tiles = malloc(sizeof(*g->tiles) *nb_tiles);
    return g;
}

int set_tile(TGrid *g, int i, TTile *t){
    if (i >= g->NbTiles){
        fprintf(stderr, "%s(g=%p, i=%d, t=%p): ERROR: i=%d is larger than g->NbTiles=%d\n", __func__, g, i, t, i, g->NbTiles);
        return 1;
    }

    g->tiles[i] = *t;
    return 0;
}

