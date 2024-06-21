# cub3D-labyrinth-explorer
Raycasting labyrinth exploration project with wall textures

Wolfenstein-inspired raycasting project in C using the miniLibX graphic library.

maps/*.cub files contain: 
- File path to wall texture pngs (N/S/E/W)
- Floor and ceiling colour settings (F/C in RGB)
- Map inputs (1 = wall, 0 == space, N/S/E/W is player start position and orientation)
 
Map must be closed to be playable (all possible player positions must be surrounded by walls).
Left/right arrows rotate player field-of-view, WASD moves the player.

Implemented:
- Wall collisions
- Dynamic window resizing
- Minimap with player position
