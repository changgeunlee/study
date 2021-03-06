#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x683cfe8d, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xd329538c, __VMLINUX_SYMBOL_STR(single_release) },
	{ 0x47275ef0, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0xbc78ef3c, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0xacc9c85e, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0x4752cef8, __VMLINUX_SYMBOL_STR(proc_create_data) },
	{ 0xb1903e77, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0xf6d8d765, __VMLINUX_SYMBOL_STR(single_open) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "15E0A3D7C56AB0154E5A911");
