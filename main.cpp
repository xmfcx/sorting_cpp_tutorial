#include <algorithm>
#include <cassert>
#include <execution>
#include <iostream>
#include <random>
#include <tbb/iterators.h>

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

  // generate a vector of random names
  std::vector<std::string> names = {
      "John", "Jane", "Mary", "Bob", "Tom", "Jack", "Joe", "Mary", "Jane", "Bob"};

  // generate a vector of ages
  std::vector<int> ages = {
      20, 21, 22, 23, 24, 25, 26, 27, 28, 29};
  // shuggle the ages
  std::shuffle(ages.begin(), ages.end(), std::default_random_engine{});

  assert(names.size() == ages.size());

  // generate a sequence of numbers from 0 to size of names
  std::vector<int> indices(names.size());
  std::iota(indices.begin(), indices.end(), 0);

  // print
  print_vector_with_name(names, "The original sequence");
  print_vector_with_name(ages, "The original sequence");
  print_vector_with_name(indices, "The original sequence");

  std::sort(std::execution::par,
            indices.begin(),
            indices.end(),
            [&](int lhs, int rhs) {
              return ages[lhs] < ages[rhs];
            });
  //print indices
  print_vector_with_name(indices, "The sorted indices");

  for (int i = 0; i < indices.size(); ++i) {
    std::cout << names.at(i) << " " << ages.at(i) << std::endl;
  }
  std::cout << std::endl;

  for (int i = 0; i < indices.size(); ++i) {
    std::cout << names.at(indices.at(i)) << " " << ages.at(indices.at(i)) << std::endl;
  }

  // copy people with ages larger than 25 using copy_if
  std::vector<std::string> names_large_age(names.size());
  std::vector<int> ages_large_age(ages.size());
  auto return_iter = std::copy_if(tbb::make_zip_iterator(names.begin(), ages.begin()),
                                  tbb::make_zip_iterator(names.end(), ages.end()),
                                  tbb::make_zip_iterator(names_large_age.begin(), ages_large_age.begin()),
                                  [](const std::tuple<std::string, int> &tuple) {
                                    const std::string &name = std::get<0>(tuple);
                                    const int &age = std::get<1>(tuple);
                                    return age > 25;
                                  });

  std::for_each(tbb::make_zip_iterator(names_large_age.begin(), ages_large_age.begin()),
                return_iter,
                [](const std::tuple<std::string, int> &tuple) {
                  const std::string &name = std::get<0>(tuple);
                  const int &age = std::get<1>(tuple);
                  std::cout << "name: " << name << " "
                            << "age: " << age << std::endl;
                });

  //  auto iter_end_ages_large_age = std::copy_if(ages.begin(),
  //                                              ages.end(),
  //                                              ages_large_age.begin(),
  //                                              [](int age) {
  //                                                return age > 25;
  //                                              });
  //
  //  ages_large_age.resize(std::distance(ages_large_age.begin(), iter_end_ages_large_age));

  //    resize the vectors to the correct size
  names_large_age.resize(std::distance(
      tbb::make_zip_iterator(names_large_age.begin(), ages_large_age.begin()), return_iter));
  ages_large_age.resize(std::distance(
      tbb::make_zip_iterator(names_large_age.begin(), ages_large_age.begin()), return_iter));

  // print
  print_vector_with_name(names_large_age, "The names with large age");
  print_vector_with_name(ages_large_age, "The ages with large age");

  /*
   * vector<string> names_global
   * vector<string> names
   * vector<bool> condition_to_keep
   */

  //
  //  // shuffle the sequence
  //  std::shuffle(indices.begin(), indices.end(), std::default_random_engine{});
  //
  //  // print the shuffled sequence
  //  print_vector_with_name(indices, "The shuffled sequence");
  //
  //  // sort the sequence
  //  std::sort(std::execution::seq, indices.begin(), indices.end());
  //
  //  // print the sorted sequence
  //  print_vector_with_name(indices, "The sorted sequence");
}
