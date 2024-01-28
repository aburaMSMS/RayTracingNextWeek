#pragma once

#include"global.h"

class Interval
{
public:
    static const Interval empty, universe;

public:
    double min;
    double max;

    Interval() :min(_INFINITY), max(-_INFINITY) {}
    Interval(double _min, double _max) :min(_min), max(_max) {}

    bool Contains(double value) const;

    bool Surrounds(double value) const;

    double Clamp(double x) const;
};

const static Interval empty;
const static Interval universe(-_INFINITY, INFINITY);
