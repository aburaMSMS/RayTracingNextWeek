#pragma once

#include"global.h"
#include"Vector3.h"

class Perlin
{
private:
    static void Permute(int* perm);

    static int* GeneratePerm();

private:
    static const int points_num = 256;

public:
    Perlin();

    double Noise(const Point3& point) const;

    ~Perlin();

private:
    double* random_doubles;
    int* x_perm;
    int* y_perm;
    int* z_perm;
};