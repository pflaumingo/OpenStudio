# geometry of L1Z1CoreBasement defined in: user/2StoreyGarage/zones/L1Z1CoreBasement.geo
GEN  L1Z1CoreBasement  HOT3000 generated zone  # type, name, descr
      11        6 0.000    # vertices, surfaces, rotation angle
#   X co-ord, Y co-ord, Z co-ord
    0.00000  11.05000  98.51000   # vert 1  
    0.00000  3.05000  98.51000   # vert 2  
    0.00000  3.05000  100.60001   # vert 3  
    0.00000  11.05000  100.60001   # vert 4  
    12.00000  11.05000  98.51000   # vert 5  
    12.00000  11.05000  100.60001   # vert 6  
    12.00000  3.05000  98.51000   # vert 7  
    12.00000  6.10000  100.60001   # vert 8  
    12.00000  3.05000  100.60001   # vert 9  
    7.25000  3.05000  100.60001   # vert 10 
    4.75000  3.05000  100.60001   # vert 11 
# no of vertices followed by list of associated vert
   4,   1,   2,   3,   4,
   4,   5,   1,   4,   6,
   5,   7,   5,   6,   8,   9,
   6,   2,   7,   9,  10,  11,   3,
   4,   2,   1,   5,   7,
   7,   3,  11,  10,   9,   8,   6,   4,
# unused index
 0   0   0   0   0   0  
# surfaces indentation (m)
0.000 0.000 0.000 0.000 0.000 0.000 
    3    0    0    0  # default insolation distribution
# surface attributes follow: 
# id surface       geom  loc/   mlc db      environment
# no name          type  posn   name        other side
  1, wa01C0101     OPAQ  VERT  foundation   BASESIMP       
  2, wa02C0101     OPAQ  VERT  foundation   BASESIMP       
  3, wa03C0101     OPAQ  VERT  foundation   BASESIMP       
  4, wa04C0101     OPAQ  VERT  foundation   BASESIMP       
  5, fl01C0101     OPAQ  FLOR  fnd_floor    BASESIMP       
  6, ce01C0101     OPAQ  CEIL  floors_r     L2Z2CoreMain   
# base
5   0   0   0   0   0   96.00    
