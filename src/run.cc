#include "run.h"

namespace cudabench {

void CudaBench::Run() {
  // TODO
  assert(iteration_ > 0);
  assert(profiling_iteration_ > 0);

  State st;

  kernel_->SetUp(st);

  // measure execution time
  for (int64_t i = 0; i < iteration_; ++i) {
    kernel_->Run();
  }
  kernel_->TearDown(st);

  return;
}

};  // namespace cudabench