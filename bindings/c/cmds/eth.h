/**
 * @file
 * This command group contains ethernet related commands.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_ETH_H__
#define __BRP_BALTECH_SDK_CMDS_ETH_H__
#include "../typedefs.h"
#ifdef BALTECH_SDK_INTERNAL
/**
 * No result yet.
 */
#define BRP_Eth_ErrNoResultYet BRP_ERR_STATUS(0x4500, 0x01)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Port is not connected.
 */
#define BRP_Eth_ErrNotConnected BRP_ERR_STATUS(0x4500, 0x02)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Detection is disabled.
 */
#define BRP_Eth_ErrDisabled BRP_ERR_STATUS(0x4500, 0x03)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	brp_buf* MAC;
	brp_mempool *mempool;
} brp_Eth_GetMacAdr_t;
/**
 * Retrieve the MAC address of the device.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **MAC** (out) 
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Eth_GetMacAdr(brp_protocol protocol, brp_buf* MAC, brp_mempool *mempool);
#else
brp_errcode brp_Eth_GetMacAdr(brp_Eth_GetMacAdr_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf* IP;
	brp_mempool *mempool;
} brp_Eth_GetConnDevIP_t;
/**
 * Retrieve the IP address of the directly connected network device.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **IP** (out) 
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Eth_GetConnDevIP(brp_protocol protocol, brp_buf* IP, brp_mempool *mempool);
#else
brp_errcode brp_Eth_GetConnDevIP(brp_Eth_GetConnDevIP_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_Eth_CreateRecoveryPoint_t;
/**
 * Create a _Recovery Point_ , backing up all relevant Ethernet- and TCP/IP- settings.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Eth_CreateRecoveryPoint(brp_protocol protocol);
#else
brp_errcode brp_Eth_CreateRecoveryPoint(brp_Eth_CreateRecoveryPoint_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_Eth_DelRecoveryPoint_t;
/**
 * Remove a Recovery Point which was created via the Eth.CreateRecoveryPoint command.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Eth_DelRecoveryPoint(brp_protocol protocol);
#else
brp_errcode brp_Eth_DelRecoveryPoint(brp_Eth_DelRecoveryPoint_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned* PortStatus;
	brp_buf* StaticIPAdr;
	brp_buf* StaticIPNetmask;
	brp_buf* StaticIPGateway;
	brp_buf* DHCPAdr;
	brp_buf* DHCPNetmask;
	brp_buf* DHCPGateway;
	brp_buf* LinkLocalAdr;
	brp_buf* LinkLocalNetmask;
	brp_buf* LinkLocalGateway;
	brp_buf* DNSAdr;
	brp_buf* HostAdr;
	unsigned* HostPort;
	unsigned* AutocloseTimeout;
	brp_mempool *mempool;
} brp_Eth_GetNetworkStatus_t;
/**
 * Retrieve current network status.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **PortStatus** (out) 
 *   - **StaticIPAdr** (out) 
 *   - **StaticIPNetmask** (out) 
 *   - **StaticIPGateway** (out) 
 *   - **DHCPAdr** (out) 
 *   - **DHCPNetmask** (out) 
 *   - **DHCPGateway** (out) 
 *   - **LinkLocalAdr** (out) 
 *   - **LinkLocalNetmask** (out) 
 *   - **LinkLocalGateway** (out) 
 *   - **DNSAdr** (out) 
 *   - **HostAdr** (out) 
 *   - **HostPort** (out) 
 *   - **AutocloseTimeout** (out) 
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Eth_GetNetworkStatus(brp_protocol protocol, unsigned* PortStatus, brp_buf* StaticIPAdr, brp_buf* StaticIPNetmask, brp_buf* StaticIPGateway, brp_buf* DHCPAdr, brp_buf* DHCPNetmask, brp_buf* DHCPGateway, brp_buf* LinkLocalAdr, brp_buf* LinkLocalNetmask, brp_buf* LinkLocalGateway, brp_buf* DNSAdr, brp_buf* HostAdr, unsigned* HostPort, unsigned* AutocloseTimeout, brp_mempool *mempool);
#else
brp_errcode brp_Eth_GetNetworkStatus(brp_Eth_GetNetworkStatus_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Port;
	unsigned** MIBCounterList;
	size_t* MIBCounterList_len;
	brp_mempool *mempool;
} brp_Eth_GetMIBCounters_t;
/**
 * Retrieve current MIB counters.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Port** (in) 0: device port, 1: network port
 *   - **MIBCounterList** (out) 
 *   - **MIBCounterList_len** (out) Number of elements in **MIBCounterList**.
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Eth_GetMIBCounters(brp_protocol protocol, unsigned _input_Port, unsigned** MIBCounterList, size_t* MIBCounterList_len, brp_mempool *mempool);
#else
brp_errcode brp_Eth_GetMIBCounters(brp_Eth_GetMIBCounters_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_Eth_GetTcpConnectionStatus_Status* Status;
} brp_Eth_GetTcpConnectionStatus_t;
/**
 * Retrieve the BRP over TCP connection status. Checks if there is an open TCP connection.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Status** (out) BRP over TCP connection status.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Eth_GetTcpConnectionStatus(brp_protocol protocol, brp_Eth_GetTcpConnectionStatus_Status* Status);
#else
brp_errcode brp_Eth_GetTcpConnectionStatus(brp_Eth_GetTcpConnectionStatus_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_Eth_OpenTcpConnection_ConnectionReason ConnectionReason;
} brp_Eth_OpenTcpConnection_t;
/**
 * Open a BRP over TCP connection to the configured host.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ConnectionReason** (in) Connection reason bit mask that is sent to the host as soon as a connection is established.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Eth_OpenTcpConnection(brp_protocol protocol, brp_Eth_OpenTcpConnection_ConnectionReason _input_ConnectionReason);
#else
brp_errcode brp_Eth_OpenTcpConnection(brp_Eth_OpenTcpConnection_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_Eth_CloseTcpConnection_t;
/**
 * Close the BRP over TCP connection.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Eth_CloseTcpConnection(brp_protocol protocol);
#else
brp_errcode brp_Eth_CloseTcpConnection(brp_Eth_CloseTcpConnection_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
#endif
/**
 * @}
 */