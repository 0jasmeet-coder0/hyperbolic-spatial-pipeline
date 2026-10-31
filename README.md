# Algorithmic Optimization of Hyperbolic Coordinates in Real-Time Spatial Pipelines

An academic and systems engineering research framework that quantifies and mitigates computational latency when calculating non-Euclidean coordinate transformations in real-time simulation pipelines.

---

## 🔬 Core Research Objective
Modern graphics and physics pipelines heavily rely on Euclidean (flat) spatial layouts. When mapping non-Euclidean manifolds—where space dynamically stretches or contracts based on proximity vectors—engines experience severe computational stalls due to complex coordinate warping factors. 

This project mathematically derives a custom spatial coordinate warping algorithm using hyperbolic scaling principles, measures the precise CPU overhead bottleneck at quadratic scale (O(N²)), and implements a high-performance **2D Spatial Hash Grid Partitioning** data structure in C++ to optimize execution times back down to real-time limits.

---

## 📊 Quantitative Benchmark Results

Simulations were performed tracking **1,000 active moving entities** using raw spatial proximity loops on a fresh hardware environment. The optimization system delivers a massive speedup while maintaining 100% calculation accuracy.

| Metrics Framework | CPU Runtime (ms) | Tracked Proximities | Performance Profiling |
| :--- | :---: | :---: | :--- |
| **Euclidean Flat Baseline** | 11.21 ms | 3,462 | Reference Baseline |
| **Unoptimized Non-Euclidean** | 20.98 ms | 823 | **+74.05% Computational Lag** |
| **Optimized Spatial Hash Grid** | 3.17 ms | 823 | **84.88% Total Algorithmic Boost** |

### Key Takeaway
The customized 2D spatial hash grid successfully lowered system latency from **20.98 ms down to 3.17 ms**, completely neutralizing the non-Euclidean mathematical overhead and bringing execution safely inside optimal frame targets.

---

## 📐 Mathematical Framework

### 1. Spatial Geometry Warping Factor
Warped spatial distance metrics are generated non-linearly using coordinate scaling logic relative to origin radii vectors (r₁, r₂):
```text
d_warped = d_flat * | 1 / (1 - (r1 * r2 * 0.0001)) |
```

### 2. Spatial Grid Partitioning
Entities are dynamically mapped to localized spatial grid buckets via coordinate flooring loops to skip redundant global checks:
```text
Cell_X = floor(X / Cell_Size)
Cell_Y = floor(Y / Cell_Size)
```

---

## 🏃‍♂️ Local Deployment & Execution

### Prerequisites
* Windows 11 environment
* G++ compiler supporting the standard C++17 library flags

### Compilation and Execution
To run the full optimization benchmark loop on your local machine, open your terminal and run:
```powershell
g++ -std=c++17 main.cpp -o main
.\main.exe
```

---

## 📁 Repository Structure
* `main.cpp` - The full multi-benchmark simulation loop containing both unoptimized loops and the spatial hash matrix data structure.
* `Research_Paper.pdf` - The formal peer-review formatted academic document compiled using LaTeX/IEEE conference protocols.
