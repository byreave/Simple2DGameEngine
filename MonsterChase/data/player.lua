Player = 
{
   name = "Byreave",
   initial_lives = 3,
   initial_position = { 100.0, 150.0 },
   
   physics_settings = {
      mass = 1.0,
      drag = 0.2
   },

   render_settings = {
      sprite = { 
         offset = { 0.0, 0.0 },
         -- left, top, right, bottom
         extents = { -1.0, -1.0, 1.0, 1.0 }
      },
      sprite_color = { 255, 255, 255, 255 }
   }
}
