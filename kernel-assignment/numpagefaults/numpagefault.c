#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros
#include <linux/proc_fs.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("WataruOshima");
MODULE_DESCRIPTION("Showing a pagefault");


static int proc_dma_show(struct seq_file *m, void *v)
{
	printk(KERN_INFO "successfully created\n");
	return 0;
}


static int __init proc_dma_init(void)
{
	proc_create_single("numpagefaults", 0, NULL, proc_dma_show);
	return 0;
}

module_init(proc_dma_init);
// module_exit();
MODULE_LICENSE("GPL");