// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include "tree.h"

static void build(std::shared_ptr<Node> node, const std::vector<char>& remaining) {
    if (remaining.empty()) return;

    for (size_t i = 0; i < remaining.size(); ++i) {
        char val = remaining[i];
        auto child = std::make_shared<Node>(val);
        node->children.push_back(child);

        std::vector<char> next_remaining = remaining;
        next_remaining.erase(next_remaining.begin() + i);
        build(child, next_remaining);
    }
}

PMTree::PMTree(const std::vector<char>& elements) {
    root = std::make_shared<Node>('\0');
    build(root, elements);
}

static void collect(std::shared_ptr<Node> node,
    std::vector<char>& path,
    std::vector<std::vector<char>>& result) {
    if (node->value != '\0')
        path.push_back(node->value);

    if (node->children.empty()) {
        result.push_back(path);
    }
    else {
        for (auto& child : node->children) {
            collect(child, path, result);
        }
    }

    if (!path.empty())
        path.pop_back();
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> path;
    collect(tree.root, path, result);
    return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    auto all = getAllPerms(tree);

    if (num < 1 || num > static_cast<int>(all.size()))
        return {};

    return all[num - 1];
}

static int factorial(int n) {
    int res = 1;
    for (int i = 2; i <= n; ++i) res *= i;
    return res;
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    std::vector<char> result;
    std::vector<char> available;

    for (auto& child : tree.root->children)
        available.push_back(child->value);

    int n = available.size();
    int totalPerms = factorial(n);

    if (num < 1 || num > totalPerms)
        return {};

    --num;

    for (int i = n; i > 0; --i) {
        int f = factorial(i - 1);
        int index = num / f;
        num %= f;

        result.push_back(available[index]);
        available.erase(available.begin() + index);
    }

    return result;
}
