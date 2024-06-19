// standard libraries
#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <numeric>
#include <algorithm> 

// user defined libraries
#include "CoreFuncs.h"
#include "AnalyticalCallPrice.h"
#include "MonteCarloCallPrice.h"

using namespace std;

int main(int argc, char *argv[]) {
	
	// option parameters
	double spot = 100.0; 
	double strike = 100.0;
	double rate = 0.05;
	double volatility = 0.2;
	double time = 0.1;
	int N = 1e6;
	
	// calculate the option price
	double mc_price = monte_carlo_call_price(spot, strike, rate, volatility, time, N);
	double bs_price = black_scholes_call_price(spot, strike, rate, volatility, time);
	float pct_error = abs((mc_price - bs_price)/bs_price) * 100;
	
	// output the result
	std::cout << "Monte Carlo European Call Option Price: £" << mc_price << std::endl;
	std::cout << "Black-Scholes European Call Option Price: £" << bs_price << std::endl;
	std::cout << "Error: " << cast_round(pct_error) << "%" << std::endl;
	
	return 0;
}