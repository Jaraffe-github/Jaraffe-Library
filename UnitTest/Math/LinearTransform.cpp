#include "Include.h"

TEST(LinearTransform, Equal)
{
    auto body = [](auto lt, auto m)
    {
        using LT = decltype(lt);
        using M = decltype(m);
        M a, b, c;
        RandomObjectsWithValuesForEqualTest<M>(a, b, c);
        LT a2(a);
        LT b2(a);
        LT c2(c);
        EXPECT_EQ(true, a2 == b2);
        EXPECT_EQ(false, a2 == c2);
    };
    body(JFLinearTransform2(), JFMatrix2());
    body(JFLinearTransform3(), JFMatrix3());
}

TEST(LinearTransform, NotEqual)
{
    auto body = [](auto lt, auto m)
    {
        using LT = decltype(lt);
        using M = decltype(m);
        M a, b, c;
        RandomObjectsWithValuesForEqualTest<M>(a, b, c);
        LT a2(a);
        LT b2(a);
        LT c2(c);
        EXPECT_EQ(false, a2 != b2);
        EXPECT_EQ(true, a2 != c2);
    };
    body(JFLinearTransform2(), JFMatrix2());
    body(JFLinearTransform3(), JFMatrix3());
}

TEST(LinearTransform, Scale)
{
    auto body = [](auto lt, auto m, auto v)
    {
        using LT = decltype(lt);
        using M = decltype(m);
        using V = decltype(v);
        m = RandomObjectWithValues<M>();
        V s = RandomObjectWithValues<V>();
        M r;
        int dimension = sizeof(m.m[0]) / sizeof(m.m[0][0]);
        for (int i = 0; i < dimension; ++i)
        {
            for (int j = 0; j < dimension; ++j)
            {
                r.m[i][j] = m.m[i][j] * s.value[j];
            }
        }
        EXPECT_EQ(LT(r), LT(m).Scale(s));
    };
    body(JFLinearTransform2(), JFMatrix2(), JFVector2());
    body(JFLinearTransform3(), JFMatrix3(), JFVector3());
}

TEST(LinearTransform, Rotate)
{
    auto checkIdentity = [](auto m) 
    {
        using M = decltype(m);
        auto identity = M();
        int size = sizeof(m.value) / sizeof(m.value[0]);
        for (int i = 0; i < size; ++i)
        {
            using elementType = typename std::remove_reference<decltype(m.value[i])>::type;
            EXPECT_EQ(true, ApproximatelyEqualAbsRel<elementType>(identity.value[i],
                                                                  m.value[i],
                                                                  1e-5f,
                                                                  1e-4f));
        }
    };

    // 모든 직교행렬의 전치행렬은 역행렬이다.
    // 모든 회전행렬은 직교행렬이다.
    auto lt2 = JFLinearTransform2();
    lt2.Rotate(DegreeToRadian(RandomFloat()));
    checkIdentity(lt2.matrix2 * lt2.matrix2.TransposeMatrix());

    auto lt3 = JFLinearTransform3();
    lt3.RotateX(DegreeToRadian(RandomFloat()));
    checkIdentity(lt3.matrix3 * lt3.matrix3.TransposeMatrix());
    
    lt3 = JFLinearTransform3();
    lt3.RotateY(DegreeToRadian(RandomFloat()));
    checkIdentity(lt3.matrix3 * lt3.matrix3.TransposeMatrix());
    
    lt3 = JFLinearTransform3();
    lt3.RotateZ(DegreeToRadian(RandomFloat()));
    checkIdentity(lt3.matrix3 * lt3.matrix3.TransposeMatrix());
    
    auto axis = RandomObjectWithValues<JFVector3>();
    axis.Normalize();
    lt3 = JFLinearTransform3();
    lt3.Rotate(axis, DegreeToRadian(RandomFloat()));
    checkIdentity(lt3.matrix3 * lt3.matrix3.TransposeMatrix());
}

TEST(LinearTransform, Multiply)
{
    auto body = [](auto lt, auto m)
    {
        using LT = decltype(lt);
        using M = decltype(m);
        M m1 = RandomObjectWithValues<M>();
        M m2 = RandomObjectWithValues<M>();
        M r = m1 * m2;
        EXPECT_EQ(LT(r), LT(m1).Multiply(m2));
    };
    body(JFLinearTransform2(), JFMatrix2());
    body(JFLinearTransform3(), JFMatrix3());
}
