#include <bits/stdc++.h>
#include "multisearcher.hh"
// helper function to read elements
template<class T>
T read(T &&d = T()) {
	T t;
	return std::cin >> t ? t : d;
}

int main() {
	// prepare execution
	Config config;
	std::cout << "Threads? ";
	config.maxThreads = read(10);
	std::cout << "Seed? (9056937456303588968) ";
	config.check = Impl::Check(read(9056937456303588968));
	std::cout << "SizeBunch? (8192) ";
	config.sizeBunch = read(8192);
	std::cout << "Rows/columns? ";
	int rows = read(0);
	int columns = read(0);
	std::cout << "Data? ";
	config.pattern = Config::Pattern(rows,Config::Row(columns));
	for (auto &row : config.pattern)
		for (auto it = row.begin(); it != row.end(); ++it)
			*it = read<int>() > 0;

	// Start search
	MultiSearcher searcher(std::move(config));
	#define DO_ZONE(x, y) \
		searcher.printZone(x, y); \
		if (searcher.isFound()) return 0;
	//DO_ZONE(0,0);
	for (int r = 1; r <= 3; ++r) {
		for (int x = -r; x <= r; ++x) {
			DO_ZONE(x, r);
			DO_ZONE(x, -r);
		}
		for (int y = -r+1; y < r; ++y) {
			DO_ZONE(r, y);
			DO_ZONE(-r, y);
		}
	}
	#undef DO_ZONE
}