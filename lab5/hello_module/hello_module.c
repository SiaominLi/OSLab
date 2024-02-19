#include <linux/module.h>

int init_module(void) {
        printk(KERN_INFO "Hello modeul insert successfully!\n");
        return 0;
}

void cleanup_module(void) {
        printk(KERN_INFO "Hello module remove successfully!\n");
}

//module information
MODULE_LICENSE("GPL");
MODULE_AUTHOR("s109037012");
MODULE_DESCRIPTION("oslab5: hello_module");


