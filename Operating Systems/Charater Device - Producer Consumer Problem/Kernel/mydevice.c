
#include <linux/init.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/semaphore.h>
#include <linux/slab.h>
#include <linux/moduleparam.h>
#include <linux/miscdevice.h>
#include <linux/mutex.h>


static DEFINE_SEMAPHORE(empty);
static DEFINE_SEMAPHORE(full);
static DEFINE_MUTEX(mutex);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Producer Consumer Using Character Device");
MODULE_AUTHOR("Kunal Zantye Prashant Kolhe");

char *buf[1000];
static int times = 0;
int size_buf = 10;
int cnt_producer = 0, cnt_consumer = 0;

module_param(size_buf, int, S_IRUSR | S_IWUSR);

static int my_open(struct inode *inodep, struct file *file);
static ssize_t my_read(struct file *file, char __user * out, size_t size, loff_t *offset);
static ssize_t my_write(struct file *file, char __user * out, size_t size, loff_t *offset);
static int my_close(struct inode *inodep, struct file *file);


static struct file_operations my_fops = { 
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_close,
    .read = my_read,
    .write= my_write,
};

static struct miscdevice my_misc_device = { 
    .minor = MISC_DYNAMIC_MINOR, 
    .name = "mydevice",
    .fops = &my_fops
};

// init_module is called when device is loaded.
 int __init init_module() {
    int majorNumber;
    majorNumber = misc_register(&my_misc_device);
    
    if(majorNumber < 0) {
	printk(KERN_ALERT "Failed to register the device\n");
      return majorNumber;
    } 
    else 
    {
        sema_init(&empty, size_buf);
        sema_init(&full, 0);
	mutex_init(&mutex);
    }
    printk(KERN_INFO "Device has been registered with major number %d\n", majorNumber);
    return majorNumber;
}

// my_exit is called when device is unloaded.
static void __exit my_exit(void) {
   
   kfree(buf);		
    misc_deregister(&my_misc_device);	
   printk(KERN_INFO "Device has been unregistered \n");
}

// my_open is called when device is opened.
static int my_open(struct inode *inodep, struct file *file) {	
   times++;
   printk(KERN_INFO "Device has been opened %d \n", times);
   return 0;
}

// my_read is called when read is called on device.
static ssize_t my_read(struct file *file, char __user * out, size_t size, loff_t *offset){
    
    char buffer[1000];   
    if(down_interruptible(&full) < 0 ) 
    {				 	
	   printk(KERN_ALERT "Device Buffer is empty.");				
	   return -1;
    }
    if(mutex_lock_interruptible(&mutex) < 0) 
    {		
	  printk(KERN_ALERT "CRITICAL SECTION :lock on mutex");                				
	   return -1;
    }

     sprintf(buffer, buf[cnt_consumer]);
    if(copy_to_user(out, buf[cnt_consumer], strlen(buffer) + 1)==0 )
    {
         printk(KERN_INFO "String Read from device: %s\n", out);
    }else
	return -EFAULT;
	
   cnt_consumer++;
   mutex_unlock(&mutex);								
    up(&empty);								
    return 0;								
}

// my_write is called when write is called on device.
static ssize_t my_write(struct file *file, char __user * out, size_t size, loff_t *offset) {
 	
   
   if(down_interruptible(&empty) < 0) {					
        printk(KERN_ALERT "Device buffer is full");				
        return -1;
    }
    if(mutex_lock_interruptible(&mutex) < 0) 
    {					
	  printk(KERN_ALERT "CRITICAL SECTION :lock on mutex");                
	   return -1;
    }
   
    buf[cnt_producer] = kmalloc(sizeof(out), GFP_KERNEL);
    

    if(copy_from_user(buf[cnt_producer], out, strlen(out) + 1)==0 )
   {
             printk(KERN_INFO "String Written to device: %s\n", buf[cnt_producer]);

   }
   else
	return -EFAULT;
   cnt_producer++;
   mutex_unlock(&mutex);						
    up(&full);						
    return 0;					
}


// my_close is called when close is called on device.
static int my_close(struct inode *inodep, struct file *file){
	times--;    
	printk(KERN_INFO "Device has been successfully closed\n");

    return 0;
}



module_exit(my_exit);
