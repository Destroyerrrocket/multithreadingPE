#include <bits/stdc++.h>

namespace Impl {
class Check {
public:
	Check() = default;
	explicit Check(int64_t seed) : seed{seed} {}

	bool operator()(int64_t x, int64_t y) const {
		int64_t localSeed = seed +
			int(x * x * 0x4c1906) +
			(int)x * 0x5ac0db +
			(int)y * y * 0x4307a7L +
			(int) (y * 0x5f24f) ^ 0x3ad8025f;
		localSeed = (localSeed ^ 0x5DEECE66DL) & ((1L << 48) - 1);
		int bits, val;
		do {
			localSeed = (localSeed * 0x5DEECE66DL + 0xBL) & ((1L << 48) - 1);
			bits = (localSeed >> (48 - 31));
			val = bits % 10;
		} while (bits - val + 9 < 0);
		return val == 0;
	}
private:
	int64_t seed;
};
}