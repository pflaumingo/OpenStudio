# geometry of L3Z4CoreAttic defined in: user/2StoreyGarage/zones/L3Z4CoreAttic.geo
GEN  L3Z4CoreAttic  HOT3000 generated zone  # type, name, descr
       9        5 0.000    # vertices, surfaces, rotation angle
#   X co-ord, Y co-ord, Z co-ord
    12.00000  3.05000  105.84000   # vert 1  
    12.00000  6.10000  105.84000   # vert 2  
    12.00000  11.05000  105.84000   # vert 3  
    12.00000  7.05000  107.17320   # vert 4  
    0.00000  11.05000  105.84000   # vert 5  
    0.00000  3.05000  105.84000   # vert 6  
    0.00000  7.05000  107.17320   # vert 7  
    7.25000  3.05000  105.84000   # vert 8  
    4.75000  3.05000  105.84000   # vert 9  
# no of vertices followed by list of associated vert
   4,   1,   2,   3,   4,
   3,   5,   6,   7,
   7,   6,   5,   3,   2,   1,   8,   9,
   6,   6,   9,   8,   1,   4,   7,
   4,   3,   5,   7,   4,
# unused index
 0   0   0   0   0  
# surfaces indentation (m)
0.000 0.000 0.000 0.000 0.000 
    3    0    0    0  # default insolation distribution
# surface attributes follow: 
# id surface       geom  loc/   mlc db      environment
# no name          type  posn   name        other side
  1, wa01C0304     OPAQ  VERT  ext_wall     EXTERIOR       
  2, wa02C0304     OPAQ  VERT  ext_wall     EXTERIOR       
  3, fl01C0304     OPAQ  FLOR  floors       L3Z3CoreMain   
  4, ce01C0304     OPAQ  SLOP  asphalt      EXTERIOR       
  5, ce02C0304     OPAQ  SLOP  asphalt      EXTERIOR       
# base
3   0   0   0   0   0   96.00    
