#include "skip_list.hpp"

SkipList::SkipList(unsigned int maxLevel, float probability) : mMaxLevel(maxLevel), mProbability(probability), mLength(0), mCurrentLevel(1)
{

    mHeader = new Node(std::nullopt, mCurrentLevel);
}

void SkipList::print(const unsigned int level) const
{
    if (level == 0 || level > mCurrentLevel)
    {
        std::cout << "Invalid level" << std::endl;
        return;
    }

    Node *current = mHeader->getNext(level - 1);
    while (current != nullptr)
    {
        std::cout << current->getValue() << " ";
        current = current->getNext(level - 1);
    }
    std::cout << std::endl;
}

Node *SkipList::search(const int value)
{
    Node *current = mHeader;

    for (int i = mCurrentLevel - 1; i >= 0; --i)
    {
        while (current->getNext(i) != nullptr && value >= current->getNext(i)->getValue())
        {
            current = current->getNext(i);
        }
    }

    return current;
}

std::pair<Node *, std::vector<Node *>> SkipList::search_with_trail(const int value)
{
    std::vector<Node *> trail(mCurrentLevel, nullptr);
    Node *current = mHeader;
    Node *next = nullptr;

    for (int i = mCurrentLevel - 1; i >= 0; --i)
    {
        while (current->getNext(i) != nullptr && value >= current->getNext(i)->getValue())
        {
            current = current->getNext(i);
        }
        trail[i] = current;
    }

    return std::make_pair(current, trail);
}

Node *SkipList::insert(const int value)
{
    mLength++;
    const int level = randomLevel();
    Node *newNode = new Node(value, level);

    auto node_and_trail = search_with_trail(value);
    auto trail = node_and_trail.second;

    for (int i = 0; i < mCurrentLevel; ++i)
    {
        if (i < level)
        {
            newNode->setNext(trail[i]->getNext(i), i);
            trail[i]->setNext(newNode, i);
        }
        else
        {
            break;
        }
    }

    if (level > mCurrentLevel)
    {
        mCurrentLevel = level;
        mHeader->increaseLevel();
    }

    return newNode;
}

void SkipList::remove(const int value)
{
    Node *position = search(value);

    if (position->isEmpty() || position->getValue() != value)
    {
        std::cerr << "Value : " << value << " not found" << std::endl;
        return;
    }

    Node *current = mHeader;

    for (int i = mCurrentLevel - 1; i >= 0; --i)
    {
        while (current->getNext(i) != nullptr && !current->getNext(i)->isEmpty() && current->getNext(i)->getValue() < value)
        {
            current = current->getNext(i);
        }

        if (current->getNext(i) != nullptr && !current->getNext(i)->isEmpty() && current->getNext(i)->getValue() == value)
        {
            current->setNext(current->getNext(i)->getNext(i), i);
        }
    }

    mLength--;
}

int SkipList::randomLevel()
{
    int level = 1;
    while (static_cast<float>(rand()) / RAND_MAX <= mProbability && (!mMaxLevel || level < mMaxLevel))
    {
        level++;
        if (level > mCurrentLevel)
        {
            break;
        }
    }
    return level;
}
