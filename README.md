# Linear Regression Calculator

## Requirements

- Windows with PowerShell
- A C++ compiler that provides `g++` (for example, MinGW-w64) installed and available on `PATH`

To check that the compiler is available, open PowerShell and run:

```powershell
g++ --version
```

## Build and run

Open PowerShell and enter these commands:

```powershell
cd A:\Sahar\Project-2
g++ -std=c++11 -Wall -Wextra -Wpedantic src\main.cpp src\RegressionCalc.cpp src\FileHandler.cpp -o regression_tool.exe
.\regression_tool.exe
```

The first command changes to the project folder. The second compiles the program; run it again after changing the source code. The third starts the program.

## Using the program

Use the displayed menu to:

1. Add an X/Y data point.
2. Calculate the regression slope, Y-intercept, R-squared, and correlation direction.
3. Display the current data points.
4. Clear all data points.
5. Forecast Y for a user-entered X value.
6. Import data points from a CSV file.
7. Exit.

For CSV import, enter the path to a `.csv` file. Each data row must contain two comma-separated finite numbers (X and Y). A first-row `X,Y` header is optional. For example:

```csv
X,Y
1,3
2,5
3,7
```

The C++ source and header files are in `src\`. The program runs in the terminal and needs no additional project libraries.
