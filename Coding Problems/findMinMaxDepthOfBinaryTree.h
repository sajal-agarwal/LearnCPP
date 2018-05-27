#pragma once
#include<iostream>
#include<algorithm>
#include<numeric>

template <typename T>
struct Node
{
    T m_data;
    Node *m_left = nullptr;
    Node *m_right = nullptr;

    Node(char data) : m_data(data) {}

    ~Node() {
        if (nullptr != m_left) {
            delete m_left;
            m_left = nullptr;
        }

        if (nullptr != m_right) {
            delete m_right;
            m_right = nullptr;
        }
    }

    Node* left() { return m_left; }

    Node* right() { return m_right; }

    Node const * const left() const { return m_left; }

    Node const * const right() const { return m_right; }

    Node* addLeft(T data) {
        m_left = new Node{ data };
        return m_left;
    }

    Node* addRight(T data) {
        m_right = new Node{ data };
        return m_right;
    }
};

template <typename T>
void findMinimumDepthInBinaryTree(const Node<T> * const root, size_t &min_depth, size_t depth = 1) {
    if (nullptr == root) return;

    if (nullptr == root->left() && nullptr == root->right() && depth < min_depth) {
        min_depth = depth;
        return ;
    }

    findMinimumDepthInBinaryTree(root->left(), min_depth, depth + 1);
    findMinimumDepthInBinaryTree(root->right(), min_depth, depth + 1);
}

#if 0
template <typename T>
size_t findMinimumDepthInBinaryTree(const Node<T> * const root) {
    if (nullptr == root) return 0;

    size_t min_depth = std::numeric_limits<size_t>::max();
    findMinimumDepthInBinaryTree(root, min_depth);
    return min_depth;
}
#endif // 0

template <typename T>
size_t findMinimumDepthInBinaryTree(const Node<T> * const root) {
    if (nullptr == root)
        return 0;

    if (nullptr == root->left() && nullptr == root->right())
        return 1;

    size_t lmin = std::numeric_limits<size_t>::max();
    if (nullptr != root->left())
        lmin = findMinimumDepthInBinaryTree(root->left());

    size_t rmin = std::numeric_limits<size_t>::max();
    if (nullptr != root->right())
        rmin = findMinimumDepthInBinaryTree(root->right());

    return 1 + std::min(lmin, rmin);
}

template <typename T>
size_t findMaximumDepthInBinaryTree(const Node<T> * const root) {
    if (nullptr == root)
        return 0;

    return 1 + std::max(findMaximumDepthInBinaryTree(root->left()),
        findMaximumDepthInBinaryTree(root->right()));
}

int main() {
    Node<char> *root = new Node<char> {'A'};
    auto l1 = root->addLeft('B');
    l1->addLeft('D')->addLeft('F');
    l1->addRight('E')->addLeft('L')->addLeft('K');
    auto r1 = root->addRight('C')->addRight('M')->addRight('P');
    std::cout << "Min Depth: " << findMinimumDepthInBinaryTree(root) << '\n';
    std::cout << "Max Depth: " << findMaximumDepthInBinaryTree(root) << '\n';

    delete root;
}
