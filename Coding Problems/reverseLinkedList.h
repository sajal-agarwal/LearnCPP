#pragma
#include<iostream>
#include<memory>
#include<random>
#include<type_traits>
#include<numeric>


struct Node {
    int data;
    Node *next = nullptr;
};

template<size_t N, size_t MAX = std::numeric_limits<int>::max()>
Node* make_list() {
    static_assert(N != 0, "Size of linked list can not be zero");
    Node *head = new Node{ std::rand() };
    for (int i = 0; i < N - 1; ++i) {
        Node *n = new Node{ std::rand() % MAX};
        n->next = head;
        head = n;
    }
    return head;
}

void print_list(Node* head) {
    if (nullptr == head)
        return;

    std::cout << head->data << "  ";

    print_list(head->next);
}

#if 0
Node* rec_reverseLinkedList(Node * const head) {
    if (nullptr == head->next)
        return head;

    auto tail = rec_reverseLinkedList(head->next);

    tail->next = head;

    return head;
}
#endif // 0

Node* reverseLinkedList(Node * const head) {
    if (nullptr == head)
        return nullptr;

    if (nullptr == head->next)
        return head;

    auto tail =  reverseLinkedList(head->next);

    head->next->next = head;

    head->next = nullptr;

    return tail;
}

int main() {
    auto head = make_list<10, 50>();
    std::cout << "Before:\n";
    print_list(head);
    std::cout << '\n';
    std::cout << "After:\n";
    print_list(reverseLinkedList(head));
    std::cout << '\n';
}
