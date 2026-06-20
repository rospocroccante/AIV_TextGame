#pragma once

#include <random>
#include <string>

// static-only helper, not instantiable
class RandomGen {
public:
    RandomGen() = delete;
    RandomGen(const RandomGen&) = delete;
    RandomGen& operator=(const RandomGen&) = delete;

    static int getIntInRange(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(engine());
    }

    static char getRandomChar() {
        return static_cast<char>(getIntInRange('A', 'Z'));
    }

    static std::string getRandomString(int size) {
        std::string result;
        result.reserve(static_cast<std::size_t>(size));
        for (int i = 0; i < size; ++i) {
            result.push_back(getRandomChar());
        }
        return result;
    }

private:
    static std::mt19937& engine() {
        static std::mt19937 gen{std::random_device{}()};
        return gen;
    }
};
