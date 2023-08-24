#include <stdio.h>
#include <rte_launch.h>
#include <rte_eal.h>
#include <rte_per_lcore.h>
#include <rte_lcore.h>
#include <rte_debug.h>


static int lcorehello(__attribute__((unused)) void *arg)
//static int lcorehello(void *arg)
{
	//unsigned int *lcoreid = (unsigned int *)arg; /* this line causes segfault */
	unsigned int l_lcoreid = rte_lcore_id();
	printf("Hello from lcore, id: %u\n", l_lcoreid);
	return 0;
}

int main(int argc, char **argv)
{
	int ret = rte_eal_init(argc, argv);
	if (ret < 0)
	{
		printf("rte_eal_init: failed\n");
		return 1;
	}
	unsigned int lcoreid;
	RTE_LCORE_FOREACH_WORKER(lcoreid)
	{
		rte_eal_remote_launch(lcorehello, NULL, lcoreid);	
	}
	lcorehello(NULL);
	/* >8 End of launching the function on each lcore. */

	rte_eal_mp_wait_lcore();

	/* clean up the EAL */
//	rte_eal_cleanup();
	return 0;
}
