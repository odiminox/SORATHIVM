#pragma once

#include "common.h"

// x64 = align to 8 bytes
// x86 = align to 4 bytes
FORCEINLINE usize align(usize n) { return (n + sizeof(uword) - 1) & ~(sizeof(uword) - 1); }

// Arena allocator

struct MemArena
{
    u8* buffer;
    usize total_size;
};

struct MemBlock
{
    MemBlock* prev;
    MemBlock* next;
    usize size;
    u32 flags;
};


FORCEINLINE MemArena* create_arena(usize size)
{
    size = align(size);
    MemArena* arena = (MemArena*)malloc(sizeof(MemArena));
    if (!arena) return NULL;
    arena->buffer = (u8*)malloc(size);
    arena->total_size = size;
    return arena;
}

FORCEINLINE void allocate_arena(MemArena* arena, usize arena_size)
{
    
}

FORCEINLINE void destroy_arena(MemArena* arena);
FORCEINLINE MemBlock* find_first_fit(MemArena* arena, usize size);