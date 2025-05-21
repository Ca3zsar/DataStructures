#ifndef SKIP_LIST_HPP
#define SKIP_LIST_HPP

#include "node.hpp"

template <typename T>
class SkipList
{
public:
    SkipList(unsigned int maxLevel, float probability);

    void print(const unsigned int level) const;
    int getLength() const { return mLength; }
    int getCurrentLevel() const { return mCurrentLevel; }

    Node<T> *search(const T value);
    std::pair<Node<T> *, std::vector<Node<T> *>> search_with_trail(const T value);

    Node<T> *insert(const T value);
    void remove(const T value);

private:
    int randomLevel();

    const unsigned int mMaxLevel;
    const float mProbability;
    int mLength;
    int mCurrentLevel;
    Node<T> *mHeader;
};

template <typename T>
SkipList<T>::SkipList(unsigned int maxLevel, float probability) : mMaxLevel(maxLevel), mProbability(probability), mLength(0), mCurrentLevel(1)
{
    mHeader = new Node<T>(std::nullopt, mCurrentLevel);
}

template <typename T>
void SkipList<T>::print(const unsigned int level) const
{
    if (level == 0 || level > mCurrentLevel)
    {
        std::cout << "Invalid level" << std::endl;
        return;
    }

    Node<T> *current = mHeader->getNext(level - 1);
    while (current != nullptr)
    {
        std::cout << current->getValue() << " ";
        current = current->getNext(level - 1);
    }
    std::cout << std::endl;
}

template <typename T>
Node<T>* SkipList<T>::search(const T value)
{
    Node<T> *current = mHeader;

    for (int i = mCurrentLevel - 1; i >= 0; --i)
    {
        while (current->getNext(i) != nullptr && value >= current->getNext(i)->getValue())
        {
            current = current->getNext(i);
        }
    }

    return current;
}

template <typename T>
std::pair<Node<T> *, std::vector<Node<T>*>> SkipList<T>::search_with_trail(const T value)
{
    std::vector<Node<T> *> trail(mCurrentLevel, nullptr);
    Node<T> *current = mHeader;
    Node<T> *next = nullptr;

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

template <typename T>
Node<T> *SkipList<T>::insert(const T value)
{
    mLength++;
    const int level = randomLevel();
    Node<T> *newNode = new Node<T>(value, level);

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

template <typename T>
void SkipList<T>::remove(const T value)
{
    Node<T> *position = search(value);

    if (position->isEmpty() || position->getValue() != value)
    {
        std::cerr << "Value : " << value << " not found" << std::endl;
        return;
    }

    Node<T> *current = mHeader;

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

template <typename T>
int SkipList<T>::randomLevel()
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

#endif // SKIP_LIST_HPP