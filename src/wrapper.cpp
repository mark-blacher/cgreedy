#include "wrapper.h"

#include "cpath.h"

#include <algorithm>
#include <unordered_map>
#include <vector>

void compute_path_with_greedy(uint64_t seed, uint64_t max_repeats, double max_time, int progbar, int minimize, int is_outer_optimal, uint32_t threshold_optimal,
                              const uint32_t num_threads, const int generate_linear,
                              const uint32_t* inputs_outputs_flat, const int32_t* inputs_outputs_sizes, uint64_t n_tensors, uint64_t n_map_items,
                              const uint32_t* keys_sizes, const uint64_t* values_sizes, double* out_flops_log10, double* out_size_log2, uint64_t*__restrict__ out_path){

  std::unordered_map<uint32_t, uint64_t> index_to_size_map;
  for (uint64_t i = 0; i < n_map_items; ++i) {
    index_to_size_map.insert({keys_sizes[i], values_sizes[i]});
  }
  Expression<uint32_t> expression(index_to_size_map);
  uint64_t c = 0;
  std::vector<uint32_t> idx;
  for (uint64_t i = 0; i < n_tensors; ++i) {
    idx.clear();
    for (uint64_t j = c; j < c + uint64_t(inputs_outputs_sizes[i]); ++j) {
      idx.push_back(inputs_outputs_flat[j]);
    }
    std::sort(begin(idx), end(idx));
    expression.add(idx);
    c += uint64_t(inputs_outputs_sizes[i]);
  }
  const bool is_compute_optimal = n_tensors <= threshold_optimal + 1;
  if(is_compute_optimal){
    expression.simplify(false); // don't add common batch to the output tensor
  } else{
    expression.simplify(true); // add common batch to the output tensor
  }

  Minimize _minimize = Minimize::FLOPS;
  if(minimize == 1){
    _minimize = Minimize::INTERMEDIATE_SIZE;
  }

  GreedyResult result;

  result = greedy_exec<uint32_t>(expression, seed, max_repeats, max_time, progbar, _minimize, is_outer_optimal, threshold_optimal, num_threads, generate_linear);

  *out_flops_log10 = result.metrics.log10_flops;
  *out_size_log2 = result.metrics.max_log2_size;
  if(generate_linear){
    for (uint64_t i = 0; i < result.path.linear.size(); ++i) {
      out_path[2 * i] = result.path.linear[i].a;
      out_path[2 * i + 1] = result.path.linear[i].b;
    }
  } else {
    for (uint64_t i = 0; i < result.path.ssa.size(); ++i) {
      out_path[2 * i] = result.path.ssa[i].a;
      out_path[2 * i + 1] = result.path.ssa[i].b;
    }
  }
}
