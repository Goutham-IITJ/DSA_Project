'use strict';

const numberbox = document.getElementById("numberbox");
const slider = document.getElementById("slider");
const progressBar = document.getElementById("progress-bar");
const playButton = document.getElementById('play-button');
const queen = '<i class="fas fa-chess-queen" style="color:#000"></i>';

let n, speed;

slider.oninput = function () {
    progressBar.style.width = this.value + "%";
    speed = (100 - slider.value) * 10;
};

// Fetch solutions from the C++ backend
async function getSolutions(n) {
    const response = await fetch('http://localhost:8080/solveNQueens', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ number: n })
    });

    const data = await response.json();
    console.log(data);
    displaySolutions(data.solutions, n);
}

function displaySolutions(solutions, n) {
    const chessBoard = document.getElementById("n-queen-board");
    const arrangement = document.getElementById("queen-arrangement");
    chessBoard.innerHTML = "";
    arrangement.textContent = `For ${n}x${n} board, ${solutions.length} arrangements are possible.`;

    solutions.forEach((solution, index) => {
        const boardDiv = document.createElement("div");
        const table = document.createElement("table");
        const header = document.createElement("h4");
        header.textContent = `Solution ${index + 1}`;
        boardDiv.appendChild(header);
        boardDiv.appendChild(table);

        for (let row = 0; row < n; row++) {
            const tableRow = table.insertRow();
            for (let col = 0; col < n; col++) {
                const cell = tableRow.insertCell();
                cell.style.border = "1px solid #373f51";
                cell.style.backgroundColor = (row + col) % 2 ? "#FF9F1C" : "#FCCD90";

                // Add a delay before placing the queen
                setTimeout(() => {
                    if (solution[row] === col) {
                        cell.innerHTML = queen;
                    } else {
                        cell.innerHTML = "-";
                    }
                }, (row * n + col) * speed);
            }
        }
        chessBoard.appendChild(boardDiv);
    });
}

// Play button event to start visualization
playButton.onclick = function () {
    n = parseInt(numberbox.value);

    if (isNaN(n) || n < 1) {
        alert("Please enter a valid number of queens.");
        numberbox.value = "";
        return;
    }

    getSolutions(n);
};
