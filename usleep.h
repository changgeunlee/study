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
        int        retrans_count;          // 재전송
               int    in_packet;
               int    out_packet;
               int    in_bytes;
               int    out_bytes;
               int        spd_id;                         // 필터링 정책ID
               int        nat_id;                         // NAT 정책ID
               short        status;                         // 상태 (close, ..)
               short        action;                         // 행위 (accept, drop, detect, appove)
               int        holding_time;           // 유지시간 
               int        sid;                            // application 이름  
               int        profile_num;            // 프로파일 
 } log_ext_fw;

typedef struct
{
	char name[64];
} ipsec_name_info;

 typedef struct
 {
         int inpacket;      // 패킷(RX)
         int outpacket; // 패킷(TX)
         int inbyte;        // 사용량(RX)
         int outbyte;       // 사용량(TX)
         ipsec_name_info serial; // 시리얼 넘버
         ipsec_name_info device; // 대상 장비
 } log_ext_vpn;


 typedef struct
 {
         char            user[64];
         int                     tunnel_id;                      // 터널 ID
         int    in_packet;                  // rx packet cnt
         int    out_packet;                 // tx packet cnt
         int    in_bytes;                   // rx packet byte
         int    out_bytes;                  // tx packet byte
         short        action;                         // 행위 ( allow, deny )
 } log_ext_ssl;

typedef struct
 {
         int audit_log_id;
         int track_id;                      // track id
         int block_byte;            // 차단 바이트 수
         int spd_id;                        // 필터링 정책 ID
         int profile_id;                         // ips 프로파일 ID
         int ips_group_id;                       // 그룹ID
         int action;                                     // alert, drop
         int block_type;                         // 차단 유형(1:1, 1:N, N:1 등 .....)
         int block_time;                         // 차단 시간
         int block_count;                        // 차단 패킷 수
         int priority;                           // 위험도

         int ips_start_time;           // 탐지,차단 시작 시간
         int ips_end_time;                     // 탐지,차단 마지막 시간

         char pattern_name[96];          // 시그너처이름
         int sid;                           // fsid
         short pattern_name_size;     // 시그너처 이름 길이
 
 } log_ext_ips;


 typedef struct
 {
         int audit_log_id;
         int track_id;                      // track id
         int block_byte;            // 차단 바이트 수
         int detect_byte;           // 탐지 바이트 수
 
         int ddos_start_time;          // 탐지, 차단 시작시간
         int ddos_end_time;            // 탐지, 차단 마지막 시간
 
         int profile_id;                         // ddos 프로파일 ID
         int action;                                     // 탐지, 차단
         int attack_type;                        // 공격 type
         int attack_pps;                         // 공격 pps
         int block_type;                         // 차단 유형(1:1, N:1)
         int block_time;                         // 차단 시간
         int block_count;                        // 차단 패킷 수
 
 } log_ext_ddos;
 

 typedef struct
 {
         char            profile_name[32];               // 프로파일 이름
         char            file_name[20];                  // 바이러스 검사된 파일
         char            virus_info[32];                 // 바이러스 정보(위협정보, 바이러스 이름
         char            sub_desc[32];                   // 상세정보
         short        profile_id;                             // 프로파일 ID
         short        action;                                 // 차단 : 0, 탐지 : 1, 통과 : 2
 } log_ext_av;

 typedef struct
 {
         char            profile_name[32];               // 프로파일 이름
         char            file_name[20];                  // 스팸 대상 첨부 파일
         char            spam_info[32];                  // 스팸 기능에 감지된 위협
         char            sub_desc[32];                   // 상세정보
         char            sender[32];                             // 발신자 메일주소
         char            receiver[32];                   // 수신자 메일주소
         short        profile_id;                             // 프로파일 ID
         short        action;                                 // 차단 : 0, 탐지 : 1, 통과 : 2
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
 
         int        extend_type; // EXTEND_TYPE enum 참조, 없는건 추가해서 사용
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
