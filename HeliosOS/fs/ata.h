#ifndef ATA_H
#define ATA_H

#include <stdint.h>

int ata_read28(uint32_t lba, uint8_t* buffer);

#endif
