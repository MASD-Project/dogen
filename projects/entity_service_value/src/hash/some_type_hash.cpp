// clang pragmas to ignore dummy function
#if __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
#endif

namespace { void dumm_function() { } }

#if __clang__
#pragma clang diagnostic pop
#endif
