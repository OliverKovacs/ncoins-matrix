#include <iostream>
#include <cstdint>
#include <array>
#include <stack>
#include <numeric>

template <typename T, size_t S>
constexpr size_t sum(const std::array<T, S> a) {
    size_t out = 0;
    for (const auto e : a) out += e;
    return out;
}

const int64_t P = 1000000007;
constexpr std::array<int64_t, 8> COINS = { 1, 2, 5, 10, 20, 50, 100, 200 };
// constexpr std::array<int64_t, 4> COINS = { 1, 2, 5, 10 };
using mat = std::array<std::array<int64_t, sum(COINS)>, sum(COINS)>;
using vec = std::array<std::array<int64_t, sum(COINS)>, 1>;
mat m = {};
std::array<mat, 2> m2 = {};
size_t m_curr = 0;
vec v = {};
std::stack<bool> stack;

template<const size_t N, const size_t M, const size_t K>
void mat_mul(
    std::array<std::array<int64_t, N>, K> &out,
    std::array<std::array<int64_t, N>, M> &a,
    std::array<std::array<int64_t, M>, K> &b
) {
    for (size_t i = 0; i < out.size(); i++) {
        for (size_t j = 0; j < out[0].size(); j++) {
            int64_t sum = 0;
            for (size_t k = 0; k < a.size(); k++) {
                sum += (a[k][j] * b[i][k]) % P;
            }
            out[i][j] = sum % P; 
        }
    }
}

int main() {
    int64_t n;
    std::cin >> n;
    n += COINS.size() - 2;
    
    v[0][v[0].size() - 1] = 1;
    v[0][v[0].size() - 3] = 1;    

    int64_t index = 0;
    for (int64_t i = COINS.size() - 1; i >= 1; i--) {
        for (size_t j = 0; j < COINS[i] - 1; j++) {
            m[index + j][index + j + 1] = 1;
        }
        m[index + COINS[i] - 1][index] = 1;
        m[index + COINS[i]][index] = 1;
        index += COINS[i];
    }
    m[m.size() - 1][m.size() - 1] = 1;

    for (size_t i = 0; i < m.size(); i++) {
        for (size_t j = 0; j < m.size(); j++) {
            m2[0][i][j] = m[i][j];
            m2[1][i][j] = m[i][j];
        }
    }
 
    while (n != 1) {
        stack.push(n & 1);
        if (n & 1) n--;
        else n /= 2;
    }
    
    while (!stack.empty()) {
        if (stack.top()) {
            mat_mul(m2[m_curr ^ 1], m2[m_curr], m);
        }
        else {
            mat_mul(m2[m_curr ^ 1], m2[m_curr], m2[m_curr]);
        }
        m_curr ^= 1;
        stack.pop();
    }

    mat_mul(v, m2[m_curr], v);
    std::cout << v[0][0] << std::endl;
}
