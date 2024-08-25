#include <linux/init.h>    // included for __init and __exit macros
#include <linux/kernel.h>  // included for KERN_INFO
#include <linux/module.h>  // included for all kernel modules

MODULE_LICENSE("REDHAT");
MODULE_AUTHOR("misheechkin");
MODULE_DESCRIPTION("FIRST MODULE");

static int __init hello_init(void) {
    printk(KERN_INFO "Hello world!\n");
    return 0;  // Non-zero return means that the module couldn't be loaded.
}

static void __exit hello_cleanup(void) {
    printk(KERN_INFO "Cleaning up module.\n");
}

module_init(hello_init);
module_exit(hello_cleanup);