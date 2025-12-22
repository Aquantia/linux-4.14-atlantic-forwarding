/* SPDX-License-Identifier: GPL-2.0-only */
/* Atlantic Network Driver
 *
 * Copyright (C) 2017 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 * Portions Copyright (C) various contributors (see specific commit references)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _ATL_COMPAT_H_
#define _ATL_COMPAT_H_

#include <linux/version.h>

#include <linux/pci.h>
#include <linux/msi.h>
#include <linux/skbuff.h>
#include <linux/netdevice.h>

#ifndef IS_REACHABLE
#define IS_REACHABLE defined
#endif

/* Feature defines - all active for kernel 6.6 */
#define ATL_HAVE_MINMAX_MTU

/* introduced in commit 3f1ac7a700d039c61d8d8b99f28d605d489a60cf */
#define ATL_HAVE_ETHTOOL_KSETTINGS

/* introduced in commit 72bb68721f80a1441e871b6afc9ab0b3793d5031 */
#define ATL_HAVE_IPV6_NTUPLE

/* introduced in commit 892311f66f2411b813ca631009356891a0c2b0a1 */
#define ATL_HAVE_RXHASH_TYPE

/* introduced in commit 3de0b592394d17b2c41a261a6a493a521213f299 */
#define ATL_HAVE_ETHTOOL_RXHASH

static inline int skb_xmit_more(struct sk_buff *skb)
{
	return netdev_xmit_more();
}

/* NB! select_queue_fallback_t MUST be defined before #include on RHEL < 7.3 */
#include "atl_fwdnl.h"

static inline u16 atlfwd_nl_select_queue(struct net_device *dev,
					 struct sk_buff *skb,
					 struct net_device *sb_dev)
{
	return atlfwd_nl_select_queue_fallback(dev, skb, sb_dev, netdev_pick_tx);
}

#define aq_netif_napi_add(dev, napi, poll, weight) netif_napi_add(dev, napi, poll)

#endif
