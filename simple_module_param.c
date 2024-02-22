#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>

int count = 1;
module_param(count,int,0644);

int simple_module_init(void)
{
	int i;
	printk(KERN_ALERT "I am @ init %s function\n", __FUNCTION__);
	for(i=0;i<count;i++)
	{
		printk("HELLO WORLD: Index = %d\n",i);
	}
	return 0;
}

void simple_module_exit(void)
{
	int i;
        printk(KERN_ALERT "I am @ init %s function\n", __FUNCTION__);
        for(i=0;i<count;i++)
        {
                printk("GoodBye: Index = %d\n",i);
        }
}

module_init(simple_module_init);
module_exit(simple_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("BIPUL");
MODULE_DESCRIPTION("This is a basic sample driver to count parameter ");
