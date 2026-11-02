#ifndef REGRESSION_CALC_H
#define REGRESSION_CALC_H

#include <string>
#include <vector>

struct DataPoint {
    long double x;
    long double y;
};

enum class Correlation {
    Positive,
    Negative,
    Neither
};

struct RegressionResult {
    long double slope;
    long double intercept;
    long double rSquared;
    Correlation correlation;
};

bool calculateRegression(const std::vector<DataPoint>& points,
                         RegressionResult& result,
                         std::string& error);

bool predictY(const RegressionResult& regression,
              long double x,
              long double& predictedY,
              std::string& error);

#endif
