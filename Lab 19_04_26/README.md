````md
# 🎮 OpenGL 3D Rotating Cube

This project is a simple **3D rotating cube** built using **OpenGL (GLUT)** in C++.  
It demonstrates basic 3D transformations such as translation, rotation, and perspective projection.

---

## 📌 Features

- 🧊 3D colored cube rendering
- 🔄 Continuous rotation animation
- ⌨️ Keyboard-controlled movement
- 🧭 Arrow key navigation (x, y movement)
- 🎥 Perspective camera view
- ⚡ Real-time rendering using GLUT timer

---

## 🧰 Technologies Used

- C++
- OpenGL
- GLUT (OpenGL Utility Toolkit)

---

## 🎮 Controls

| Key / Action   | Function                     
| -------------- | ---------------------------- 
| ⬅️ Arrow Left  | Move cube left               
| ➡️ Arrow Right | Move cube right              
| ⬆️ Arrow Up    | Move cube up                 
| ⬇️ Arrow Down  | Move cube down               
| `A` key        | Rotate cube (manual control) 

---

## 🧊 3D Cube Overview

The cube is made using **6 faces**, each with a different color:

* 🔴 Front → Red
* 🟢 Back → Green
* 🔵 Left → Blue
* 🟡 Right → Yellow
* 🟦 Top → Cyan
* 🟠 Bottom → Orange

Each face is drawn using `GL_QUADS`.

---

## 🎨 Changing Colors

Each face color is defined using:

```cpp
glColor3f(R, G, B);
```

### Example:

```cpp
glColor3f(1.0, 0.0, 0.0); // Red
```

### RGB Range:

* `0.0` → No intensity
* `1.0` → Full intensity

---

## 🔄 Rotation System

The cube rotates using:

```cpp
glRotatef(angle, x, y, z);
```

### Examples:

Rotate around X-axis:

```cpp
glRotatef(angle, 1, 0, 0);
```

Rotate around Y-axis:

```cpp
glRotatef(angle, 0, 1, 0);
```

Rotate around Z-axis:

```cpp
glRotatef(angle, 0, 0, 1);
```

Rotate on all axes:

```cpp
glRotatef(angle, 1, 1, 1);
```

---

## ⚡ Rotation Speed Control

Modify:

```cpp
float angle = 0.5f;
```

Or update in timer:

```cpp
angle += 1.0f;
```

* Higher value → faster rotation
* Lower value → smoother rotation

---

## 🧠 How It Works

* `glTranslatef()` moves the cube in 3D space
* `glRotatef()` rotates the cube
* `gluPerspective()` creates a 3D camera view
* `glutTimerFunc()` keeps animation running
* Depth testing ensures correct 3D rendering

---

---

## ✨ Future Improvements

* Add lighting (realistic shading)
* Mouse-controlled rotation
* Texture mapping
* Multiple cubes animation
* Camera zoom controls

---

## 👨‍💻 Author

Basic OpenGL learning project for understanding 3D graphics, transformations, and animation.

---

## 📜 License

This project is open-source and free to use for learning purposes.

```
