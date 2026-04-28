# Moving Ball Simulation

A real-time kinematics simulation built with **C++17** and **SFML 3.1.0**, exploring vector-based physics and 2D collision detection.

## Features

- **Kinematics engine** *(in progress)* — velocity and acceleration integration using `position += velocity * dt`
- **Gravity simulation** *(in progress)* — `velocity.y += gravity * dt` applied per frame
- **Collision detection** *(in progress)* — velocity sign flip on wall/floor contact with energy restitution

---

## Tech Stack

| Tool | Purpose |
|---|---|
| C++17 | Core language |
| SFML 3.1.0 | 2D rendering and window management |
| CMake 3.22+ | Cross-platform build system |
| Static linking | Self-contained executable, no DLL dependencies |

---

## Building

SFML 3.1.0 is required. Download from [sfml-dev.org](https://sfml-dev.org/download) and place the extracted folder in the project root as `SFML/`.

```bash
git clone https://github.com/richardleong/moving-ball-simulation.git
cd moving-ball-simulation
mkdir build && cd build
cmake ..
cmake --build .
```

## Project Structure

```
moving-ball-simulation/
├── CMakeLists.txt
├── src/
│   └── main.cpp
└── README.md
```

---

## Roadmap

- [x] Project setup — CMake + SFML 3.1.0 static linking
- [x] Layer 1: Static ball rendered on screen
- [x] Layer 2: Game loop with delta time
- [x] Layer 3: Ball class (position, velocity, radius)
- [x] Layer 4: Movement — `position += velocity * dt`
- [x] Layer 5: Bouncing — velocity flip on collision
- [X] Layer 6: Restitution, multiple balls, air drag
