# BlackSpace

A 2D space rescue game built in **C++17 with raylib**. Pilot a rescue ship through drifting asteroids, reach stranded crews, and bring everyone home across three missions.

The project was developed for **Game Engineering Principles at Sheridan College**. It combines an arcade rescue loop with object-oriented game entities, collision detection, resource management, and a custom linked-list mission log.

## The mission

Each mission places three stranded crews and eight drifting asteroids in the playfield. Moving consumes fuel; asteroid contact drains both health and fuel. Get close to an SOS beacon and press Space to rescue its crew, earn 100 points, and recover 12 fuel.

Rescue every crew to complete a mission. Each completion awards 300 points plus a time bonus of up to 200. Health and fuel reset between missions; your score carries forward. Complete all three missions to win.

## Controls

| Key | Action |
| --- | --- |
| WASD / arrow keys | Move |
| Space | Rescue a nearby crew |
| Enter | Start / continue / return after a result |
| Esc | Pause / resume |
| M while paused | Return to the menu |
| F | Toggle fullscreen |

Close the window to quit. The game renders at 1280 × 720 and scales with the window while preserving its aspect ratio.

## Build and run

### CMake (macOS, Linux, Windows)

Requires a C++17 compiler, CMake 3.20 or newer, and Git. CMake uses an installed raylib 5.5 package when available; otherwise it downloads raylib's pinned 5.5 release on the first configuration.

```sh
git clone https://github.com/Shrustiii/blackSpace.git
cd blackSpace
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

On macOS and Linux, run `./build/blackspace`. With a multi-configuration Windows generator, run `build\Release\blackspace.exe`.

For Ubuntu/Debian, install the desktop dependencies before configuring:

```sh
sudo apt-get install build-essential cmake git libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libxcursor-dev libxinerama-dev
```

If using these X11 dependencies, add `-DGLFW_BUILD_WAYLAND=OFF` to the CMake configure command.

### Quick build on macOS

With Homebrew installed:

```sh
brew install raylib pkg-config
make
make run
```

The Makefile also works on Linux with raylib and pkg-config installed. No external image, font, or audio assets are needed.

## Code architecture

| Component | Responsibility |
| --- | --- |
| `GameController` | State transitions, mission generation, scoring, collisions, and rescue interactions |
| `GameObject` | Abstract base class with position, radius, and virtual update/draw methods |
| `PlayerShip` | Normalized movement, heading, fuel, health, and ship rendering |
| `Obstacle` | Asteroid drift and boundary reflection |
| `RescueTarget` | Animated SOS beacons and rescued state |
| `HUD` | Mission status and resource bars |
| `MissionLog` | Owned singly linked list retaining the latest six events; the HUD shows the latest three |
| `CollisionHelper` | Reusable circle/circle and circle/rectangle checks |
| `Constants.h` | Gameplay tuning and logical screen dimensions |

The state machine covers menu, playing, paused, level complete, victory, and failure. Updates use elapsed time for movement and resource consumption; frame time is capped to limit jumps after a stall. Rendering uses a fixed-size texture so resizing and fullscreen keep the HUD and collision space aligned.

## Project scope and credits

BlackSpace is a small coursework prototype prepared for a portfolio. Missions use randomized layouts with the same rules and difficulty; there is no save system or audio. The original space rescue concept and gameplay balance are preserved.

Maintained by [Shrusti Shah](https://github.com/Shrustiii). This project originated as group coursework; repository authorship should not be interpreted as sole authorship of the original assignment.

Built with [raylib](https://www.raylib.com/), by Ramon Santamaria and contributors. Game visuals are drawn directly with raylib primitives.
