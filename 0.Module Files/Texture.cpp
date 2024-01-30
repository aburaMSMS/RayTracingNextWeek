#include"Texture.h"

Color SolidColor::Value(double u, double v, const Point3& point) const
{
    return value;
}

Color CheckerTexture::Value(double u, double v, const Point3& point) const
{
    auto x = static_cast<int>(std::floor(scale * point.X()));
    auto y = static_cast<int>(std::floor(scale * point.Y()));
    auto z = static_cast<int>(std::floor(scale * point.Z()));

    return (x + y + z) % 2 == 0 ? even->Value(u, v, point) : odd->Value(u, v, point);
}