# geometry of L2Z6FrontAttic defined in: user/2StoreyGarage/zones/L2Z6FrontAttic.geo
GEN  L2Z6FrontAttic  HOT3000 generated zone  # type, name, descr
       6        5 0.000    # vertices, surfaces, rotation angle
#   X co-ord, Y co-ord, Z co-ord
    4.75000  1.05000  103.22000   # vert 1  
    7.25000  1.05000  103.22000   # vert 2  
    6.00000  1.05000  103.63663   # vert 3  
    7.25000  3.05000  103.22000   # vert 4  
    4.75000  3.05000  103.22000   # vert 5  
    6.00000  3.05000  103.63663   # vert 6  
# no of vertices followed by list of associated vert
   3,   1,   2,   3,
   3,   4,   5,   6,
   4,   1,   5,   4,   2,
   4,   2,   4,   6,   3,
   4,   5,   1,   3,   6,
# unused index
 0   0   0   0   0  
# surfaces indentation (m)
0.000 0.000 0.000 0.000 0.000 
    3    0    0    0  # default insolation distribution
# surface attributes follow: 
# id surface       geom  loc/   mlc db      environment
# no name          type  posn   name        other side
  1, wa01F0206     OPAQ  VERT  ext_wall     EXTERIOR       
  2, wa02F0206     OPAQ  VERT  intern_wall  L3Z3CoreMain   
  3, fl01F0206     OPAQ  FLOR  floors       L2Z5FrontMudroom
  4, ce01F0206     OPAQ  SLOP  asphalt      EXTERIOR       
  5, ce02F0206     OPAQ  SLOP  asphalt      EXTERIOR       
# base
3   0   0   0   0   0   5.00     
