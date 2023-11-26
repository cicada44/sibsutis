#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define PAGE_DEFAULT_SIZE 1024

struct page {
    uint32_t frames[PAGE_DEFAULT_SIZE];
};

struct PDE {
    uint32_t P : 1;
    uint32_t RW : 1;
    uint32_t US : 1;
    uint32_t PWT : 1;
    uint32_t PCD : 1;
    uint32_t A : 1;
    uint32_t D : 1;
    uint32_t PS : 1;
    uint32_t G : 1;
    uint32_t reserved : 3;
    uint32_t address : 20;
} __attribute__((packed));

struct PTE {
    uint32_t P : 1;
    uint32_t RW : 1;
    uint32_t US : 1;
    uint32_t PWT : 1;
    uint32_t PCD : 1;
    uint32_t A : 1;
    uint32_t D : 1;
    uint32_t PAT : 1;
    uint32_t G : 1;
    uint32_t reserved : 3;
    uint32_t address : 20;
} __attribute__((packed));

struct PDE page_dir[PAGE_DEFAULT_SIZE] __attribute__((aligned(PAGE_DEFAULT_SIZE * 4)));
struct PTE page_tab[PAGE_DEFAULT_SIZE][PAGE_DEFAULT_SIZE] __attribute__((aligned(PAGE_DEFAULT_SIZE * 4)));
struct page page_0;
uint32_t cr3;

uint32_t translate_from_logic(uint32_t la) {
    uint32_t dir_addr = (cr3 >> 12) << 12;
    uint32_t cat_id = la >> 22;
    uint32_t tab_id = (la << 10) >> 22;
    uint32_t addr_on_page = (la << 20) >> 20;
    struct PDE *directory_addr = (struct PDE *)(uintptr_t)dir_addr;
    struct PTE *table_addr = (struct PTE *)(uintptr_t)((directory_addr[cat_id]).address << 12);
    struct page *page_addr = (struct page *)(uintptr_t)((table_addr[tab_id]).address << 12) + addr_on_page;
    uint32_t phys_addr = ((uintptr_t)page_addr << 12) + addr_on_page;
    return phys_addr;
}

void print_mmu(uint32_t page_tab_count, uint32_t page_count) {
    printf("table addr\n");
    for (uint32_t i = 0; i < page_tab_count; ++i) {
        printf("0x%x\n", (uint32_t)((page_dir[i]).address));
        printf("physical\tvirtual\n");
        for (uint32_t j = 0; j < PAGE_DEFAULT_SIZE; ++j) {
            printf("%p\t\t", (void *)(uintptr_t)((page_tab[i][j]).address << 12));
            printf("%p\t\t", (void *)(uintptr_t)(((i << 10) | j) << 12));
        }
    }
}

int main(int argc, char **argv) {
    cr3 = ((uintptr_t)page_dir >> 12) << 12;
    uint32_t bin_size = 4096 * 16;

    uint32_t page_count = bin_size / 4096;
    if ((bin_size % 4096) > 0) page_count++;
    uint32_t page_tab_count = page_count / 1024;
    if ((page_count % 1024) > 0) page_tab_count++;

    for (uint16_t i = 0; i < page_tab_count; i++) {
        page_dir[i] = (struct PDE) {
            .P = 1, .RW = 1, .US = 1, .PWT = 1, .PCD = 1, .A = 0, .D = 1,
            .PS = 1, .address = (uintptr_t)(&page_tab[i]) >> 12};
    for (uint32_t j = 0; j < PAGE_DEFAULT_SIZE; j++) {
            page_tab[i][j] = (struct PTE){ .D = 0, .A = 0, .PAT = 0, .PCD = 0,
            .G = 1, .P = 1, .RW = 1, .US = 1, .PWT = 1,
            .address = ((uintptr_t)(&page_0) + j * 4096) >> 12};
        }
    }
    
    printf("memsize = %d, ", bin_size);
    printf("pgdiraddr = %p, ", (void *)page_dir);
    printf("pgtabcnt = %d, ", page_tab_count);
    printf("pgcnt = %d\n\n", page_count);
    printf("MMU table\n");
    print_mmu(page_tab_count, page_count);
}
