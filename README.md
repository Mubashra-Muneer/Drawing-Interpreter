# Drawing-Interpreter
A console-based C++ project that interprets drawing commands to render lines and shapes using basic graphics logic.
## Features

- Draw shapes using commands like `fd`, `bk`, `circle`, etc.
- REPEAT loops for repetitive drawing sequences.
- Pen Control – Pen up (`pu`) and down (`pd`) to control drawing.
- Color and Width Customization using `color` and `width` commands.
- Save and Load your command history to/from text files.
- Command History is printed dynamically in the console.
- Fullscreen Mode enabled for an immersive drawing experience.

## How It Works

1. **User Inputs Command**:  
   You type a command like:  
   `fd 100`  
   `rt 90`  
   `circle 50`  
   `repeat 4[fd 50 rt 90]`

2. **Command is Parsed**:  
   The program extracts the command and numerical value using custom logic.

3. **Drawing Logic**:  
   - Calculates direction and position using trigonometry.  
   - Updates coordinates.  
   - Uses custom graphics functions like `myLine3()` and `myEllipse()` to simulate drawing on console.

4. **Graphics Rendering**:  
   - Arrows show direction using trigonometric rotations.  
   - Circles and lines are drawn using Windows GDI-like functions (via `help.h`).

5. **Repeat Block Execution**:  
   `repeat 4[fd 10 rt 90]` executes the inner commands 4 times.

6. **File Handling**:  
   - `save "filename.txt"` saves current commands.  
   - `load "filename.txt"` loads and re-executes saved commands.

7. **Full Screen Console**:  
   The console is set to fullscreen with adjusted buffer size using Windows API.

## Technologies Used

- C++
- Windows.h, conio.h, fstream
- Custom Graphics Header (`help.h`)
- Mathematics (sin, cos) for direction handling

## File Structure

```
main.cpp         // Your main logic file
help.h           // Custom graphics header (handles drawing)
README.md        // Project description
```

> Note: `help.h` must include `myLine3()` and `myEllipse()` functions for drawing lines and circles. Make sure it’s in the same directory.

## Example Commands

- `fd 100`         // move forward 100 units
- `bk 50`          // move backward 50 units
- `rt 90`          // rotate right 90 degrees
- `lt 45`          // rotate left 45 degrees
- `pu`             // pen up (stop drawing)
- `pd`             // pen down (start drawing)
- `color 2`        // change color (e.g. 2 = green)
- `width 3`        // change pen width
- `circle 50`      // draw circle with radius 50
- `cs`             // clear screen
- `save "file.txt"`// save commands
- `load "file.txt"`// load and execute saved commands
- `repeat 4[fd 10 rt 90]`  // repeat loop

## Learning Outcomes

- String parsing and command handling
- Basic trigonometry in graphics
- File I/O with error handling
- Dynamic console updates
- Working with Windows console API


