#include <linux/linkage.h>
#include <linux/moduleloader.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/compiler.h>
#include <linux/file.h>
#include <linux/fsnotify.h>
#include <linux/uaccess.h>
#include <linux/unistd.h>
#include <linux/slab.h>
#include <linux/stat.h>
#include <linux/fcntl.h>
#include <linux/mman.h>
#include "tps.h"

asmlinkage extern long (*sysptr)(void *arg, int argslen);


void list_implementation(void){
		
	
	init_queue();	


	enQueue(1000, 2000, 12345, 4096);
	enQueue(1001, 2001, 12345, 4096);
	enQueue(1002, 2002, 12345, 4096);
	enQueue(1003, 2003, 12345, 4096);


	display();

	deinit_queue();
	display();
}


asmlinkage long xconcat(void *arg, int argslen)
{
	unsigned long res = 0;
	//void *access = NULL;
	//void *ptr = NULL;
	//ptr = kmalloc(argslen, GFP_KERNEL);

	//res = copy_from_user(ptr, arg, argslen);

	//printk("res: %lu \n", res);
	//printk("ptr: %s \n", (char *)ptr);

	//res = do_mmap(0, 0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, 0);
	//printk("res mmap: %p \n", (void *)res);
	list_implementation();

	return res;
}

static int __init init_sys_xconcat(void)
{
	printk(KERN_INFO "installed new sys_xconcat module\n");
	if (sysptr == NULL)
		sysptr = xconcat;
	return 0;
}

static void  __exit exit_sys_xconcat(void)
{
	if (sysptr != NULL)
		sysptr = NULL;
	printk(KERN_INFO "removed sys_xconcat module\n");
}

module_init(init_sys_xconcat);
module_exit(exit_sys_xconcat);
MODULE_LICENSE("GPL");
