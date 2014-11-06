#include <linux/linkage.h>
#include <linux/moduleloader.h>
#include <linux/mm.h>
#include <linux/mman.h>
#include <linux/sched.h>
#include <linux/err.h>
#include <linux/syscalls.h>

asmlinkage extern long (*sysptr)(void *arg, int argslen);

unsigned long res;

void process(int arg){

	//mutex_lock(&tps_mutex);	
	//init_queue();	

	res = do_mmap(0, 0, arg, PROT_WRITE | PROT_READ, MAP_SHARED, 0);

	if(!IS_ERR_VALUE(res)){
		enQueue(current->tgid, current->pid, res, arg);	
	}
	else{
		printk("Mmap failed \n");
	}

	//mutex_unlock(&tps_mutex);
}


asmlinkage long xconcat(void *arg, int argslen)
{
	//void *access = NULL;
	//void *ptr = NULL;
	//ptr = kmalloc(argslen, GFP_KERNEL);

	//res = copy_from_user(ptr, arg, argslen);

	//printk("res: %lu \n", res);
	//printk("ptr: %s \n", (char *)ptr);

	//res = do_mmap(0, 0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, 0);
	//printk("res mmap: %p \n", (void *)res);
	process(argslen);

	return res;
}

static int __init init_sys_xconcat(void)
{
	//mutex_init(&tps_mutex);
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
	display();
	deinit_queue();
}

module_init(init_sys_xconcat);
module_exit(exit_sys_xconcat);
MODULE_LICENSE("GPL");
