
typedef struct TGrid {
   char     Id[14];                       ///< Grid identifier
   // TGeoRef *GRef;                         ///< Georeference structure
   int      NI,NJ,NK;                     ///< Global grid dimensions
   int      HI,HJ;                        ///< Global grid halo width
   int      NbTiles;                      ///< Number of tiles/PEs
   // TTile   *Tiles;                        ///< Array of tiles definitions                     
} TGrid;
