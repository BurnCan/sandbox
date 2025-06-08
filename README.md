
# OpenGL FPS Project (Cross-Platform Setup Guide)

This guide walks you through setting up your development environment and compiling this project on **Windows**, **macOS**, and **Ubuntu/Debian**.

---

## 🧰 Prerequisites

- Git
- CMake (3.14+)
- C++ Compiler (GCC, Clang, or MSVC)
- OpenGL-compatible GPU

---

## 🪟 Windows (MSYS2 + MinGW64)

### 1. Open MSYS2 MinGW 64-bit terminal

> Not `MSYS`, `UCRT`, or `CLANG`.

### 2. Update MSYS2

```bash
pacman -Syu
# Restart terminal if prompted
pacman -Su
```

### 3. Install tools

```bash
pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake mingw-w64-x86_64-make git
```

### 4. Clone the repository

```bash
git clone https://github.com/BurnCan/OpenGLProjectTemplate
cd OpenGLProjectTemplate
```

### 5. Build

```bash
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
```

### 6. Run

```bash
cd bin
./OpenGLApp.exe
```

---

## 🍏 macOS

### 1. Install tools

```bash
brew install cmake git
```

### 2. Build

```bash
git clone https://github.com/BurnCan/OpenGLProjectTemplate
cd OpenGLProjectTemplate
mkdir build && cd build
cmake ..
make
```

### 3. Run

```bash
cd bin/OpenGLApp.app/Contents/MacOS
./OpenGLApp

```

---

## 🐧 Ubuntu / Debian Linux

### 1. Install tools

```bash
sudo apt update
sudo apt install build-essential cmake git libgl1-mesa-dev libx11-dev libxi-dev libxrandr-dev libxinerama-dev libxcursor-dev
```

### 2. Build

```bash
git clone https://github.com/BurnCan/OpenGLProjectTemplate
cd OpenGLProjectTemplate
mkdir build && cd build
cmake ..
make
```

### 3. Run

```bash
cd bin
./YourAppExecutableName
```

---

## 📦 Optional: Install libraries manually (Windows only)

```bash
pacman -S mingw-w64-x86_64-glfw mingw-w64-x86_64-glew mingw-w64-x86_64-glm mingw-w64-x86_64-imgui
```

If you're using `FetchContent` in CMake, these are **not required**.

---

## 📁 Project Structure Example (windows)

```
OpenGLProjectTemplate/
├── shaders/
├── src/
├── CMakeLists.txt
├── README.md
└── build/
    └── bin/
	├── shaders/
        └── OpenGLApp.exe
```

---

## ✅ You're good to go!

Happy coding! 🎮
