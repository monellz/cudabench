#ifndef CUDA_BENCH_H_
#define CUDA_BENCH_H_

#include <assert.h>
#include <stdint.h>

#include <memory>
#include <vector>

namespace cudabench {

class Reporter {};

class Kernel {
 public:
  virtual void SetUp(std::vector<int64_t>& args) = 0;
  virtual void Run() = 0;
  virtual void TearDown(std::vector<int64_t>& args) = 0;
};

struct Record {
  std::string name;
  uint64_t execution_time;
  uint64_t iteration;
  uint64_t profiling_iteration;

  enum DataType {
    Double,
    UINT64,
    INT64,
    PERCENT,
    THROUGHPUT,
    UTILIZATION,
  };
  struct Data {
    DataType type;
    uint64_t val;
  };

  std::vector<Data> data;
};

class CudaBench {
 public:
  CudaBench(const char* name, Kernel* k);

  CudaBench* Arg(int64_t x);
  CudaBench* Args(const std::vector<int64_t>& args);
  CudaBench* ArgName(const std::string& name);
  CudaBench* ArgNames(const std::vector<std::string>& name);
  CudaBench* Iterations(uint64_t count);
  CudaBench* ProfilingIterations(uint64_t count);
  CudaBench* Metric(const std::string& metric);
  CudaBench* Metrics(const std::vector<std::string>& metrics);

  void Run();

 private:
  std::string name_;
  std::unique_ptr<Kernel> kernel_;

  uint64_t iteration_;
  uint64_t profiling_iteration_;
  std::vector<std::string> arg_names_;
  std::vector<std::vector<int64_t>> args_;
};

};  // namespace cudabench

// from
// google/benchmark/include/benchmark/benchmark.h(https://github.com/google/benchmark/blob/master/include/benchmark/benchmark.h)
#if defined(__COUNTER__) && (__COUNTER__ + 1 == __COUNTER__ + 0)
#define CUDABENCH_PRIVATE_UNIQUE_ID __COUNTER__
#else
#define CUDABENCH_PRIVATE_UNIQUE_ID __LINE__
#endif

#define CUDABENCH_PRIVATE_NAME(n) \
  CUDABENCH_PRIVATE_CONCAT(_cudabench_, CUDABENCH_PRIVATE_UNIQUE_ID, n)
#define CUDABENCH_PRIVATE_CONCAT(a, b, c) CUDABENCH_PRIVATE_CONCAT2(a, b, c)
#define CUDABENCH_PRIVATE_CONCAT2(a, b, c) a##b##c

#define CUDABENCH_PRIVATE_DECLARE(n) \
  static ::cudabench::CudaBench* CUDABENCH_PRIVATE_NAME(n)

#define CUDABENCH(k)             \
  CUDABENCH_PRIVATE_DECLARE(k) = \
      (::cudabench::RegisterCudaBench(new CudaBench(#k, new k)))

#endif  // CUDA_BENCH_H_