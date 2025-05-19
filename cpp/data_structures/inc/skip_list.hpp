#include "node.hpp"

class SkipList
{
public:
    SkipList(unsigned int maxLevel, float probability);

    void print(const unsigned int level) const;
    int getLength() const { return mLength; }
    int getCurrentLevel() const { return mCurrentLevel; }

    Node *search(const int value);
    std::pair<Node *, std::vector<Node *>> search_with_trail(const int value);

    Node *insert(const int value);
    void remove(const int value);

private:
    int randomLevel();

    const unsigned int mMaxLevel;
    const float mProbability;
    int mLength;
    int mCurrentLevel;
    Node *mHeader;
};