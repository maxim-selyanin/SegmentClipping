#ifndef COMMON_H
#define COMMON_H
#include <random>

using PointType = int;

class RandomGenerator {
    std::mt19937 gen;
    std::uniform_int_distribution<PointType> dist;

public:
    RandomGenerator(PointType min, PointType max);

    PointType operator()();
};

#endif // COMMON_H
