#include<linux/init.h>
#include<linux/module.h>

int simple_module_init(void)
{
	printk(KERN_ALERT"Iam @ init %s function\n",__FUNCTION__);
	printk("Hello world\n");
	return 0;
}


void simple_module_exit(void)
{
	printk("good bye\n");
}

module_init(simple_module_init);
module_exit(simple_module_exit);



