/* $Id: upnpglobalvars.c,v 1.3 2009/07/02 01:26:29 bert Exp $ */
/* project: MiniUPnP
 * Website: http://miniupnp.free.fr/
 * Author : Thomas Bernard
 * This software is subject to the conditions
 * detailed in the LICENCE file provided in this
 * distribution. */
#include <sys/types.h>
#include <netinet/in.h>
#include "upnpglobalvars.h"

/* network interface for internet */
char ext_if_name[MAX_LEN_IF_NAME];
const char * lan_if_name = 0;

/* ip address of this interface */
char ext_ip_addr[INET_ADDRSTRLEN];
#ifdef ENABLE_IPV6
char ext_ip_addr6[INET6_ADDRSTRLEN];
#endif

/* LAN address */
char lan_ip_addr[INET_ADDRSTRLEN];
char listen_addr[INET_ADDRSTRLEN];

#ifdef ENABLE_IPV6 
char lan_ip_addr6[INET6_ADDRSTRLEN];
char listen_addr6[INET6_ADDRSTRLEN];
#endif

unsigned long downstream_bitrate = 0;
unsigned long upstream_bitrate = 0;

#ifdef ENABLE_NATPMP
/* UPnP permission rules : */
struct upnpperm * upnppermlist = 0;
unsigned int num_upnpperm = 0;

/* NAT-PMP */
unsigned int nextnatpmptoclean_timestamp = 0;
unsigned short nextnatpmptoclean_eport = 0;
unsigned short nextnatpmptoclean_proto = 0;
#endif

#ifdef CONFIG_RANDOM_URL
char random_url[RANDOM_URL_MAX_LEN] = "random";
#endif /*CONFIG_RANDOM_URL*/

/* startup time */
time_t startup_time = 0;
/*wan iface uptime*/
time_t wan_uptime = 0;
int wan_states=-1;

/* use system uptime */
int sysuptime = 0;

/* log packets flag */
int logpackets = 0;

const char * pidfilename = "/var/run/miniupnpd.pid";

//char uuidvalue[] = "uuid:00000000-0000-0000-0000-000000000000";
//char uuidvalue[] = "uuid:02350000-4000-0000-0000-000000000001";

#ifdef CONFIG_RTL8186_KB
char uuidvalue[] = "uuid:82350000-4000-0000-0000-000000000001";
#else
#ifdef CONFIG_RTL8186_GR
char uuidvalue[] = "uuid:02350000-4000-0000-0000-000000000001";
#else
#ifdef CONFIG_CERTIFICATION
char *uuidvalue[] = {"uuid:12342409-1234-1234-5678-ee1234cc5678",
						"uuid:22342409-1234-1234-5678-ee1234cc5678",
						"uuid:32342409-1234-1234-5678-ee1234cc5678"};
#else
char uuidvalue[] = "uuid:12342409-1234-1234-5678-ee1234cc5678";	
#endif
#endif
#endif

char location_url[72];
char server_id[72];
char ssdp_ext[72];
unsigned int ssdp_mx=0;
int isCfgFromFile=0;

/* presentation url :
 * http://nnn.nnn.nnn.nnn:ppppp/  => max 30 bytes including terminating 0 */
char presentationurl[PRESENTATIONURL_LEN];

#ifdef ENABLE_6FC_SERVICE
int ipv6fc_firewall_enabled = 1;
int ipv6fc_inbound_pinhole_allowed = 1;
#endif
#ifdef ENABLE_6FC_SERVICE
const char * miniupnpd_v6_filter_chain = "MINIUPNPD";
#endif
#ifdef CONFIG_CERTIFICATION
/* rfc822 (1123) time is exactly 29 characters long
 * "Sun, 06 Nov 1994 08:49:37 GMT"
 */
static const char month_tab[48] ="Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec ";
static const char day_tab[28] = "Sun,Mon,Tue,Wed,Thu,Fri,Sat,";

void rfc822_time_buf(char *buf, time_t s)
{
    struct tm *t;
    char *p;
    unsigned int a;
    t = gmtime(&s);
    p = buf + 28;
    /* p points to the last char in the buf */

    p -= 3;
    /* p points to where the ' ' will go */
    memcpy(p--, " GMT", 4);

    a = t->tm_sec;
    *p-- = '0' + a % 10;
    *p-- = '0' + a / 10;
    *p-- = ':';
    a = t->tm_min;
    *p-- = '0' + a % 10;
    *p-- = '0' + a / 10;
    *p-- = ':';
    a = t->tm_hour;
    *p-- = '0' + a % 10;
    *p-- = '0' + a / 10;
    *p-- = ' ';
    a = 1900 + t->tm_year;
    while (a) {
        *p-- = '0' + a % 10;
        a /= 10;
    }
    /* p points to an unused spot to where the space will go */
    p -= 3;
    /* p points to where the first char of the month will go */
    memcpy(p--, month_tab + 4 * (t->tm_mon), 4);
    *p-- = ' ';
    a = t->tm_mday;
    *p-- = '0' + a % 10;
    *p-- = '0' + a / 10;
    *p-- = ' ';
    p -= 3;
    memcpy(p, day_tab + t->tm_wday * 4, 4);
}
#endif

