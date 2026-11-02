# Introduction & AI Tools

## Presentation script

"This project is a multi-file C++ linear regression calculator. It separates the terminal interface, regression calculations, and CSV file handling into different source files. A user can add or import X/Y data points, calculate a best-fit line and R-squared value, forecast a Y value for a supplied X, review or clear the data, and exit."

## What the program does

Each data point contains an X value and a Y value. With at least two valid points and more than one distinct X value, the program calculates the slope and Y-intercept of the least-squares line, reports the direction indicated by its slope, and calculates R-squared. Its forecasting option evaluates that line at a new X value.

The CSV importer accepts rows containing two numeric values separated by a comma. A first-row `X,Y` header is optional. Invalid rows cause the import to fail without adding a partial set of points.

## Project architecture

- **`src/main.cpp`:** Runs the menu, validates interactive numeric input, and connects the user actions to the calculation and file-handling functions.
- **`src/RegressionCalc.h` / `src/RegressionCalc.cpp`:** Define the data and result types, calculate regression statistics, and forecast Y values.
- **`src/FileHandler.h` / `src/FileHandler.cpp`:** Read and validate CSV input before appending imported points to the program's collection.

## Explaining the AI tools

- **Gemini and GitHub Copilot:** The project materials identify these as tools used to help design and build the program.
- **Your role:** Explain the architecture, inputs, validation, calculations, CSV format, and menu options in your own words.

This section describes the project and its stated tools without assigning individual code changes to a specific tool.
