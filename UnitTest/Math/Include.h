#pragma once

#include "Math/JFMath.h"
using namespace JFL;

#include "gtest/gtest.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <random>
#include <limits>
#include <algorithm>

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<float> dis(-100, 100);

template<class T>
float DegreeToRadian(T degree)
{
    return degree * static_cast<T>(M_PI) / 180.f;
}

template<class T>
float RadianToDegree(T radian)
{
    return radian * 180.f / static_cast<T>(M_PI);
}

static float RandomFloat()
{
    return dis(gen);
}

template<class T>
T RandomObjectWithValues()
{
    T r;
    int len = sizeof(r.value) / sizeof(r.value[0]);
    for (int i = 0; i < len; ++i)
    {
        r.value[i] = RandomFloat();
    }
    return r;
}

template<class T>
void RandomObjectsWithValuesForEqualTest(T& a, T& b, T& c)
{
    a = RandomObjectWithValues<T>();
    b = a;
    c = RandomObjectWithValues<T>();
    while (a.value[0] == c.value[0])
        c = RandomObjectWithValues<T>();
}

template<class T>
T SumEachValueOfObject(const T& a, const T& b)
{
    T r;
    int len = sizeof(r.value) / sizeof(r.value[0]);
    for (int i = 0; i < len; ++i)
    {
        r.value[i] = a.value[i] + b.value[i];
    }
    return r;
}

template<class T>
T SubEachValueOfObject(const T& a, const T& b)
{
    T r;
    int len = sizeof(r.value) / sizeof(r.value[0]);
    for (int i = 0; i < len; ++i)
    {
        r.value[i] = a.value[i] - b.value[i];
    }
    return r;
}

template<class T>
T MulEachValueOfObject(const T& a, float s)
{
    T r;
    int len = sizeof(r.value) / sizeof(r.value[0]);
    for (int i = 0; i < len; ++i)
    {
        r.value[i] = a.value[i] * s;
    }
    return r;
}

// return true if the difference between a and b is less than absEpsilon, or within relEpsilon percent of the larger of a and b 
template<class F>
bool ApproximatelyEqualAbsRel(F a, F b, F absEpsilon, F relEpsilon)
{ 
    // Check if the numbers are really close -- needed when comparing numbers near zero. 
    double diff = std::fabs(a - b);
    if (diff <= absEpsilon) 
        return true; 
    
    // Otherwise fall back to Knuth's algorithm 
    return diff <= ( (std::fabs(a) < std::fabs(b) ? std::fabs(b) : std::fabs(a)) * relEpsilon);
}
