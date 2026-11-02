# User Interface & Execution

## Presentation script

"`main` runs a continuous menu loop. Each choice calls a small UI operation, the regression module, or the CSV importer. Invalid menu choices are reported and the menu appears again. Choosing 7 ends the loop; end-of-input also exits safely. All normal exit paths reach `return 0`."

## Menu options

1. **Add a data point:** Prompts for X and Y, requiring each entry to be exactly one finite number.
2. **Calculate regression:** Displays the slope, Y-intercept, R-squared, and direction label when the data is sufficient.
3. **Display data points:** Lists the current points, or reports that there are none.
4. **Clear all data points:** Removes the current points.
5. **Predict Y for an X value:** Fits the current data and prompts for a finite X, then displays the forecast.
6. **Import data points from CSV:** Prompts for a `.csv` path and appends valid imported rows to the current data.
7. **Exit:** Ends the loop and prints a goodbye message.

An unrecognized menu choice displays an error and does not terminate the program.

## CSV input

The CSV file must have a `.csv` extension, case-insensitively. Each nonblank row must contain exactly two finite numeric fields separated by a comma. A first nonblank row with the header `X,Y` is optional; header matching ignores case and surrounding spaces. Quoted fields are accepted, including escaped quotes. If a row is malformed or cannot be read, the importer reports the line or file error and does not append a partial import.

## How input ends safely

- If reading a menu choice reaches end-of-input, `main` leaves the loop.
- If input ends during point entry or while requesting a CSV path, the relevant operation returns failure to the loop, which exits.
- If input ends while entering a forecast X, the forecast is abandoned; the next menu read detects end-of-input and exits.
- Choosing option 7 ends the loop normally.

Each path leaves `main` through its final `return 0`. Invalid numeric input during point entry or forecasting is rejected and prompted again while input remains available.
