/**
 * @file Lab_10_Graph_traversal.cpp
 * @brief Interactive program to demonstrate Breadth-First Search (BFS)
 *        and Depth-First Search (DFS) on an undirected/directed graph
 *        represented by an adjacency matrix.
 */

#include <cctype>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

constexpr int MAX_VERTICES = 20;

/**
 * @brief Reads a single integer from standard input within an inclusive range.
 *
 * The input is read as a whole line and validated so that trailing garbage
 * (such as "12abc" or "3.5") is rejected.
 *
 * @param prompt   The prompt displayed to the user.
 * @param value    Output variable for the validated integer.
 * @param minVal   Minimum acceptable value.
 * @param maxVal   Maximum acceptable value.
 * @return true    If a valid integer was read.
 * @return false   If the input was missing, non-numeric, or out of range.
 */
bool readInteger(const std::string& prompt, int& value, int minVal, int maxVal)
{
    std::cout << prompt;
    std::string line;
    if (!std::getline(std::cin, line))
        return false;

    // Trim leading and trailing whitespace.
    std::size_t start = 0;
    while (start < line.size() &&
           std::isspace(static_cast<unsigned char>(line[start])))
        ++start;

    std::size_t end = line.size();
    while (end > start &&
           std::isspace(static_cast<unsigned char>(line[end - 1])))
        --end;

    if (start >= end)
        return false;

    try
    {
        std::size_t idx = 0;
        const int parsed =
            std::stoi(line.substr(start, end - start), &idx);

        // Ensure the entire token was consumed (no trailing "abc", etc.).
        if (idx != (end - start))
            return false;

        if (parsed < minVal || parsed > maxVal)
            return false;

        value = parsed;
        return true;
    }
    catch (const std::exception&)
    {
        return false;
    }
}

/**
 * @brief Reads one row of the adjacency matrix.
 *
 * Each row must contain exactly @p n integer values, each either 0 or 1,
 * separated by whitespace.
 *
 * @param rowIndex Index of the row being entered.
 * @param n        Number of vertices (columns).
 * @param row      Output vector populated with the validated row entries.
 * @return true    If the row was read and validated successfully.
 * @return false   Otherwise.
 */
bool readMatrixRow(int rowIndex, int n, std::vector<int>& row)
{
    std::cout << "Row " << rowIndex << " (" << n
              << " values, each 0 or 1): ";

    std::string line;
    if (!std::getline(std::cin, line))
        return false;

    std::istringstream iss(line);
    row.assign(n, 0);

    for (int j = 0; j < n; ++j)
    {
        if (!(iss >> row[j]) || row[j] < 0 || row[j] > 1)
            return false;
    }

    // Reject rows with extra non-whitespace characters.
    std::string extra;
    if (iss >> extra)
        return false;

    return true;
}

/**
 * @brief Performs Breadth-First Search starting from the given vertex.
 *
 * @param adj   The graph adjacency matrix.
 * @param start The starting vertex.
 */
void BFS(const std::vector<std::vector<int>>& adj, int start)
{
    const int n = static_cast<int>(adj.size());
    std::vector<bool> visited(n, false);
    std::queue<int> q;

    q.push(start);
    visited[start] = true;

    std::cout << "BFS Traversal: ";
    while (!q.empty())
    {
        const int node = q.front();
        q.pop();

        std::cout << node << ' ';

        for (int i = 0; i < n; ++i)
        {
            if (adj[node][i] == 1 && !visited[i])
            {
                q.push(i);
                visited[i] = true;
            }
        }
    }
    std::cout << '\n';
}

/**
 * @brief Recursively performs Depth-First Search.
 *
 * @param adj     The graph adjacency matrix.
 * @param visited Visited-state vector.
 * @param node    The current vertex being visited.
 */
void DFS(const std::vector<std::vector<int>>& adj,
         std::vector<bool>& visited,
         int node)
{
    std::cout << node << ' ';
    visited[node] = true;

    const int n = static_cast<int>(adj.size());
    for (int i = 0; i < n; ++i)
    {
        if (adj[node][i] == 1 && !visited[i])
            DFS(adj, visited, i);
    }
}

/**
 * @brief Entry point of the program.
 *
 * Prompts the user for the number of vertices, the adjacency matrix,
 * a traversal choice, and a starting vertex, then performs BFS or DFS.
 *
 * @return 0 on successful execution.
 */
int main()
{
    int n = 0;
    while (!readInteger("Enter number of vertices: ", n, 1, MAX_VERTICES))
    {
        std::cout << "Invalid input. Please enter an integer between 1 and "
                  << MAX_VERTICES << ".\n";
    }

    std::vector<std::vector<int>> adj(n, std::vector<int>(n, 0));

    std::cout << "Enter adjacency matrix (0 or 1):\n";
    for (int i = 0; i < n; ++i)
    {
        while (!readMatrixRow(i, n, adj[i]))
        {
            std::cout << "Invalid row. Please enter " << n
                      << " values (each 0 or 1) separated by spaces.\n";
        }
    }

    int choice = 0;
    while (!readInteger("\n1. BFS\n2. DFS\nEnter choice: ",
                        choice, 1, 2))
    {
        std::cout << "Invalid choice. Please enter 1 or 2.\n";
    }

    int start = 0;
    const std::string startPrompt =
        std::string("Enter starting vertex (0 to ") +
        std::to_string(n - 1) + "): ";

    while (!readInteger(startPrompt, start, 0, n - 1))
    {
        std::cout << "Invalid starting vertex. Please enter an integer "
                  << "between 0 and " << (n - 1) << ".\n";
    }

    if (choice == 1)
    {
        BFS(adj, start);
    }
    else // choice == 2
    {
        std::vector<bool> visited(n, false);
        std::cout << "DFS Traversal: ";
        DFS(adj, visited, start);
        std::cout << '\n';
    }

    return 0;
}