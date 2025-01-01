#pragma once

#define TREE_ALLOCATE_MEMORY(size) tree_cur_mem += size; if (tree_cur_mem > tree_max_mem) tree_max_mem = tree_cur_mem;
#define TREE_FREE_MEMORY(size) tree_cur_mem -= size;
#define ALLOCATE_MEMORY(size) cur_mem += size; if (cur_mem > max_mem) max_mem = cur_mem;
#define FREE_MEMORY(size) cur_mem -= size;