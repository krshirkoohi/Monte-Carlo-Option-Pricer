#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <numeric>
#include <algorithm> 

using namespace std;

// calculate the payoff of a European call option
double european_call_payoff(double spot, double strike) {
	return std::max(spot - strike, 0.0); // must be postive
};

// main simulation
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
};

int main(int argc, char *argv[]) {
	
	// option parameters
	double spot = 100.0; 
	double strike = 100.0;
	double rate = 0.05;
	double volatility = 0.2;
	double time = 0.1;
	int N = 1e8;
	
	// calculate the option price
	double price = monte_carlo_call_price(spot, strike, rate, volatility, time, N);
	
	// output the result
	std::cout << "European Call Option Price: £" << price << std::endl;
	
	return 0;
};