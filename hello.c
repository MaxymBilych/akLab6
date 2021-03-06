#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>

#include <linux/ktime.h>
#include <linux/slab.h>

struct head_list {
  struct head_list *next;
  ktime_t time;
};

MODULE_AUTHOR("Maksym Bilych IO-82");
MODULE_DESCRIPTION("Hello world printing Linux module for lab5");
MODULE_LICENSE("Dual BSD/GPL");

static struct head_list *head;

static int amount = 1;
module_param(amount, uint, S_IRUGO);
MODULE_PARM_DESC(amount, "Amount of outputting Hello worlds");



static int __init thisinit(void)
{
  uint i = 0;

  struct head_list *var_1, *var_2;

  head = kmalloc(sizeof(struct head_list *), GFP_KERNEL);

  var_1 = head;
  if (amount == 0) {
    printk(KERN_WARNING "Entered parameter equals 0");
  } else if (amount >= 5 && amount <= 10) {
    printk(KERN_WARNING "Entered parameter is between 5 and 10");
  } else if (amount > 10) {
    printk(KERN_ERR "Entered parameter is bigger than 10");
    return -EINVAL;
  }

  for (i = 0; i < amount; i++) {
    var_1->next = kmalloc(sizeof(struct head_list), GFP_KERNEL);
    var_1->time = ktime_get();
    pr_info("Hello World!");
    var_2 = var_1;
    var_1 = var_1->next;
  }
  if (amount != 0) {
    kfree(var_2->next);
    var_2->next = NULL;
  }

  printk(KERN_INFO "Amount: %d\n", amount);

  return 0;
}

static void __exit thisexit(void)
{
  struct head_list *var;

  while (head != NULL && amount != 0) {
    var = head;
    pr_info("Time: %lld", var->time);
    head = var->next;
    kfree(var);
  }
  pr_info("");
}

module_init(thisinit);
module_exit(thisexit);
