void dump(int type)
{
    block = t_block + var
    (void *)block
    int i = page->block->size - page->block->busy;
    
    while (i < page->block->size - t_block)
    {
        print(memory_plus(page->block, i), hexa);
    }

}