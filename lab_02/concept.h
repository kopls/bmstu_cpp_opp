#ifndef CONCEPT_H
#define CONCEPT_H

#include <concepts>

template<typename Type, typename Type2>
concept support_sum = requires (const Type &t, const Type2 &t2)
{
    {t + t2} -> std::convertible_to<std::common_type_t<Type, Type2>>;
};

template<typename Type, typename Type2>
concept support_sub = requires (const Type &t, const Type2 &t2)
{
    {t - t2} -> std::convertible_to<std::common_type_t<Type, Type2>>;
};

template<typename Type, typename Type2>
concept support_prod = requires (const Type &t, const Type2 &t2)
{
    {t * t2} -> std::convertible_to<std::common_type_t<Type, Type2>>;
};

template<typename Type, typename Type2>
concept support_quot = requires (const Type &t, const Type2 &t2)
{
    {t / t2} -> std::convertible_to<std::common_type_t<Type, Type2>>;
};

template<typename Type, typename Type2>
concept supports_sum_mul = support_prod<Type, Type2> && support_quot<Type, Type2>;

#endif
