/*!
 * This program demonstrates how to retrieve the type a template
 * iterator points to.
 *
 * This may be useful, for instance, if you need to allocate a
 * temporary memory based on that type.
 * In the implementation of mergesort or radix, you might need
 * to do this.
 *
 * @author Selan
 * @date December 5th, 2021.
 */

#include <iostream>
#include <vector>
#include <type_traits>

template <typename Itr>
void func(Itr f, Itr l){
    // ============================================================
    // Method 1: gambiarra-oriented.
    // ============================================================
    auto temp = *f; // This may fail (segfault) IF the range is empty.
    using MyType1 = decltype(temp);

    // Allocating an array manually.
    MyType1 *A = new MyType1[10];
    // Freeing memory.
    delete [] A;
    // ------------------------------------------------------------

    // ============================================================
    // Method 2: Explicitly accessing iterator traits.
    // ============================================================
    using MyType2 = typename std::iterator_traits<Itr>::value_type;

    // Allocating an array manually.
    MyType2 *B = new MyType2[10];
    // Freeing memory.
    delete [] B;
    // ------------------------------------------------------------

    // ============================================================
    // Method 3: Cleaner method, needs at least c++11
    // ============================================================
    using MyType3 = typename Itr::value_type;

    // Allocating an array manually.
    MyType3 *C = new MyType3[10];
    // Freeing memory.
    delete [] C;
    // ------------------------------------------------------------

    // Creating variables based on the recovered type.
    MyType1 x{};
    MyType2 y{};
    MyType3 z{};

    std::cout << ">>> Value of x: " << x << '\n';
    std::cout << ">>> Value of y: " << y << '\n';
    std::cout << ">>> Value of z: " << z << '\n';

    std::cout << "MyType1 is int? " << std::boolalpha
              << std::is_same_v<decltype(x), int> << '\n';
    std::cout << "MyType2 is int? " << std::boolalpha
              << std::is_same_v<decltype(y), int> << '\n';
    std::cout << "MyType3 is int? " << std::boolalpha
              << std::is_same_v<decltype(y), int> << '\n';
}



int main(){
    std::vector<int> V{1, 2, 3, 4, 5};

    func(V.begin(), V.end());

    return 0;
}
