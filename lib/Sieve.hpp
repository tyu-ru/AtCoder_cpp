/**
 * @brief prime sieve [0,n]
 * @tparam n
 */
template <std::size_t n>
class Sieve
{
    static_assert(2 <= n);

    // sieve[i] = min prime factor 2i+1
    std::array<std::uint64_t, (n + 1) / 2> sieve = {};
    std::array<std::uint64_t, (n + 1) / 2> primes = {};

public:
    constexpr Sieve()
    {
        sieve[0] = 1; // 1
        primes[0] = 2;
        std::size_t count = 1;
        for (std::size_t i = 1; i < sieve.size(); ++i) {
            if (sieve[i]) continue;
            auto p = 2 * i + 1;
            sieve[i] = p;
            for (std::size_t j = p * p; j / 2 < sieve.size(); j += p * 2) {
                if (sieve[j / 2] == 0) sieve[j / 2] = p;
            }
            primes[count++] = p;
        }
    }
    const std::array<std::uint64_t, (n + 1) / 2> half_sieve() const { return sieve; }
    const std::array<std::uint64_t, (n + 1) / 2> prime() const { return primes; }

    std::vector<std::pair<std::uint64_t, std::uint64_t>> factorization(std::uint64_t x)
    {
        if (x < 2) return {};
        std::vector<std::pair<std::uint64_t, std::uint64_t>> res;
        auto y = __builtin_popcountll((x & -x) - 1);
        x >>= y;
        if (y != 0) res.emplace_back(2, y);
        if (x == 1) return res;

        while (x != 1) {
            auto p = sieve[x / 2];
            if (res.empty() || res.back().first != p) {
                res.emplace_back(p, 1);
            } else {
                ++res.back().second;
            }
            x /= p;
        }
        return res;
    }
};
