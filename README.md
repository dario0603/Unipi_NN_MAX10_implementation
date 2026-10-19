# Handwritten Character Recognition on Intel MAX10 FPGA

[![FPGA](https://img.shields.io/badge/FPGA-Intel%20MAX%2010-0071C5?style=flat&logo=intel&logoColor=white)](https://www.intel.com)
[![Tools](https://img.shields.io/badge/EDA-Quartus%20Prime%20%7C%20Eclipse-00599C)](https://www.intel.com)
[![Framework](https://img.shields.io/badge/Framework-PyTorch-EE4C2C?logo=pytorch&logoColor=white)](https://pytorch.org)
[![Language](https://img.shields.io/badge/Language-C%20%7C%20C%2B%2B%2B%2B-00599C?logo=cplusplus)](https://isocpp.org)

Academic project for the **University of Pisa** focused on implementing and optimizing a neural network for handwritten character recognition on an embedded FPGA platform.

---

## 📌 Project Overview

This project implements an end-to-end pipeline for handwritten digit/character recognition deployed on an **Intel MAX10 FPGA**. A three-layer fully connected Neural Network (MLP) was designed and trained off-target using PyTorch, then deployed on a Nios II soft-core processor.

By exploring hardware architectures, custom compiler optimizations, and hardware-accelerated multiplication, the inference time was drastically reduced from **6.0s down to 0.5s** (**12x speedup**).

---

## ⚡ Performance Optimization & Results

| Optimization Stage | Inference Time | Speedup Factor | Key Improvements |
| :--- | :---: | :---: | :--- |
| **Baseline Implementation** | **6.0 s** | 1.0x | Standard C software execution on Nios II |
| **Compiler Optimizations** | — | — | Target-specific gcc flag tuning (`-O3`, loop unrolling) |
| **Hardware Acceleration** | **0.5 s** | **12.0x** | Hardware multiplier integration & tailored architecture |

---

## 🛠️ System Architecture

1. **Training Phase (PyTorch):**
   - Trained a 3-layer fully connected neural network (MLP) on character recognition datasets.
   - Extracted, quantized, and formatted weight/bias matrices for embedded deployment.

2. **Hardware/Software Co-Design (Quartus & Eclipse):**
   - Configured Nios II soft-core processor on the **Intel MAX10 FPGA**.
   - Integrated dedicated hardware multiplier modules for matrix operations.
   - Optimized embedded C/C++ runtime execution.

---

## 📁 Repository Structure

```text
.
├── hw/             # Quartus Prime project files, Qsys/Platform Designer system definitions
├── sw/             # Eclipse C/C++ source code for Nios II execution
├── model/          # PyTorch training scripts, weight extraction, and quantization routines
└── README.md
