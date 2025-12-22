/* SPDX-License-Identifier: GPL-2.0-only */
/* Atlantic Network Driver
 *
 * Copyright (C) 2017 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _ATL_DRVIFACE_H_
#define _ATL_DRVIFACE_H_

/* These structures define the driver interface for Atlantic network hardware */

typedef u16 in_port_t;
typedef u32 in_addr_t;

struct offload_ka_v4 {
	u32 timeout;
	in_port_t local_port;
	in_port_t remote_port;
	u8 remote_mac_addr[6];
	u16 win_size;
	u32 seq_num;
	u32 ack_num;
	in_addr_t local_ip;
	in_addr_t remote_ip;
} __packed;

struct offload_ka_v6 {
	u32 timeout;
	in_port_t local_port;
	in_port_t remote_port;
	u8 remote_mac_addr[6];
	u16 win_size;
	u32 seq_num;
	u32 ack_num;
	struct in6_addr local_ip;
	struct in6_addr remote_ip;
} __packed;

struct offload_ip_info {
	u8 v4_local_addr_count;
	u8 v4_addr_count;
	u8 v6_local_addr_count;
	u8 v6_addr_count;
	u32 v4_addr_offt;
	// u8 *
	u32 v4_prefix_offt;
	// in6_addr *
	u32 v6_addr_offt;
	// u8 *
	u32 v6_prefix_offt;
} __packed;

struct offload_port_info {
	u16 udp_port_count;
	u16 tcp_port_count;
	// in_port_t *
	// See the comment in the offload_ip_info struct
	u32 udp_port_offt;
	// in_port_t *
	u32 tcp_port_offt;
} __packed;

struct offload_ka_info {
	u16 v4_ka_count;
	u16 v6_ka_count;
	u32 retry_count;
	u32 retry_interval;
	// struct offload_ka_v4 *
	// See the comment in the offload_ip_info struct
	u32 v4_ka_offt;
	// struct offload_ka_v6 *
	u32 v6_ka_offt;
} __packed;

struct offload_rr_info {
	u32 rr_count;
	u32 rr_buf_len;
	u32 rr_idx_offt;
	u32 rr_buf_offt;
};

struct offload_info {
	u32 version;               // = 0 till it stabilizes some
	u32 len;                   // The whole structure length including the variable-size buf
	u8 mac_addr[8];
	struct offload_ip_info ips;
	struct offload_port_info ports;
	struct offload_ka_info kas;
	struct offload_rr_info rrs;
	u8 buf[];
} __packed;

#define FW_PACK_STRUCT __packed

#define DRV_REQUEST_SIZE 3072
#define DRV_MSG_PING            0x01
#define DRV_MSG_ARP             0x02
#define DRV_MSG_INJECT          0x03
#define DRV_MSG_WOL_ADD         0x04
#define DRV_MSG_WOL_REMOVE      0x05
#define DRV_MSG_ENABLE_WAKEUP   0x06
#define DRV_MSG_MSM             0x07
#define DRV_MSG_PROVISIONING    0x08
#define DRV_MSG_OFFLOAD_ADD     0x09
#define DRV_MSG_OFFLOAD_REMOVE	0x0A
#define DRV_MSG_MSM_EX          0x0B
#define DRV_MSG_SMBUS_PROXY     0x0C

#define DRV_PROV_APPLY         1
#define DRV_PROV_REPLACE       2
#define DRV_PROV_ADD           3

#define FW_RPC_INJECT_PACKET_LEN 1514U

enum driver_event {
	EVENT_DRIVER_ENABLE_WOL
};

//typedef enum {
//    HOST_UNINIT = 0,
//    HOST_RESET,
//    HOST_INIT,
//    HOST_RESERVED,
//    HOST_SLEEP,
//    HOST_INVALID
//} hostState_t;

struct drv_msg_ping {
	u32 ping;
} FW_PACK_STRUCT;

union ip_addr {
	struct {
		u8 addr[16];
	} FW_PACK_STRUCT v6;
	struct {
		u8 padding[12];
		u8 addr[4];
	} FW_PACK_STRUCT v4;
} FW_PACK_STRUCT;

struct drv_msg_arp {
	u8 mac_addr[6];
	u32 u_ip_addr_cnt;
	struct {
		union ip_addr addr;
		union ip_addr mask;
	} FW_PACK_STRUCT ip[1];
} FW_PACK_STRUCT;

struct drv_msg_inject {
	u32 len;
	u8 packet[FW_RPC_INJECT_PACKET_LEN];
} FW_PACK_STRUCT;

enum ndis_pm_wol_packet {
	NDIS_PM_WOL_PACKET_UNSPECIFIED = 0,
	NDIS_PM_WOL_PACKET_BITMAP_PATTERN,
	NDIS_PM_WOL_PACKET_MAGIC_PACKET,
	NDIS_PM_WOL_PACKET_IPV4_TCP_SYN,
	NDIS_PM_WOL_PACKET_IPV6_TCP_SYN,
	NDIS_PM_WOL_PACKET_EAPOL_REQUEST_ID_MESSAGE,
	NDIS_PM_WOL_PACKET_MAXIMUM
};

enum aq_pm_wol_packet {
	AQ_PM_WOL_PACKET_UNSPECIFIED = 0x10000,
	AQ_PM_WOL_PACKET_ARP,
	AQ_PM_WOL_PACKET_IPV4_PING,
	AQ_PM_WOL_PACKET_IPV6_NS_PACKET,
	AQ_PM_WOL_PACKET_IPV6_PING,
	AQ_PM_WOL_REASON_LINK_UP,
	AQ_PM_WOL_REASON_LINK_DOWN,
	AQ_PM_WOL_PACKET_MAXIMUM
};

enum ndis_pm_protocol_offload_type {
	NDIS_PM_PROTOCOL_OFFLOAD_ID_UNSPECIFIED,
	NDIS_PM_PROTOCOL_OFFLOAD_ID_IPV4_ARP,
	NDIS_PM_PROTOCOL_OFFLOAD_ID_IPV6_NS,
	NDIS_PM_PROTOCOL_OFFLOAD_80211_RSN_REKEY,
	NDIS_PM_PROTOCOL_OFFLOAD_ID_MAXIMUM
};

struct drv_msg_enable_wakeup {
	u32 pattern_mask_windows;
	u32 pattern_mask_aquantia;
	u32 pattern_mask_other;
	u32 offloads_mask_windows;
	u32 offloads_mask_aquantia;
} FW_PACK_STRUCT;

struct drv_msg_wol_add_ipv4_tcp_syn_wol_packet_parameters {
	u32 flags;
	union {
		u8 v8[4];
		u32 v32;
	} ipv4_source_address;
	union {
		u8 v8[4];
		u32 v32;
	} ipv4_dest_address;
	union {
		u8 v8[2];
		u16 v16;
	} tcp_source_port_number;
	union {
		u8 v8[2];
		u16 v16;
	} tcp_dest_port_number;
} FW_PACK_STRUCT;

struct drv_msg_wol_add_ipv6_tcp_syn_wol_packet_parameters {
	u32 flags;
	union {
		u8 v8[16];
		u32 v32[4];
	} ipv6_source_address;
	union {
		u8 v8[16];
		u32 v32[4];
	} ipv6_dest_address;
	union {
		u8 v8[2];
		u16 v16;
	} tcp_source_port_number;
	union {
		u8 v8[2];
		u16 v16;
	} tcp_dest_port_number;
} FW_PACK_STRUCT;

struct drv_msg_wol_add_ipv4_ping_wol_packet_parameters {
	u32 flags;
	union {
		u8 v8[4];
		u32 v32;
	} ipv4_source_address;
	union {
		u8 v8[4];
		u32 v32;
	} ipv4_dest_address;
} FW_PACK_STRUCT;

struct drv_msg_wol_add_ipv6_ping_wol_packet_parameters {
	u32 flags;
	union {
		u8 v8[16];
		u32 v32[4];
	} ipv6_source_address;
	union {
		u8 v8[16];
		u32 v32[4];
	} ipv6_dest_address;
} FW_PACK_STRUCT;

struct drv_msg_wol_add_eapol_request_id_message_wol_packet_parameters {
	u32 flags;
	union {
		u8 v8[4];
		u32 v32;
	} ipv4_source_address;
	union {
		u8 v8[4];
		u32 v32;
	} ipv4_dest_address;
} FW_PACK_STRUCT;

struct drv_msg_wol_add_bitmap_pattern {
	u32 flags;
	u32 mask_offset;
	u32 mask_size;
	u32 pattern_offset;
	u32 pattern_size;
} FW_PACK_STRUCT;

struct drv_msg_wol_add_magic_packet_pattern {
	u8 mac_addr[6];
} FW_PACK_STRUCT;

struct drv_msg_wol_add_arp_wol_packet_parameters {
	u32 flags;
	union {
		u8 v8[4];
		u32 v32;
	} ipv4_address;
} FW_PACK_STRUCT;

struct drv_msg_wol_add_link_up_wol_parameters {
	u32 timeout;
} FW_PACK_STRUCT;

struct drv_msg_wol_add_link_down_wol_parameters {
	u32 timeout;
} FW_PACK_STRUCT;

struct drv_msg_wol_add {
	u32 priority; // Currently not used
	u32 packet_type; // One of ndisPmWoLPacket or aqPmWoLPacket
	u32 pattern_id; // Id to save - will be used in remove message
	u32 next_wol_pattern_offset; // For chaining multiple additions in one request

	// Depends on `parrernId`
	union _WOL_PATTERN {
		struct drv_msg_wol_add_ipv4_tcp_syn_wol_packet_parameters wol_ipv4_tcp_syn;
		struct drv_msg_wol_add_ipv6_tcp_syn_wol_packet_parameters wol_ipv6_tcp_syn;
		struct drv_msg_wol_add_eapol_request_id_message_wol_packet_parameters
			wol_eapol_request_id_message;
		struct drv_msg_wol_add_bitmap_pattern wol_bitmap;
		struct drv_msg_wol_add_magic_packet_pattern wol_magic_packet;
		struct drv_msg_wol_add_ipv4_ping_wol_packet_parameters wol_ipv4_ping;
		struct drv_msg_wol_add_ipv6_ping_wol_packet_parameters wol_ipv6_ping;
		struct drv_msg_wol_add_arp_wol_packet_parameters wol_arp;
		struct drv_msg_wol_add_link_up_wol_parameters wol_link_up_reason;
		struct drv_msg_wol_add_link_down_wol_parameters wol_link_down_reason;
	} wol_pattern;
} FW_PACK_STRUCT;

struct drv_msg_wol_remove {
	u32 id;
} FW_PACK_STRUCT;

struct ipv4_arp_parameters {
	u32 flags;
	u8 remote_ipv4_address[4];
	u8 host_ipv4_address[4];
	u8 mac_address[6];
} FW_PACK_STRUCT;

struct ipv6_ns_parameters {
	u32 flags;
	union {
		u8 v8[16];
		u32 v32[4];
	} remote_ipv6_address;
	union {
		u8 v8[16];
		u32 v32[4];
	} solicited_node_ipv6_address;
	union {
		u8 v8[16];
		u32 v32[4];
	} target_ipv6_addresses[2];
	u8 mac_address[6];
} FW_PACK_STRUCT;

struct drv_msg_offload_add {
	u32 priority;
	u32 protocol_offload_type;
	u32 protocol_offload_id;
	u32 next_protocol_offload_offset;
	union {
		struct ipv4_arp_parameters ipv4_arp;
		struct ipv6_ns_parameters ipv6_ns;
	} wol_offload;
} FW_PACK_STRUCT;

struct drv_msg_offload_remove {
	u32 id;
} FW_PACK_STRUCT;

struct drv_msm_settings {
	u32 msm_reg_054;
	u32 msm_reg_058;
	u32 msm_reg_05c;
	u32 msm_reg_060;
	u32 msm_reg_064;
	u32 msm_reg_068;
	u32 msm_reg_06c;
	u32 msm_reg_070;
	u32 flags;     // Valid for message DRV_MSG_MSM_EX only
} FW_PACK_STRUCT;

//struct drvMsgProvisioning {
//    u32 command;
//    u32 len;
//    provList_t list;
//} FW_PACK_STRUCT;

//struct drvMsgSmbusProxy {
//    u32 typeMsg;
//    union {
//        struct smbusProxyWrite smbWrite;
//        struct smbusProxyRead smbRead;
//        struct smbusProxyGetStatus smbStatus;
//        struct smbusProxyReadResp smbReadResp;
//    } FW_PACK_STRUCT;
//} FW_PACK_STRUCT;

struct drv_iface {
	u32 msg_id;

	union {
		struct drv_msg_ping msg_ping;
		struct drv_msg_arp msg_arp;
		struct drv_msg_inject msg_inject;
		struct drv_msg_wol_add msg_wol_add;
		struct drv_msg_wol_remove msg_wol_remove;
		struct drv_msg_enable_wakeup msg_enable_wakeup;
		struct drv_msm_settings msg_msm;
		//struct drvMsgProvisioning msg_provisioning;
		struct drv_msg_offload_add msg_offload_add;
		struct drv_msg_offload_remove msg_offload_remove;
		//struct drvMsgSmbusProxy msg_smbus_proxy;
		struct offload_info fw2x_offloads;
	} FW_PACK_STRUCT;
} FW_PACK_STRUCT;

#endif
