# FDF Project

## Introduction

FDF (Fil De Fer) is a 3D wireframe viewer project. The goal of this project is to represent a 3D object in a 2D space using a wireframe model. This project is part of the 42 curriculum and aims to help students understand the basics of computer graphics, coordinate systems, and transformations.

## Features

- Load and parse a map file containing height values.
- Render a 3D wireframe representation of the map.
- Support for different projections (isometric and parallel).
- Basic controls for rotating, zooming, and translating the view.

## Requirements

- GCC compiler
- Make
- X11 libraries (Xlib, Xext)
- MinilibX library

## Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/fdf.git
   cd fdf
   ```

2. Install the required libraries:
   ```sh
   sudo apt-get install gcc make xorg libxext-dev libbsd-dev
   ```

3. Compile the project:
   ```sh
   make
   ```

## Usage

1. Run the program with a map file:
   ```sh
   ./fdf maps/10-2.fdf
   ```

2. Use the following controls to interact with the wireframe:
   - Arrow keys: Rotate the view
   - `+` / `-`: Zoom in/out
   - `W` / `S`: Move up/down
   - `A` / `D`: Move left/right
   - `ESC`: Exit the program
```