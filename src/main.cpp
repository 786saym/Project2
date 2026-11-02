#include "FileHandler.h"
#include "RegressionCalc.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace {

bool readFiniteNumber(const std::string& prompt, long double& value) {
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) {
            return false;
        }

        std::istringstream input(line);
        long double parsed = 0.0L;
        char extra = '\0';
        if ((input >> parsed) && !(input >> extra) && std::isfinite(parsed)) {
            value = parsed;
            return true;
        }

        std::cout << "Invalid input. Enter one finite number.\n";
    }
}

bool addDataPoint(std::vector<DataPoint>& points) {
    long double x = 0.0L;
    long double y = 0.0L;
    if (!readFiniteNumber("Enter X: ", x) ||
        !readFiniteNumber("Enter Y: ", y)) {
        return false;
    }

    points.push_back({x, y});
    std::cout << "Point added.\n";
    return true;
}

void displayData(const std::vector<DataPoint>& points) {
    if (points.empty()) {
        std::cout << "There are no data points.\n";
        return;
    }

    std::cout << std::fixed << std::setprecision(6)
              << "\nData points (" << points.size() << "):\n";
    for (std::size_t i = 0; i < points.size(); ++i) {
        std::cout << i + 1 << ". X = " << points[i].x
                  << ", Y = " << points[i].y << '\n';
    }
}

bool calculateAndDisplay(const std::vector<DataPoint>& points,
                         RegressionResult& result) {
    std::string error;
    if (!calculateRegression(points, result, error)) {
        std::cout << error << '\n';
        return false;
    }

    std::cout << std::fixed << std::setprecision(6)
              << "\nLinear regression results\n"
              << "Slope: " << result.slope << '\n'
              << "Y-intercept: " << result.intercept << '\n'
              << "R-squared: " << result.rSquared << '\n';

    switch (result.correlation) {
        case Correlation::Positive:
            std::cout << "Correlation: POSITIVE\n";
            break;
        case Correlation::Negative:
            std::cout << "Correlation: NEGATIVE\n";
            break;
        case Correlation::Neither:
            std::cout << "Correlation: NEITHER POSITIVE NOR NEGATIVE "
                         "(zero slope)\n";
            break;
    }
    return true;
}

void predict(const std::vector<DataPoint>& points) {
    RegressionResult result;
    if (!calculateAndDisplay(points, result)) {
        return;
    }

    long double x = 0.0L;
    if (!readFiniteNumber("Enter X to forecast: ", x)) {
        std::cout << "\nInput ended.\n";
        return;
    }

    long double predictedY = 0.0L;
    std::string error;
    if (!predictY(result, x, predictedY, error)) {
        std::cout << error << '\n';
        return;
    }

    std::cout << std::fixed << std::setprecision(6)
              << "Forecast Y for X = " << x << ": " << predictedY << '\n';
}

bool importCsv(std::vector<DataPoint>& points) {
    std::cout << "Enter CSV file path: ";
    std::string path;
    if (!std::getline(std::cin, path)) {
        return false;
    }

    std::vector<DataPoint> importedPoints;
    std::string error;
    if (!importCsvData(path, importedPoints, error)) {
        std::cout << "CSV import failed: " << error << '\n';
        return true;
    }

    points.insert(points.end(), importedPoints.begin(), importedPoints.end());
    std::cout << "Imported " << importedPoints.size()
              << " data point(s).\n";
    return true;
}

}  // namespace

int main() {
    std::vector<DataPoint> points;
    bool running = true;

    while (running) {
        std::cout << "\n=== Linear Regression Calculator ===\n"
                  << "1. Add a data point\n"
                  << "2. Calculate regression\n"
                  << "3. Display data points\n"
                  << "4. Clear all data points\n"
                  << "5. Predict Y for an X value\n"
                  << "6. Import data points from CSV\n"
                  << "7. Exit\n"
                  << "Choose an option: ";

        std::string choice;
        if (!std::getline(std::cin, choice)) {
            std::cout << "\nInput ended. Exiting.\n";
            break;
        }

        if (choice == "1") {
            if (!addDataPoint(points)) {
                std::cout << "\nInput ended. Exiting.\n";
                break;
            }
        } else if (choice == "2") {
            RegressionResult result;
            calculateAndDisplay(points, result);
        } else if (choice == "3") {
            displayData(points);
        } else if (choice == "4") {
            points.clear();
            std::cout << "All data points cleared.\n";
        } else if (choice == "5") {
            predict(points);
        } else if (choice == "6") {
            if (!importCsv(points)) {
                std::cout << "\nInput ended. Exiting.\n";
                break;
            }
        } else if (choice == "7") {
            running = false;
            std::cout << "Goodbye.\n";
        } else {
            std::cout << "Invalid menu choice. Enter a number from 1 to 7.\n";
        }
    }

    return 0;
}
