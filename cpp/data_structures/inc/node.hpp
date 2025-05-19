#include <iostream>
#include <vector>
#include <cstdlib>
#include <optional>

class Node
{
public:
    Node(std::optional<const int> value, const int level);

    void increaseLevel();

    Node *getNext(const unsigned int level) const;
    void setNext(Node *next, const unsigned int level);

    int getValue() const;
    bool isEmpty() const;

    void print() const;

private:
    std::optional<const int> mValue;
    int mLevel;
    std::vector<Node *> mNext;
};
