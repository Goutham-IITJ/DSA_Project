#include "crow.h"
#include <vector>
#include "json.hpp"
#include "crow/middlewares/cors.h"

using json = nlohmann::json;

// Function prototypes
void solveNQueens(int row, int n, int cols, int diag1, int diag2, std::vector<int>& position, std::vector<std::vector<int>>& solutions);

// Main Crow Application
int main() {
    crow::App<crow::CORSHandler> app;

    auto& cors = app.get_middleware<crow::CORSHandler>();

    cors.global()
        .headers("Content-Type", "Authorization", "Accept")
        .methods("POST"_method, "GET"_method, "PUT"_method, "DELETE"_method, "OPTIONS"_method)
        .prefix("/")
        .origin("*")
        .allow_credentials();

    // Endpoint to solve N-Queens and return JSON data
    CROW_ROUTE(app, "/solveNQueens").methods("POST"_method)
    ([](const crow::request& req) {
        // Parse request JSON data
        json jsonData = json::parse(req.body);
        if (jsonData.empty())
            return crow::response(400);

        int n = jsonData["number"];
        std::vector<std::vector<int>> solutions;
        std::vector<int> position(n, -1);
        
        // Bitmask version of solveNQueens
        solveNQueens(0, n, 0, 0, 0, position, solutions);

        // Prepare response JSON
        json response;
        response["solutionCount"] = solutions.size();
        json solutionArray = json::array();

        for (const auto& singleSolution : solutions) {
            json singleSolutionJson = json::array();
            for (int j = 0; j < n; j++) {
                singleSolutionJson.push_back(singleSolution[j]);
            }
            solutionArray.push_back(singleSolutionJson);
        }
        
        response["solutions"] = solutionArray;
        return crow::response(response.dump());
    });

    app.port(8080).multithreaded().run();
}

// Solve the N-Queens problem using optimized bitmasking
void solveNQueens(int row, int n, int cols, int diag1, int diag2, std::vector<int>& position, std::vector<std::vector<int>>& solutions) {
    if (row == n) {
        solutions.push_back(position);
        return;
    }

    // Calculate available positions for the queen
    int availablePositions = ((1 << n) - 1) & ~(cols | diag1 | diag2);
    while (availablePositions) {
        int bit = availablePositions & -availablePositions;  // Rightmost available position
        availablePositions -= bit;  // Remove this position from available

        // Find the column number for the current bit
        int col = __builtin_ctz(bit);
        position[row] = col;

        // Recur with updated bitmasks
        solveNQueens(row + 1, n, cols | bit, (diag1 | bit) << 1, (diag2 | bit) >> 1, position, solutions);

        position[row] = -1;  // Reset for backtracking
    }
}
