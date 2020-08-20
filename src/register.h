#ifndef CUDA_BENCH_REGISTER_H_
#define CUDA_BENCH_REGISTER_H_

#include "cudabench/cudabench.h"

namespace cudabench {

class BenchFamily {
 public:
  static BenchFamily* GetInstance();
  size_t AddBenchmark(std::unique_ptr<CudaBench> bench);
  void Clear();

 private:
  BenchFamily() {}
  std::vector<std::unique_ptr<CudaBench>> family_;
};

};  // namespace cudabench

#endif  // CUDA_BENCH_REGISTER_H_