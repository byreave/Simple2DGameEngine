Player = 
{
   name = "Ball",
   initial_lives = 3,
   initial_position = { 0.0, 100.0 },
   initial_rotation = {0.0, 0.0, 0.0},
   
   physics_settings = {
      mass = 1.0,
      drag = 0.00,
      kinematic = false
   },

   render_settings = {
      sprite = "data\\GoodGuy.dds"
   },

   collision_settings = {
      center = {0.0, 82.0},
      extents = {44.0, 82.0}
   },
   
   controller = "randommove"
}
