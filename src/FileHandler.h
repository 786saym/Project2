#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "RegressionCalc.h"

#include <string>
#include <vector>

bool importCsvData(const std::string& path,
                   std::vector<DataPoint>& points,
                   std::string& error);

#endif
