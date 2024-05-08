# AdvisorBot - Cryptocurrency Exchange Data Analysis Tool

AdvisorBot is a command-line program designed to assist cryptocurrency investors in analyzing data from an exchange. It provides various commands to retrieve statistics and predictions based on price data input by the user.

## Features

- **Help Command** (`help`): Displays a list of available commands.
- **Command-Specific Help** (`help cmd`): Provides detailed information about a specific command.
- **Product Calculation** (`prod`): Computes the product of a set of prices.
- **Minimum Price** (`min`): Determines the minimum price from a set of prices.
- **Maximum Price** (`max`): Identifies the maximum price from a set of prices.
- **Average Price** (`Avg`): Calculates the average price from a set of prices.
- **Market Trend Prediction** (`predict`): Predicts future market trends.
- **Current Time** (`time`): Retrieves the current time.
- **Step Details** (`step`): Displays instructions or details for a specific step.

## Implementation Details

The implementation of AdvisorBot includes:
- **Command Parsing**: The program processes user commands through `processUserInput()` which tokenizes and interprets user input.
- **Help System**: Utilizes `printHelp()` to display a general command list and `printHelpCmd(cmd)` to show detailed help for a specific command.
- **Data Analysis**: Performs calculations such as product, minimum, maximum, and average based on user-provided data.
- **Future Market Prediction**: Employs prediction algorithms to forecast market trends.

## Usage

To use AdvisorBot:
1. Clone the repository.
2. Run the program.
3. Enter commands as prompted to analyze cryptocurrency data.

### Command Examples

- `help`: Displays available commands.
- `help prod`: Shows usage information for the product command.
- `prod 10 20 30`: Calculates the product of prices 10, 20, and 30.
- `min 15 25 10`: Determines the minimum price from the given set.
- `predict`: Provides a prediction of future market trends.
