#define MAX_EXTEND_LEN 304
#define LOG_DESC_LEN 128

typedef struct
{
	char user[64];
}log_ext_system;

typedef struct
{
	int spd_id;
}log_ext_network;

typedef struct
{
	char      url[64];
        char         userid[32];
        int        url_category;
        int        retrans_count;          // ������
               int    in_packet;
               int    out_packet;
               int    in_bytes;
               int    out_bytes;
               int        spd_id;                         // ���͸� ��åID
               int        nat_id;                         // NAT ��åID
               short        status;                         // ���� (close, ..)
               short        action;                         // ���� (accept, drop, detect, appove)
               int        holding_time;           // �����ð� 
               int        sid;                            // application �̸�  
               int        profile_num;            // �������� 
 } log_ext_fw;

typedef struct
{
	char name[64];
} ipsec_name_info;

 typedef struct
 {
         int inpacket;      // ��Ŷ(RX)
         int outpacket; // ��Ŷ(TX)
         int inbyte;        // ��뷮(RX)
         int outbyte;       // ��뷮(TX)
         ipsec_name_info serial; // �ø��� �ѹ�
         ipsec_name_info device; // ��� ���
 } log_ext_vpn;


 typedef struct
 {
         char            user[64];
         int                     tunnel_id;                      // �ͳ� ID
         int    in_packet;                  // rx packet cnt
         int    out_packet;                 // tx packet cnt
         int    in_bytes;                   // rx packet byte
         int    out_bytes;                  // tx packet byte
         short        action;                         // ���� ( allow, deny )
 } log_ext_ssl;

typedef struct
 {
         int audit_log_id;
         int track_id;                      // track id
         int block_byte;            // ���� ����Ʈ ��
         int spd_id;                        // ���͸� ��å ID
         int profile_id;                         // ips �������� ID
         int ips_group_id;                       // �׷�ID
         int action;                                     // alert, drop
         int block_type;                         // ���� ����(1:1, 1:N, N:1 �� .....)
         int block_time;                         // ���� �ð�
         int block_count;                        // ���� ��Ŷ ��
         int priority;                           // ���赵

         int ips_start_time;           // Ž��,���� ���� �ð�
         int ips_end_time;                     // Ž��,���� ������ �ð�

         char pattern_name[96];          // �ñ׳�ó�̸�
         int sid;                           // fsid
         short pattern_name_size;     // �ñ׳�ó �̸� ����
 
 } log_ext_ips;


 typedef struct
 {
         int audit_log_id;
         int track_id;                      // track id
         int block_byte;            // ���� ����Ʈ ��
         int detect_byte;           // Ž�� ����Ʈ ��
 
         int ddos_start_time;          // Ž��, ���� ���۽ð�
         int ddos_end_time;            // Ž��, ���� ������ �ð�
 
         int profile_id;                         // ddos �������� ID
         int action;                                     // Ž��, ����
         int attack_type;                        // ���� type
         int attack_pps;                         // ���� pps
         int block_type;                         // ���� ����(1:1, N:1)
         int block_time;                         // ���� �ð�
         int block_count;                        // ���� ��Ŷ ��
 
 } log_ext_ddos;
 

 typedef struct
 {
         char            profile_name[32];               // �������� �̸�
         char            file_name[20];                  // ���̷��� �˻�� ����
         char            virus_info[32];                 // ���̷��� ����(��������, ���̷��� �̸�
         char            sub_desc[32];                   // ������
         short        profile_id;                             // �������� ID
         short        action;                                 // ���� : 0, Ž�� : 1, ��� : 2
 } log_ext_av;

 typedef struct
 {
         char            profile_name[32];               // �������� �̸�
         char            file_name[20];                  // ���� ��� ÷�� ����
         char            spam_info[32];                  // ���� ��ɿ� ������ ����
         char            sub_desc[32];                   // ������
         char            sender[32];                             // �߽��� �����ּ�
         char            receiver[32];                   // ������ �����ּ�
         short        profile_id;                             // �������� ID
         short        action;                                 // ���� : 0, Ž�� : 1, ��� : 2
 } log_ext_as;

union log_address {
	int	ip;
	int	ip6[4];
};

typedef struct
{
         int        version;
         int        event;
 
         int        timestamp;
         int        microtime;
 
         union log_address src;
         union log_address dest;
         union log_address nat_src;
         union log_address nat_dest;
 
         char            desc[LOG_DESC_LEN];
 
         short        protocol;
         char     ip_type;
         char     direction;
         short        packet_id;
         short    tcp_flag;
	 union {
                 char         dummy[MAX_EXTEND_LEN];
                 log_ext_system  system;
                 log_ext_network network;
                 log_ext_fw              fw;
                 log_ext_vpn             vpn;
                 log_ext_ssl             ssl;
                 log_ext_ips             ips;
                 log_ext_ddos    ddos;
                 log_ext_av              av;
                 log_ext_as              as;
         };
 
         int        extend_type; // EXTEND_TYPE enum ����, ���°� �߰��ؼ� ���
         char                    name[32];
}__attribute__((packed)) log_param_struct;

typedef struct{
	unsigned char hdd_save;
	unsigned char mail;
	unsigned char send_alert;
	unsigned char syslog;
	unsigned char smc_log;
	unsigned char log_lev;
	unsigned char rvd2;
	unsigned char rvd3;

}log_setting_struct;

typedef struct{
	union {
		long flag; // 8 
		log_setting_struct set;	 // 8
	}log;
	log_param_struct log_param;
}__attribute__((packed)) log_config_struct;
