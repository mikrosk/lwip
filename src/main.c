#include <unistd.h>
#include <getopt.h>
#include <string.h>

#include "lwip/init.h"
#include "lwip/debug.h"
 #include "lwip/timeouts.h"
#include "lwip/stats.h"
#include "lwip/ip.h"
// //#include "netif/tapif.h"
 #include "netif/etharp.h"

/* (manual) host IP configuration */
static ip4_addr_t ipaddr, netmask, gw;

/* nonstatic debug cmd option, exported in lwipopts.h */
unsigned char debug_flags;

static struct option longopts[] = {
  /* turn on debugging output (if build with LWIP_DEBUG) */
  {"debug", no_argument,        NULL, 'd'},
  /* help */
  {"help", no_argument, NULL, 'h'},
  /* gateway address */
  {"gateway", required_argument, NULL, 'g'},
  /* ip address */
  {"ipaddr", required_argument, NULL, 'i'},
  /* netmask */
  {"netmask", required_argument, NULL, 'm'},
  /* ping destination */
  {"trap_destination", required_argument, NULL, 't'},
  /* new command line options go here! */
  {NULL,   0,                 NULL,  0}
};
#define NUM_OPTS ((sizeof(longopts) / sizeof(struct option)) - 1)

static void
usage(void)
{
  unsigned char i;

  printf("options:\n");
  for (i = 0; i < NUM_OPTS; i++) {
    printf("-%c --%s\n",longopts[i].val, longopts[i].name);
  }
}

int
main(int argc, char **argv)
{
  struct netif netif;
  int ch;
  char ip_str[16] = {0}, nm_str[16] = {0}, gw_str[16] = {0};

  /* startup defaults (may be overridden by one or more opts) */
  IP4_ADDR(&gw, 192,168,0,1);
  IP4_ADDR(&ipaddr, 192,168,0,2);
  IP4_ADDR(&netmask, 255,255,255,0);

  /* use debug flags defined by debug.h */
  debug_flags = LWIP_DBG_OFF;

  while ((ch = getopt_long(argc, argv, "dhg:i:m:t:", longopts, NULL)) != -1) {
    switch (ch) {
      case 'd':
        debug_flags |= (LWIP_DBG_ON|LWIP_DBG_TRACE|LWIP_DBG_STATE|LWIP_DBG_FRESH|LWIP_DBG_HALT);
        break;
      case 'h':
        usage();
        exit(0);
        break;
      case 'g':
        ip4addr_aton(optarg, &gw);
        break;
      case 'i':
        ip4addr_aton(optarg, &ipaddr);
        break;
      case 'm':
        ip4addr_aton(optarg, &netmask);
        break;
      case 't':
        break;
      default:
        usage();
        break;
    }
  }
  argc -= optind;
  argv += optind;

  strncpy(ip_str, ip4addr_ntoa(&ipaddr), sizeof(ip_str));
  strncpy(nm_str, ip4addr_ntoa(&netmask), sizeof(nm_str));
  strncpy(gw_str, ip4addr_ntoa(&gw), sizeof(gw_str));
  printf("Host at %s mask %s gateway %s\n", ip_str, nm_str, gw_str);


  lwip_init();

  printf("TCP/IP initialized.\n");

  netif_add(&netif, &ipaddr, &netmask, &gw, NULL, /*tapif_init*/NULL, ethernet_input);
  netif_set_default(&netif);
  netif_set_up(&netif);

  printf("Applications started.\n");

  while (1) {
    /* poll netif, pass packet to lwIP */
    //tapif_select(&netif);

    sys_check_timeouts();
  }

  return 0;
}
