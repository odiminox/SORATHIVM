#pragma once

#if (_MSC_VER >= 1500 && _MSC_VER <= 1600)
#include <malloc.h>
#endif

#include "common.h"

// x64 = align to 8 bytes
// x86 = align to 4 bytes
FORCEINLINE usize align(usize n) { return (n + sizeof(uword) - 1) & ~(sizeof(uword) - 1); }

// Arena allocator

enum MemBlockFlags
{
    MemBlockFlagNone = 0x0,
    memBlockFlagUsed = 0x1,
};

struct MemBlock
{
    MemBlock* next;
    u32 flags;
    usize size;
};

struct MemArena
{
    MemBlock* head;
    u8* buffer;
    usize total_size;
    usize total_used;
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
    arena->head = NULL;
    return arena;
}

FORCEINLINE MemBlock* split_block(MemArena* arena, usize size);
FORCEINLINE MemBlock* coalesce_adjacent(MemArena* arena);

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

        // Not efficient as any size < block->size can be returned resulting in wasted space
        if (!(block->flags & memBlockFlagUsed) || (block->size < size))
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
    ASSERT(size > 0)
    uword offset = (uword)arena->total_used;
    if ((offset + size)  <= arena->total_size)
    {
        void* ptr = &arena->buffer[offset];

        MemBlock* block = (MemBlock*)ptr;
        arena->total_used += size;
        memset(block, 0, size);
        block->flags = MemBlockFlagNone;
        block->next = NULL;
        block->size = size;

        // TODO: Insert block and set block->next

        return block;
    }

    return NULL;
}

FORCEINLINE void free_arena(MemArena* arena)
{
    arena->buffer = 0;
    arena->total_size = 0;
    arena->total_used = 0;
}

FORCEINLINE usize remaining_arena_mem(MemArena* arena)
{
    ASSERT(arena != NULL);
    return arena->total_size - arena->total_used;
}

FORCEINLINE MemBlock* get_block(MemArena* arena, u32 offset)
{
    ASSERT(offset >= 0)
    void* ptr = &arena->buffer[offset];
    MemBlock* block = (MemBlock*)ptr;
    ASSERT(block != NULL)
    return block;
}

FORCEINLINE MemBlock* get_block_from_memory(MemArena* arena, void* memory)
{
    MemBlock* block = (MemBlock*)memory;
    ASSERT(block != NULL)
    return block;
}

FORCEINLINE MemBlock* get_top(MemArena* arena)
{
    void* ptr = &arena->buffer[0];
    MemBlock* block = (MemBlock*)ptr;
    return block;
}

FORCEINLINE MemBlock* get_bottom(MemArena* arena)
{
    uword bottom = (uword)arena->total_used;
    void* ptr = &arena->buffer[bottom];
    MemBlock* block = (MemBlock*)ptr;
    return block;
}

FORCEINLINE MemBlock* get_end(MemArena* arena)
{
    uword end = (uword)arena->total_size;
    void* ptr = &arena->buffer[end];
    MemBlock* block = (MemBlock*)ptr;
    return block;
}