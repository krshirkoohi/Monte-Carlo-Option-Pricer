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
