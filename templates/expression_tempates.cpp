#include <iostream>
#include <type_traits>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <cassert>
template <typename E>
class VecExpression {
public:
    static constexpr bool IS_LEAF = false;

    [[nodiscard]]
    double operator[](size_t i) const {
        // Delegation to the actual expression type. This avoids dynamic polymorphism (a.k.a. virtual functions in C++)
        return static_cast<E const&>(*this)[i];
    }

    [[nodiscard]]
    size_t size() const { 
        return static_cast<E const&>(*this).size(); 
    }
};

class Vec3 : public VecExpression<Vec3> {
private:
    std::array<double, 3> elems;
public:
    static constexpr bool IS_LEAF = true;

    [[nodiscard]]
    double operator[](size_t i) const noexcept { 
        return elems[i]; 
    }

    double& operator[](size_t i) noexcept { 
        return elems[i]; 
    }

    [[nodiscard]]
    size_t size() const noexcept { 
        return elems.size(); 
    }

    // construct Vec using initializer list 
    Vec3(std::initializer_list<double> init) {
        std::ranges::copy(init, elems.begin());
    }

    // A Vec can be constructed from any VecExpression, forcing its evaluation.
    template <typename E>
    Vec3(VecExpression<E> const& expr) {
        for (size_t i = 0; i != expr.size(); ++i) {
            elems[i] = expr[i];
        }
    }
};

template <typename E1, typename E2>
class Vec3Sum : public VecExpression<Vec3Sum<E1, E2>> {
private:
    // cref if leaf, copy otherwise
    typename std::conditional<E1::IS_LEAF, const E1&, const E1>::type u;
    typename std::conditional<E2::IS_LEAF, const E2&, const E2>::type v;
public:
    static constexpr bool IS_LEAF = false;

    Vec3Sum(E1 const& u, E2 const& v): 
        u{u}, v{v} {
        assert(u.size() == v.size());
    }

    [[nodiscard]]
    double operator[](size_t i) const noexcept { 
        return u[i] + v[i]; 
    }

    [[nodiscard]]
    size_t size() const noexcept { 
        return v.size(); 
    }
};
  
template <typename E1, typename E2>
Vec3Sum<E1, E2> operator+(VecExpression<E1> const& u, VecExpression<E2> const& v) {
   return Vec3Sum<E1, E2>(*static_cast<const E1*>(&u), *static_cast<const E2*>(&v));
}

int main() {
    Vec3 v0 = {23.4,  12.5,  144.56};
    Vec3 v1 = {67.12, 34.8,  90.34};
    Vec3 v2 = {34.90, 111.9, 45.12};
    
    // Following assignment will call the ctor of Vec3 which accept type of 
    // `VecExpression<E> const&`. Then expand the loop body to 
    // a.elems[i] + b.elems[i] + c.elems[i]
    Vec3 sumOfVecType = v0 + v1 + v2; 

    for (size_t i = 0; i < sumOfVecType.size(); ++i) {
        std::cout << sumOfVecType[i] << std::endl;
    }

    // To avoid creating any extra storage, other than v0, v1, v2
    // one can do the following (Tested with C++11 on GCC 5.3.0)
    auto sum = v0 + v1 + v2;
    for (size_t i = 0; i < sum.size(); ++i) {
        std::cout << sum[i] << std::endl;
    }
    // Observe that in this case typeid(sum) will be Vec3Sum<Vec3Sum<Vec3, Vec3>, Vec3>
    // and this chaining of operations can go on.
}
