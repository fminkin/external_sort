#include "external_sort.h"
#include <string>

namespace external_sort {

void UpdateQueueFromStream(PriorityQueue *pqueue,
                           ExternalSortFileSystem *file_system,
                           size_t stream_index) {
  if (file_system->IsChunkEmpty(stream_index)) {
    return;
  }
  std::string next_string;
  if (file_system->GetLineFromChunk(stream_index, &next_string)) {
    pqueue->push(std::make_pair(stream_index, next_string));
  }
}

std::string KWayMerge(PriorityQueue *pqueue,
                      ExternalSortFileSystem *file_system) {
  auto qelement = pqueue->top();
  pqueue->pop();
  UpdateQueueFromStream(pqueue, file_system, qelement.first);
  return qelement.second;
}


void ExternalSort(ExternalSortFileSystem *filesystem) {
  while (!filesystem->IsInputExhausted()) {
    auto strings = filesystem->ReadInput();
    std::sort(std::begin(strings), std::end(strings));

    filesystem->AddSortedChunk(std::move(strings));
  }

  PriorityQueue pqueue;
  for (size_t i = 0; i < filesystem->GetChunkNumber(); ++i) {
    UpdateQueueFromStream(&pqueue, filesystem, i);
  }

  while (!pqueue.empty()) {
    std::string next_string = KWayMerge(&pqueue, filesystem);
    filesystem->Out(next_string + '\n');
  }
}
}  // namespace external_sort
