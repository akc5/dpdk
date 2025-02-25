..  SPDX-License-Identifier: BSD-3-Clause
    Copyright 2018 The DPDK contributors

ABI and API Deprecation
=======================

See the guidelines document for details of the :doc:`ABI policy
<../contributing/abi_policy>`.

With DPDK 23.11, there will be a new major ABI version: 24.
This means that during the development of 23.11,
new items may be added to structs or enums,
even if those additions involve an ABI compatibility breakage.

Other API and ABI deprecation notices are to be posted below.

Deprecation Notices
-------------------

* build: Enabling deprecated libraries
  won't be possible anymore through the use of the ``disable_libs`` build option.
  A new build option for deprecated libraries will be introduced instead.

* kvargs: The function ``rte_kvargs_process`` will get a new parameter
  for returning key match count. It will ease handling of no-match case.

* cmdline: The function ``cmdline_poll`` does not work correctly on either
  Linux or Windows and is unused by any part of DPDK.
  This function is now deprecated and will be removed in DPDK 23.11.

* telemetry: The functions ``rte_tel_data_add_array_u64`` and ``rte_tel_data_add_dict_u64``,
  used by telemetry callbacks for adding unsigned integer values to be returned to the user,
  are renamed to ``rte_tel_data_add_array_uint`` and ``rte_tel_data_add_dict_uint`` respectively.
  As such, the old function names are deprecated and will be removed in a future release.

* eal: The functions ``rte_thread_setname`` and ``rte_ctrl_thread_create``
  are planned to be deprecated starting with the 23.07 release, subject to
  the replacement API rte_thread_set_name and rte_thread_create_control being
  marked as stable, and planned to be removed by the 23.11 release.

* eal: ``RTE_CPUFLAG_NUMFLAGS`` will be removed in DPDK 23.11 release.
  This is to allow new CPU features to be added without ABI breakage.

* rte_atomicNN_xxx: These APIs do not take memory order parameter. This does
  not allow for writing optimized code for all the CPU architectures supported
  in DPDK. DPDK has adopted the atomic operations from
  https://gcc.gnu.org/onlinedocs/gcc/_005f_005fatomic-Builtins.html. These
  operations must be used for patches that need to be merged in 20.08 onwards.
  This change will not introduce any performance degradation.

* rte_smp_*mb: These APIs provide full barrier functionality. However, many
  use cases do not require full barriers. To support such use cases, DPDK has
  adopted atomic operations from
  https://gcc.gnu.org/onlinedocs/gcc/_005f_005fatomic-Builtins.html. These
  operations and a new wrapper ``rte_atomic_thread_fence`` instead of
  ``__atomic_thread_fence`` must be used for patches that need to be merged in
  20.08 onwards. This change will not introduce any performance degradation.

* lib: will fix extending some enum/define breaking the ABI. There are multiple
  samples in DPDK that enum/define terminated with a ``.*MAX.*`` value which is
  used by iterators, and arrays holding these values are sized with this
  ``.*MAX.*`` value. So extending this enum/define increases the ``.*MAX.*``
  value which increases the size of the array and depending on how/where the
  array is used this may break the ABI.
  ``RTE_ETH_FLOW_MAX`` is one sample of the mentioned case, adding a new flow
  type will break the ABI because of ``flex_mask[RTE_ETH_FLOW_MAX]`` array
  usage in following public struct hierarchy:
  ``rte_eth_fdir_flex_conf -> rte_eth_fdir_conf -> rte_eth_conf (in the middle)``.
  Need to identify this kind of usages and fix in 20.11, otherwise this blocks
  us extending existing enum/define.
  One solution can be using a fixed size array instead of ``.*MAX.*`` value.

* ethdev: The flow API matching pattern structures, ``struct rte_flow_item_*``,
  should start with relevant protocol header structure from lib/net/.
  The individual protocol header fields and the protocol header struct
  may be kept together in a union as a first migration step.
  In future (target is DPDK 23.11), the protocol header fields will be cleaned
  and only protocol header struct will remain.

  These items are not compliant (not including struct from lib/net/):

  - ``rte_flow_item_ah``
  - ``rte_flow_item_e_tag``
  - ``rte_flow_item_geneve``
  - ``rte_flow_item_geneve_opt``
  - ``rte_flow_item_gre``
  - ``rte_flow_item_icmp6``
  - ``rte_flow_item_icmp6_nd_na``
  - ``rte_flow_item_icmp6_nd_ns``
  - ``rte_flow_item_icmp6_nd_opt``
  - ``rte_flow_item_icmp6_nd_opt_sla_eth``
  - ``rte_flow_item_icmp6_nd_opt_tla_eth``
  - ``rte_flow_item_igmp``
  - ``rte_flow_item_ipv6_ext``
  - ``rte_flow_item_l2tpv3oip``
  - ``rte_flow_item_mpls``
  - ``rte_flow_item_nsh``
  - ``rte_flow_item_nvgre``
  - ``rte_flow_item_pfcp``
  - ``rte_flow_item_pppoe``
  - ``rte_flow_item_pppoe_proto_id``

* ethdev: Queue specific stats fields will be removed from ``struct rte_eth_stats``.
  Mentioned fields are: ``q_ipackets``, ``q_opackets``, ``q_ibytes``, ``q_obytes``,
  ``q_errors``.
  Instead queue stats will be received via xstats API. Current method support
  will be limited to maximum 256 queues.
  Also compile time flag ``RTE_ETHDEV_QUEUE_STAT_CNTRS`` will be removed.

* ethdev: Flow actions ``PF`` and ``VF`` have been deprecated since DPDK 21.11
  and are yet to be removed. That still has not happened because there are net
  drivers which support combined use of either action ``PF`` or action ``VF``
  with action ``QUEUE``, namely, i40e, ixgbe and txgbe (L2 tunnel rule).
  It is unclear whether it is acceptable to just drop support for
  such a complex use case, so maintainers of the said drivers
  should take a closer look at this and provide assistance.

* ethdev: Actions ``OF_DEC_NW_TTL``, ``SET_IPV4_SRC``, ``SET_IPV4_DST``,
  ``SET_IPV6_SRC``, ``SET_IPV6_DST``, ``SET_TP_SRC``, ``SET_TP_DST``,
  ``DEC_TTL``, ``SET_TTL``, ``SET_MAC_SRC``, ``SET_MAC_DST``, ``INC_TCP_SEQ``,
  ``DEC_TCP_SEQ``, ``INC_TCP_ACK``, ``DEC_TCP_ACK``, ``SET_IPV4_DSCP``,
  ``SET_IPV6_DSCP``, ``SET_TAG``, ``SET_META`` are marked as legacy and
  superseded by the generic ``RTE_FLOW_ACTION_TYPE_MODIFY_FIELD``.
  The legacy actions should be removed
  once ``MODIFY_FIELD`` alternative is implemented in drivers.

* bonding: The macro ``RTE_ETH_DEV_BONDED_SLAVE`` will be
  deprecated in DPDK 23.07, and removed in DPDK 23.11.
  The relevant code can be updated using ``RTE_ETH_DEV_BONDING_MEMBER``.
  The data structure ``struct rte_eth_bond_8023ad_slave_info`` will be
  renamed to ``struct rte_eth_bond_8023ad_member_info`` in DPDK 23.11.
  The following functions will be removed in DPDK 23.11.
  The old functions:
  ``rte_eth_bond_8023ad_slave_info``,
  ``rte_eth_bond_active_slaves_get``,
  ``rte_eth_bond_slave_add``,
  ``rte_eth_bond_slave_remove``, and
  ``rte_eth_bond_slaves_get``
  will be replaced by:
  ``rte_eth_bond_8023ad_member_info``,
  ``rte_eth_bond_active_members_get``,
  ``rte_eth_bond_member_add``,
  ``rte_eth_bond_member_remove``, and
  ``rte_eth_bond_members_get``.

* cryptodev: The function ``rte_cryptodev_cb_fn`` will be updated
  to have another parameter ``qp_id`` to return the queue pair ID
  which got error interrupt to the application,
  so that application can reset that particular queue pair.

* cryptodev: The arrays of algorithm strings ``rte_crypto_cipher_algorithm_strings``,
  ``rte_crypto_auth_algorithm_strings``, ``rte_crypto_aead_algorithm_strings`` and
  ``rte_crypto_asym_xform_strings`` are deprecated and will be removed in DPDK 23.11.
  Application can use the new APIs ``rte_cryptodev_get_cipher_algo_string``,
  ``rte_cryptodev_get_auth_algo_string``, ``rte_cryptodev_get_aead_algo_string`` and
  ``rte_cryptodev_asym_get_xform_string`` respectively.

* security: Hide structures ``rte_security_ops`` and ``rte_security_ctx``
  as these are internal to DPDK library and drivers.

* security: New SA option ``ingress_oop`` would be added in structure
  ``rte_security_ipsec_sa_options`` to support out of place processing
  for inline inbound SA from DPDK 23.11. ``reserved_opts`` field in the
  same struct would be removed as discussed in techboard meeting.

* eventdev: The single-event (non-burst) enqueue and dequeue operations,
  used by static inline burst enqueue and dequeue functions in ``rte_eventdev.h``,
  will be removed in DPDK 23.11.
  This simplification includes changing the layout and potentially also
  the size of the public ``rte_event_fp_ops`` struct, breaking the ABI.
  Since these functions are not called directly by the application,
  the API remains unaffected.

* pipeline: The pipeline library legacy API (functions rte_pipeline_*)
  will be deprecated and subsequently removed in DPDK 24.11 release.
  Before this, the new pipeline library API (functions rte_swx_pipeline_*)
  will gradually transition from experimental to stable status.

* table: The table library legacy API (functions rte_table_*)
  will be deprecated and subsequently removed in DPDK 24.11 release.
  Before this, the new table library API (functions rte_swx_table_*)
  will gradually transition from experimental to stable status.

* port: The port library legacy API (functions rte_port_*)
  will be deprecated and subsequently removed in DPDK 24.11 release.
  Before this, the new port library API (functions rte_swx_port_*)
  will gradually transition from experimental to stable status.
