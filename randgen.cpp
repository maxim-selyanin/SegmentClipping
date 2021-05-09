#include "randgen.h"

RandomGenerator::RandomGenerator(PointType min, PointType max)
    : gen(std::random_device()())
    , dist(min, max)
{}

PointType RandomGenerator::operator()() {
    return dist(gen);
}
