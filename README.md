# Barnes-Hut Quadtree N-Body Simulation (C++)

A high-performance C++ project implementing an N-body physics simulation using a quadtree with Barnes–Hut optimizations. Designed to efficiently simulate thousands or tens of thousands of particles interacting under gravitational forces.

---

## Overview

This project demonstrates the use of hierarchical spatial partitioning to accelerate N-body force calculations. By grouping distant particles and approximating their collective effect, the Barnes–Hut algorithm reduces computational complexity from O(N²) to approximately O(N log N), enabling large-scale simulations that would otherwise be infeasible.

---

## Features

* Quadtree-based spatial subdivision for efficient force calculations.
* Barnes–Hut approximation with configurable opening angle (θ).
* Gravitational softening to prevent singularities.
* Optional OpenGL visualization for real-time display.

---

## Requirements

* C++17 or newer
* SDL2
---
## Performance

* Computational complexity: O(N log N)
* Scales well with thousands to tens of thousands of particles

---

## Visualization

The optional visualization module provides a real-time graphical view of the simulation. It can display particle motion, quadtree partitions, and center-of-mass markers. Controls may include pause/resume, zoom, and real-time parameter adjustments.

---

## References

* Barnes, J., & Hut, P. (1986). *A Hierarchical O(N log N) Force-Calculation Algorithm*.
* Additional open-source N-body simulation projects for reference and benchmarking.
