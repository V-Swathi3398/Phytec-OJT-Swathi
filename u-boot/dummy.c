#include<common.h>
#include<command.h>
static int do_dummy(cmd_tbl_t *cmdtp, int flag, int argc,
char * const argv[])
{
	printf("Hello Rugged Board A5d2x\n");
	printf("This is dummy command implementation\n");
	return 0;
}

U_BOOT_CMD(dummy, 2, 1, do_dummy, "testing hello","arg1 not needed");
