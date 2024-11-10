# N-Queens Visualization Project
 In this project, N-queens algorithm is implemented graphically. N queens must be placed on an N×N chessboard such that no two queens attack each other. Thus, a solution requires that no two queens share the same row, column, or diagonal.

Backtracking technique is used to place queens in each row at right place. Backtracking constructs candidate solutions one component at a time and evaluates the partially constructed solutions. This approach makes it possible to solve some large instances of difficult combinatorial problems, though, in the worst case, we still face the same curse of exponential explosion encountered in exhaustive search.

The primary objective of this project is to graphically show the concept of backtracking with the help of the N-queen puzzle as an example.

## Table of Contents
- Overview
- Project Structure
- Technologies Used
- Setup and Installation
- How It Works
- Usage
- Backend C++ Code
- Frontend JavaScript Code

## Overview
The N-Queens problem is a classic chess puzzle where the objective is to place N queens on an N×N chessboard such that no two queens threaten each other. This project computes and visualizes all possible solutions for the given input N.

The solution comprises:

A C++ backend server using the Crow library to calculate the solutions.
A front-end interface built with HTML, CSS, and JavaScript to display solutions with animations.

## Project Structure

- n_queens
│ 
- ├──-  frontend/
|
- │   ├──-  index.html              # Main HTML file
|
- │   ├──- style.css               # CSS for styling the board and page layout
|
- │   └──-  script.js               # JavaScript for fetching solutions and visualizing them
|
│
- ├──-  backend/
|
- │   ├──-  main.cpp                # Main C++ application with Crow server for N-Queens calculation
|
- │   └──- solveNQueens.cpp        # C++ functions for solving N-Queens
|
│
- └──-  README.md                   # Project documentation

## Technologies Used
Frontend: HTML, CSS, JavaScript
Backend: C++ (Crow Library, nlohmann/json for JSON parsing)
Libraries:
Crow: A C++ micro web framework
nlohmann/json: JSON library for C++

## Setup and Installation
## Prerequisites
Install Crow and nlohmann/json for C++.
Ensure you have a C++17 compatible compiler.
Make sure Node.js and a local HTTP server are installed if running the frontend locally.

## Running the Backend Server
Navigate to the backend directory.
Compile and run the C++ server with:

bash
Copy code
g++ main.cpp -lpthread && ./a.out
This will start the backend on http://localhost:8080.

## Running the Frontend
Open frontend/index.html in your browser, or run a local HTTP server to access it through localhost.

## How It Works
- Frontend: Users enter a value for N and adjust the speed using a slider. Upon clicking the "Play" button, a request is sent to the backend.
- Backend: The C++ server receives the request, calculates all valid N-Queens solutions using a bitmask-based recursive algorithm, and sends the solutions as a JSON response.
- Display: The frontend receives the solutions, visualizes each arrangement with animations, and displays a queen (<i class="fas fa-chess-queen"></i>) on each valid cell.

## Usage
Open the front-end application (index.html).
Input the desired number of queens (N) in the provided text box.
Adjust the animation speed using the slider.
Click "Play" to view the animated solutions on the chessboard.

## Backend C++ Code
The backend server is built using the Crow C++ framework. The solveNQueens function uses bitmasking for optimized recursive backtracking. It calculates the column positions for each queen, ensuring no two queens can attack each other.

The backend route /solveNQueens:

Accepts a POST request with JSON data containing the value of N.
Returns a JSON response with the number of possible solutions and their arrangements.

## Example Request
json
Copy code
{
    "number": 8
}

## Example Response
json
Copy code
{
    "solutionCount": 92,
    "solutions": [
        [0, 4, 7, 5, 2, 6, 1, 3],
        ...
    ]
}

## Frontend JavaScript Code
The JavaScript code interacts with the backend to retrieve and visualize solutions. Key functions:

getSolutions(n): Sends a POST request to the backend to fetch N-Queens solutions.
displaySolutions(solutions, n): Displays each solution as an animated chessboard arrangement using a delay defined by the speed slider.

## Key Files
index.html: Main HTML structure for the application.
style.css: Styles for the chessboard and queen display.
script.js: Handles the user input, fetch requests, and displays solutions.

## Future Improvements
Add support for larger N values with performance optimizations.
Allow users to pause or restart the visualization.
Improve UI and add more interactive features.

## License
This project is open-source and available for modification and personal use.
