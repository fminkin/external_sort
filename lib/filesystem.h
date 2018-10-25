#ifndef EXTERNAL_SORT_CHUNKED_READER_H
#define EXTERNAL_SORT_CHUNKED_READER_H
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <cstdlib>
#include <cassert>


namespace external_sort {

class ChunkedReader {
 public:
  ChunkedReader(std::string fn, int memory_size);

  // is reader done reading input
  bool Done() const;

  // read chunk from the input, considering memory limit
  std::vector<std::string> ReadInput();

 private:
  std::unique_ptr<std::ifstream> file_;
  int memory_size_;
  std::string buffer_string;
  bool is_buffer_filled;
};


class ExternalSortFileSystem {
 public:
  ExternalSortFileSystem(std::string input_filepath,
                         std::string output_filepath,
                         int memory_size);

  // check if input is empty
  bool IsInputExhausted() const;

  // read chunk from the input, considering memory limit
  std::vector<std::string> ReadInput();

  // add sorted chunk to tmp file
  void AddSortedChunk(std::vector<std::string> string_to_dump);

  // how many chunks are we using to sort input
  size_t GetChunkNumber() const;

  // is chunk with index "index" empty
  bool IsChunkEmpty(size_t index) const;

  // readline from index th chunk
  bool GetLineFromChunk(size_t index, std::string *s);

  // output string to output stream
  void Out(std::string s);

 private:
  ChunkedReader reader_;
  std::vector<std::ifstream> sorted_streams_;
  std::ofstream output_filestream_;
};
}  // namespace external_sort

#endif  // EXTERNAL_SORT_CHUNKED_READER_H
