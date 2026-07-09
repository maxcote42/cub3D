*This project has been created as part of the 42 curriculum by sfeijoei, maxcote.*

# cub3D

## Description

**cub3D** is a graphical project from the 42 curriculum inspired by the classic game **Wolfenstein 3D**.

The goal of the project is to build a simple real-time 3D engine using the **raycasting** technique. Starting from a 2D map described in a `.cub` configuration file, the program renders a first-person view of a maze where the player can freely move and explore.

This project introduces several important concepts in computer graphics, including:

* Raycasting
* DDA (Digital Differential Analyzer) algorithm
* Perspective projection
* Texture mapping
* Event handling
* Real-time rendering with MiniLibX

---

## Features

### Bonus

* Interactive minimap
* Doors that can be opened and closed
* Animated sprites
* Mouse-controlled camera rotation

---

## Instructions

### Requirements

This project requires the latest Linux version of **MiniLibX** available on GitHub.

### Compilation

```bash
make
```

Build the bonus version:

```bash
make bonus
```

Useful Makefile targets:

```bash
make
make bonus
make clean
make fclean
make re
make re-bonus
```

### Execution

```bash
./cub3D maps/example.cub
```

---

## Controls

| Key   | Action                     |
| ----- | -------------------------- |
| W     | Move forward               |
| S     | Move backward              |
| A     | Strafe left                |
| D     | Strafe right               |
| ←     | Rotate left                |
| →     | Rotate right               |
| Mouse | Rotate camera (Bonus)      |
| SPACE | Open / Close doors (Bonus) |
| ESC   | Exit the game              |

---

## Map Format

The program expects a scene description file with the `.cub` extension.

A valid file contains:

* Four wall textures paths:

  * `NO`
  * `SO`
  * `WE`
  * `EA`
* Floor color (`F`)
* Ceiling color (`C`)
* A map

Example:

```text
NO textures/north.xpm
SO textures/south.xpm
WE textures/west.xpm
EA textures/east.xpm

F 220,100,0
C 225,30,0

111111
100001
100001
10N001
100001
111111
```

Map symbols:

| Character | Meaning                                   |
| --------- | ----------------------------------------- |
| 1         | Wall                                      |
| 0         | Empty space                               |
| 2         | Door (Bonus)                              |
| N         | Player spawn facing North                 |
| S         | Player spawn facing South                 |
| E         | Player spawn facing East                  |
| W         | Player spawn facing West                  |
| Space     | Empty/outside area handled during parsing |

The parser verifies that:

* the map is completely enclosed by walls,
* exactly one player spawn exists,
* every required texture and color is provided,
* invalid configurations produce a descriptive error message.

For practical reasons, the maximum supported map size is **500 × 500** cells.

---

## Technical Overview

The rendering engine works by casting one ray for every vertical column of the screen.

For each ray:

1. Compute its direction according to the player's field of view.
2. Traverse the map using the **DDA algorithm** until a wall (or door) is reached.
3. Compute the perpendicular distance to avoid the fish-eye effect.
4. Calculate the projected wall height.
5. Determine the correct texture and texture coordinates.
6. Render the textured wall column.

## Resources

The following resources were especially helpful while implementing the raycasting engine:

* https://lodev.org/cgtutor/raycasting.html
* https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/
* https://www.youtube.com/watch?v=gYRrGTC7GtA
* https://www.youtube.com/watch?v=pzXOgXmO3Tw
* https://www.youtube.com/watch?v=G9i78WoBBIU
* https://www.youtube.com/watch?v=w0Bm4IA-Ii8
* https://www.youtube.com/watch?v=NbSee-XM7WA

Our previous **FdF** and **so_long** projects also provided valuable experience with MiniLibX and graphics programming.

### Use of AI

AI tools were used as development assistants, primarily to:

* review mathematical formulas used in the DDA algorithm,
* verify raycasting and distance calculations,
* clarify texture coordinate mapping,
* improve code documentation,
* proofread and improve the English wording of this README.

AI was used only as a supporting tool. The project design, implementation, debugging, and validation were completed by the authors.

We also benefited from discussions with fellow 42 students working on cub3D, which helped us better understand several implementation details.
