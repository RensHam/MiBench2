# MiBench2
[MiBench](http://vhosts.eecs.umich.edu/mibench/) ported for IoT devices and adjusted to run on the pulpino.

All benchmarks include [barebench.h](barebench.h).  This file contains the `main()` used in building every benchmark and determines the number of benchmark trials and what happens when a benchmark attempts to print to the screen.

### Building

Add the line to main cmakemake list in sw/apps dir

 `add_subdirectory(mibench)`

### Statically Allocated

Benchmark susan: Statically Allocated for this specific data set.

Benchmark fft: Statically Allocated for this specific data set.


