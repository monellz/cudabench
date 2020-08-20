#include "register.h"

namespace cudabench {

CudaBench* RegisterCudaBench(CudaBench* bench) {
  std::unique_ptr<CudaBench> bench_ptr(bench);
  BenchFamily* family = BenchFamily::GetInstance();
  family->AddBenchmark(std::move(bench_ptr));
  return bench;
}

CudaBench::CudaBench(const char* name, Kernel* k)
    : name_(name), kernel_(k), iteration_(0), profiling_iteration_(0) {}

CudaBench::~CudaBench() {}

CudaBench* CudaBench::Arg(int64_t x) {
  args_.push_back({x});
  return this;
}

CudaBench* CudaBench::Args(const std::vector<int64_t>& args) {
  args_.push_back(args);
  return this;
}

CudaBench* CudaBench::Iterations(uint64_t n) {
  assert(n > 0);
  iteration_ = n;
  return this;
}

CudaBench* CudaBench::ProfilingIterations(uint64_t n) {
  assert(n > 0);
  profiling_iteration_ = n;
  return this;
}

CudaBench* CudaBench::ArgName(const std::string& name) {
  arg_names_ = {name};
  return this;
}

CudaBench* CudaBench::ArgNames(const std::vector<std::string>& names) {
  arg_names_ = names;
  return this;
}

CudaBench* CudaBench::Metric(const std::string& metric) {
  // TODO
  return this;
}

};  // namespace cudabench