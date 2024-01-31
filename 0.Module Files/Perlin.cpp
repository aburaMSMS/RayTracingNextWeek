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
double Perlin::TrilinearInterpolation(double volumes[2][2][2], double x, double y, double z)
{
    double c00 = volumes[0][0][0] * (1 - x) + volumes[1][0][0] * x;
    double c01 = volumes[0][0][1] * (1 - x) + volumes[1][0][1] * x;
    double c10 = volumes[0][1][0] * (1 - x) + volumes[1][1][0] * x;
    double c11 = volumes[0][1][1] * (1 - x) + volumes[1][1][1] * x;

    double c0 = c00 * (1 - y) + c10 * y;
    double c1 = c01 * (1 - y) + c11 * y;

    double c = c0 * (1 - z) + c1 * z;

    return c;
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
    auto x = point.X() - std::floor(point.X());
    auto y = point.Y() - std::floor(point.Y());
    auto z = point.Z() - std::floor(point.Z());

    auto i = static_cast<int>(std::floor(point.X()));
    auto j = static_cast<int>(std::floor(point.Y()));
    auto k = static_cast<int>(std::floor(point.Z()));

    double volumes[2][2][2]{};

    for (int delta_i = 0; delta_i < 2; delta_i++)
    {
        for (int delta_j = 0; delta_j < 2; delta_j++)
        {
            for (int delta_k = 0; delta_k < 2; delta_k++)
            {
                volumes[delta_i][delta_j][delta_k] = random_doubles[
                    x_perm[(i + delta_i) & 255] ^ y_perm[(j + delta_j) & 255] ^ z_perm[(k + delta_k) & 255]];
            }
        }
    }

    return TrilinearInterpolation(volumes, x, y, z);
}

Perlin::~Perlin()
{
    delete[] random_doubles;
    delete[] x_perm;
    delete[] y_perm;
    delete[] z_perm;
}