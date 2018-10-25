#include <iostream>
#include <string>

#include "external_sort.h"
#include "filesystem.h"

int main(int argc, char** argv) {

  if (argc < 4) {
    std::cout << "Usage: ./main input_filepath output_filepath memory_limit(bytes)";
    return 1;
  }
  std::string input_filepath = argv[1];
  std::string output_filepath = argv[2];
  int memory_limit = std::stoi(argv[3]);

  // I have't used the virtual classes for the simplicity
  // create basic class to manipulate files and streams
  external_sort::ExternalSortFileSystem file_system(std::move(input_filepath),
                                                    std::move(output_filepath),
                                                    memory_limit);
  // apply external sort
  external_sort::ExternalSort(&file_system);


  return 0;
}