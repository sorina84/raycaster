# Raycasting Engine (C + Raylib)

Final project: a simple raycasting (Wolfenstein 3D-style) engine implemented in pure C using Raylib (2D drawing only).

## Features
- 3D raycasting with DDA
- Player movement with collision + wall sliding
- Toggle between 3D play mode and 2D edit mode
- Map editor (mouse)
- Save/Load map

## Controls
- **W/A/S/D**: move (including strafing if implemented)
- **Arrow Left/Right**: rotate camera
- **M**: toggle 3D view / 2D edit mode
- **Edit mode**
  - Left click: add wall
  - Right click: remove wall
- **S**: save map
- **L**: load map

## Build (Windows)
This project requires **Raylib**.
Build command example (depending on your Raylib setup):
```bash
gcc main.c map.c player.c renderer.c -o raycaster.exe -std=c99 -Wall -Wextra -lraylib -lopengl32 -lgdi32 -lwinmm -lm