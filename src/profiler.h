#ifndef CUDA_BENCH_PROFILER_H_
#define CUDA_BENCH_PROFILER_H_

#include <cupti.h>

#include "cudabench/cudabench.h"

namespace cudabench {

class Profiler {
 public:
  void MetricRegister(std::vector<std::string> metrics);
};

};  // namespace cudabench

#endif  // CUDA_BENCH_PROFILER_H_