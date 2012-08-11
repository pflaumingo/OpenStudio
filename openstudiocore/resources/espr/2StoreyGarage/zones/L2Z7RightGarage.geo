# geometry of L2Z7RightGarage defined in: user/2StoreyGarage/zones/L2Z7RightGarage.geo
GEN  L2Z7RightGarage  HOT3000 generated zone  # type, name, descr
      30       11 0.000    # vertices, surfaces, rotation angle
#   X co-ord, Y co-ord, Z co-ord
    12.00000  6.10000  100.60001   # vert 1  
    12.00000  3.05000  100.60001   # vert 2  
    12.00000  0.00000  100.60001   # vert 3  
    12.00000  0.00000  103.22000   # vert 4  
    12.00000  3.05000  103.22000   # vert 5  
    12.00000  6.10000  103.22000   # vert 6  
    12.00000  1.63184  101.50000   # vert 7  
    12.00000  1.63184  102.70000   # vert 8  
    12.00000  0.30000  102.70000   # vert 9  
    12.00000  0.30000  101.50000   # vert 10 
    18.10000  6.10000  100.60001   # vert 11 
    18.10000  6.10000  103.22000   # vert 12 
    13.63184  6.10000  101.50000   # vert 13 
    13.63184  6.10000  102.70000   # vert 14 
    12.30000  6.10000  102.70000   # vert 15 
    12.30000  6.10000  101.50000   # vert 16 
    18.10000  0.00000  100.60001   # vert 17 
    18.10000  0.30000  100.60001   # vert 18 
    18.10000  0.30000  102.70000   # vert 19 
    18.10000  1.20000  102.70000   # vert 20 
    18.10000  1.20000  100.60001   # vert 21 
    18.10000  0.00000  103.22000   # vert 22 
    18.10000  4.46817  101.50000   # vert 23 
    18.10000  4.46817  102.70000   # vert 24 
    18.10000  5.80000  102.70000   # vert 25 
    18.10000  5.80000  101.50000   # vert 26 
    12.30000  0.00000  100.60001   # vert 27 
    12.30000  0.00000  102.70000   # vert 28 
    17.80000  0.00000  102.70000   # vert 29 
    17.80000  0.00000  100.60001   # vert 30 
# no of vertices followed by list of associated vert
  13,   1,   2,   3,   4,   5,   6,   1,   7,   8,   9,  10,   7,   1,
  11,  11,   1,   6,  12,  11,  13,  14,  15,  16,  13,  11,
  15,  17,  18,  19,  20,  21,  11,  12,  22,  17,  23,  24,  25,  26,  23,  17,
   8,   3,  27,  28,  29,  30,  17,  22,   4,
   5,   3,   2,   1,  11,  17,
   5,   4,  22,  12,   6,   5,
   4,   7,  10,   9,   8,
   4,  13,  16,  15,  14,
   4,  18,  21,  20,  19,
   4,  23,  26,  25,  24,
   4,  27,  30,  29,  28,
# unused index
 0   0   0   0   0   0   0   0   0   0   0  
# surfaces indentation (m)
0.000 0.000 0.000 0.000 0.000 0.000 0.000 0.000 0.000 0.000 0.000 
    3    0    0    0  # default insolation distribution
# surface attributes follow: 
# id surface       geom  loc/   mlc db      environment
# no name          type  posn   name        other side
  1, wa01R0207     OPAQ  VERT  ext_wall     EXTERIOR       
  2, wa02R0207     OPAQ  VERT  ext_wall     EXTERIOR       
  3, wa03R0207     OPAQ  VERT  ext_wall     EXTERIOR       
  4, wa04R0207     OPAQ  VERT  ext_wall     EXTERIOR       
  5, fl01R0207     OPAQ  FLOR  slab_floor   BASESIMP       
  6, ce01R0207     OPAQ  CEIL  floors_r     L2Z8RightAttic 
  7, wi01R0207     TRAN  VERT  window       EXTERIOR       
  8, wi02R0207     TRAN  VERT  window       EXTERIOR       
  9, do01R0207     OPAQ  VERT  ext_door     EXTERIOR       
 10, wi03R0207     TRAN  VERT  window       EXTERIOR       
 11, do02R0207     OPAQ  VERT  ext_door     EXTERIOR       
# base
5   0   0   0   0   0   37.21    
