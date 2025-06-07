// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
#include "tree.h"

using namespace std;
using namespace std::chrono;

// Генерация вектора символов '1', '2', ...
vector<char> generateAlphabet(int n) {
    vector<char> res;
    for (int i = 1; i <= n; ++i)
        res.push_back('0' + i);
    return res;
}

// Факториал
int factorial(int n) {
    int res = 1;
    for (int i = 2; i <= n; ++i)
        res *= i;
    return res;
}

// Измерение времени одной функции
template<typename Func>
long long measure(Func f) {
    auto start = high_resolution_clock::now();
    f();
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

int main() {
    random_device rd;
    mt19937 gen(rd());

    cout << "n,time_getAll,time_getPerm1,time_getPerm2\n";

    for (int n = 2; n <= 8; ++n) {
        vector<char> alphabet = generateAlphabet(n);
        PMTree tree(alphabet);
        int maxPerms = factorial(n);
        uniform_int_distribution<> distrib(1, maxPerms);

        int randomNum = distrib(gen);  // случайный номер перестановки

        long long t_all = measure([&]() {
            auto perms = getAllPerms(tree);
            (void)perms;
            });

        long long t_p1 = measure([&]() {
            auto perm = getPerm1(tree, randomNum);
            (void)perm;
            });

        long long t_p2 = measure([&]() {
            auto perm = getPerm2(tree, randomNum);
            (void)perm;
            });

        cout << n << ","
            << t_all << ","
            << t_p1 << ","
            << t_p2 << "\n";
    }

    return 0;
}
