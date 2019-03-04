/*
FILE: vector.h
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/18/2019
*/

#pragma once

#include <array>

typedef std::array<float, 2> Vec2;
typedef std::array<float, 3> Vec3;

template <size_t N>
inline std::array<float, N> operator - (const std::array<float, N>& A, const std::array<float, N>& B)
{
    std::array<float, N> ret;
    for (size_t i = 0; i < N; ++i)
        ret[i] = A[i] - B[i];
    return ret;
}

template <size_t N>
inline std::array<float, N> operator + (const std::array<float, N>& A, const std::array<float, N>& B)
{
    std::array<float, N> ret;
    for (size_t i = 0; i < N; ++i)
        ret[i] = A[i] + B[i];
    return ret;
}

template <size_t N>
inline std::array<float, N> operator * (const std::array<float, N>& A, const std::array<float, N>& B)
{
    std::array<float, N> ret;
    for (size_t i = 0; i < N; ++i)
        ret[i] = A[i] * B[i];
    return ret;
}

template <size_t N>
inline std::array<float, N> operator / (const std::array<float, N>& A, const std::array<float, N>& B)
{
    std::array<float, N> ret;
    for (size_t i = 0; i < N; ++i)
        ret[i] = A[i] / B[i];
    return ret;
}

template <size_t N>
inline std::array<float, N> operator * (const std::array<float, N>& A, float B)
{
    std::array<float, N> ret;
    for (size_t i = 0; i < N; ++i)
        ret[i] = A[i] * B;
    return ret;
}

template <size_t N>
inline std::array<float, N> operator - (const std::array<float, N>& A, float B)
{
    std::array<float, N> ret;
    for (size_t i = 0; i < N; ++i)
        ret[i] = A[i] - B;
    return ret;
}

template <size_t N>
inline std::array<float, N> operator + (const std::array<float, N>& A, float B)
{
    std::array<float, N> ret;
    for (size_t i = 0; i < N; ++i)
        ret[i] = A[i] + B;
    return ret;
}

template <size_t N>
inline float DistanceUnitTorroidal(const std::array<float, N>& A, const std::array<float, N>& B)
{
    float axisDistSquaredSum = 0.0f;
    for (size_t i = 0; i < N; ++i)
    {
        float axisDist = B[i] - A[i];
        if (axisDist > 0.5f)
            axisDist = 1.0f - axisDist;
        axisDistSquaredSum += axisDist * axisDist;
    }
    return sqrtf(axisDistSquaredSum);
}
