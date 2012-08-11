# geometry of L2Z5FrontMudroom defined in: user/2StoreyGarage/zones/L2Z5FrontMudroom.geo
GEN  L2Z5FrontMudroom  HOT3000 generated zone  # type, name, descr
      24       10 0.000    # vertices, surfaces, rotation angle
#   X co-ord, Y co-ord, Z co-ord
    4.75000  3.05000  100.60001   # vert 1  
    4.75000  1.05000  100.60001   # vert 2  
    4.75000  1.05000  103.22000   # vert 3  
    4.75000  3.05000  103.22000   # vert 4  
    4.75000  1.78667  101.50000   # vert 5  
    4.75000  1.78667  102.70000   # vert 6  
    4.75000  1.35001  102.70000   # vert 7  
    4.75000  1.35001  101.50000   # vert 8  
    7.25000  3.05000  100.60001   # vert 9  
    7.25000  3.05000  103.22000   # vert 10 
    7.25000  1.05000  100.60001   # vert 11 
    7.25000  1.05000  103.22000   # vert 12 
    7.25000  2.31334  101.50000   # vert 13 
    7.25000  2.31334  102.70000   # vert 14 
    7.25000  2.75000  102.70000   # vert 15 
    7.25000  2.75000  101.50000   # vert 16 
    5.05000  1.05000  100.60001   # vert 17 
    5.05000  1.05000  102.70000   # vert 18 
    5.95000  1.05000  102.70000   # vert 19 
    5.95000  1.05000  100.60001   # vert 20 
    6.40417  1.05000  101.50000   # vert 21 
    6.40417  1.05000  102.70000   # vert 22 
    6.95000  1.05000  102.70000   # vert 23 
    6.95000  1.05000  101.50000   # vert 24 
# no of vertices followed by list of associated vert
  11,   1,   2,   3,   4,   1,   5,   6,   7,   8,   5,   1,
   4,   9,   1,   4,  10,
  11,  11,   9,  10,  12,  11,  13,  14,  15,  16,  13,  11,
  15,   2,  17,  18,  19,  20,  11,  12,   3,   2,  21,  22,  23,  24,  21,   2,
   4,   2,   1,   9,  11,
   4,   3,  12,  10,   4,
   4,   5,   8,   7,   6,
   4,  13,  16,  15,  14,
   4,  17,  20,  19,  18,
   4,  21,  24,  23,  22,
# unused index
 0   0   0   0   0   0   0   0   0   0  
# surfaces indentation (m)
0.000 0.000 0.000 0.000 0.000 0.000 0.000 0.000 0.000 0.000 
    3    0    0    0  # default insolation distribution
# surface attributes follow: 
# id surface       geom  loc/   mlc db      environment
# no name          type  posn   name        other side
  1, wa01F0205     OPAQ  VERT  ext_wall     EXTERIOR       
  2, wa02F0205     OPAQ  VERT  intern_wall  L2Z2CoreMain   
  3, wa03F0205     OPAQ  VERT  ext_wall     EXTERIOR       
  4, wa04F0205     OPAQ  VERT  ext_wall     EXTERIOR       
  5, fl01F0205     OPAQ  FLOR  floors       EXTERIOR       
  6, ce01F0205     OPAQ  CEIL  floors_r     L2Z6FrontAttic 
  7, wi01F0205     TRAN  VERT  window       EXTERIOR       
  8, wi02F0205     TRAN  VERT  window       EXTERIOR       
  9, do01F0205     OPAQ  VERT  ext_door     EXTERIOR       
 10, wi03F0205     TRAN  VERT  window       EXTERIOR       
# base
5   0   0   0   0   0   5.00     
