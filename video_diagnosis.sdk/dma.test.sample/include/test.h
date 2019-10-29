#define USED_LEN 44



#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>     // sockaddr_in, "man 7 ip" ,htons
#include <poll.h>             //poll,pollfd
#include <arpa/inet.h>   //inet_addr,inet_aton
#include <unistd.h>        //read,write
#include <netdb.h>         //gethostbyname
#include <sys/ioctl.h>
#include <net/if.h>

struct board_info {
    unsigned char upmac[6];	/* mac*/
    unsigned char downmac[6];	/* mac*/
    unsigned char upip[4];
    unsigned char downip[4];
    unsigned char flag_4G;		/* 0x1a 移动 0x1b 联通 0x1c电信	其他都不启动*/
    unsigned char flag_wifi;	/*wifi 是否启动 0x5a 启动 其他不启动*/
    unsigned char flag_upnet;	/*上行 是否udhcpc启动 0x5a 启动 其他不启动*/
    unsigned char flag_downnet;/*下行 是否udhcpc启动 0x5a 启动 其他不启动*/
    unsigned char name[16];/*下行 是否udhcpc启动*/
    unsigned char resever[256-44];//减的数据跟USED_LEN保持一致
    unsigned char crc32[4];	
};

//#define BOARD_ENV            "/root/board_env.bin" 
#define BOARD_ENV            "board_env.bin" 
#define UP_ETH               "eth0"
#define DOWN_ETH             "eth1"
#define DEF_IP               "176.1.1.110"
#define WIFI_WPA             "/root/wpa.conf"

uint32_t crc32(unsigned char *buf, uint32_t size);
void get_local_ip(char *ifname);
void get_local_mac(char *ifname);  