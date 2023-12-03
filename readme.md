## Bin Packing Problem (BPP)

The BPP is a classic hard optimization problem aiming to efficiently fit items of varying sizes into a limited number of containers (bins). The goal is to minimize the number of bins used while accommodating all items without exceeding each bin's capacity. This challenge comes with different variations, such as the 1D or 2D bin packing, where items may have different dimensions and shapes. It finds applications in logistics, resource allocation, and computer science, requiring algorithms that intelligently allocate items to bins to optimize space usage and minimize waste.

The bin packing problem falls under the category of NP-hard problems, meaning that no known polynomial-time algorithm guarantees an optimal solution for all instances within a reasonable timeframe. Its complexity depends on the specific variant of the problem. Here we present some exact and heuristic algorithms to 1D BPP.

### Heuristics

- Next Fit Decreasing Height (NFDH)
- Local search algorithm
- Tabu search algorithm

In order to execute a test in any of those algorithm, please execute:

1. `cd heuristics`
2. `g++ ffdh.cpp local_search.cpp next_fit_decreasing_height.cpp tabu_search.cpp heuristics.cpp -o main.out`
3. `./main.out`

It will ask the number of the instance of dataset called `hard28` that can be find at `Instances/hard28`.

### Exacts (⚠️ in construction)

- All Permutations (tooo slow)
- Branch and bound (BB) (⚠️ with bug)

In order to execute BB algorithm, execute:

1. `g++ -std=c++11 ffdh.cpp branch_and_bound.cpp -o main.out`
2. `./main.out`

### Random Instances

In order to generate a set of items with random values, execute:

`python instance_generator.py` or `python3 instance_generator.py`

This script will generate `instance.txt` that could be used as input to any of the algoritms presented here.

### Authors

| [<img src="https://avatars3.githubusercontent.com/u/31693006?s=460&v=4" width=115><br><sub>@isaacmsl</sub>](https://github.com/isaacmsl) | [<img src="https://avatars.githubusercontent.com/u/55766685?v=4" width=115><br><sub>@viniciu21</sub>](https://github.com/viniciu21) |
| :--------------------------------------------------------------------------------------------------------------------------------------: | :--------------------------------------------------------------------------------------------------------------------------------------: |
