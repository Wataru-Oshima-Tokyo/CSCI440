#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros
#include <linux/proc_fs.h>
#include <linux/vmstat.h>
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("WataruOshima");
MODULE_DESCRIPTION("Showing a pagefault");

static struct proc_dir_entry *ent;


static int proc_status_show(struct seq_file *m, void *v)
{
	unsigned long  pagecount[NR_VM_EVENT_ITEMS];
	all_vm_events(pagecount);
	// printk(KERN_INFO "successfully created\n");
	seq_printf(m, "%lu\n", pagecount[PGFAULT]);
	return 0;
}



// static ssize_t myread(struct file *file, char __user *ubuf,size_t count, loff_t *ppos) 
// {
// 	char buf[BUFSIZE];
// 	int len=0;
// 	if(*ppos > 0 || count < BUFSIZE)
// 		return 0;
// 	len += sprintf(buf,"irq = %d\n",irq);
// 	len += sprintf(buf + len,"mode = %d\n",mode);
	
// 	if(copy_to_user(ubuf,buf,len))
// 		return -EFAULT;
// 	*ppos = len;
// 	return len;
// }


static int __init proc_numpagefaults_init(void)
{
	printk(KERN_INFO "successfully created\n");
	// printk(KERN_INFO "successfully created\n");
	ent = proc_create_single("numpagefaults", 0, NULL, proc_status_show);
	return 0;
}

static void __exit numpagefaults_cleanup(void)
{
    printk(KERN_INFO "Cleaning up module.\n");
	proc_remove(ent);
}

module_init(proc_numpagefaults_init);
module_exit(numpagefaults_cleanup);
// module_exit();
MODULE_LICENSE("GPL");