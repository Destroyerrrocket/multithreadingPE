#include <bits/stdc++.h>
#include "check.hh"

struct Config {
	using Row = std::vector<bool>;
	using Pattern = std::vector<Row>;
	Pattern pattern;
	int sizeBunch;
	Impl::Check check;
	int maxThreads;
};

class MultiSearcher {
private:
	bool checkPos(int64_t x_loc, int64_t y_loc);
	void findPrint(int64_t x, int64_t y);
	std::list<std::thread> threads;
	std::atomic<bool> found = false;
	const Config c;
public:
	explicit MultiSearcher(Config &&config) : c(std::move(config)) {}
	~MultiSearcher();

	void printZone(int64_t x, int64_t y);
	inline bool isFound() {return found.load();}
};