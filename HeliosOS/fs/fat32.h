
#ifndef FAT32_H
#define FAT32_H

#include <stdint.h>

typedef struct
{
    uint8_t jump[3];
    char oem[8];

    uint16_t bytes_per_sector;
    uint8_t sectors_per_cluster;
    uint16_t reserved_sectors;
    uint8_t fat_count;

    uint16_t root_entries;
    uint16_t total_sectors16;
    uint8_t media;
    uint16_t fat_size16;

    uint16_t sectors_per_track;
    uint16_t heads;
    uint32_t hidden_sectors;
    uint32_t total_sectors32;

    uint32_t fat_size32;
    uint16_t flags;
    uint16_t version;

    uint32_t root_cluster;

} __attribute__((packed)) FAT32_BPB;

int fat32_init(void);
uint32_t fat32_cluster_to_lba(uint32_t cluster);

#endif
