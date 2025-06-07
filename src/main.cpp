// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
#include "tree.h"

std::vector<char> generateAlphabet(int32_t n) {
    std::vector<char> res;
    for (int32_t i = 1; i <= n; ++i)
        res.push_back('0' + i);
    return res;
}

int32_t factorial(int32_t n) {
    int32_t res = 1;
    for (int32_t i = 2; i <= n; ++i)
        res *= i;
    return res;
}

template<typename Func>
int64_t measure(Func f) {
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::cout << "n,time_getAll,time_getPerm1,time_getPerm2\n";

    for (int32_t n = 2; n <= 8; ++n) {
        auto alphabet = generateAlphabet(n);
        PMTree tree(alphabet);
        int32_t maxPerms = factorial(n);

        if (maxPerms == 0) {
            std::cerr << "factorial overflow or invalid input for n=" << n << "\n";
            continue;
        }

        std::uniform_int_distribution<int32_t> distrib(1, maxPerms);
        int32_t randomNum = distrib(gen);

        int64_t t_all = measure([&]() {
            auto perms = getAllPerms(tree);
            (void)perms;
        });

        int64_t t_p1 = measure([&]() {
            auto perm = getPerm1(tree, randomNum);
            (void)perm;
        });

        int64_t t_p2 = measure([&]() {
            auto perm = getPerm2(tree, randomNum);
            (void)perm;
        });

        std::cout << n << ","
                  << t_all << ","
                  << t_p1 << ","
                  << t_p2 << "\n";
    }

    return 0;
}

