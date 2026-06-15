#include "paging.h"

#define PAGE_SIZE 4096

static uint32_t page_directory[1024] __attribute__((aligned(4096)));
static uint32_t first_page_table[1024] __attribute__((aligned(4096)));

void paging_init()
{
    for(int i = 0; i < 1024; i++)
    {
        first_page_table[i] = (i * PAGE_SIZE) | 3;
    }

    page_directory[0] = ((uint32_t)first_page_table) | 3;

    for(int i = 1; i < 1024; i++)
    {
        page_directory[i] = 0;
    }

    paging_enable();
}

void paging_enable()
{
    __asm__ volatile("mov %0, %%cr3" :: "r"(page_directory));

    uint32_t cr0;
    __asm__ volatile("mov %%cr0, %0" : "=r"(cr0));

    cr0 |= 0x80000000; // PG bit

    __asm__ volatile("mov %0, %%cr0" :: "r"(cr0));
}

void paging_map(uint32_t virt, uint32_t phys)
{
    uint32_t dir = virt >> 22;
    uint32_t table = (virt >> 12) & 0x3FF;

    uint32_t* pt = (uint32_t*)(page_directory[dir] & ~0xFFF);

    pt[table] = phys | 3;
}
