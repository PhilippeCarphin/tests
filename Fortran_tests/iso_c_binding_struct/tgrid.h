
/*
 * From repo Iris
 */

typedef struct TTile {
   int I0,I1;                             ///< Limits in X within global grid
   int J0,J1;                             ///< Limits in Y within global grid
   int HI,HJ;                             ///< Halo width in X and Y
} TTile;

typedef struct TGrid {
   char     Id[14];                       ///< Grid identifier
   // TGeoRef *GRef;                         ///< Georeference structure
   int      NI,NJ,NK;                     ///< Global grid dimensions
   int      HI,HJ;                        ///< Global grid halo width
   int      NbTiles;                      ///< Number of tiles
   TTile    *tiles;
} TGrid;

