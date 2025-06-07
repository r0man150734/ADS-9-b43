// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

class Node {
 public:
    char value;
    std::vector<std::shared_ptr<Node>> children;

    explicit Node(char val) : value(val) {}
};
class PMTree {
 public:
    std::shared_ptr<Node> root;

    explicit PMTree(const std::vector<char>& elements);
};
std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
