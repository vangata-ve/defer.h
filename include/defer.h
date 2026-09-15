#ifndef DEFER_H
#define DEFER_H

#if defined(__clang__) || defined(_MSC_VER)
#  error "defer.h requires GCC nested functions; Clang and MSVC aren't supported"
#elif !defined(__GNUC__) || defined(__STRICT_ANSI__)
#  error "defer.h requires GCC GNU C extensions"
#endif

#if defined(__has_attribute)
#  if !__has_attribute(cleanup)
#    error "defer.h requires __attribute__((cleanup))"
#  endif
# if !__has_attribute(unused)
#   error "defer.h requires __attribute_((unused))"
# endif
#endif

#define DEFER_CAT_IMPL(a, b) a##b
#define DEFER_CAT(a, b)      DEFER_CAT_IMPL(a, b)

#define DEFER_IMPL(N)                                                       \
    auto void DEFER_CAT(defer_fn_, N)(int*);                                \
    int DEFER_CAT(defer_var_, N)                                            \
        __attribute__((cleanup(DEFER_CAT(defer_fn_, N)), unused));          \
    auto void DEFER_CAT(defer_fn_, N)(                                      \
        int* DEFER_CAT(defer_cleanup_arg_, N)                               \
            __attribute__((unused)))

#define defer DEFER_IMPL(__COUNTER__)

#endif /* DEFER_H */