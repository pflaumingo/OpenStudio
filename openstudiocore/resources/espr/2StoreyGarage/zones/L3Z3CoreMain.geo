# geometry of L3Z3CoreMain defined in: user/2StoreyGarage/zones/L3Z3CoreMain.geo
GEN  L3Z3CoreMain  HOT3000 generated zone  # type, name, descr
      32       11 0.000    # vertices, surfaces, rotation angle
#   X co-ord, Y co-ord, Z co-ord
    0.00000  11.05000  103.22000   # vert 1  
    0.00000  3.05000  103.22000   # vert 2  
    0.00000  3.05000  105.84000   # vert 3  
    0.00000  11.05000  105.84000   # vert 4  
    0.00000  5.09667  104.12000   # vert 5  
    0.00000  5.09667  105.32000   # vert 6  
    0.00000  3.35001  105.32000   # vert 7  
    0.00000  3.35001  104.12000   # vert 8  
    12.00000  11.05000  103.22000   # vert 9  
    12.00000  11.05000  105.84000   # vert 10 
    2.92000  11.05000  104.12000   # vert 11 
    2.92000  11.05000  105.32000   # vert 12 
    0.30000  11.05000  105.32000   # vert 13 
    0.30000  11.05000  104.12000   # vert 14 
    12.00000  3.05000  103.22000   # vert 15 
    12.00000  6.10000  103.22000   # vert 16 
    12.00000  6.10000  105.84000   # vert 17 
    12.00000  3.05000  105.84000   # vert 18 
    12.00000  3.05000  104.23656   # vert 19 
    12.00000  9.00333  104.12000   # vert 20 
    12.00000  9.00333  105.32000   # vert 21 
    12.00000  10.75000  105.32000   # vert 22 
    12.00000  10.75000  104.12000   # vert 23 
    4.75000  3.05000  103.22000   # vert 24 
    6.00000  3.05000  103.63663   # vert 25 
    7.25000  3.05000  103.22000   # vert 26 
    7.25000  3.05000  105.84000   # vert 27 
    4.75000  3.05000  105.84000   # vert 28 
    9.08000  3.05000  104.12000   # vert 29 
    9.08000  3.05000  105.32000   # vert 30 
    11.70000  3.05000  105.32000   # vert 31 
    11.70000  3.05000  104.12000   # vert 32 
# no of vertices followed by list of associated vert
  11,   1,   2,   3,   4,   1,   5,   6,   7,   8,   5,   1,
  11,   9,   1,   4,  10,   9,  11,  12,  13,  14,  11,   9,
  14,  15,  16,   9,  10,  17,  18,  19,  15,  20,  21,  22,  23,  20,  15,
  17,   2,  24,  25,  26,  15,  19,  18,  27,  28,   3,   2,  29,  30,  31,  32,  29,   2,
   3,  24,  26,  25,
   7,   2,   1,   9,  16,  15,  26,  24,
   7,   3,  28,  27,  18,  17,  10,   4,
   4,   5,   8,   7,   6,
   4,  11,  14,  13,  12,
   4,  20,  23,  22,  21,
   4,  29,  32,  31,  30,
# unused index
 0   0   0   0   0   0   0   0   0   0   0  
# surfaces indentation (m)
0.000 0.000 0.000 0.000 0.000 0.000 0.000 0.000 0.000 0.000 0.000 
    3    0    0    0  # default insolation distribution
# surface attributes follow: 
# id surface       geom  loc/   mlc db      environment
# no name          type  posn   name        other side
  1, wa01C0303     OPAQ  VERT  ext_wall     EXTERIOR       
  2, wa02C0303     OPAQ  VERT  ext_wall     EXTERIOR       
  3, wa03C0303     OPAQ  VERT  ext_wall     EXTERIOR       
  4, wa04C0303     OPAQ  VERT  ext_wall     EXTERIOR       
  5, wa05C0303     OPAQ  VERT  intern_wall  L2Z6FrontAttic 
  6, fl01C0303     OPAQ  FLOR  floors       L2Z2CoreMain   
  7, ce01C0303     OPAQ  CEIL  floors_r     L3Z4CoreAttic  
  8, wi01C0303     TRAN  VERT  window       EXTERIOR       
  9, wi02C0303     TRAN  VERT  window       EXTERIOR       
 10, wi03C0303     TRAN  VERT  window       EXTERIOR       
 11, wi04C0303     TRAN  VERT  window       EXTERIOR       
# base
6   0   0   0   0   0   96.00    
