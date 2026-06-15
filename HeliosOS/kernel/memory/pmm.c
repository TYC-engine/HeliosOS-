#include "pmm.h"

static uint8_t* bitmap = (uint8_t*)0x80000; // временно безопасная зона
static uint32_t total_pages = 0;
static uint32_t used_pages = 0;

static void bitmap_set(uint32_t page)
{
    bitmap[page / 8] |= (1 << (page % 8));
}

static void bitmap_clear(uint32_t page)
{
    bitmap[page / 8] &= ~(1 << (page % 8));
}

static uint8_t bitmap_test(uint32_t page)
{
    return bitmap[page / 8] & (1 << (page % 8));
}

void pmm_init(uint32_t memory_size)
{
    total_pages = memory_size / PAGE_SIZE;
    used_pages = 0;

    for(uint32_t i = 0; i < total_pages / 8; i++)
        bitmap[i] = 0xFF; // всё занято по умолчанию
}

void pmm_mark_region(uint32_t base, uint32_t size, uint8_t used)
{
    uint32_t start = base / PAGE_SIZE;
    uint32_t end   = (base + size) / PAGE_SIZE;

    for(uint32_t i = start; i < end; i++)
    {
        if(used)
            bitmap_set(i);
        else
            bitmap_clear(i);
    }
}

uint32_t pmm_alloc_page()
{
    for(uint32_t i = 0; i < total_pages; i++)
    {
        if(!bitmap_test(i))
        {
            bitmap_set(i);
            used_pages++;
            return i * PAGE_SIZE;
        }
    }

    return 0;
}

void pmm_free_page(uint32_t page)
{
    uint32_t p = page / PAGE_SIZE;

    if(bitmap_test(p))
    {
        bitmap_clear(p);
        used_pages--;
    }
}

uint32_t pmm_get_total_pages()
{
    return total_pages;
}

uint32_t pmm_get_used_pages()
{
    return used_pages;
}
