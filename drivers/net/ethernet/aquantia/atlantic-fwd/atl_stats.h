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

#ifndef _ATL_STATS_H_
#define _ATL_STATS_H_

#include <linux/types.h>

struct atl_rx_ring_stats {
	u64 packets;
	u64 bytes;
	u64 linear_dropped;
	u64 alloc_skb_failed;
	u64 reused_head_page;
	u64 reused_data_page;
	u64 alloc_head_page;
	u64 alloc_data_page;
	u64 alloc_head_page_failed;
	u64 alloc_data_page_failed;
	u64 non_eop_descs;
	u64 mac_err;
	u64 csum_err;
	u64 multicast;
};

struct atl_rx_fwd_ring_stats {
	u64 packets;
	u64 bytes;
};

struct atl_tx_ring_stats {
	u64 packets;
	u64 bytes;
	u64 tx_busy;       /* number of times ring was full and tx failed */
	u64 tx_restart;
	u64 dma_map_failed;
};

struct atl_ring_stats {
	union {
		struct_group(rxtx,
				struct atl_rx_ring_stats rx;
				struct atl_tx_ring_stats tx;
		);
	};
};

struct atl_ether_stats {
	u64 tx_pause;
	u64 tx_ether_pkts;
	u64 tx_ether_octets;
	u64 tx_errors; /* from MSM block */
	u64 rx_pause;
	u64 rx_ether_octets;
	u64 rx_ether_pkts;
	u64 rx_ether_broacasts;
	u64 rx_ether_multicasts;
	u64 rx_ether_crc_align_errs;
	u64 rx_filter_host;
	u64 rx_filter_lost;
	u64 rx_errors; /* from MSM block */
	u64 rx_drops;  /* from MSM block */
	u64 rx_dma_packets;
	u64 rx_dma_octets;
	u64 rx_dma_drops;   /* DMA level RX drops */
	u64 tx_dma_packets;
	u64 tx_dma_octets;
};

struct atl_global_stats {
	struct atl_rx_ring_stats rx;
	struct atl_tx_ring_stats tx;
	struct atl_rx_fwd_ring_stats rx_fwd;

	/* MSM counters can't be reset without full HW reset, so
	 * store them in relative form:
	 * eth[i] == HW_counter - eth_base[i]
	 */
	struct atl_ether_stats eth;
	struct atl_ether_stats eth_base;
};

struct atl_fwd_ring;

#if IS_ENABLED(CONFIG_ATLFWD_FWD_NETLINK)
void atl_fwd_get_ring_stats(struct atl_fwd_ring *ring,
			    struct atl_ring_stats *stats);
#endif

#endif /* _ATL_STATS_H_ */
