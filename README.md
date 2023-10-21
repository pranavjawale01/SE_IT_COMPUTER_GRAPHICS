# SE_IT_COMPUTER_GRAPHICS
Computer Graphics Code

To Run Code (Linux)
gcc filename.c -lglut -lGL -lGLU
OR 
gcc filename.c -lglut -lGL -lGLU -lm (If math lib is include)

This code involves the implementation of various graphics algorithms and 2D transformations. The project aims to create a graphical interface where users can draw lines, circles, polygons, and apply transformations to objects.

### 1. Line Drawing Algorithms
- DDA Line Drawing Algorithm
- Bresenham Line Drawing Algorithm
  - Simple Line
  - Dotted Line
  - Dashed Line
  - Solid Line
  - All slopes (positive and negative) supported

### 2. Circle Drawing Algorithm
- Bresenham Circle Drawing Algorithm
  - Object displayed in all quadrants with respect to center and radius

### 3. Polygon Filling Methods
- Flood Fill / Seed Fill
  - Implemented using mouse click, keyboard interface, and menu-driven programming
- Boundary Fill
  - Implemented using mouse click, keyboard interface, and menu-driven programming

### 4. Polygon Clipping Method
- Cohen Sutherland Polygon Clipping Method
  - Clipping the polygon with respect to the viewport and window
  - Implemented using mouse click and keyboard interface

### 5. 2D Transformations
- Scaling
- Rotation about Arbitrary Point
- Reflection
  - Transformations applied with respect to the axis

### 6. Fractal Patterns Generation
- Bezier Curve
- Koch Curve
  - Fractal patterns generated using Bezier and Koch Curve algorithms

#### Mini Project Water Drop
