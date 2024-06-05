#pragma once

#include <cinttypes>

extern "C" {

void compute_path_with_greedy(uint64_t seed, uint64_t max_repeats, double max_time, int progbar, int minimize,
                              int is_outer_optimal, uint32_t threshold_optimal, uint32_t num_threads,
                              int generate_linear,
                              const uint32_t *inputs_outputs_flat, const int32_t *inputs_outputs_sizes,
                              uint64_t n_tensors, uint64_t n_map_items,
                              const uint32_t *keys_sizes, const uint64_t *values_sizes, double *out_flops_log10,
                              double *out_size_log2, uint64_t *out_path);

}


