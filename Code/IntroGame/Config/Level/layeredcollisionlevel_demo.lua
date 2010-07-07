Ground = {
  def = "ground_actor",
  position = {0, -11},
  tag = "spawned",
  layer = "foreground",
}

Bouncy = {
  def = "physics_event_actor",
  position = {0, 8},
  layer = "foreground",
  tag = "spawned",
}

Hud = {
  def = "simple_actor",
  size = 3,
  position = {0, 1},
  alpha = 1.0,
  layer = "hud",
  color = {0, 0, 1},
  tag = "spawned",
}

WayInBack = {
  def = "simple_actor",
  color = {1, 1, 0},
  size = 3,
  position = {0, -3},
  alpha = 1.0,
  layer = "background",
  tag = "spawned",
}
