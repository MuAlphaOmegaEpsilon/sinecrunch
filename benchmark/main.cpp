#include <benchmark/benchmark.h>
#include <math.h>
#include <numeric>

// A simple shorthand for single precision floating point.
using floatSP = float;
// A simple shorthand for double precision floating point.
using floatDP = double;
// A simple shorthand for quadruple precision floating point.
using floatQP = long double;

// The total number of samples to take. 
// One more is added since the sample at ZERO is also required.
constexpr uint32_t samplesNum = (1 << 15) + 1;

// The amount of space there is between two consecutive samples.
constexpr floatSP samplePeriod = M_PI * 2.0f / (samplesNum - 1);

// Since the purpose of the benchmark is about measuring sinusoid function 
// calls performance, we don't want to deal with angle conversions at 
// bench-time: lets have all the angles for every float precision already 
// calculated. 
static floatSP anglesSP [samplesNum];
static floatDP anglesDP [samplesNum];
static floatQP anglesQP [samplesNum];

// Returns the array of angles of the specified type.
template <typename T> T* getAngles ();
template <> floatSP* getAngles () { return anglesSP; }
template <> floatDP* getAngles () { return anglesDP; }
template <> floatQP* getAngles () { return anglesQP; }

// The ground truth values for a sinusoid.
// These samples are calculated using the highest precision function at
// disposal, which returns a quad precision float.
static floatQP groundTruth [samplesNum];

// A little shorthand to specify both, the BEGIN and END iterators of the
// passed array. 
// Since the number of samples is always the same in this whole file, there's
// no need to always specify the same details about array length.
#define RANGE(array) array, array + samplesNum

void initialize () 
{
    // Populate the single precision angles array first.
    // The single precision array gets populated first since its lowest 
    // precision one, and there's no precision loss when converting to higher
    // precision arrays.
    std::iota (RANGE (anglesSP), samplePeriod);
    // Copy over the other precision arrays.
    // The copy is required instead of doing iota again: 
    // we don't want to populate the angles arrays at different precision
    // levels, we want to have the EXACT same angles just converted to
    // different types! That's why we populated anglesSP first.
    std::copy (RANGE (anglesSP), anglesDP);
    std::copy (RANGE (anglesSP), anglesQP);

    // Calculate the ground truth samples.
    std::transform (RANGE (anglesQP), groundTruth, sinl);
}

template <typename T> constexpr
floatDP error_abs (const T& value, const floatQP& groundTruth) noexcept
{
    return (floatDP) abs ((value - (T) groundTruth));
}

template <typename T> constexpr
floatDP error_rel (const T& value, const floatQP& groundTruth) noexcept
{
    return (floatDP) abs (value / (T) groundTruth - (T) 1.0L);
}

template <typename T, T (*sinusoid)(T)>
static void benchSinusoid (benchmark::State& state)
{
    const T* angles = getAngles <T> ();
    T result [samplesNum];
    floatDP errors [samplesNum];
    
    // Main funciton benchmark loop: this is where the execution of the 
    // function is actually measured.
    for (const auto _ : state) 
        std::transform (RANGE (angles), result, sinusoid);

    // Total number of items processed. 
    // Google Benchmark will calculate how many items_per_second based on this.
    state.SetItemsProcessed (state.iterations () * samplesNum);

    // Absolute errors calculations
    std::transform (RANGE (result), groundTruth, errors, error_abs <T>);
    state.counters["err_abs_avg"] = std::accumulate (RANGE (errors), (T) 0.0L) * (floatDP) samplePeriod;
    state.counters["err_abs_max"] = *std::max_element (RANGE (errors));
    state.counters["err_abs_min"] = *std::min_element (RANGE (errors));

    // Relative errors calculations
    std::transform (RANGE (result), groundTruth, errors, error_rel <T>);
    state.counters["err_rel_avg"] = std::accumulate (RANGE (errors), (T) 0.0L) * (floatDP) samplePeriod;
    state.counters["err_rel_max"] = *std::max_element (RANGE (errors));
    state.counters["err_rel_min"] = *std::min_element (RANGE (errors));
}

// A little shorthand to mark a function for benchmarking and to rename it.
// Type is at the same time the argument and the return type.
// Function is the sinusoid to test.
// Name defines under which tag the function should appear in the results.
#define BENCH_SINUSOID(type, function, name)                            \
const auto SIN_ ## type ## _ ## name = benchSinusoid <type, function>;  \
BENCHMARK (SIN_ ## type ## _ ## name);

// Register all the functions to benchmark.
BENCH_SINUSOID (floatQP, std::sin, std);
BENCH_SINUSOID (floatQP, sinl, compiler);
BENCH_SINUSOID (floatDP, std::sin, std);
BENCH_SINUSOID (floatDP, sin, compiler);
BENCH_SINUSOID (floatSP, std::sin, std);
BENCH_SINUSOID (floatSP, sin, compiler);
BENCH_SINUSOID (floatSP, sinf, compiler_f);

int main(int argc, char** argv) 
{
    benchmark::Initialize (&argc, argv);
    if (benchmark::ReportUnrecognizedArguments (argc, argv)) 
        return 1;

    initialize ();
    benchmark::RunSpecifiedBenchmarks ();
}  
