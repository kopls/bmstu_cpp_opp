#ifndef CONCEPT_H
#define CONCEPT_H

#include <concepts>
#include <type_traits>

template<typename Type>
concept VectorElement = true;

template<typename Type, typename Type2>
concept ConvertibleTo = std::convertible_to<Type2, Type>;

template<typename Type, typename Type2>
concept EqualityComparableWith = std::equality_comparable_with<Type2, Type>;

template<typename Type, typename Type2>
concept SupportSum = requires (const Type &t, const Type2 &t2)
{
    {t + t2} -> std::convertible_to<std::common_type_t<Type, Type2>>;
};

template<typename Type, typename Type2>
concept SupportSub = requires (const Type &t, const Type2 &t2)
{
    {t - t2} -> std::convertible_to<std::common_type_t<Type, Type2>>;
};

template<typename Type, typename Type2>
concept SupportProd = requires (const Type &t, const Type2 &t2)
{
    {t * t2} -> std::convertible_to<std::common_type_t<Type, Type2>>;
};

template<typename Type, typename Type2>
concept SupportQuot = requires (const Type &t, const Type2 &t2)
{
    {t / t2} -> std::convertible_to<std::common_type_t<Type, Type2>>;
};

template<typename Type, typename Type2>
concept SupportsSumMul = SupportProd<Type, Type2> && SupportQuot<Type, Type2>;

template<typename Type, typename Type2>
concept ConvertibleToDouble = std::convertible_to<Type, double>;

#endif
