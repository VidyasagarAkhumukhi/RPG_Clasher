# RPG Clasher

RPG Clasher is a classic top-down 2D Action RPG demo built from the ground up in C++ using the Raylib library. It showcases a clean, object-oriented design for managing characters, enemies, and world objects. The game features a scrolling world camera that keeps the player centered, a simple but effective combat system, and animated characters.



![Dasher Gameplay](https://github.com/user-attachments/assets/fd005422-967b-4b4c-a935-b8993654cd38)


## 🎮 Gameplay & Controls

- **Objective**: Explore the world, fight the goblin and slime enemies, and survive for as long as you can.
- **Controls**:
    - **WASD**: Move the character around the world.
    - **Left Mouse Click**: Swing your sword to attack enemies.
- **UI**:
    - Health is displayed in the top-left corner.
    - "Game Over!" appears when your health reaches zero.

---

## ✨ Key Features

- **Scrolling World Camera**: The player remains centered while the world map and all objects move underneath for a smooth camera-following effect.
- **Object-Oriented Design**: Clean class-based architecture. `BaseCharacter` provides shared movement/animation for both `Character` (player) and `Enemy`.
- **Sprite Animation System**: Characters and enemies switch between idle and running animations based on movement state.
- **Simple Combat & AI**: Attack with a sword hitbox. Enemies chase the player and deal damage on contact.
- **Collision Detection**:
    - Player vs. static props (rocks, logs)
    - Player vs. world boundaries
    - Player's weapon vs. enemies
    - Enemies vs. player

---

## 📂 Project Structure

```
project_3_RPG_Clasher/
│
├── .vscode/              # VSCode editor settings
├── characters/           # Spritesheets for player and enemies
├── nature_tileset/       # World map and prop textures
│
├── .gitignore            # Git ignore file
├── Makefile              # Build instructions for the compiler
├── README.md             # This file
│
├── main.cpp              # Main game loop, initialization, and high-level logic
│
├── BaseCharacter.h/.cpp  # Base class for all characters (player/enemy)
├── Character.h/.cpp      # Player-specific class (input, weapon)
├── Enemy.h/.cpp          # Enemy-specific class (AI, targeting)
└── Prop.h/.cpp           # Class for static world objects (rocks, logs)
```

---

## 🛠️ Technical Deep Dive

- **Language/Framework**: C++ with the [Raylib](https://www.raylib.com/) library for windowing, rendering, and input.
- **OOP Principles**:
    - **Inheritance**: `Character` and `Enemy` inherit from `BaseCharacter` to reuse code for movement, animation, and positioning.
    - **Polymorphism**: Virtual functions like `tick()` and `getScreenPos()` allow for specialized behavior in derived classes.
    - **Encapsulation**: Each class manages its own data and logic, exposing only necessary functions.
- **World vs. Screen Space**: The distinction between an object's position in the game world (`worldPos`) and its position on the screen (`screenPos`) is key. Rendering logic translates world coordinates to screen coordinates relative to the player for the scrolling camera effect.
- **Game Loop**: `main.cpp` contains a standard game loop that processes input, updates all game objects (`tick()`), and handles rendering for each frame.

---

## ⚙️ How to Build and Run

### Prerequisites

- C++ compiler (like `g++` or `clang`)
- `make` build tool
- [Raylib](https://www.raylib.com/) library installed

### Build Instructions

The included `Makefile` handles compilation. In your terminal, run:

```bash
make
```

This will compile all `.cpp` files and create an executable.

### Running the Game

After a successful build, run:

```bash
# On Linux/macOS
./main

# On Windows (MinGW/MSYS2)
./main.exe
```

---

## 🧩 Troubleshooting

- **Blank or white screen**: Ensure your working directory is the project root and all asset paths (like `nature_tileset/worldMap.png`) are correct.
- **Texture load failures**: Raylib returns an invalid texture ID if a file is missing. Check your asset paths and add error handling if needed.
- **Build errors**: Make sure Raylib include/lib paths are set up for your compiler and platform.

---

## 🚀 Contributing & Extending

- Add more enemy types or behaviors (patrol, ranged attacks)
- Replace placeholder art with custom sprites and tiles
- Implement a tilemap loader for more complex worlds
- Add sound effects and music

---

## 📜 License & Credits

This project is a learning demo. Raylib is used under its own permissive license — see [raylib.com](https://www.raylib.com/) for details. Replace or include license metadata for any third-party assets you use.

---

Enjoy exploring and expanding RPG Clasher! If you want a CONTRIBUTING.md, gameplay GIF, or more documentation, just ask.
