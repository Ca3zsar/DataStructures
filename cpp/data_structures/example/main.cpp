#include <skip_list.hpp>
#include <iostream>
#include <random>

int getRandomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

int main() {
    constexpr int MAX_LEVEL = 16;
    constexpr int MAX_VALUE = 10;
    constexpr int MAX_SKIP_LIST_SIZE = 100;

    int value = 0;

    SkipList s(MAX_LEVEL, 0.5);
    for (int i = 0; i < MAX_SKIP_LIST_SIZE; ++i) {
        value = getRandomInt(0, MAX_VALUE);
        s.insert(value);
    }

    std::cout<< "Skip List size : " << s.getLength() << std::endl;
    std::cout<< "Skip List level : " << s.getCurrentLevel() << std::endl;

    std::cout << "Skip List content : " << std::endl;
    // s.print(1);

    for (int i = 0; i < MAX_SKIP_LIST_SIZE; ++i) {
        value = getRandomInt(0, MAX_VALUE);
        s.remove(value);
    }

    std::cout<< "Skip List size : " << s.getLength() << std::endl;

    return 0;
}