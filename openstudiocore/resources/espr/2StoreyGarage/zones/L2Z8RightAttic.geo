# geometry of L2Z8RightAttic defined in: user/2StoreyGarage/zones/L2Z8RightAttic.geo
GEN  L2Z8RightAttic  HOT3000 generated zone  # type, name, descr
       7        5 0.000    # vertices, surfaces, rotation angle
#   X co-ord, Y co-ord, Z co-ord
    18.10000  0.00000  103.22000   # vert 1  
    18.10000  6.10000  103.22000   # vert 2  
    18.10000  3.05000  104.23656   # vert 3  
    12.00000  6.10000  103.22000   # vert 4  
    12.00000  3.05000  103.22000   # vert 5  
    12.00000  0.00000  103.22000   # vert 6  
    12.00000  3.05000  104.23656   # vert 7  
# no of vertices followed by list of associated vert
   3,   1,   2,   3,
   4,   4,   5,   6,   7,
   5,   6,   5,   4,   2,   1,
   4,   6,   1,   3,   7,
   4,   2,   4,   7,   3,
# unused index
 0   0   0   0   0  
# surfaces indentation (m)
0.000 0.000 0.000 0.000 0.000 
    3    0    0    0  # default insolation distribution
# surface attributes follow: 
# id surface       geom  loc/   mlc db      environment
# no name          type  posn   name        other side
  1, wa01R0208     OPAQ  VERT  ext_wall     EXTERIOR       
  2, wa02R0208     OPAQ  VERT  ext_wall     EXTERIOR       
  3, fl01R0208     OPAQ  FLOR  floors       L2Z7RightGarage
  4, ce01R0208     OPAQ  SLOP  asphalt      EXTERIOR       
  5, ce02R0208     OPAQ  SLOP  asphalt      EXTERIOR       
# base
3   0   0   0   0   0   37.21    
