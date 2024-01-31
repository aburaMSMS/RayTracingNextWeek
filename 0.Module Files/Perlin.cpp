#include"Perlin.h"

void Perlin::Permute(int* perm)
{
    for (int i = points_num - 1; i > 0; i--)
    {
        auto j = RandomInt(0, i);

        std::swap(perm[i], perm[j]);
    }
}

int* Perlin::GeneratePerm()
{
    auto perm = new int[points_num];

    for (int i = 0; i < points_num; i++)
    {
        perm[i] = i;
    }

    Permute(perm);

    return perm;
}

Perlin::Perlin()
{
    random_doubles = new double[points_num];

    for (int i = 0; i < points_num; i++)
    {
        random_doubles[i] = RandomDouble();
    }

    x_perm = GeneratePerm();
    y_perm = GeneratePerm();
    z_perm = GeneratePerm();
}

double Perlin::Noise(const Point3& point) const
{
    auto i = static_cast<int>(4 * point.X()) & (points_num - 1);
    auto j = static_cast<int>(4 * point.Y()) & (points_num - 1);
    auto k = static_cast<int>(4 * point.Z()) & (points_num - 1);

    return random_doubles[x_perm[i] ^ y_perm[j] ^ z_perm[k]];
}

Perlin::~Perlin()
{
    delete[] random_doubles;
    delete[] x_perm;
    delete[] y_perm;
    delete[] z_perm;
}