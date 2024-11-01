
# QuantSim Project

This project is a quantitative finance simulation tool using Monte Carlo methods to price financial derivatives. 
It includes multiple strategies for asset path generation and supports various payoff structures.

## Features

- **Monte Carlo Simulation** for option pricing
- **Statistical Strategies** including Standard Normal and Heston processes
- **Flexible Payoff Calculation** with Call and Put options
- **Multithreading** enabled through a customizable thread pool
- **Factory Pattern** for creating payoff types dynamically
- **Google Test Integration** for testing

## Requirements

- **C++17** or later
- **CMake 3.10** or higher
- **Google Test** for unit testing (downloaded automatically if not found locally)

## Installation

### Step 1: Clone the Repository

```bash
git clone <repository_url>
cd QuantSim
```

### Step 2: Build the Project

1. **Create a build directory** and navigate to it:

    ```bash
    mkdir build && cd build
    ```

2. **Run CMake** to configure the project:

    ```bash
    cmake ..
    ```

3. **Compile the project** using `make`:

    ```bash
    make
    ```

### Step 3: Run the Executable

- Run the main application to see Monte Carlo simulation results:

    ```bash
    ./QuantSim
    ```

### Step 4: Run Tests

- To verify functionality, run the test suite:

    ```bash
    ./QuantSim_tests
    ```

## Project Structure

- **`src/`** - Contains the main source files for the Monte Carlo simulation and strategies.
- **`include/`** - Header files for the classes, organized by functionality.
- **`tests/`** - Unit tests for each major component.
- **`CMakeLists.txt`** - CMake configuration file for building the project and setting up Google Test.

## Example Usage

The main application (`main.cpp`) demonstrates how to set up and run a Monte Carlo simulation with both `StandardNormalStrategy` and `HestonStrategy`.

Example code:

```cpp
double initial_spot = 100.0;
double strike = 100.0;
size_t num_sims = 100000;

ThreadPool pool(4);
auto strategy = std::make_shared<StandardNormalStrategy>(initial_spot, 0.05, 0.2);
auto payoff = std::make_unique<PayOffCall>(strike);
MonteCarloSimulation mc_simulation(num_sims, strategy, std::move(payoff), pool);
double result = mc_simulation.run();
std::cout << "Simulation result: " << result << std::endl;
```

## Contributing

Feel free to submit pull requests or report issues. Contributions are welcome!

## License

This project is licensed under the MIT License.
