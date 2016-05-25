#include <linux/init.h>  // init, exit
#include <linux/module.h>  // must have
#include <linux/kernel.h>  // printk
#include <linux/sched.h>  // API, sleep
#include <linux/types.h> // dev_t
#include <linux/fs.h> // reg region
#include <linux/pci.h>  // pci reg config space
#include <asm/io.h>  // mem cache
#include "ctl.h"

MODULE_LICENSE("Dual BSD/GPL");

static struct pci_device_id ids[] = {
    {PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82801AA_3), },
    {0, }
};

static int probe(struct pci_dev *dev, const struct pci_device_id *id) {
    pci_enable_device(dev); // init dev
    
    void *addr = ioremap_nocache(99, 4); // some memory
    
    register_chrdev(0, "pci_subdev1", fops);

    return 0;
}

static void remove(struct pci_dev *dev) {
    unregister_chrdev(0, "pci_subdev1");
}

static int *fops_open(inode *node, file *f) {
    scull_dev *dev;
}

static int *fops_release(inode *node, file *f) {

}

static long pci_ioctl(struct file *f, unsigned int cmd, unsigned long arg)
{
    switch (cmd)
    {
        case RW_GET_VARIABLES:
            return ioread8(addr);
            break;
        case RW_CLR_VARIABLES:
            addr = ioremap_nocache(0, 4);
            break;
        case RW_SET_VARIABLES:
            // if (sizeof(mocha) <= sizeof(*addr)) {
            //     iowrite8(mocha, addr);
            // }
            break;
        default:
            return -EINVAL;
    }
 
    return 0;
}

static struct pci_driver pci_driver = {
    .name = "pci_dev",
    .id_table = ids,
    .probe = probe,
    .remove = remove
};

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .unlocked_ioctl = pci_ioctl,
    .open = fops_open,
    .release = fops_release
};

static int initialization_function(void) {
    MODULE_DEVICE_TABLE(pci, ids);  //return ptr to ids

    if (printk_ratelimit())
        printk(KERN_ALERT "Module has been loaded OK\n");


    if (printk_ratelimit())
        printk(KERN_ALERT "Module was getting some memory OK\n");

    return pci_register_driver(&pci_driver);
}

static void cleanup_function(void) {
    pci_unregister_driver(&pci_driver);

    if (printk_ratelimit())
        printk(KERN_ALERT "Module has been unloaded\n");
}

module_init(initialization_function);
module_exit(cleanup_function);
