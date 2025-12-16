# Lumen

> A C++ simulation and rendering engine exploring light, physics, and real-time systems.

![Ray Tracing Demo](ray_tracer.gif)
---

## Overview

**Lumen** is a ground-up C++ project focused on understanding how light, motion, and simulation work at their most fundamental level.

The project currently implements a real-time **2D ray casting system** using **SDL2**, featuring a movable light source, dynamic shadow casting, and animated obstacles. Lumen is designed as a long-term learning and experimentation platform that will gradually evolve into a full simulation engine.

Rather than relying on high-level frameworks, Lumen emphasizes **low-level control**, **clear math**, and **deterministic systems**.

---

## Current Features

- **Mouse-controlled light source**
  - Rays originate from a point light that follows mouse movement
-  **Real-time shadow casting**
   - Rays terminate on obstacle collision or screen bounds
-  **Animated obstacles**
   - Circular objects move dynamically over time
-  **Ray marching**
   - Rays advance step-by-step using trigonometry
-  **Software rendering**
   - Pixel-level rendering using SDL surfaces

---

##  How It Works

- Rays are generated uniformly in **360°** around the light source
- Each ray:
  - Steps forward using `cos(angle)` and `sin(angle)`
  - Draws pixels incrementally
  - Stops when it:
    - Intersects an obstacle (circle collision)
    - Exits the screen
- Shadows emerge naturally as blocked rays stop propagating

---

##  Tech Stack

- **Language:** C++
- **Library:** SDL2
- **Rendering:** Software (pixel-by-pixel)
- **Math:** Trigonometry, distance checks, ray marching

---

##  Inspiration

Lumen is inspired by creators and educators who focus on building systems from first principles:

- **Daniel Hirsch** — ray casting & graphics fundamentals  
- **AngeTheGreat** — simulation-driven engine design  
- **Pezzza** — creative coding & visual experimentation  

---

## Roadmap

Lumen is intended to grow into a broader simulation engine. Planned explorations include:

- Gravity & rigid body dynamics
- Fluid simulation
- Smoke & particle systems
- Cloth simulation
- Engine architecture inspired by AngeTheGreat & Pezzza
- Transition from simple ray casting to complex simulations

---

##  Build & Run

### Requirements
- SDL2
- MinGW / g++

### Compile
```bash
g++ ray_tracing.cpp -o lumen \
  -I C:/MinGW/include \
  -L C:/MinGW/lib \
  -lmingw32 -lSDL2main -lSDL2 -lm
