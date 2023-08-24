#include <stdio.h>
#include <rte_eal.h>

int main(int argc, char **argv)
{
	int ret = rte_eal_init(argc, argv);
	if (ret < 0)
	{
		printf("rte_eal_init: failed\n");
		return 1;
	}
	printf("Hello World !\n");
	return 0;
}
