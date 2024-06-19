# Monte-Carlo-Option-Pricer

This is a simple program which prices a European call option using a Monte Carlo simulation written in C++.

## Overview

This project provides a C++ implementation for pricing European call options using both Monte Carlo simulation and the Black-Scholes analytical formula. The program calculates and compares the option prices obtained from these two methods to ensure accuracy.

## Requirements

- C++11 or later
- A C++ compiler like `g++`

## Files Description

- **main.cpp**: The main program file that runs the Monte Carlo simulation and Black-Scholes analytical pricing, and prints the results.
- **MonteCarloCallPrice.h**: Header file containing the Monte Carlo simulation function for pricing European call options.
- **AnalyticalCallPrice.h**: Header file containing the Black-Scholes analytical formula function for pricing European call options.
- **CoreFuncs.h**: Header file containing core utility functions, including the cumulative normal distribution function.

## Compilation and Execution

1. **Compile the program**:

    ```sh
    g++ -o OptionPricer main.cpp -std=c++11
    ```

2. **Run the program**:

    ```sh
    ./OptionPricer
    ```

## Program Parameters

- **spot**: The current stock price (e.g., 100.0)
- **strike**: The strike price of the option (e.g., 100.0)
- **rate**: The risk-free interest rate (e.g., 0.05 for 5%)
- **volatility**: The volatility of the underlying stock (e.g., 0.2 for 20%)
- **time**: The time to maturity in years (e.g., 1.0 for one year)
- **num_simulations**: The number of Monte Carlo simulations to run (e.g., 10000)

These parameters can be adjusted within the `main.cpp` file.

## Explanation of Key Functions

**monte_carlo_call_price**: 

```cpp
double monte_carlo_call_price(double spot, double strike, double rate, double volatility, double time, int N) {
	
	// setup random number generator
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> d(0,1);
	
	// store payoffs in a vector
	std::vector<double> payoffs;
	payoffs.reserve(N);
	
	// mc
	for (int i=0; i<N; ++i) {
		double z = d(gen);
		double spot_at_maturity = spot * std::exp((rate - 0.5 * volatility * volatility) * time + volatility * std::sqrt(time) * z);
		double payoff = european_call_payoff(spot_at_maturity, strike);
		payoffs.push_back(payoff);
	};
	
	// calculate average payoff and discout it back to current value
	double average_payoff = std::accumulate(payoffs.begin(), payoffs.end(), 0.0) / N;
	return std::exp(-rate * time) * average_payoff;
}
```

- Generates multiple simulated future stock prices using geometric Brownian motion.
- Calculates the payoff for each simulation.
- Computes the average payoff and discounts it to the present value to obtain the option price.

**black_scholes_call_price**:

```cpp
double black_scholes_call_price(double spot, double strike, double rate, double volatility, double time) {
	double d1 = (std::log(spot / strike) + (rate + 0.5 * volatility * volatility) * time) / (volatility * std::sqrt(time));
	double d2 = d1 - volatility * std::sqrt(time);
	double call_price = spot * normal_cdf(d1) - strike * std::exp(-rate * time) * normal_cdf(d2);
	return call_price;
}
```

- Uses the Black-Scholes formula to calculate the theoretical price of a European call option.
- Provides an analytical solution based on input parameters.

**european_call_payoff**: 

```cpp
double european_call_payoff(double spot, double strike) {
    return std::max(spot - strike, 0.0);
}
```

Returns the payoff for a European call option at maturity.

**cast_round**:

```cpp
// typecast round value function
float cast_round(float num) {
	float val = (int)(num * 100 + .5);
	return (float)val / 100;
}
```

Returns a value to 2 decimal places, used in outputting error percentage.

**normal_cdf**:

```cpp
// calculate cumulative normal distribution
double normal_cdf(double value) {
	return 0.5 * std::erfc(-value * M_SQRT1_2);
}
```

Returns the cumulative normal distribution of a value.

## Output

The program will output three values:
1. The Monte Carlo estimate
2. The analytical solution using the Black-Scholes formula
3. The percentage error between the two, to 2 decimal places

## Notes

- The accuracy of the Monte Carlo simulation improves with an increasing number of simulations.
- Ensure the parameters are set to realistic values to obtain meaningful results.
- The Black-Scholes formula assumes continuous compounding and constant volatility.
