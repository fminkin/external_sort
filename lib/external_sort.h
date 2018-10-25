#ifndef UNTITLED_EXTERNAL_SORT_H
#define UNTITLED_EXTERNAL_SORT_H

#include <algorithm>
#include <queue>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#include <string>

#include "filesystem.h"


namespace external_sort {

struct PairStringComparator {
  bool operator()(const std::pair<size_t, std::string> &l,
                  const std::pair<size_t, std::string> &r) const {
    return l.second > r.second;
  }
};

// utility naming
using IndexStringPair = std::pair<size_t, std::string>;
using VectorOfStrings = std::vector<IndexStringPair>;
using PriorityQueue = std::priority_queue<IndexStringPair,
                                          VectorOfStrings,
                                          PairStringComparator>;


void UpdateQueueFromStream(PriorityQueue *pqueue,
                           ExternalSortFileSystem *file_system,
                           size_t stream_index);

std::string KWayMerge(PriorityQueue *pqueue,
                      ExternalSortFileSystem *file_system);

void ExternalSort(ExternalSortFileSystem *filesystem);

}  // namespace external_sort

#endif  // UNTITLED_EXTERNAL_SORT_H
