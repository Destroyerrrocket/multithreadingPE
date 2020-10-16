#include "multisearcher.hh"

MultiSearcher::~MultiSearcher() {
	for (auto &thread : threads) thread.join();
}

bool MultiSearcher::checkPos(int64_t x_loc, int64_t y_loc)
{
	for (auto y = 0; y < c.pattern.size(); ++y) {
		for (auto x = 0; x < c.pattern[0].size(); ++x) {
			if (c.check(x+x_loc,y+y_loc) != c.pattern[y][x])
				return false;
		}
	}
	return true;
}

static std::atomic<int> count = 0;
void MultiSearcher::findPrint(int64_t x, int64_t y)
{
	int IAM = count.fetch_add(1);
	if (found.load()) return;
	int64_t chunkx = x * c.sizeBunch;
	int64_t chunky = y * c.sizeBunch;
	// First item to check
	for (int64_t y_loc = chunky; y_loc < c.sizeBunch + chunky; ++y_loc) {
		for (int64_t x_loc = chunkx; x_loc < c.sizeBunch + chunkx; ++x_loc) {
			if (checkPos(x_loc, y_loc)) {
				found.store(true);
				std::stringstream output;
				output << IAM << " found on " << x_loc << ", " << y_loc << std::endl;
				std::cout << output.str() << std::flush;
				return;
			}
			if (found.load()) return;
		}
	}
}

void MultiSearcher::printZone(int64_t x, int64_t y) {
	while (threads.size() == c.maxThreads) {
		auto it = threads.begin();
		while(it != threads.end() && !it->joinable()) ++it;
		if (it != threads.end()) {
			it->join();
			threads.erase(it);
		}
	}
	threads.emplace_back(&MultiSearcher::findPrint, this, x,y);
}