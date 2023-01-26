
## What to do
to show the number of page faults that the operating system has handled since it booted


```
~$ ls -al /proc/numpagefaults
ls: /proc/numpagefaults: No such file or directory
~$ sudo insmod ./numpagefaults.ko
~$ ls -al /proc/numpagefaults
-r--r--r--  1 root root 37 August 22 21:38 /proc/numpagefaults
~$ cat /proc/numpagefaults
658103
~$ cat /proc/numpagefaults
658295
~$ cat /proc/numpagefaults
658485
~$ sudo rmmod numpagefaults 
~$ ls -al /proc/numpagefaults
ls: /proc/numpagefaults: No such file or directory
~$
```


## It’s worth thinking of this problem in a few steps
Read about how the /proc filesystem works  <br>
Figure out how you write information to a /proc file  <br>
Write a kernel module that successfully prints a fixed string when one cat’s the /proc/numpagefaults file.  <br>
Locate the kernel code that generates page faults statistics <br>
Write a kernel module that prints that statistic every time someone cat’s the /proc/numpagefaults file.  <br>

## Hints
You will need to find the symbol that has been explicitly exported by the kernel to be accessible to kernel modules; not all functions and variables in the kernel code are accessible to kernel modules. The kernel uses the EXPORT SYMBOL macro to export a particular symbol, so you need to find the specific symbol that’s been exported as such that provides the page fault statistic we want. <br>
You may need to declare your kernel module is licensed under the GPL open source license, as some kernel symbols are only accessible if you have declared your kernel module as being licensed under the GPL license. To declare it you only need to add a single line at the end of your kernel module code[4]: <br>
```
MODULE_LICENSE("GPL");
```

The Linux kernel already includes the page fault statistic in a /proc file, along with numerous other statistics. It is useful to see how this is already done and see if you can modify it to make a new /proc file that contains the current number of page faults only. The following command provides a good reference for the comparing the kernel statistics with those of your kernel module: <br>

Instead of performing standard file I/O, we need to register event handlers for various events.The seq_file API[9] introduced in Linux 3.10 is quite useful for this. version.c is a simple example that can be readily adapted to complete the pagefault portion of the assignment. <br>

The only function you really need to get the pagefault stat is all_vm_events, which populates an array of longs with various statistical information[10]. You just need to invoke the function, then index to the correct array element in the result; in our case, PGFAULT is the index we need. Examples of all_vm_events usage are available in the Linux kernel source[11]. You’ll need to #include <linux/mm.h> in your kernel module to access the all_vm_events function. <br>

seq_printf uses the same format specifiers as printf. The format specifier for an unsigned long is just a Google search away.<br>
