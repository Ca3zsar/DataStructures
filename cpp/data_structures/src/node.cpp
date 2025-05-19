#include "node.hpp"

Node::Node(std::optional<const int> value, const int level) : mValue(value), mLevel(level)
{
    mNext.resize(level, nullptr);
}

void Node::increaseLevel()
{
    mNext.resize(mLevel + 1, nullptr);
    mLevel++;
}

Node *Node::getNext(const unsigned int level) const
{
    if (level >= mLevel)
    {
        std::cerr << "Getting next node failed: Invalid level" << std::endl;
        std::cerr << "Invalid level" << std::endl;
        return nullptr;
    }
    return mNext[level];
}

void Node::setNext(Node *next, const unsigned int level)
{
    if (level >= mLevel)
    {
        std::cerr << "Setting next node failed: Invalid level" << std::endl;
        std::cerr << "Invalid level" << std::endl;
        return;
    }
    mNext[level] = next;
}

void Node::print() const
{
    if (!mValue.has_value())
    {
        std::cerr << "Node value is not set" << std::endl;
        return;
    }
    std::cout << "Value: " << mValue.value() << ", Level: " << mLevel << std::endl;
}

int Node::getValue() const
{
    if (!mValue.has_value())
    {
        std::cerr << "Node value is not set" << std::endl;
        throw std::runtime_error("Node value is not set");
        return -1; // or throw an exception
    }
    return mValue.value();
}

bool Node::isEmpty() const
{
    return !mValue.has_value();
}