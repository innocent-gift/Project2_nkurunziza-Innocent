# Advanced C Systems Programming Portfolio

This repository contains a collection of three high-performance C console applications designed to demonstrate mastery over advanced low-level programming concepts. The projects systematically implement complex pointer architectures, runtime dynamic memory management, and event-driven design patterns.

---

## 📂 Project Modules Overview

1. **Project 1: Dynamic Student Record Engine** (Data Processing & Custom Analytics)
2. **Project 2: Adaptive Text Intelligence Tool** (String Tokenization & Memory Mapping)
3. **Project 3: Callback-Based Device Monitoring Simulator** (Unions, Hardware Simulation & Hooks)

---

## 📊 Project 1: Dynamic Student Record Engine

A runtime management system that dynamically tracks, scales, and evaluates academic profiles using dynamic arrays and mathematical dispersion logic.

### Architectural Highlights & Specs
* **Dynamic Sizing:** Scales heap allocation boundaries seamlessly using `realloc()` whenever a new record is added.
* **Pointer Traversal:** Bypasses regular array indexing (`arr[i]`) entirely, navigating records exclusively via address increments (`ptr++`).
* **Statistical Engine:** Evaluates dataset variance to calculate data spreads.
* **Header Signature Requirement:** Prints Student ID and active custom analysis metrics within the main runtime menu.

### Data Layout
```c
typedef struct {
    int id;
    char name[50];
    float grade;
} Student;
