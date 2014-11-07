#include <linux/linkage.h>
#include <linux/moduleloader.h>
#include <linux/mm.h>
#include <linux/mman.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/syscalls.h>

asmlinkage extern long (*sysptr)(void *arg, int argslen);

unsigned long res;

/*
void dequeue_entry(){
				if(var == current->mm->tps_head){
					current->mm->tps_head = var->next;
					kfree(var);
					return;
				}
				else{
					prev->next = var->next;
					kfree(var);
					return;
				}
			 	
			}
			else{

				prev = var;
				var = var->next;
			}
}

bool dequeue_entry(unsigned long addr, int len){

	struct tps_list *var = current->mm->tps_head;
	struct tps_list *prev = NULL;

	if(var != NULL){
		while(var != NULL){
			
			if(!((addr > (var->addr + var->len)) || ((addr + len) < var->addr))){

			if((var->addr == addr) && (var->len == len)){

				if(((var->process_id == current->tgid) && (var->thread_id == current->pid))){
		
					printk("Match !!!!!!!!!!!!!\n");
					if(var == current->mm->tps_head){
						current->mm->tps_head = var->next;						kfree(var);
						return true;
					}
					else{
						prev->next = var->next;
						kfree(var);
						return true;
					}
				}
				else{
					prev = var;
					var = var->next;
				}		

			}
			else{
				prev = var;
				var = var->next;
			}	

		}
		else{
			prev = var;
			var = var->next;
		}
	}	
	}		
	else{
		//continue
	}	
	return false;
}*/

void process(int arg){

	//init_queue();	

	res = do_mmap(0, 0, arg, PROT_WRITE | PROT_READ, MAP_SHARED, 0);

	if(!IS_ERR_VALUE(res)){
		enQueue(current->tgid, current->pid, res, arg);	
	}
	else{
		printk("Mmap failed \n");
	}
}


asmlinkage long xconcat(void *arg, int argslen)
{
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
	//deinit_queue();
}

module_init(init_sys_xconcat);
module_exit(exit_sys_xconcat);
MODULE_LICENSE("GPL");
