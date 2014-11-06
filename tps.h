
struct tps_list{

	pid_t process_id;
	pid_t thread_id;
	unsigned long addr;
	int len;
	struct tps_list *next;	
} *head, *tail;


void init_queue(void){

	head = NULL;
	tail = NULL;
}


int enQueue(pid_t process_id, pid_t thread_id, unsigned long addr, int len){

	struct tps_list *temp = NULL;
	int err = 0;

	temp = kmalloc(sizeof(struct tps_list), GFP_KERNEL);

	if(!temp){
		printk("temp allocation failed \n");
		err = -1;
		goto out;
	}

	temp->process_id = process_id;
	temp->thread_id = thread_id;
	temp->addr = addr;
	temp->len = len;

	if(head == NULL){
		tail = temp;
		tail->next = NULL;
		head = tail;
	}	
	else{
		tail->next = temp;
		tail = temp;
		tail->next = NULL;
	}

out: 
	return err;
}


void deinit_queue(void){

	struct tps_list *temp, *buf;

	while(head != NULL){
		temp = head;
		buf = head->next;
		kfree(temp);
		head = buf;
	}

}

void display(void){

	struct tps_list *var = head;
	if(var != NULL){
		while(var != NULL){

			printk("pid: %d\t", var->process_id);
			printk("tid: %d\t", var->thread_id);
			printk("addr: %lu\t", var->addr);
			printk("length: %d\n", var->len);
			var = var->next;
		}
		printk("\n");
	}
	else{
		printk("Queue is empty\n");
	}

}
