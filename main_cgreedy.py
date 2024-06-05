import time
import opt_einsum as oe
import numpy as np
from cgreedy import CGreedy, compute_path

# generate a random tensor equation and corresponding shapes
format_string, shapes = oe.helpers.rand_equation(65, 3, seed=12, d_min=2, d_max=10, n_out=2)
tensors = [np.random.rand(*shape) for shape in shapes]

# initialize the CGreedy optimizer with specific parameters
optimizer = CGreedy(seed=1, minimize="size", max_repeats=1024, max_time=1.0, progbar=True, threshold_optimal=12, threads=0)

# compute a path using the optimizer with opt_einsum
path_info = oe.contract_path(format_string, *tensors, optimize=optimizer)

# display important information about the optimization process
print("\nMax log2 size:", optimizer.size_log2)
print("Flops log10:", optimizer.flops_log10)
print("Time to compute the path:", optimizer.path_time, "seconds")

# perform the tensor contraction using the optimized path
tic = time.time()
result = oe.contract(format_string, *tensors, optimize=path_info[0])
toc = time.time()
print("\nExecution time for contraction:", toc - tic, "seconds\n")

# alternative, more efficient approach without using opt_einsum, focusing only on the path computation
path, size_log2, flops_log10 = compute_path(format_string, *tensors, seed=1, minimize="size", max_repeats=1024,
                                            max_time=1.0, progbar=True, threshold_optimal=12, threads=0, is_linear=True)

# display the path computation results
print("\nMax log2 size:", size_log2)
print("Flops log10:", flops_log10)

# perform the contraction using the computed path
tic = time.time()
result2 = oe.contract(format_string, *tensors, optimize=path)
toc = time.time()
print("\nExecution time for contraction:", toc - tic, "seconds")