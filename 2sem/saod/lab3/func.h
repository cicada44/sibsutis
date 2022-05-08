#pragma once

int heap_insert(struct heap* h, int key, int value);
int heap_extract_min(struct heap* h);
void heap_decrease_key(struct heap* node, int newkey);