#include <fstream>
#include <string>

#include "filesystem.h"


namespace external_sort {

ChunkedReader::ChunkedReader(std::string fn, int memory_size) {
  file_ = std::make_unique<std::ifstream>(std::ifstream(fn));
  memory_size_ = memory_size;
  buffer_string = "";
  is_buffer_filled = false;
}

bool ChunkedReader::Done() const {
  return !is_buffer_filled && file_->eof();
}

size_t static CalculateStringSize(const std::string &s) {
  return sizeof(std::string::value_type) * s.capacity();
}

std::vector<std::string> ChunkedReader::ReadInput() {
  std::vector<std::string> current_chunk;

  // current_chunk_memory is the size of strings elements
  size_t current_chunk_memory = 0;

  if (is_buffer_filled) {
    // we could throw here in case we can't read the string to memory
    // but for simplicity I've omitted that part
    current_chunk_memory += CalculateStringSize(buffer_string);
    current_chunk.emplace_back(std::move(buffer_string));
    is_buffer_filled = false;
  }

  std::string current_string;
  // read lines while we fit into RAM
  while (getline(*file_, current_string)) {
    size_t line_size = CalculateStringSize(current_string);

    // sizeof(std::string) * current_chunk.capacity() is the size of the vector
    // with elements
    if (current_chunk_memory + line_size +
        sizeof(std::string) * current_chunk.capacity() > memory_size_) {
      // we read enough
      // add string we didn't read
      is_buffer_filled = true;
      buffer_string = current_string;
      break;
    }
    current_chunk_memory += line_size;
    current_chunk.emplace_back(std::move(current_string));
  }
  return current_chunk;
}

ExternalSortFileSystem::ExternalSortFileSystem(std::string input_filepath,
                                               std::string output_filepath,
                                               int memory_size)
                                               : reader_(std::move(input_filepath),
                                                         memory_size) {
    output_filestream_ = std::ofstream(output_filepath);
}

bool ExternalSortFileSystem::IsInputExhausted() const {
  return reader_.Done();
}

std::vector<std::string> ExternalSortFileSystem::ReadInput() {
  return reader_.ReadInput();
}

void ExternalSortFileSystem::AddSortedChunk(std::vector<std::string> string_to_dump) {
  // create tmp filename
  char filename[L_tmpnam];
  std::tmpnam(filename);
  std::ofstream of(filename);
  for (auto &string : string_to_dump) {
    of << string << "\n";
  }
  of.close();
  sorted_streams_.emplace_back(std::ifstream(filename));
}

size_t ExternalSortFileSystem::GetChunkNumber() const {
  return sorted_streams_.size();
}

bool ExternalSortFileSystem::IsChunkEmpty(size_t index) const {
  assert(index < sorted_streams_.size());
  return sorted_streams_[index].eof();
}

bool ExternalSortFileSystem::GetLineFromChunk(size_t index, std::string *s) {
  assert(index < sorted_streams_.size());
  std::string tmp_string;
  if (getline(sorted_streams_[index], tmp_string)) {
    *s = tmp_string;
    return true;
  }
  return false;
}

void ExternalSortFileSystem::Out(std::string s) {
  output_filestream_ << s;
}
}  // namespace external_sort
