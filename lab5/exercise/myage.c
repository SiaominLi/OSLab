#include <linux/module.h>
#include <linux/time.h>

extern long long int ts;
long long int diff,t,y,d;


int init_module(void){
	
	t = ktime_get_real()/1000000000;
	diff = t-ts;
	if(diff<0)
		printk(KERN_INFO "What???????");
	else{
		y = diff/31536000;
		d = (diff - y*31536000)/(24*60*60);
		
		printk(KERN_INFO "Wow you have survived on this worid %lld years %lld days\n",y,d);
		printk(KERN_INFO "myage inserted successfully!");
	}
	return 0;
}

void cleanup_module(void) {
	printk(KERN_INFO "Hello myage remove successfully!\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("s109037012");
MODULE_DESCRIPTION("oslab5: myage");

