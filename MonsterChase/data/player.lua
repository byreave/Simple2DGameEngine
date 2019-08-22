Player = 
{
   name = "Platform",
   initial_lives = 3,
   initial_position = { -0.0, -350.0 },
   initial_rotation = {0.0, 0.0, 0.0},
   
   physics_settings = {
      mass = 2.0,
      drag = 0.0,
      kinematic = true
   },

   render_settings = {
      sprite = "data\\BadGuy.dds"
   },

   collision_settings = {
      center = {0.0, 118.0},
      extents = {160.0, 118.0}
   },
   controller = "platform"
}
