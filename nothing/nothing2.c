#include <linux/module.h>
#include <net/sock.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>

#define NETLINK_USER 30

struct sock *nl_sk = NULL;


static void using_netlink_nl_recv_msg(struct sk_buff *skb)
{
	struct nlmsghdr *nlh;
	int pid;
	struct sk_buff *skb_out;
	int msg_size;
	char *msg = "hello from kernel";
	int res;

	printk(KERN_INFO "Entering : %s()\n", __FUNCTION__);
	msg_size = strlen(msg);

	nlh = (struct nlmsghdr *)skb->data;
	printk(KERN_INFO "Netlink received msg payload: %s\n", (char *)nlmsg_data(nlh));
	pid = nlh->nlmsg_pid;

	skb_out = nlmsg_new(msg_size,0);
	if (!skb_out){
		printk(KERN_ERR "Failed to allocate new skb\n");
		return;
	}
	nlh = nlmsg_put(skb_out, 0, 0, NLMSG_DONE, msg_size, 0);
	NETLINK_CB(skb_out).dst_group = 0;
	strncpy(nlmsg_data(nlh), msg, msg_size);

	res = nlmsg_unicast(nl_sk, skb_out, pid);
	if(res < 0){
		printk(KERN_INFO "Error while sending back to user\n");
	}
	else
		printk(KERN_INFO "kernel module Sent back to user\n");
}


static int __init kthread_init(void)
{
  printk(KERN_ALERT "entering : %s()\n",__FUNCTION__);
  struct netlink_kernel_cfg cfg = {
	.groups = 1,
	.input = using_netlink_nl_recv_msg,
  };

  nl_sk = netlink_kernel_create(&init_net, NETLINK_USER, &cfg);

  if (!nl_sk){
	printk(KERN_ALERT "Error creating socket.\n");
	return -10;
  }
  return 0;
} 

static void __exit kthread_exit(void)
{
  printk(KERN_ALERT "@ %s() : Bye.\n", __FUNCTION__);
  netlink_kernel_release(nl_sk);
} 
 
module_init(kthread_init);
module_exit(kthread_exit);
MODULE_LICENSE("Dual BSD/GPL"); 
