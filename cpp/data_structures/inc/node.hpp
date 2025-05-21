#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <optional>

template <typename T>
class Node
{
public:
    Node(std::optional<const T> value, const int level);

    void increaseLevel();

    Node<T> *getNext(const unsigned int level) const;
    void setNext(Node<T> *next, const unsigned int level);

    T getValue() const;
    bool isEmpty() const;

    void print() const;

private:
    std::optional<const T> mValue;
    int mLevel;
    std::vector<Node *> mNext;
};

template <typename T>
Node<T>::Node(std::optional<const T> value, const int level) : mValue(value), mLevel(level)
{
    mNext.resize(level, nullptr);
}

template <typename T>
void Node<T>::increaseLevel()
{
    mNext.resize(mLevel + 1, nullptr);
    mLevel++;
}

template <typename T>
Node<T>* Node<T>::getNext(const unsigned int level) const
{
    if (level >= mLevel)
    {
        std::cerr << "Getting next node failed: Invalid level" << std::endl;
        std::cerr << "Invalid level" << std::endl;
        return nullptr;
    }
    return mNext[level];
}

template <typename T>
void Node<T>::setNext(Node *next, const unsigned int level)
{
    if (level >= mLevel)
    {
        std::cerr << "Setting next node failed: Invalid level" << std::endl;
        std::cerr << "Invalid level" << std::endl;
        return;
    }
    mNext[level] = next;
}

template <typename T>
void Node<T>::print() const
{
    if (!mValue.has_value())
    {
        std::cerr << "Node value is not set" << std::endl;
        return;
    }
    std::cout << "Value: " << mValue.value() << ", Level: " << mLevel << std::endl;
}

template <typename T>
T Node<T>::getValue() const
{
    if (!mValue.has_value())
    {
        std::cerr << "Node value is not set" << std::endl;
        throw std::runtime_error("Node value is not set");
        return -1; // or throw an exception
    }
    return mValue.value();
}

template <typename T>
bool Node<T>::isEmpty() const
{
    return !mValue.has_value();
}

#endif // NODE_HPP