# MiBench2
[MiBench](http://vhosts.eecs.umich.edu/mibench/) ported for IoT devices and adjusted to run on the pulpino.

All benchmarks include [barebench.h](barebench.h).  This file contains the `main()` used in building every benchmark and determines the number of benchmark trials and what happens when a benchmark attempts to print to the screen.

### Prerequisites

You will need a cross-compiler for your target platform. The default target is the ARM-Cortex-M0+.  The easiest way to get a working cross-compiler for the Cortex-M0+ is to download the prebuilt binaries from [Launchpad.net](https://launchpad.net/gcc-arm-embedded).

Whatever toolchain you go with, update the paths and commands in the global [make file](Makefile.mk).

### Building

Add the line to main cmakemake list in sw/apps dir

 `add_subdirectory(mibench)`

### Statically Allocated

Benchmark susan: Statically Allocated for this specific data set.

Benchmark fft: Statically Allocated for this specific data set.


