#include "FileHandler.h"

#include <cctype>
#include <cmath>
#include <fstream>
#include <sstream>

namespace {

std::string trim(const std::string& value) {
    const std::string whitespace = " \t\r\n";
    const std::string::size_type first = value.find_first_not_of(whitespace);
    if (first == std::string::npos) {
        return std::string();
    }
    const std::string::size_type last = value.find_last_not_of(whitespace);
    return value.substr(first, last - first + 1);
}

std::string lowercase(std::string value) {
    for (char& character : value) {
        character = static_cast<char>(
            std::tolower(static_cast<unsigned char>(character)));
    }
    return value;
}

bool hasCsvExtension(const std::string& path) {
    const std::string::size_type separator = path.find_last_of("/\\");
    const std::string::size_type dot = path.find_last_of('.');
    if (dot == std::string::npos ||
        (separator != std::string::npos && dot < separator)) {
        return false;
    }
    return lowercase(path.substr(dot)) == ".csv";
}

bool parseCsvRow(const std::string& line,
                 std::vector<std::string>& fields,
                 std::string& error) {
    fields.clear();
    std::string::size_type position = 0;

    while (true) {
        while (position < line.size() &&
               (line[position] == ' ' || line[position] == '\t')) {
            ++position;
        }

        std::string field;
        if (position < line.size() && line[position] == '"') {
            ++position;
            bool closedQuote = false;
            while (position < line.size()) {
                if (line[position] == '"') {
                    if (position + 1 < line.size() &&
                        line[position + 1] == '"') {
                        field += '"';
                        position += 2;
                    } else {
                        ++position;
                        closedQuote = true;
                        break;
                    }
                } else {
                    field += line[position++];
                }
            }
            if (!closedQuote) {
                error = "unterminated quoted field";
                return false;
            }
            while (position < line.size() &&
                   (line[position] == ' ' || line[position] == '\t')) {
                ++position;
            }
            if (position < line.size() && line[position] != ',') {
                error = "unexpected characters after a quoted field";
                return false;
            }
            fields.push_back(trim(field));
        } else {
            const std::string::size_type start = position;
            while (position < line.size() && line[position] != ',') {
                if (line[position] == '"') {
                    error = "quote inside an unquoted field";
                    return false;
                }
                ++position;
            }
            fields.push_back(trim(line.substr(start, position - start)));
        }

        if (position == line.size()) {
            break;
        }
        ++position;
        if (position == line.size()) {
            fields.push_back(std::string());
            break;
        }
    }

    return true;
}

bool parseFiniteNumber(const std::string& text, long double& value) {
    std::istringstream input(text);
    long double parsed = 0.0L;
    char extra = '\0';
    if (!(input >> parsed) || (input >> extra) || !std::isfinite(parsed)) {
        return false;
    }
    value = parsed;
    return true;
}

bool isHeader(const std::vector<std::string>& fields) {
    return fields.size() == 2 &&
           lowercase(trim(fields[0])) == "x" &&
           lowercase(trim(fields[1])) == "y";
}

}  // namespace

bool importCsvData(const std::string& path,
                   std::vector<DataPoint>& points,
                   std::string& error) {
    if (!hasCsvExtension(path)) {
        error = "the file name must have a .csv extension";
        return false;
    }

    std::ifstream file(path.c_str());
    if (!file.is_open()) {
        error = "could not open the file";
        return false;
    }

    std::vector<DataPoint> importedPoints;
    std::vector<std::string> fields;
    std::string line;
    std::size_t lineNumber = 0;
    bool firstRecordSeen = false;

    while (std::getline(file, line)) {
        ++lineNumber;
        if (trim(line).empty()) {
            continue;
        }

        std::string parseError;
        if (!parseCsvRow(line, fields, parseError)) {
            std::ostringstream message;
            message << "line " << lineNumber << ": " << parseError;
            error = message.str();
            return false;
        }

        if (!firstRecordSeen) {
            firstRecordSeen = true;
            if (isHeader(fields)) {
                continue;
            }
        }

        if (fields.size() != 2) {
            std::ostringstream message;
            message << "line " << lineNumber
                    << ": expected exactly two comma-separated values";
            error = message.str();
            return false;
        }

        DataPoint point;
        if (!parseFiniteNumber(fields[0], point.x) ||
            !parseFiniteNumber(fields[1], point.y)) {
            std::ostringstream message;
            message << "line " << lineNumber
                    << ": X and Y must each be finite numbers";
            error = message.str();
            return false;
        }
        importedPoints.push_back(point);
    }

    if (file.bad()) {
        error = "an error occurred while reading the file";
        return false;
    }
    if (importedPoints.empty()) {
        error = "the file contains no data points";
        return false;
    }

    points.insert(points.end(), importedPoints.begin(), importedPoints.end());
    error.clear();
    return true;
}
