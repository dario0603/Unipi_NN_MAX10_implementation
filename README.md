# Handwritten Character Recognition on Intel MAX 10 FPGA

<p align="center">
  <img src="https://img.shields.io/badge/FPGA-Intel%20MAX%2010-0071C5?style=for-the-badge&logo=intel&logoColor=white" alt="Intel MAX 10 FPGA">
  <img src="https://img.shields.io/badge/EDA-Quartus%20Prime-0071C5?style=for-the-badge&logo=intel&logoColor=white" alt="Quartus Prime">
  <img src="https://img.shields.io/badge/IDE-Eclipse-2C2255?style=for-the-badge&logo=eclipseide&logoColor=white" alt="Eclipse IDE">
  <img src="https://img.shields.io/badge/ML-PyTorch-EE4C2C?style=for-the-badge&logo=pytorch&logoColor=white" alt="PyTorch">
  <img src="https://img.shields.io/badge/Language-C%20%2F%20C%2B%2B-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C and C++">
</p>

Academic project at the **University of Pisa** focused on deploying and optimizing a neural network for handwritten character recognition on an embedded FPGA platform.

The project combines neural network training, embedded software optimization, and hardware/software co-design using an **Intel MAX 10 FPGA** and a **Nios II soft-core processor**.

By exploring alternative hardware architectures, compiler optimizations, and hardware-accelerated multiplication, inference time was reduced from **6.0 s to 0.5 s**, achieving a **12× speedup**.

## Overview

- **Neural network:** Three-layer fully connected multilayer perceptron (MLP)
- **Training framework:** PyTorch
- **FPGA platform:** Intel MAX 10
- **Processor:** Nios II soft-core
- **Hardware design:** Quartus Prime
- **Embedded development:** Eclipse, C/C++
- **Final inference time:** 0.5 s
- **Speedup:** 12× relative to the baseline implementation

## System Architecture

### 1. Neural Network Training

The neural network was trained offline using PyTorch.

- Trained a three-layer fully connected MLP for handwritten character recognition.
- Extracted trained weights and biases for embedded deployment.
- Prepared and quantized model parameters for execution on the target platform.

### 2. FPGA Hardware/Software Co-Design

The embedded inference pipeline was deployed on a Nios II processor implemented on the Intel MAX 10 FPGA.

- Configured the processor system using Quartus Prime and the associated system integration tools.
- Explored alternative hardware architectures for computationally intensive operations.
- Integrated hardware multiplication support to accelerate neural network computations.
- Developed and optimized the embedded C/C++ inference software.

### 3. Performance Optimization

Compiler-level and hardware-level optimizations were explored to reduce inference latency.

- **Compiler optimization:** Target-specific GCC options, including `-O3` and loop unrolling.
- **Hardware acceleration:** Dedicated multiplier hardware and an optimized computational architecture.
- **Performance evaluation:** Compared inference execution time against the baseline implementation.

## Performance Results

Inference performance was evaluated under four configurations to assess the individual and combined impact of compiler optimizations and hardware-accelerated floating-point operations.

| Configuration | Inference Time | Speedup |
|---|---:|---:|
| No hardware acceleration, no compiler optimization | 6.101 s | 1.00× |
| No hardware acceleration, with compiler optimization | 3.150 s | 1.94× |
| With hardware acceleration, no compiler optimization | 2.089 s | 2.92× |
| With hardware acceleration and compiler optimization | **0.509 s** | **11.99×** |

The results demonstrate that both software and hardware optimizations contribute significantly to inference performance. Compiler optimizations alone reduced inference time by approximately **48.4%**, while hardware acceleration alone reduced it by approximately **65.8%** compared with the baseline.

Combining both techniques achieved the best result, reducing inference time by approximately **91.7%** — from 6.101 s to 0.509 s — corresponding to an approximately **12× speedup**.
