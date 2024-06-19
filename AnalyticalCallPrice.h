double black_scholes_call_price(double spot, double strike, double rate, double volatility, double time) {
	double d1 = (std::log(spot / strike) + (rate + 0.5 * volatility * volatility) * time) / (volatility * std::sqrt(time));
	double d2 = d1 - volatility * std::sqrt(time);
	double call_price = spot * normal_cdf(d1) - strike * std::exp(-rate * time) * normal_cdf(d2);
	return call_price;
}
