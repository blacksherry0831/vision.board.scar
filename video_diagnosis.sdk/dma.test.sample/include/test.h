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
    unsigned char flag_4G;		/* 0x1a �ƶ� 0x1b ��ͨ 0x1c����	������������*/
    unsigned char flag_wifi;	/*wifi �Ƿ����� 0x5a ���� ����������*/
    unsigned char flag_upnet;	/*���� �Ƿ�udhcpc���� 0x5a ���� ����������*/
    unsigned char flag_downnet;/*���� �Ƿ�udhcpc���� 0x5a ���� ����������*/
    unsigned char name[16];/*���� �Ƿ�udhcpc����*/
    unsigned char resever[256-44];//�������ݸ�USED_LEN����һ��
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