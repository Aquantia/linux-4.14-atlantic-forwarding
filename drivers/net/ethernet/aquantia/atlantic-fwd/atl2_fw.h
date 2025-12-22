/* SPDX-License-Identifier: GPL-2.0-only */
/* Atlantic Network Driver
 *
 * Copyright (C) 2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _ATL2_FW_H_
#define _ATL2_FW_H_

/* CHECKPATCH FALSE POSITIVE: CamelCase names in this file are firmware
 * interface definitions that must match the hardware specification.
 */

/* Start of HW byte packed interface declaration */
#pragma pack(push, 1)

/* F W    A P I */

struct link_options_s {
	u32 link_up:1;
	u32 link_renegotiate:1;
	u32 minimal_link_speed:1;
	u32 internal_loopback:1;
	u32 external_loopback:1;
	u32 rate_10M_hd:1;
	u32 rate_100M_hd:1;
	u32 rate_1G_hd:1;

	u32 rate_10M:1;
	u32 rate_100M:1;
	u32 rate_1G:1;
	u32 rate_2P5G:1;
	u32 rate_N2P5G:1;
	u32 rate_5G:1;
	u32 rate_N5G:1;
	u32 rate_10G:1;

	u32 eee_100M:1;
	u32 eee_1G:1;
	u32 eee_2P5G:1;
	u32 eee_5G:1;
	u32 eee_10G:1;
	u32 rsvd3:2;
	u32 low_power_autoneg:1;

	u32 pause_rx:1;
	u32 pause_tx:1;
	u32 rsvd4:1;
	u32 downshift:1;
	u32 downshift_retry:4;
};

struct link_control_s {
	u32 mode:4;

	u32 disable_crc_corruption : 1;
	u32 discard_short_frames : 1;
	u32 flow_control_mode : 1;
	u32 disable_length_check : 1;
	u32 discard_errored_frames : 1;
	u32 control_frame_enable : 1;
	u32 enable_tx_padding : 1;
	u32 enable_crc_forwarding : 1;
	u32 enable_frame_padding_removal_rx: 1;
	u32 promiscuous_mode: 1;
	u32 rsvd:18;
};

struct thermal_shutdown_s {
	u32 shutdown_enable :1;
	u32 warning_enable :1;
	u32 rsvd:6;

	u32 shutdown_temp_threshold :8;
	u32 warning_cold_temp_threshold :8;
	u32 warning_hot_temp_threshold :8;
};

struct mac_address_s {
	u8 mac_address[6];
};

struct mac_address_aligned_s {
	struct mac_address_s aligned;
	u16 rsvd;
};

struct sleep_proxy_s {
	struct wake_on_lan_s {
		u32 wake_on_magic_packet:1;
		u32 wake_on_pattern:1;
		u32 wake_on_link_up:1;
		u32 wake_on_link_down:1;
		u32 wake_on_ping:1;
		u32 wake_on_timer:1;
		u32 wake_on_link_mac_method:1;
		u32 rsrvd1:1;
		u32 restore_link_before_wake:1;
		u32 rsvd:23;

		u32 link_up_timeout;
		u32 link_down_timeout;
		u32 timer;

		struct {
			u32 mask[4];
			u32 crc32;
		} wake_up_patterns[8];
	} wake_on_lan;

	struct {
		u32 arp_responder:1;
		u32 echo_responder:1;
		u32 igmp_client:1;
		u32 echo_truncate:1;
		u32 address_guard:1;
		u32 ignore_fragmented:1;
		u32 rsvd:2;
		u32 echo_max_len:16;
		u32 ipv4[8];
		u32 reserved[8];

	} ipv4_offload;

	struct {
		u32 ns_responder:1;
		u32 echo_responder:1;
		u32 mld_client:1;
		u32 echo_truncate:1;
		u32 address_guard:1;
		u32 rsvd:3;
		u32 echo_max_len:16;
		u32 ipv6[16][4];
	} ipv6_offload;

	struct {
		u16 ports[16];
	} tcp_port_offload;

	struct {
		u16 ports[16];
	} udp_port_offload;

	struct ka4_offloads_s {
		u32 retry_count;
		u32 retry_interval;

		struct ka4_offload_s {
			u32 timeout;
			u16 local_port;
			u16 remote_port;
			u8 remote_mac_addr[6];
			u32 rsvd:16;
			u32 rsvd2:32;
			u32 rsvd3:32;
			u32 rsvd4:16;
			u16 win_size;
			u32 seq_num;
			u32 ack_num;
			u32 local_ip;
			u32 remote_ip;
		} offloads[16];
	} ka4_offload;

	struct ka6_offloads_s {
		u32 retry_count;
		u32 retry_interval;

		struct ka6_offload_s {
			u32 timeout;
			u16 local_port;
			u16 remote_port;
			u8 remote_mac_addr[6];
			u32 rsvd:16;
			u32 rsvd2:32;
			u32 rsvd3:32;
			u32 rsvd4:16;
			u16 win_size;
			u32 seq_num;
			u32 ack_num;
			u32 local_ip[4];
			u32 remote_ip[4];
		} offloads[16];
	} ka6_offload;

	struct {
		u32 rr_count;
		u32 rr_buf_len;
		u32 idx_offset;
		u32 rr__offset;
	} mdns;
	/* WARN: where this gap actually is not known */
	u32 reserve_fw_gap:16;
};

struct ptp_s {
	u32 enable:1;
};

struct pause_quanta_s {
	u16 quanta_10M;
	u16 threshold_10M;
	u16 quanta_100M;
	u16 threshold_100M;
	u16 quanta_1G;
	u16 threshold_1G;
	u16 quanta_2P5G;
	u16 threshold_2P5G;
	u16 quanta_5G;
	u16 threshold_5G;
	u16 quanta_10G;
	u16 threshold_10G;
};

struct data_buffer_status_s {
	u32 data_offset;
	u32 data_length;
};

struct device_caps_s {
	u32 finite_flashless: 1;
	u32 cable_diag: 1;
	u32 ncsi: 1;
	u32 avb: 1;
	u32 rsvd: 28;
	u32 rsvd2: 32;
};

struct version_s {
	struct bundle_version_t {
		u32 major:8;
		u32 minor:8;
		u32 build:16;
	} bundle;
	struct mac_version_t {
		u32 major:8;
		u32 minor:8;
		u32 build:16;
	} mac;
	struct phy_version_t {
		u32 major:8;
		u32 minor:8;
		u32 build:16;
	} phy;
	u32 drv_iface_ver:4;
	u32 rsvd:28;
};

struct link_status_s {
	u32 link_state:4;
	u32 link_rate:4;

	u32 pause_tx:1;
	u32 pause_rx:1;
	u32 eee:1;
	u32 duplex:1;
	u32 rsvd:4;

	u32 rsvd2:16;
};

struct wol_status_s {
	u32 wake_count:8;
	u32 wake_reason:8;
	u32 wake_up_packet_length :12;
	u32 wake_up_pattern_number :3;
	u32 rsvd:1;
	u32 wake_up_packet[379];
};

struct mac_health_monitor_s {
	u32 mac_ready:1;
	u32 mac_fault:1;
	u32 mac_flashless_finished:1;
	u32 rsvd:5;
	u32 mac_temperature:8;
	u32 mac_heart_beat:16;
	u32 mac_fault_code:16;
	u32 rsvd2:16;
};

struct phy_health_monitor_s {
	u32 phy_ready:1;
	u32 phy_fault:1;
	u32 phy_hot_warning:1;
	u32 rsvd:5;
	u32 phy_temperature:8;
	u32 phy_heart_beat:16;
	u32 phy_fault_code:16;
	u32 rsvd2:16;
};

struct device_link_caps_s {
	u32 rsvd:3;
	u32 internal_loopback:1;
	u32 external_loopback:1;
	u32 rate_10M_hd:1;
	u32 rate_100M_hd:1;
	u32 rate_1G_hd:1;

	u32 rate_10M:1;
	u32 rate_100M:1;
	u32 rate_1G:1;
	u32 rate_2P5G:1;
	u32 rate_N2P5G:1;
	u32 rate_5G:1;
	u32 rate_N5G:1;
	u32 rate_10G:1;

	u32 rsvd3:1;
	u32 eee_100M:1;
	u32 eee_1G:1;
	u32 eee_2P5G:1;
	u32 rsvd4:1;
	u32 eee_5G:1;
	u32 rsvd5:1;
	u32 eee_10G:1;

	u32 pause_rx:1;
	u32 pause_tx:1;
	u32 pfc:1;
	u32 downshift:1;
	u32 downshift_retry:4;
};

struct sleep_proxy_caps_s {
	u32 ipv4_offload:1;
	u32 ipv6_offload:1;
	u32 tcp_port_offload:1;
	u32 udp_port_offload:1;
	u32 ka4_offload:1;
	u32 ka6_offload:1;
	u32 mdns_offload:1;
	u32 wake_on_ping:1;

	u32 wake_on_magic_packet:1;
	u32 wake_on_pattern:1;
	u32 wake_on_timer:1;
	u32 wake_on_link:1;
	u32 wake_patterns_count:4;

	u32 ipv4_count:8;
	u32 ipv6_count:8;

	u32 tcp_port_offload_count:8;
	u32 udp_port_offload_count:8;

	u32 tcp4_ka_count:8;
	u32 tcp6_ka_count:8;

	u32 igmp_offload:1;
	u32 mld_offload:1;
	u32 rsvd:30;
};

struct lkp_link_caps_s {
	u32 rsvd:5;
	u32 rate_10M_hd:1;
	u32 rate_100M_hd:1;
	u32 rate_1G_hd:1;

	u32 rate_10M:1;
	u32 rate_100M:1;
	u32 rate_1G:1;
	u32 rate_2P5G:1;
	u32 rate_N2P5G:1;
	u32 rate_5G:1;
	u32 rate_N5G:1;
	u32 rate_10G:1;

	u32 rsvd2:1;
	u32 eee_100M:1;
	u32 eee_1G:1;
	u32 eee_2P5G:1;
	u32 rsvd3:1;
	u32 eee_5G:1;
	u32 rsvd4:1;
	u32 eee_10G:1;

	u32 pause_rx:1;
	u32 pause_tx:1;
	u32 rsvd5:6;
};

struct core_dump_s {
	u32 reg0;
	u32 reg1;
	u32 reg2;

	u32 hi;
	u32 lo;

	u32 regs[32];
};

struct trace_s {
	u32 sync_counter;
	u32 mem_buffer[0x1ff];
};

struct cable_diag_control_s {
	u32 toggle :1;
	u32 rsvd:7;
	u32 wait_timeout_sec:8;
	u32 rsvd2:16;

};

struct cable_diag_lane_data_s {
	u32 result_code :8;
	u32 dist :8;
	u32 far_dist :8;
	u32 rsvd:8;
};

struct cable_diag_status_s {
	struct cable_diag_lane_data_s lane_data[4];
	u32 transact_id:8;
	u32 status:4;
	u32 rsvd:20;
};

struct phy_fw_load_status_s {
	u32 phy_fw_load_from_host :1;
	u32 phy_fw_load_from_flash :1;
	u32 phy_fw_load_from_d_c :1;
	u32 phy_load_from_flash_failed :1;
	u32 phy_load_from_host_failed :1;
	u32 phy_load_from_d_c_failed :1;
	u32 phy_hash_validation_failed :1;
	u32 phy_fw_started :1;

	u32 phy_stall_timeout :1;
	u32 phy_unstall_timeout :1;
	u32 phy_fw_start_timeout :1;
	u32 phy_iram_load_error :1;
	u32 phy_dram_load_error :1;
	u32 phy_mcp_run_failed :1;
	u32 phy_mcp_stall_failed :1;
	u32 phy_mcp_unstall_failed :1;

	u32 phy_wait_for_semaphore :1;
	u32 phy_semaphore_locked :1;
	u32 rsvd :2;
	u32 phy_worst_block_upload_retry_number:4;

	u32 phy_worst_upload_block_number :6;
	u32 rsvd2:2;
};

struct statistics_a0_s {
	struct {
		u32 link_up;
		u32 link_down;
	} link;

	struct {
		u64 tx_unicast_octets;
		u64 tx_multicast_octets;
		u64 tx_broadcast_octets;
		u64 rx_unicast_octets;
		u64 rx_multicast_octets;
		u64 rx_broadcast_octets;

		u32 tx_unicast_frames;
		u32 tx_multicast_frames;
		u32 tx_broadcast_frames;
		u32 tx_errors;

		u32 rx_unicast_frames;
		u32 rx_multicast_frames;
		u32 rx_broadcast_frames;
		u32 rx_dropped_frames;
		u32 rx_error_frames;

		u32 tx_good_frames;
		u32 rx_good_frames;
		u32 reserve_fw_gap;
	} msm;
	u32 main_loop_cycles;
	u32 reserve_fw_gap;
};

struct statistics_b0_s {
	u64 rx_good_octets;
	u64 rx_pause_frames;
	u64 rx_good_frames;
	u64 rx_errors;
	u64 rx_unicast_frames;
	u64 rx_multicast_frames;
	u64 rx_broadcast_frames;

	u64 tx_good_octets;
	u64 tx_pause_frames;
	u64 tx_good_frames;
	u64 tx_errors;
	u64 tx_unicast_frames;
	u64 tx_multicast_frames;
	u64 tx_broadcast_frames;

	u32 main_loop_cycles;
};

struct statistics_s {
	union {
		struct statistics_a0_s a0;
		struct statistics_b0_s b0;
	};
};

struct filter_caps_s {
	u8 l2_filters_base_index:6;
	u8 flexible_filter_mask:2;
	u8 l2_filter_count;
	u8 ethertype_filter_base_index;
	u8 ethertype_filter_count;

	u8 vlan_filter_base_index;
	u8 vlan_filter_count;
	u8 l3_ip4_filter_base_index:4;
	u8 l3_ip4_filter_count:4;
	u8 l3_ip6_filter_base_index:4;
	u8 l3_ip6_filter_count:4;

	u8 l4_filter_base_index:4;
	u8 l4_filter_count:4;
	u8 l4_flex_filter_base_index:4;
	u8 l4_flex_filter_count:4;
	u8 rslv_tbl_base_index;
	u8 rslv_tbl_count;
};

struct request_policy_s {
	struct {
		u8 all:1;
		u8 rsvd:1;
		u8 rx_queue_tc_index:5;
		u8 queue_or_tc:1;
	} promisc;

	struct {
		u8 accept:1;
		u8 rsvd:1;
		u8 rx_queue_tc_index:5;
		u8 queue_or_tc:1;
	} bcast;

	struct {
		u8 accept:1;
		u8 promisc:1;
		u8 rx_queue_tc_index:5;
		u8 queue_or_tc:1;
	} mcast;

	u8 rsvd:8;
};

struct fw_interface_in {
	u32 mtu;
	u32 rsvd1:32;
	struct mac_address_aligned_s mac_address;
	struct link_control_s link_control;
	u32 rsvd2:32;
	struct link_options_s link_options;
	u32 rsvd3:32;
	struct thermal_shutdown_s thermal_shutdown;
	u32 rsvd4:32;
	struct sleep_proxy_s sleep_proxy;
	u32 rsvd5:32;
	struct pause_quanta_s pause_quanta[8];
	struct cable_diag_control_s cable_diag_control;
	u32 rsvd6:32;
	struct data_buffer_status_s data_buffer_status;
	u32 rsvd7:32;
	struct request_policy_s request_policy;
};

struct transaction_counter_s {
	u32 transaction_cnt_a:16;
	u32 transaction_cnt_b:16;
};

struct management_status_s {
	struct mac_address_s mac_address;
	u16 vlan;

	struct{
		u32 enable : 1;
		u32 rsvd:31;
	} flags;

	u32 rsvd1:32;
	u32 rsvd2:32;
	u32 rsvd3:32;
	u32 rsvd4:32;
	u32 rsvd5:32;
};

struct fw_interface_out {
	struct transaction_counter_s transaction_id;
	struct version_s version;
	struct link_status_s link_status;
	struct wol_status_s wol_status;
	u32 rsvd:32;
	u32 rsvd2:32;
	struct mac_health_monitor_s mac_health_monitor;
	u32 rsvd3:32;
	u32 rsvd4:32;
	struct phy_health_monitor_s phy_health_monitor;
	u32 rsvd5:32;
	u32 rsvd6:32;
	struct cable_diag_status_s cable_diag_status;
	u32 rsvd7:32;
	struct device_link_caps_s device_link_caps;
	u32 rsvd8:32;
	struct sleep_proxy_caps_s sleep_proxy_caps;
	u32 rsvd9:32;
	struct lkp_link_caps_s lkp_link_caps;
	u32 rsvd10:32;
	struct core_dump_s core_dump;
	u32 rsvd11:32;
	struct statistics_s stats;
	struct filter_caps_s filter_caps;
	struct device_caps_s device_caps;
	u32 rsvd13:32;
	struct management_status_s management_status;
	u32 reserve[21];
	struct trace_s trace;
};

struct fw_iti_subblock_header {
	u32 type :8;
	u32 length :24;
};

struct fw_iti_hdr {
	u32 instuction_bitmask;
	u32 reserved;
	struct fw_iti_subblock_header iti[6];
};

/* End of HW byte packed interface declaration */
#pragma pack(pop)

#define ATL2_FW_LINK_RATE_INVALID 0
#define ATL2_FW_LINK_RATE_10M     1
#define ATL2_FW_LINK_RATE_100M    2
#define ATL2_FW_LINK_RATE_1G      3
#define ATL2_FW_LINK_RATE_2G5     4
#define ATL2_FW_LINK_RATE_5G      5
#define ATL2_FW_LINK_RATE_10G     6

#define ATL2_HOST_MODE_INVALID      0
#define ATL2_HOST_MODE_ACTIVE       1
#define ATL2_HOST_MODE_SLEEP_PROXY  2
#define ATL2_HOST_MODE_LOW_POWER    3
#define ATL2_HOST_MODE_SHUTDOWN     4

#define ATL2_FW_INTERFACE_A0     0
#define ATL2_FW_INTERFACE_B0     1

#define ATL2_FW_CABLE_STATUS_OPEN_CIRCUIT  7
#define ATL2_FW_CABLE_STATUS_HIGH_MISMATCH 6
#define ATL2_FW_CABLE_STATUS_LOW_MISMATCH  5
#define ATL2_FW_CABLE_STATUS_SHORT_CIRCUIT 4
#define ATL2_FW_CABLE_STATUS_PAIR_D        3
#define ATL2_FW_CABLE_STATUS_PAIR_C        2
#define ATL2_FW_CABLE_STATUS_PAIR_B        1
#define ATL2_FW_CABLE_STATUS_OK            0

#define ATL2_FW_HOST_INTERRUPT_MAC_READY           0x0004
#define ATL2_FW_HOST_INTERRUPT_DATA_HANDLED        0x0100
#define ATL2_FW_HOST_INTERRUPT_LINK_UP             0x0200
#define ATL2_FW_HOST_INTERRUPT_LINK_DOWN           0x0400
#define ATL2_FW_HOST_INTERRUPT_PHY_FAULT           0x0800
#define ATL2_FW_HOST_INTERRUPT_MAC_FAULT           0x1000
#define ATL2_FW_HOST_INTERRUPT_TEMPERATURE_WARNING 0x2000
#define ATL2_FW_HOST_INTERRUPT_HEARTBEAT           0x4000

#define ATL2_ITI_ADDRESS_START    0x100000
#define ATL2_ITI_ADDRESS_BLOCK_1  (ATL2_ITI_ADDRESS_START +\
				   sizeof(struct fw_iti_hdr) / sizeof(u32))
enum {
	ATL2_MEMORY_MAILBOX_STATUS_FAIL = 0,
	ATL2_MEMORY_MAILBOX_STATUS_SUCCESS = 1
};

enum {
	ATL2_MEMORY_MAILBOX_TARGET_MEMORY = 0,
	ATL2_MEMORY_MAILBOX_TARGET_MDIO = 1
};

enum {
	ATL2_MEMORY_MAILBOX_OPERATION_READ = 0,
	ATL2_MEMORY_MAILBOX_OPERATION_WRITE = 1
};

enum ATL2_WAKE_REASON {
	ATL2_WAKE_REASON_UNKNOWN,
	ATL2_WAKE_REASON_PANIC,
	ATL2_WAKE_REASON_LINK,
	ATL2_WAKE_REASON_TIMER,
	ATL2_WAKE_REASON_RESERVED,
	ATL2_WAKE_REASON_NAME_GUARD,
	ATL2_WAKE_REASON_ADDR_GUARD,
	ATL2_WAKE_REASON_TCPKA,

	ATL2_WAKE_REASON_DATA_FLAG,

	ATL2_WAKE_REASON_PING,
	ATL2_WAKE_REASON_SYN,
	ATL2_WAKE_REASON_UDP,
	ATL2_WAKE_REASON_PATTERN,
	ATL2_WAKE_REASON_MAGIC_PACKET
};

int atl2_fw_init(struct atl_hw *hw);
int atl2_fw_set_filter_policy(struct atl_hw *hw, bool promisc, bool allmulti);

#endif
