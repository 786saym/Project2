# Preprocessor Directives

## Presentation script

"The program's C++ source and header files are organized under `src/`. Each implementation file includes its corresponding project header, while `src/main.cpp` includes the interfaces it calls. Standard-library headers are included where their functionality is used. Header guards prevent declarations from being included more than once in a translation unit."

## Project headers

- **`src/RegressionCalc.h`:** Declares `DataPoint`, `Correlation`, `RegressionResult`, `calculateRegression`, and `predictY`.
- **`src/FileHandler.h`:** Declares the CSV import function and includes `RegressionCalc.h` for the shared `DataPoint` type.
- **Include guards:** `REGRESSION_CALC_H` and `FILE_HANDLER_H` keep each header's declarations from being processed repeatedly.

## Standard-library headers by file

- **`src/main.cpp`:**
  - `<cmath>` checks entered values with `std::isfinite`.
  - `<iomanip>` formats displayed values to six decimal places.
  - `<iostream>` handles the menu, prompts, and output.
  - `<sstream>` parses complete numeric input lines.
  - `<string>` and `<vector>` provide text and data-point storage.
- **`src/RegressionCalc.cpp`:**
  - `<algorithm>` bounds R-squared to `[0, 1]`.
  - `<cmath>` provides finite-number checks.
- **`src/FileHandler.cpp`:**
  - `<cctype>` supports case-insensitive extension and header checks.
  - `<cmath>` rejects non-finite numeric CSV values.
  - `<fstream>` opens and reads the CSV file.
  - `<sstream>` parses numeric fields and builds error messages.

The headers are included in the files that use their declarations. `src/FileHandler.cpp` explicitly includes `<fstream>` as required for file input. From the project root, build the program with:

```powershell
g++ -std=c++11 -Wall -Wextra -Wpedantic src\main.cpp src\RegressionCalc.cpp src\FileHandler.cpp -o regression_tool.exe
```
