# Core Logic

## Presentation script

"The calculation module is separate from the terminal interface. `calculateRegression` validates the data, finds the means of X and Y, and calculates the least-squares slope and intercept. It also calculates R-squared from the residual sum of squares. The result includes a direction label based on the slope. `predictY` uses the fitted line to estimate Y for a new X value."

## Regression calculation

1. **Validate the data.** At least two points are required, and every X and Y value must be finite.
2. **Calculate the means.** The function computes `meanX` and `meanY` from all points, then verifies that the results are finite.
3. **Accumulate centered sums.** For each point it calculates `centeredX = x - meanX` and `centeredY = y - meanY`, then accumulates:
   - `sumXX`: the sum of `centeredX * centeredX`
   - `sumXY`: the sum of `centeredX * centeredY`
   - `sumYY`: the sum of `centeredY * centeredY`
4. **Check for an undefined line.** If `sumXX` is zero, all X values are equal and no regression slope can be calculated. Non-finite accumulated sums are reported as numeric overflow.
5. **Calculate the fitted line.**
   - `slope = sumXY / sumXX`
   - `intercept = meanY - slope * meanX`
   - The resulting line is `y = slope * x + intercept`.
6. **Calculate R-squared.** The function computes the residual sum of squares from the fitted line and uses `1 - residualSumSquares / sumYY`. The result is bounded to the interval `[0, 1]` to avoid small numerical excursions. If all Y values are identical (`sumYY == 0`), the implementation reports R-squared as `1`.
7. **Classify the direction.** Positive slope produces `Correlation::Positive`, negative slope produces `Correlation::Negative`, and a zero slope produces `Correlation::Neither`.

The displayed `POSITIVE` or `NEGATIVE` classification describes the direction of the fitted slope; it is not a separate correlation-coefficient strength measurement.

## Forecasting

`predictY` evaluates the fitted line with `predictedY = slope * x + intercept`. It rejects non-finite X values and reports an error if the computed forecast is not finite.

## Error handling

Calculation and forecasting functions return `true` on success and `false` on failure, placing a user-readable explanation in the `error` string. The UI displays that message. This keeps mathematical logic independent of console output.
