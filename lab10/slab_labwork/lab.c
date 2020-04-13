#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/unistd.h>
#include <linux/sched.h>
#include <linux/ktime.h>
#include <linux/timekeeping.h>
#include <linux/gfp.h>
#include <linux/mm_types.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#define PAGE_SIZE 4096
struct mystruct {
   unsigned int arrayOfIntegers[8];
};


static int param = 2000; // any premade default value
module_param(param, int, 0660);

struct kmem_cache *km; //slab allocation for memory allocation process
void kmallocAlloc(int size) {
   struct timespec t1, t2;
   //just considering the documentation, putting arguments inside the kmem_cache_create
   km = kmem_cache_create("slabAllocation", size, 0, 
                        SLAB_HWCACHE_ALIGN|SLAB_PANIC|SLAB_POISON|SLAB_RED_ZONE, 
                        NULL);
   getnstimeofday(&t1);
   int i;
   char *buf;
   for(i = 0; i < param; i++) {
       buf = kmem_cache_alloc(km, GFP_KERNEL);
       kmem_cache_free(km, buf);
   }
   getnstimeofday(&t2);
   printk(KERN_INFO "Start: %lu. Finish: %lu. Throught: %lu.", t1.tv_nsec, t2.tv_nsec, t2.tv_nsec - t1.tv_nsec);
}

int init_module(void) {
   printk(KERN_INFO "Starting Lab 10 - Slab Allocation.\n");
   printk(KERN_INFO "Starting part 1:");
   printk(KERN_INFO "My module param: .%d\n", param);
   struct mystruct m;
   int temp1 = PAGE_SIZE/sizeof(m);
   printk(KERN_INFO "Starting part 2:");
   printk(KERN_INFO "Page Size: %d. Struct Size: %d. Page size/struct instances: %d.\n", PAGE_SIZE, sizeof(m), temp1);
   printk(KERN_INFO "Starting part 3:");
   kmallocAlloc(sizeof(m));
   return 0;
}

void cleanup_module(void) {
   printk(KERN_INFO "Cleanup module. End of lab 10.\n");
   kmem_cache_destroy(km);
}