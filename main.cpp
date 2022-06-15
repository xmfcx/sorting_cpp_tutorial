#include <algorithm>
#include <execution>
#include <iostream>
#include <random>

template<typename T>
void print_vector(const std::vector<T> &v) {
  for (auto i: v)
    std::cout << i << " ";
  std::cout << std::endl;
}

template<typename T>
void print_vector_with_name(const std::vector<T> &v, const std::string &msg) {
  std::cout << msg << ": ";
  print_vector(v);
}

int main() {
  // generate a sequence of numbers from 0 to 100
  std::vector<int> v(10);
  std::iota(v.begin(), v.end(), 0);

  // print the sequence
  print_vector_with_name(v, "The original sequence");

  // shuffle the sequence
  std::shuffle(v.begin(), v.end(), std::default_random_engine{});

  // print the shuffled sequence
  print_vector_with_name(v, "The shuffled sequence");

  // sort the sequence
  std::sort(std::execution::par, v.begin(), v.end());

  // print the sorted sequence
  print_vector_with_name(v, "The sorted sequence");
}
