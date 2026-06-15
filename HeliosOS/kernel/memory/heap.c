#include "heap.h"

static heap_block_t* head = 0;

static uint32_t heap_start_addr = 0;
static uint32_t heap_total_size = 0;

static uint32_t used_memory = 0;

static void memset8(uint8_t* p, uint8_t v, uint32_t s)
{
    for(uint32_t i = 0; i < s; i++)
        p[i] = v;
}

static void memcpy8(uint8_t* d, uint8_t* s, uint32_t size)
{
    for(uint32_t i = 0; i < size; i++)
        d[i] = s[i];
}

void heap_init(uint32_t start, uint32_t size)
{
    heap_start_addr = start;
    heap_total_size = size;

    head = (heap_block_t*)start;

    head->size = size - sizeof(heap_block_t);
    head->free = 1;
    head->next = 0;
    head->prev = 0;

    used_memory = 0;
}

static heap_block_t* find_block(uint32_t size)
{
    heap_block_t* cur = head;

    while(cur)
    {
        if(cur->free && cur->size >= size)
            return cur;

        cur = cur->next;
    }

    return 0;
}

static void split(heap_block_t* block, uint32_t size)
{
    if(block->size <= size + sizeof(heap_block_t))
        return;

    heap_block_t* new_block =
        (heap_block_t*)((uint8_t*)block + sizeof(heap_block_t) + size);

    new_block->size = block->size - size - sizeof(heap_block_t);
    new_block->free = 1;

    new_block->next = block->next;
    new_block->prev = block;

    if(block->next)
        block->next->prev = new_block;

    block->next = new_block;
    block->size = size;
}

void* kmalloc(uint32_t size)
{
    if(size == 0)
        return 0;

    size = (size + 7) & ~7;

    heap_block_t* block = find_block(size);

    if(!block)
        return 0;

    split(block, size);

    block->free = 0;
    used_memory += block->size;

    return (uint8_t*)block + sizeof(heap_block_t);
}

void kfree(void* ptr)
{
    if(!ptr)
        return;

    heap_block_t* block =
        (heap_block_t*)((uint8_t*)ptr - sizeof(heap_block_t));

    block->free = 1;

    used_memory -= block->size;

    // merge
    if(block->next && block->next->free)
    {
        block->size += sizeof(heap_block_t) + block->next->size;
        block->next = block->next->next;
    }

    if(block->prev && block->prev->free)
    {
        block->prev->size += sizeof(heap_block_t) + block->size;
        block->prev->next = block->next;
    }
}

void* kcalloc(uint32_t count, uint32_t size)
{
    uint32_t total = count * size;

    void* p = kmalloc(total);

    if(p)
        memset8((uint8_t*)p, 0, total);

    return p;
}

void* krealloc(void* ptr, uint32_t size)
{
    if(!ptr)
        return kmalloc(size);

    if(size == 0)
    {
        kfree(ptr);
        return 0;
    }

    heap_block_t* block =
        (heap_block_t*)((uint8_t*)ptr - sizeof(heap_block_t));

    if(block->size >= size)
        return ptr;

    void* new_ptr = kmalloc(size);

    if(!new_ptr)
        return 0;

    memcpy8(new_ptr, ptr, block->size);

    kfree(ptr);

    return new_ptr;
}

uint32_t heap_get_used()
{
    return used_memory;
}

uint32_t heap_get_free()
{
    return heap_total_size - used_memory;
}
