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
    usize total_used;
};

struct MemBlock
{
    MemBlock* next;
    usize size;
    u32 flags;
};


FORCEINLINE MemArena* alloc_arena(usize size)
{
    ASSERT(size > 0);
    size = align(size);
    MemArena* arena = (MemArena*)malloc(sizeof(MemArena));
    if (!arena) return NULL;
    arena->buffer = (u8*)malloc(size);
    arena->total_size = size;
    arena->total_used = 0;
    return arena;
}

FORCEINLINE MemBlock* find_first_block(MemArena* arena, usize size)
{
    ASSERT(size > 0)
    uword top = (uword)arena->buffer;
    top -= (uword)arena->buffer;
	void* ptr = &arena->buffer[top];
	MemBlock* block = (MemBlock*)ptr;
    while (block != NULL)
    { 
        if (!block->next)
        {
            return block;
        }

        if (block->size < size)
        {
            block = block->next;
            continue;
        }

        return block;
    }

    return NULL;
}

FORCEINLINE MemBlock* alloc_block(MemArena* arena, usize size)
{
    uword offset = (uword)arena->buffer + (uword)arena->total_used;

    offset -= (uword)arena->buffer;
    if ((offset + size)  <= arena->total_size)
    {
        void* ptr = &arena->buffer[offset];

		MemBlock* block = (MemBlock*)ptr;
        arena->total_used += size;
        memset(block, 0, size);
        block->flags = 0x0;
        block->next = NULL;
        block->size = size;
        return block;
    }

    return NULL;
}

FORCEINLINE void free_arena(MemArena* arena);
FORCEINLINE MemBlock* find_first_fit(MemArena* arena, usize size);

FORCEINLINE usize remaining_arena_mem(MemArena* arena)
{
    ASSERT(arena != NULL);
    return arena->total_size - arena->total_used;
}