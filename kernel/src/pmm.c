
#include "stewieos/pmm.h"

u32* physical_frame = NULL;
u32 physical_frame_count = 0;

// The starting address of the stack
u16* phys_stack = NULL;
// the size of the stack
u32 phys_stack_size = 0;
// The current stack pointer
u16* phys_stack_ptr = NULL;

void push_frame(u32 frame)
{
	if( phys_stack_ptr == phys_stack ){
		printk("%2Verror: physical frame allocator stack overflow!\n");
		asm volatile ("cli; hlt");
	}
	
	*(--phys_stack_ptr) = ((u16)(frame / 0x1000));
}

u32 pop_frame( void )
{
	if( phys_stack_ptr == ((u16*)( (u32)phys_stack + phys_stack_size )) ){
		printk("%2Verror: out of physical memory!\n");
		asm volatile ("cli; hlt");
	}
	
	return (u32)(*(phys_stack_ptr++)) * 0x1000;
}


u32 find_free_frame( void )
{
	for(u32 i = 0; i < (physical_frame_count/32); ++i)
	{
		if( physical_frame[i] == 0xFFFFFFFF ) continue;
		for(u32 m = 0; m < 32; m++){
			if( i == 0 && m == 0 ) continue;
			if( !(physical_frame[i] & (u32)(1<<m)) ){
				return i*32 + m;
			}
		}
	}
	return (u32)-1;
}

void reserve_frame(u32 idx)
{
	//idx /= 0x1000; // get a frame index instead of a frame address
	physical_frame[(int)(idx/32)] |= (u32)(1 << (idx % 32));
}

void release_frame(u32 idx)
{
	//idx /= 0x1000; // get a frame index instead of a frame address
	physical_frame[(int)(idx/32)] &= (u32)(~(1 << (idx % 32)));
}

void alloc_frame(page_t* page, int user, int rw)
{
	//printk("PHYSICAL_ADDRESS: %p\n", physical_frame);
	if( page->present != 0 ){
		printk("%1Vwarning: attempting to map to an address already in use!\n");
		asm volatile ("cli; hlt");
		while(1);
		return;
	}
	
	u32 flags = disablei();
	u32 idx = find_free_frame();
	if( idx == (u32)-1 ){
		printk("%2VOUT OF MEMORY!\n");
		asm volatile ("cli; hlt");
		while(1);
	}
	reserve_frame(idx);
	page->present = 1;
	page->user = user ? 1 : 0;
	page->rw = rw ? 1 : 0;
	page->frame = (idx & 0x000FFFFF);
	restore(flags);
	return;
}

void clone_frame(page_t* dst, page_t* src)
{
	dst->present = 1;
	dst->user = src->user;
	dst->rw = src->rw;
	dst->frame = src->frame;
}

void free_frame(page_t* page) 
{
	if( !page->present || page->frame == 0 ) return;
	
	release_frame(page->frame);
	page->frame = 0;
	page->present = 0;
}
