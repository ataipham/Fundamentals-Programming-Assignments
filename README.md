# Sherlock: A Study in Pink (C++ OOP Simulation)

A strategic simulation game inspired by the BBC series *Sherlock*, developed in C++. This project demonstrates advanced Object-Oriented Programming principles, complex movement algorithms, and dynamic memory management to simulate a chase between detectives and a criminal in a trap-filled maze.

## 🔎 Project Overview

In this simulation, **Sherlock Holmes** and **Dr. Watson** attempt to catch a **Criminal** on a 2D grid map. The map is populated with walls, fake walls, and various types of robots spawned by the Criminal to impede the detectives.

The project focuses on the robust application of **Object-Oriented Programming (OOP)** concepts, specifically:
* **Polymorphism:** Handling diverse moving objects (Characters, Robots) and map elements uniformly.
* **Inheritance:** Hierarchical structure for Characters, Items, and Robots sharing common behaviors.
* **Encapsulation:** Managing complex game states (Health, Experience, Inventory) securely within classes.
* **Abstraction:** Using abstract base classes for generic game entities.

## ⚙️ Key Features

### 1. Complex Map System
The game world is a grid `(R x C)` containing different element types:
* **Path:** Standard walkable tile.
* **Wall:** Impassable obstacle.
* **Fake Wall:** A special wall that only certain characters can pass through based on their Experience Points (EXP).

### 2. Intelligent Moving Objects
* **Sherlock & Watson:** Move according to a predefined rule string (e.g., "RUU" - Right, Up, Up). They manage stats like **HP** (Health) and **EXP** (Experience).
* **The Criminal:** Uses a pathfinding logic to move to the valid adjacent tile that maximizes the **Manhattan Distance** from both Sherlock and Watson to evade capture.
* **Robots:** Spawned by the Criminal every 3 steps. They have distinct behaviors:
    * **RobotC:** Follows the Criminal's trail.
    * **RobotS:** Chases Sherlock (shortest path).
    * **RobotW:** Chases Watson (shortest path).
    * **RobotSW:** Chases both, aiming for the "optimal" intercept point.

### 3. Inventory & Item System (Linked Lists)
Sherlock and Watson possess **Bags** implemented as **Singly Linked Lists** to store items found during the chase.
* **Items:** *Magic Book* (XP Boost), *Energy Drink* (Heal), *First Aid* (Major Heal), *Exemption Card* (Avoid Penalty), *Passing Card* (Skip Challenge).
* **Smart Usage:** Characters automatically check their inventory to use the optimal item before or after encountering a Robot challenge.

## 🛠️ Technical Architecture

The project is structured around several core classes:

* **`MapElement`**: Base class for `Wall`, `Path`, `FakeWall`.
* **`MovingObject`**: Abstract base class for all entities.
    * **`Character`**: Base for `Sherlock`, `Watson`, `Criminal`.
    * **`Robot`**: Base for `RobotS`, `RobotW`, `RobotSW`, `RobotC`.
* **`BaseItem`**: Abstract base class for all consumable items.
* **`BaseBag`**: Linked List implementation for inventory management.
* **`StudyPinkProgram`**: The main game engine that orchestrates the game loop, collision detection, and win/loss conditions.

## 🚀 Installation & Build

### Prerequisites
* G++ Compiler (supporting C++11 standard)
* Make (Optional, but recommended)

### Compilation
Use the following command to compile the project:

```bash
g++ -o main main.cpp study_in_pink2.cpp -I . -std=c++11
```
🎮 Usage
1. Prepare a Configuration File: The game requires a config file (e.g., sa_tc_02_config) defining the map size, walls, starting positions, and movement rules. (See main.cpp for example format).

2. Run the Simulation:
```bash
./main
```
3. Sample Output
```plaintext
Step: 001 -- Sherlock[index=1;pos=(1,4);moving_rule=RUU] --|-- Watson[...] --|-- Criminal[...]
...
Sherlock caught the criminal
```

👤 Author
* Anh Tai Pham
* Role: Software Engineering Student
* University: The University of Queensland / HCMUT

## Acknowledgement
This README was written with the support of Gemini 3.0
