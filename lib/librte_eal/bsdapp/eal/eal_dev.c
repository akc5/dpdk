/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018 Intel Corporation
 */

#include <rte_log.h>
#include <rte_compat.h>
#include <rte_dev.h>

int __rte_experimental
rte_dev_event_monitor_start(void)
{
	RTE_LOG(ERR, EAL, "Device event is not supported for FreeBSD\n");
	return -1;
}

int __rte_experimental
rte_dev_event_monitor_stop(void)
{
	RTE_LOG(ERR, EAL, "Device event is not supported for FreeBSD\n");
	return -1;
}

int __rte_experimental
rte_dev_hotplug_handle_enable(void)
{
	RTE_LOG(ERR, EAL, "Device event is not supported for FreeBSD\n");
	return -1;
}

int __rte_experimental
rte_dev_hotplug_handle_disable(void)
{
	RTE_LOG(ERR, EAL, "Device event is not supported for FreeBSD\n");
	return -1;
}

void  __rte_experimental
rte_dev_event_callback_process(const char *device_name,
			       enum rte_dev_event_type event)
{
	RTE_LOG(ERR, EAL,
		"Device event callback process is not supported for FreeBSD.\n");
}
