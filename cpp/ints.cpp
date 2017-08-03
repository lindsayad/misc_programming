#include <iostream>
#include <cstdint>

template <typename T>
bool is_int64() { return false; }

template <>
bool is_int64<int64_t>() { return true; }

template <typename T>
bool is_intp() { return false; }

template <>
bool is_intp<intp_t>() { return true; }

int main()
{
 std::cout << "int:\t" << is_int64<int>() << std::endl;
 std::cout << "int64_t:\t" << is_int64<int64_t>() << std::endl;
 std::cout << "long int:\t" << is_int64<long int>() << std::endl;
 std::cout << "long long int:\t" << is_int64<long long int>() << std::endl;
 std::cout << "intp_t:\t" << is_int64<intp_t>() << std::endl;

 std::cout << "int:\t" << is_intp<int>() << std::endl;
 std::cout << "int64_t:\t" << is_intp<int64_t>() << std::endl;
 std::cout << "long int:\t" << is_intp<long int>() << std::endl;
 std::cout << "long long int:\t" << is_intp<long long int>() << std::endl;
 std::cout << "intp_t:\t" << is_intp<intp_t>() << std::endl;

 return 0;
}
