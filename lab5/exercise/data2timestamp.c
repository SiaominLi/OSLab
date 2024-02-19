#include <linux/module.h>
#include <linux/time.h>

unsigned int date = 1 , month = 1 , year = 2000 , hour = 0 , minute = 0 , second = 0;
long long int ts;

module_param(date, int, 0);
MODULE_PARM_DESC(date, "date of time");
module_param(month, int, 0);
MODULE_PARM_DESC(month, "month of time");
module_param(year, int, 0);
MODULE_PARM_DESC(year, "year of time");

int init_module(void){
	time64_t t;
	int m[] = {31,28,31,30,31,30,31,31,30,31,30,31};
	if(month<0 || month>12 || date>m[month-1] || date==0){
		printk(KERN_ERR "Invalid argument(s))");
		return -EINVAL;
	}
	t = mktime64( year, month, date, hour, minute, second);
	ts = t;
	printk(KERN_INFO "data2timestamp inserted successfully! ts=%lld\n", t);
	return 0;
}

void cleanup_module(void) {
	printk(KERN_INFO "Hello data2timestamp remove successfully!\n");
}
EXPORT_SYMBOL(ts);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("s109037012");
MODULE_DESCRIPTION("oslab5: data2timestamp");

