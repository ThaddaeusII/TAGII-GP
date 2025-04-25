#pragma once

#include <emp/math/Random.hpp>

class RandomGenerator {
public:
    static emp::Random& get() {
        static emp::Random instance;
        return instance;
    }

private:
    RandomGenerator() = default;
};