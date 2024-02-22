#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/fs.h>

int usb_open(struct inode *ipnode, struct file *pfile)
{
	printk(KERN_ALERT "Inside the %s function\n",__FUNCTION__);
	return 0;
}

ssize_t usb_write(struct file *pfile, const char __user * buffer, size_t length, loff_t *offset)
{
	printk(KERN_ALERT "Inside the %s function\n",__FUNCTION__);
	return length;
}

ssize_t usb_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset)
{
	printk(KERN_ALERT "Inside the %s function\n",__FUNCTION__);
	return 0;
}

int usb_close(struct inode *ipnode, struct file *pfile)
{
	printk(KERN_ALERT "Inside the %s function\n",__FUNCTION__);
        return 0;
}

struct file_operations usb_fops = {
	.owner = THIS_MODULE,
	.open = usb_open,
	.write = usb_write,
	.read = usb_read,
	.release = usb_close,
};
int usb_simple_module_init(void)
{
	printk(KERN_ALERT "Inside the %s function\n",__FUNCTION__);
	register_chrdev(240,"Simple_CharDev",&usb_fops);
        return 0;
}

void usb_simple_module_exit(void)
{
	printk(KERN_ALERT "Inside the %s function\n",__FUNCTION__);
	unregister_chrdev(240,"Simple CharDev");
}

module_init(usb_simple_module_init);
module_exit(usb_simple_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dummy ChrDriver");
MODULE_DESCRIPTION("C-Developer");

