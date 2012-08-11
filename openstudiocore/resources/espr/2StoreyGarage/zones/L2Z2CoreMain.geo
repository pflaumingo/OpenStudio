# geometry of L2Z2CoreMain defined in: user/2StoreyGarage/zones/L2Z2CoreMain.geo
GEN  L2Z2CoreMain  HOT3000 generated zone  # type, name, descr
      38       14 0.000    # vertices, surfaces, rotation angle
#   X co-ord, Y co-ord, Z co-ord
    0.00000  11.05000  100.60001   # vert 1  
    0.00000  3.05000  100.60001   # vert 2  
    0.00000  3.05000  103.22000   # vert 3  
    0.00000  11.05000  103.22000   # vert 4  
    0.00000  5.09667  101.50000   # vert 5  
    0.00000  5.09667  102.70000   # vert 6  
    0.00000  3.35001  102.70000   # vert 7  
    0.00000  3.35001  101.50000   # vert 8  
    12.00000  11.05000  100.60001   # vert 9  
    11.70000  11.05000  100.60001   # vert 10 
    11.70000  11.05000  102.70000   # vert 11 
    10.80000  11.05000  102.70000   # vert 12 
    10.80000  11.05000  100.60001   # vert 13 
    12.00000  11.05000  103.22000   # vert 14 
    2.92000  11.05000  101.50000   # vert 15 
    2.92000  11.05000  102.70000   # vert 16 
    0.30000  11.05000  102.70000   # vert 17 
    0.30000  11.05000  101.50000   # vert 18 
    12.00000  3.05000  100.60001   # vert 19 
    12.00000  6.10000  100.60001   # vert 20 
    12.00000  6.10000  103.22000   # vert 21 
    12.00000  3.05000  103.22000   # vert 22 
    12.00000  9.00333  101.50000   # vert 23 
    12.00000  9.00333  102.70000   # vert 24 
    12.00000  10.75000  102.70000   # vert 25 
    12.00000  10.75000  101.50000   # vert 26 
    7.25000  3.05000  100.60001   # vert 27 
    7.25000  3.05000  103.22000   # vert 28 
    10.66292  3.05000  101.50000   # vert 29 
    10.66292  3.05000  102.70000   # vert 30 
    11.70000  3.05000  102.70000   # vert 31 
    11.70000  3.05000  101.50000   # vert 32 
    4.75000  3.05000  100.60001   # vert 33 
    4.75000  3.05000  103.22000   # vert 34 
    3.41292  3.05000  101.50000   # vert 35 
    3.41292  3.05000  102.70000   # vert 36 
    4.45000  3.05000  102.70000   # vert 37 
    4.45000  3.05000  101.50000   # vert 38 
# no of vertices followed by list of associated vert
  11,   1,   2,   3,   4,   1,   5,   6,   7,   8,   5,   1,
  15,   9,  10,  11,  12,  13,   1,   4,  14,   9,  15,  16,  17,  18,  15,   9,
  13,  19,  20,   9,  14,  21,  22,  19,  23,  24,  25,  26,  23,  19,
  11,  27,  19,  22,  28,  27,  29,  30,  31,  32,  29,  27,
  11,   2,  33,  34,   3,   2,  35,  36,  37,  38,  35,   2,
   4,  33,  27,  28,  34,
   7,   2,   1,   9,  20,  19,  27,  33,
   7,   3,  34,  28,  22,  21,  14,   4,
   4,   5,   8,   7,   6,
   4,  10,  13,  12,  11,
   4,  15,  18,  17,  16,
   4,  23,  26,  25,  24,
   4,  29,  32,  31,  30,
   4,  35,  38,  37,  36,
# unused index
 0   0   0   0   0   0   0   0   0   0   0   0   0   0  
# surfaces indentation (m)
0.000 0.000 0.000 0.000 0.000 0.000 0.000 0.000 0.000 0.000 0.000 0.000 0.000 0.000 
    3    0    0    0  # default insolation distribution
# surface attributes follow: 
# id surface       geom  loc/   mlc db      environment
# no name          type  posn   name        other side
  1, wa01C0202     OPAQ  VERT  ext_wall     EXTERIOR       
  2, wa02C0202     OPAQ  VERT  ext_wall     EXTERIOR       
  3, wa03C0202     OPAQ  VERT  ext_wall     EXTERIOR       
  4, wa04C0202     OPAQ  VERT  ext_wall     EXTERIOR       
  5, wa05C0202     OPAQ  VERT  ext_wall     EXTERIOR       
  6, wa06C0202     OPAQ  VERT  intern_wall  L2Z5FrontMudroom
  7, fl01C0202     OPAQ  FLOR  floors       L1Z1CoreBasement
  8, ce01C0202     OPAQ  CEIL  floors_r     L3Z3CoreMain   
  9, wi01C0202     TRAN  VERT  window       EXTERIOR       
 10, do01C0202     OPAQ  VERT  ext_door     EXTERIOR       
 11, wi02C0202     TRAN  VERT  window       EXTERIOR       
 12, wi03C0202     TRAN  VERT  window       EXTERIOR       
 13, wi04C0202     TRAN  VERT  window       EXTERIOR       
 14, wi05C0202     TRAN  VERT  window       EXTERIOR       
# base
7   0   0   0   0   0   96.00    
