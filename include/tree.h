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

#endif  // INCLUDE_TREE_H_
