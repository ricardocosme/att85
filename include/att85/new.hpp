#pragma once

#include <stddef.h>

inline void* operator new(size_t, void* p) noexcept
{ return p; }
