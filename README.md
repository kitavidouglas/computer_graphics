# OpenGL Circle Demo with Grid & Texture

A small OpenGL/GLUT demo that draws a coordinate grid and renders a circle at world‑coordinates **(-3, 1)** with a **4 cm** radius. You can:

- **Toggle background** between blue and green  
- **Toggle circle fill** between solid white and a wood‑grain texture  
- See on‑screen UI instructions and world grid

---

## 📋 Features

- Orthographic projection covering **–10…+10** in X and Y  
- Light‑gray grid lines with bold white axes  
- Solid‑color (white) and textured (wood) circle fills  
- Keyboard controls for live toggling  

---

## ⚙️ Prerequisites

- Linux/macOS or Windows with:
  - OpenGL development libraries
  - FreeGLUT (or GLUT)
  - [SOIL](http://www.lonesock.net/soil.html) (Simple OpenGL Image Library)
  - C++ compiler (e.g. `g++`)

---

## 🛠 Installation & Build

1. **Clone** this repo (or copy files)  
2. Place a **wood.jpg** (e.g. 256×256 wood‑grain) alongside `textured_circle.cpp`  
3. **Compile**:

   ```bash
   g++ textured_circle.cpp -lGL -lGLU -lglut -lSOIL -o textured_circle
