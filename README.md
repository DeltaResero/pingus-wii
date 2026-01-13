# Pingus

Pingus is a free and open source game that originally started in 1998 with the
simple goal of creating a Free (as in freedom) [Lemmings](
https://en.wikipedia.org/wiki/Lemmings_(video_game)) clone. Over the years
this has grown beyond its original scope to include original artwork and unique
gameplay features.

Just like *Lemmings*, the game is presented in a 2D side view and involves
taking command of a bunch of small animals to guide them through levels. As the
animals walk on their own, the goal of each level is to reach the exit by
issuing command actions to them.

While Pingus is based on the idea of *Lemmings*, it doesn't try to be an exact
clone. It includes a few ideas of its own such as the **Worldmap** and **Secret
Levels** and it also introduces new command actions such as the **Jumper**,
which were not present in the original game.

## Gameplay Mechanics

### Pingu Actions

To navigate the level, the player assigns specific actions to the Pingus. Some
actions are permanent, while others are temporary or one-time uses.

* **Basher:** Digs a horizontal tunnel until they hit steel or run out of 
  ground.
* **Blocker:** Stands still and reverses the direction of any other Pingu
  that touches them.
* **Bomber:** Explodes after a 5-second countdown, destroying the Pingu and
  surrounding terrain.
* **Bridger:** Builds a staircase at a 30-degree angle until they hit a
  ceiling or run out of bricks.
* **Climber:** Permanently allows a Pingu to scale vertical walls instead of
  turning around.
* **Digger:** Digs a vertical shaft straight down until they hit steel or fall
  into empty space.
* **Floater:** Deploys a propeller to glide gently down from heights,
  preventing death from falling.
* **Jumper:** Performs a high leap forward to clear small gaps or obstacles.
* **Miner:** Digs a diagonal tunnel downwards through the terrain.
* **Slider:** Slides on their belly for a short distance to pass through
  narrow tunnels.

### Pingu Behavior

Pingus are autonomous; they will walk forward until they hit an obstacle or are
given a command.

* **Walls:** If a Pingu hits a wall or a border higher than they can step
  (approx. 3 pixels), they will reverse direction.
* **Slopes:** Pingus can walk up slopes and over diagonal terrain.
* **Falling:** If a Pingu walks off a ledge, they begin to fall; if the fall
  is too high, they will not survive the impact.

## How to Build

This project uses the [CMake](https://cmake.org/) build system and depends on
[SDL](https://www.libsdl.org/) (1.2) along with `SDL_image` and `SDL_mixer`.

### Prerequisites

* CMake 3.10 or later
* C++20 compatible compiler (GCC/Clang)
* **Required Libraries:** SDL 1.2, SDL_image, SDL_mixer, libpng
* **Optional Libraries:** OpenGL

### Build Options

You can configure the build by passing `-DOPTION=ON/OFF` to cmake.

| Option           | Description                                    | Default |
|------------------|------------------------------------------------|---------|
| `WITH_EDITOR`    | Build with the level editor                    | `OFF`   |
| `WITH_OPENGL`    | Build with OpenGL support                      | `ON`    |
| `ENABLE_LOGGING` | Enable application logging                     | `OFF`   |
| `WARNINGS`       | Enable extra compiler warnings (-Wall -Wextra) | `ON`    |
| `WERROR`         | Treat compiler warnings as errors (-Werror)    | `OFF`   |
| `BUILD_TESTS`    | Build test programs                            | `OFF`   |

```bash
mkdir build
cd build
cmake ..
make
```

### Rendering Backends

Pingus supports multiple rendering backends which can be selected at runtime
using the `-r` or `--renderer` command line flags or via the options menu.

* **sdl:** A simple software renderer based on SDL. This is the default and
  safest option for compatibility.
* **opengl:** Uses hardware acceleration to render graphics. It is much faster
  than the SDL renderer and is recommended if your hardware supports OpenGL.
* **delta:** Uses SDL but attempts to optimize performance by only
  re-rendering screen elements that have changed. Some effects (like scrolling
  backgrounds) are disabled in this mode to maximize performance.

## Bug Reporting

This is a fork of the original Pingus project. **Please do not report bugs for
this version to the original Pingus developers.** This version deviates from the
original codebase and follows a different development philosophy.

Please report any bugs, crashes, or issues found in this fork via the **Issues**
tab on the GitHub repository page.

## Acknowledgments

This software is a fork of the original Pingus project created by Ingo Ruhnke.
For a detailed history and a full list of attributions, please see the
[AUTHORS](AUTHORS) file.

## Disclaimer

This fork is not affiliated with, endorsed by, nor sponsored by the original
authors of Pingus.

This program is distributed under the terms of the GNU General Public License
version 3 (or later). You can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation,
either version 3 of the License, or (at your option) any later version.

This project is distributed in the hope that it will be useful, but **WITHOUT
ANY WARRANTY**; without even the implied warranty of **MERCHANTABILITY** or
**FITNESS FOR A PARTICULAR PURPOSE**. See the [GNU General Public License](
https://www.gnu.org/licenses/gpl-3.0.html) for more details.
