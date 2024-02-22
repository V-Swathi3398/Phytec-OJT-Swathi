#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include <linux/fs.h>
#include<linux/uaccess.h>
//#include<asm/uaccess.h>
#include <linux/gpio.h>
//#include<linux/cdev.h>
//#include<linux/slab.h>

#define GPIO_PC_13 77

int major_number;
char kbuff[20];

int led_init(int gpio_num)

{
	int retval=0;
	retval= gpio_request(gpio_num,"sled");
	
	if(retval<0) 
		return retval;

	retval= gpio_direction_output(gpio_num,1);
	return retval;
}

void led_on(int gpio_num)
{
	gpio_set_value(gpio_num,1);

}

void led_off(int gpio_num)
{
	gpio_set_value(gpio_num,0);
}

int sled_open(struct inode *in, struct file *fp)
{
	printk(KERN_INFO "This is sled open function\n");
	led_init(GPIO_PC_13);
	return 0;
}

ssize_t sled_read (struct file *fp, char __user *buff, size_t sz, loff_t *offset)
{
	printk(KERN_INFO "This is sled read function\n");
	return 0;
}
ssize_t sled_write (struct file *fp, const char __user *buff, size_t sz, loff_t *offset)
{
	printk(KERN_INFO "This is sled write function\n");
	copy_from_user(kbuff,buff,sz);

	if(kbuff[0]=='O' && kbuff[1]=='N')
	       led_on(GPIO_PC_13);
	else if(kbuff[0]=='O' && kbuff[1]=='F' && kbuff[2]=='F')
		led_off(GPIO_PC_13);
	else
		printk(KERN_INFO "Invalid function");
	return 0;
}

int sled_release (struct inode *in, struct file *fp)
{
	printk(KERN_INFO "This is sled release function\n");
	return 0;
}


struct file_operations fops= {
	.open=sled_open,
	.read=sled_read,
	.write=sled_write,
	.release=sled_release 
};

	
static int __init sled_init(void)
{
    major_number=register_chrdev(0,"sled",&fops);
    printk(KERN_INFO "Major number is %d",major_number);
    printk(KERN_INFO "sled driver Inserted..\n");
    return 0;
}

static void __exit sled_exit(void)
{
    unregister_chrdev(major_number,"sled");
    printk(KERN_INFO "sled driver Removed...\n");
}
 
module_init(sled_init);
module_exit(sled_exit);
 

