#include "Include.h"

TEST(Vector, Equal)
{
    auto body = [](auto v)
    {
        using V = decltype(v);
        V a, b, c;
        RandomObjectsWithValuesForEqualTest<V>(a, b, c);
        EXPECT_EQ(true, a == b);
        EXPECT_EQ(false, a == c);
    };
    body(JFVector2());
    body(JFVector3());
    body(JFVector4());
}

TEST(Vector, NotEqual)
{
    auto body = [](auto v)
    {
        using V = decltype(v);
        V a, b, c;
        RandomObjectsWithValuesForEqualTest<V>(a, b, c);
        EXPECT_EQ(false, a != b);
        EXPECT_EQ(true, a != c);
    };
    body(JFVector2());
    body(JFVector3());
    body(JFVector4());
}

TEST(Vector, Add)
{
    auto body = [](auto v)
    {
        using V = decltype(v);
        V a = RandomObjectWithValues<V>();
        V b = RandomObjectWithValues<V>();
        V r = SumEachValueOfObject<V>(a, b);
        EXPECT_EQ(r, a + b);
        a += b;
        EXPECT_EQ(r, a);
    };
    body(JFVector2());
    body(JFVector3());
    body(JFVector4());
}

TEST(Vector, Sub)
{
    auto body = [](auto v)
    {
        using V = decltype(v);
        V a = RandomObjectWithValues<V>();
        V b = RandomObjectWithValues<V>();
        V r = SubEachValueOfObject<V>(a, b);
        EXPECT_EQ(r, a - b);
        a -= b;
        EXPECT_EQ(r, a);
    };
    body(JFVector2());
    body(JFVector3());
    body(JFVector4());
}

TEST(Vector, ScalarMultiply)
{
    auto body = [](auto v)
    {
        using V = decltype(v);
        V a = RandomObjectWithValues<V>();
        float s = RandomFloat();
        V r = MulEachValueOfObject<V>(a, s);
        EXPECT_EQ(r, a * s);
        a *= s;
        EXPECT_EQ(r, a);
    };
    body(JFVector2());
    body(JFVector3());
    body(JFVector4());
}

TEST(Vector, Dot)
{
    auto body = [](auto v)
    {
        using V = decltype(v);
        V a = RandomObjectWithValues<V>();
        V b = RandomObjectWithValues<V>();
        int dimension = sizeof(a.scalars) / sizeof(a.scalars[0]);
        float r = 0.0f;
        for (int i = 0; i < dimension; ++i)
        {
            r += a.scalars[i] * b.scalars[i];
        }
        EXPECT_EQ(r, V::Dot(a, b));
    };
    body(JFVector2());
    body(JFVector3());
    body(JFVector4());
}

TEST(Vector, Cross)
{
    JFVector3 v1{ 1.f, 0.f, 0.f };
    JFVector3 v2{ 0.f, 1.f, 0.f };
    JFVector3 answer{0.f, 0.f, 1.f};
    EXPECT_EQ(answer, JFVector3::Cross(v1, v2));
}

TEST(Vector, MulMatrix)
{
    auto body = [](auto v, auto m)
    {
        using V = decltype(v);
        using M = decltype(m);
        v = RandomObjectWithValues<V>();
        m = RandomObjectWithValues<M>();
        int vDimension = sizeof(v.scalars) / sizeof(v.scalars[0]);
        int mDimension = sizeof(m.m[0]) / sizeof(m.m[0][0]);
        V r;
        for (int i = 0; i < vDimension; ++i)
        {
            for (int j = 0; j < mDimension; ++j)
            {
                r.scalars[i] += v.scalars[j] * m.m[j][i];
            }
        }
        EXPECT_EQ(r, v * m);
    };
    body(JFVector2(), JFMatrix2());
    body(JFVector3(), JFMatrix3());
    body(JFVector4(), JFMatrix4());
}

TEST(Vector, Length)
{
    auto body = [](auto v)
    {
        using V = decltype(v);
        v = RandomObjectWithValues<V>();
        int dimension = sizeof(v.scalars) / sizeof(v.scalars[0]);
        float r = 0.0f;
        for (int i = 0; i < dimension; ++i)
        {
            r += v.scalars[i] * v.scalars[i];
        }
        EXPECT_EQ(sqrtf(r), v.Length());
    };
    body(JFVector2());
    body(JFVector3());
    body(JFVector4());
}

TEST(Vector, LengthSq)
{
    auto body = [](auto v)
    {
        using V = decltype(v);
        v = RandomObjectWithValues<V>();
        int dimension = sizeof(v.scalars) / sizeof(v.scalars[0]);
        float r = 0.0f;
        for (int i = 0; i < dimension; ++i)
        {
            r += v.scalars[i] * v.scalars[i];
        }
        EXPECT_EQ(r, v.LengthSq());
    };
    body(JFVector2());
    body(JFVector3());
    body(JFVector4());
}

TEST(Vector, Normalize)
{
    auto body = [](auto v)
    {
        using V = decltype(v);
        v = RandomObjectWithValues<V>();
        V r = v;

        float lenSq = v.LengthSq();
        if (lenSq > 0.0f)
        {
            float lenInv = 1.0f / sqrt(lenSq);
            int vSize = sizeof(v.scalars) / sizeof(v.scalars[0]);
            for (int i = 0; i < vSize; ++i)
            {
                r.scalars[i] *= lenInv;
            }
        }

        EXPECT_EQ(r, v.Normalize());
    };
    body(JFVector2());
    body(JFVector3());
    body(JFVector4());
}
