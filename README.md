# MazeSolver
## Description
This is a program that finds a path in a maze between two points.
Along the way, the program shows every step of the searching algorithm.

## The maze
The maze is represented as a TXT file.
- Symbol `#` represents a wall,
- Symbol `A` represents the starting point. If omitted, the starting point is set to {1, 1} (indexing starts with 0),
- Symbol `B` represents the end point. If omitted, the end point is set to {height - 2, width - 2} a.k.a {num_rows - 2, num_cols - 2} (indexing starts with 0),
- Symbol `(whitespace)` represents the road (where the path can be set through).


## Searching algorithms
For now there are two available algorithms:
- Depth First Searching Algorithm (DFS)
- Breadth First Searching Algorithm (BFS)

## Usage
After building the project, run the `bin/main.exe` file and follow the instructions of the menu.

### Possible options in the menu
- **Set delay**: The program shows every step of the algorithm. Set the delay between showing each step. The delay is set in seconds.
- **Solve a maze**: The program starts searching the way from A to B, showing every step. You should provide the program with a file path of the file with a maze.

