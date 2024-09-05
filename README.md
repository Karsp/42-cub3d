# **Cub3D - Our RayCaster implementation with miniLibX** 

Welcome to **cub3D**, an immersive 3D maze exploration project inspired by the legendary *Wolfenstein 3D*—the first FPS game! This project is built using **C** and leverages **miniLibX** for graphical rendering, focusing on implementing a first-person perspective view using **ray-casting** techniques.

In this project, you'll navigate through a maze, see realistic 3D textures, and experience dynamic player movement—all with smooth controls and exciting features!

## 🌟 **Features**

### Mandatory Part:
- **Ray-casting for 3D rendering**: Creates a realistic first-person 3D environment using ray-casting principles.
- **Maze navigation**: Move through the maze with keyboard controls (W, A, S, D).
- **Smooth player rotation**: Use the left and right arrow keys to look around.
- **Textured walls**: Enjoy different textures for walls depending on the direction (North, South, East, West).
- **Floor and ceiling color customization**: You can customize the floor and ceiling colors for a personal touch!
- **Error handling**: Handles file parsing errors gracefully with meaningful error messages.
  
### Bonus Features We Implemented 🎉:
- 🛑 **Wall Collision Protection**: No walking through walls here! Movement is restricted within the maze boundaries, ensuring a realistic experience.
- 🗺️ **Minimap System**: Get a bird’s-eye view of the maze as you move around. This minimap helps you find your way, adding an extra layer of functionality and aesthetics.
- 🖱️ **Mouse-Controlled POV Rotation**: Enhance your experience with smooth point-of-view rotation using your mouse. Navigate the maze with precision!

## 🛠️ **How to Build and Run**

### Prerequisites
- **GCC** or any standard C compiler
- **miniLibX** a basic but powerfull graphic library (included on github submodule)
- **libft** our custom C library (included on github submodule)

### Steps:
1. Clone this repository:
   ```bash
   git clone https://github.com/Karsp/42-cub3d.git
   ```

2. Navigate to the project directory:
   ```bash
   cd 42-cub3d
   ```

3. Update the git submodules:
   ```bash
   git submodule update --init --recursive
   ```

4. Build the project using the provided `Makefile`:
   ```bash
   make
   ```

5. Run the game with a valid `.cub` map file:
   ```bash
   ./cub3D src/maps/circle.cub
   ```

## 🕹️ **Controls**
- **W, A, S, D, Up/Down Arrow**: Move forward, left, backward, and right.
- **Q, E, Left/Right Arrow**: Rotate the player's view left and right.
- **ESC**: Quit the game.
- - **C**: Show/Hide mouse cursor.
- **Mouse**: Rotate the view by moving the mouse.

## 🧩 **Bonus Features Showcase**
![Minimap Preview](path_to_image/minimap.png)  
*Our project comes with a minimap to assist you in navigating the maze!* 

![Mouse Rotation](path_to_image/mouse_control.png)  
*Rotate the point of view using your mouse for smooth, intuitive navigation.*

## 🏗️ **Project Structure**
- **src/**: Contains all the source code files.
- **src/maps/**: Holds example `.cub` files for testing.
- **src/textures/**: Directory where wall textures are stored.
- **external/**: Directory where external librarys are stored.
- **Makefile**: Compiles the project and manages clean, fclean, and bonus rules.

## 😄 **We hope you enjoy it!** 👋 


## 📜 **License**
This project is open-source and available under the [MIT License](LICENSE).
```

This markdown version includes everything from the second step (navigating to the project directory) and the rest of the instructions, all formatted in markdown syntax. Let me know if you'd like to add or adjust anything further!
