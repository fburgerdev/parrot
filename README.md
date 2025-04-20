![parrot-title](https://github.com/user-attachments/assets/1056fc4a-0e39-4856-b956-507c1975ae27)

# 🦜 Parrot

Welcome to Parrot, a C++ game engine designed as an educational project
to help developers learn about game engine architecture and graphics programming.

## 🚀 About

Parrot is a modern C++ game engine focused on clean architecture
and an intuitive game development. It is asset-based,
meaning everything you do to create a game involves creating and managing assets.
Featuring an entity component system, a rendering pipeline,
an asset manager and window handling, the game engine provides a basic foundation for game development

![showcase](https://github.com/user-attachments/assets/998e8642-6cc0-464e-9837-f3d0b7d5a54c)

## 📖 Documentation
Read the full documentation [here](docs/index.md).

## 🎮 Create a game!

### Make sure you have installed
- C++ compiler (>= c++20)
- CMake (>= 3.16)

### Run in your console
```sh
# Clone the repository
git clone https://github.com/fburgerdev/parrot.git -b game my_game
cd my_game

# Configure and build
cmake -S . -B build
cd build
cmake --build . -j20

# Play!
./build/Debug/my_game.exe
```

## 🛠 Developer Notes
For more details on Parrot’s architecture and contribution guidelines:
- [Architecture Overview](./docs/architecture.md)
- [Contributing Guidelines](./CONTRIBUTING.md)

## 📬 Get Involved
We welcome contributions! Feel free to open issues, submit PRs, or discuss improvements.

---
🦜 Happy coding with Parrot!
