#include "RegressionCalc.h"

#include <algorithm>
#include <cmath>

bool calculateRegression(const std::vector<DataPoint>& points,
                         RegressionResult& result,
                         std::string& error) {
    if (points.size() < 2) {
        error = "At least two data points are required.";
        return false;
    }

    long double meanX = 0.0L;
    long double meanY = 0.0L;
    for (const DataPoint& point : points) {
        if (!std::isfinite(point.x) || !std::isfinite(point.y)) {
            error = "Regression data must contain only finite numbers.";
            return false;
        }
        meanX += point.x;
        meanY += point.y;
    }

    const long double count = static_cast<long double>(points.size());
    meanX /= count;
    meanY /= count;
    if (!std::isfinite(meanX) || !std::isfinite(meanY)) {
        error = "Unable to calculate regression: numeric overflow occurred.";
        return false;
    }

    long double sumXX = 0.0L;
    long double sumXY = 0.0L;
    long double sumYY = 0.0L;
    for (const DataPoint& point : points) {
        const long double centeredX = point.x - meanX;
        const long double centeredY = point.y - meanY;
        sumXX += centeredX * centeredX;
        sumXY += centeredX * centeredY;
        sumYY += centeredY * centeredY;
    }

    if (!std::isfinite(sumXX) || !std::isfinite(sumXY) ||
        !std::isfinite(sumYY)) {
        error = "Unable to calculate regression: numeric overflow occurred.";
        return false;
    }
    if (sumXX == 0.0L) {
        error = "Linear regression is undefined: all X values are equal.";
        return false;
    }

    const long double slope = sumXY / sumXX;
    const long double intercept = meanY - slope * meanX;
    if (!std::isfinite(slope) || !std::isfinite(intercept)) {
        error = "Unable to calculate regression: numeric overflow occurred.";
        return false;
    }

    long double residualSumSquares = 0.0L;
    for (const DataPoint& point : points) {
        const long double residual =
            point.y - (slope * point.x + intercept);
        residualSumSquares += residual * residual;
    }
    if (!std::isfinite(residualSumSquares)) {
        error = "Unable to calculate R-squared: numeric overflow occurred.";
        return false;
    }

    long double rSquared = 1.0L;
    if (sumYY != 0.0L) {
        rSquared = 1.0L - residualSumSquares / sumYY;
        if (!std::isfinite(rSquared)) {
            error = "Unable to calculate R-squared: numeric overflow occurred.";
            return false;
        }
        rSquared = std::max(0.0L, std::min(1.0L, rSquared));
    }

    Correlation correlation = Correlation::Neither;
    if (slope > 0.0L) {
        correlation = Correlation::Positive;
    } else if (slope < 0.0L) {
        correlation = Correlation::Negative;
    }

    result = {slope, intercept, rSquared, correlation};
    error.clear();
    return true;
}

bool predictY(const RegressionResult& regression,
              long double x,
              long double& predictedY,
              std::string& error) {
    if (!std::isfinite(x)) {
        error = "Forecast X must be a finite number.";
        return false;
    }

    const long double prediction = regression.slope * x + regression.intercept;
    if (!std::isfinite(prediction)) {
        error = "Unable to forecast Y: numeric overflow occurred.";
        return false;
    }

    predictedY = prediction;
    error.clear();
    return true;
}
