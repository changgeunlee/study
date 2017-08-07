#if 0
#define ERR(fmt, args...) do{} while(0)
#else
#define ERR(fmt, args...) printf(fmt, ##args)
#endif

