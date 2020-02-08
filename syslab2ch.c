#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <asm/current.h>

void print_processes(void) {
	struct task_struct *p, *t;
	printk(KERN_INFO "Begin");

	for_each_process(p) {
		/* this pointlessly prints the name and PID of each task */
		printk(KERN_INFO "%s[%d]\n[Thread sync. flags = %u,\nLow flags = %u",
         p->comm, p->pid, p->thread_info.status, p->thread_info.flags);
		for_each_thread(p, t) {
			printk(KERN_INFO "  %s[%d] TS fls = %u, Low fls = %u\n", t->comm, t->pid , t->thread_info.status, t->thread_info.flags);
		}
	}

	printk(KERN_INFO "END");
}

int init_module(void)
{

        printk(KERN_INFO "Lab2: start.\n");
	print_processes();

        return 0;
}

void cleanup_module(void)
{
        printk(KERN_INFO "Lab2: end.\n");
}