#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/kthread.h>
 
#include <linux/skbuff.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>
 
#include <linux/netlink.h>
#include <net/netlink.h>
 
//#include "netlink.h"
 
#define NETLINK_PROTOCOL		30
#define NETLINK_TYPE			SOCK_RAW
#define NETLINK_GROUP		4
#define MAX_PAYLOAD			1024
 
struct sock *nl_sock = 0;
int seq_id=0;
struct task_struct *my_task = NULL;
 
static int netlink_test(int index)
{
	struct sk_buff *skb = NULL;
	struct nlmsghdr *nlh;
	unsigned char *data;
	int ret;
 
	printk("%4d allocation sk_buff\n", index);
	skb = alloc_skb(NLMSG_SPACE(MAX_PAYLOAD), GFP_KERNEL);
	if(skb == NULL)
	{
		printk("fail to alloc sk_buff\n");
		return -1;
	}
 
	printk("NLMSG_SPACE(MAX_PAYLOAD)=%d\n", NLMSG_SPACE(MAX_PAYLOAD));
	printk("skb->len=%d\n", skb->len);
 
#if 1
 
//	nlh = (struct nlmsghdr *)skb->data;
	nlh = (struct nlmsghdr *)skb_put(skb, NLMSG_SPACE(MAX_PAYLOAD));
	data = NLMSG_DATA(nlh);
	printk("skb->len=%d\n", skb->len);
 
	nlh->nlmsg_len = NLMSG_SPACE(MAX_PAYLOAD);
	nlh->nlmsg_type = 0;
	nlh->nlmsg_flags = 0;
	nlh->nlmsg_seq = 0;
	nlh->nlmsg_pid = 0; // from kerenel
 
	printk("copy data\n");
	strcpy(data, "Notify Message from kernel!!!!");
 
	NETLINK_CB(skb).dst_group = 1;
 
	/*
	int netlink_broadcast(struct sock *ssk, struct sk_buff *skb, u32 pid,
		      u32 group, gfp_t allocation)
	 */
 
	printk("broad casting\n");
	ret = netlink_broadcast(nl_sock, skb, 0, 1, GFP_KERNEL);
	if(ret)
	{
		printk("fail to send kernel->user\n=%d\n", ret);
	}
 
#endif
 
//	kfree_skb(skb);
 
 
	return ret;
}
 
static void netlink_recv(struct sk_buff *skb)
{
}
 
static int netlink_init(void)
{
	int i = NETLINK_KOBJECT_UEVENT;
	printk("create netlink socket\n");
	nl_sock = netlink_kernel_create(&init_net, 31, 1, netlink_recv, NULL, THIS_MODULE);
	if(nl_sock == NULL)
	{
		printk("fail to create netlink socket\n");
		return -1;
	}
	netlink_set_nonroot(31, NL_NONROOT_RECV);
	return 0;
}
 
static int netlink_close(void)
{
	printk("close netlink socket\n");
	netlink_kernel_release(nl_sock);
	return 0;
}
 
static int thread_proc(void *unused)
{
//	DECLARE_WAITQUEUE(wait, current);
	int thread_proc_count = 0;
//	int i;
 
	msleep(100);
 
	printk("thread start\n");
 
	while(!kthread_should_stop())
	{
		thread_proc_count++;
		printk("thread processing %d\n", thread_proc_count);
		netlink_test(thread_proc_count);
		msleep(1000);
	}
 
	printk("set current state TASK_RUNNING\n");
//	__set_current_state(TASK_RUNNING);
 
	printk("remove wait queue\n");
//	remove_wait_queue(&thread_proc_wait, &wait);
 
	return 0;
}
 
static int thread_start(void)
{
	my_task = kthread_create(thread_proc, NULL, "%s", "my_thread");
	if(my_task)
	{
		printk("thread start complete\n");
		wake_up_process(my_task);
//		wake_up(my_task);
	}
	return 0;
}
 
static int thread_terminate(void)
{
	if(my_task) kthread_stop(my_task);
	return 0;
}
 
int test_init(void)
{
	int ret = 0;
 
	printk("\n\n\n");
	printk("Module Init\n");
 
	printk("netlink init\n");
	netlink_init();
	printk("thread init\n");
	thread_start();
 
	/*
	 {
	 int i;
	 for(i=0; i<100; i++)
	 {
	 netlink_test(i);
	 msleep(1000);
	 }
	 }
	 */
 
	return ret;
}
 
void test_exit(void)
{
	printk("netlink close\n");
	netlink_close();
	printk("thread terminate\n");
	thread_terminate();
	printk("Module Exit\n");
}
 
module_init(test_init);
module_exit(test_exit);
 
//MODULE_LICENSE("Dual BSD/GPL");
MODULE_LICENSE("GPL");
