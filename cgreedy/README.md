# CGreedy

The `cgreedy` package implements a greedy algorithm for finding efficient contraction paths in tensor computations, utilizing multiple cost functions.

## Installation

You can install `cgreedy` directly from PyPI:

```bash
pip install cgreedy
```

## Usage Example

Below is a comprehensive example that demonstrates how to use `cgreedy` to optimize tensor contractions in Python.
(For executing the example code, you need [`opt_einsum`](https://pypi.org/project/opt-einsum/).)


```python
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
```

##  Parameters of the `compute_path` Function

- **format_string (str)**: The format string specifying the contraction. (e.g., 'ij,jk->ik').
- **arguments (numpy.ndarray or list or tuple)**: Shapes of tensors involved in the contraction, provided as numpy arrays, lists, or tuples.
- **seed (int, optional)**: Seed for random number generation to ensure reproducibility. Default is 0.
- **minimize (str, optional)**: The criterion to minimize ('size' or 'flops'). Default is 'size'.
- **max_repeats (uint, optional)**: The maximum number of iterations for the optimization. Default is 8.
- **max_time (float, optional)**: The maximum allowed time for the optimization process in seconds. Default is 0.0.
- **progbar (bool, optional)**: Whether to show a progress bar during optimization. Default is False.
- **is_outer_optimal (bool, optional)**: Whether to consider outer products in the optimal search. Default is False.
- **threshold_optimal (uint, optional)**: Maximum number of input tensors to perform an expensive optimal search instead
  of a greedy search. Default is 12.
- **threads (uint, optional)**: Number of threads to use. Setting this to 0 utilizes all available threads. Default is 0.
- **is_linear (bool, optional)**: Whether the path is computed in a linear format or static single assignement (SSA) format. Default is True. (linear format)

## Reference Paper

The multiple-cost-functions strategy employed in `cgreedy` is discussed in our paper, titled [_"Optimizing Tensor Contraction Paths: A Greedy Algorithm Approach With Improved Cost Functions"_](https://arxiv.org/abs/2405.09644).

```bibtex
@article{Orgler2024,
  author    = {Orgler, Sheela and Blacher, Mark},
  title     = {Optimizing Tensor Contraction Paths: A Greedy Algorithm Approach With Improved Cost Functions},
  year      = {2024},
  journal   = {arXiv},
  doi       = {10.48550/arXiv.2405.09644}
}
```

## Source Code
The source code which was used to compile the package is available at [GitHub](https://github.com/mark-blacher/cgreedy).
