#include<linux/module.h>

int symbol_variable = 99;
int symbol_function(int x){
	if (x > 0) return 1;
	else if (x == 0) return 0;
	else return -1;
}

int init_module(void){
	printk(KERN_INFO "Symbol A insert successfully!\n");
	return 0;
}

void cleanup_module(void){
	 printk(KERN_INFO "Symbol A remove successfully!\n");
}

EXPORT_SYMBOL(symbol_variable);
EXPORT_SYMBOL(symbol_function);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("s109037012");
MODULE_DESCRIPTION("oslab5: symbol_A");
