// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

class Node {
public:
    char value;
    std::vector<std::shared_ptr<Node>> children;

    Node(char val) : value(val) {}
};

class PMTree {
public:
    std::shared_ptr<Node> root;

    PMTree(const std::vector<char>& elements);
};

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
    root = std::make_shared<Node>('\0');  // корень пустой
    build(root, elements);
}

#endif  // INCLUDE_TREE_H_
