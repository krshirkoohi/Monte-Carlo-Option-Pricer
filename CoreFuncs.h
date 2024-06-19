// typecast round value function
float cast_round(float num) {
	float val = (int)(num * 100 + .5);
	return (float)val / 100;
}

// calculate cumulative normal distribution
double normal_cdf(double value) {
	return 0.5 * std::erfc(-value * M_SQRT1_2);
}

// calculate the payoff of a European call option
double european_call_payoff(double spot, double strike) {
	return std::max(spot - strike, 0.0); // must be postive
}