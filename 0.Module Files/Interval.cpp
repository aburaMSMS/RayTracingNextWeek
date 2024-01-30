#include"Interval.h"

bool Interval::Contains(double value) const
{
    return value >= min && value <= max;
}

bool Interval::Surrounds(double value) const
{
    return value > min && value < max;
}

double Interval::Clamp(double x) const
{
    if (x < min)
    {
        return min;
    }
    if (x > max)
    {
        return max;
    }
    return x;
}

double Interval::Size() const
{
    return max - min;
}

Interval Interval::Expand(double delta) const
{
    return Interval(min - delta / 2., max + delta / 2.);
}