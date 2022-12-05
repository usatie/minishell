#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	printf("%d\n", access("/bin/cat", X_OK));
	printf("%d\n", access("/bin//cat", X_OK));
	printf("%d\n", access("/bin////////cat", X_OK));
	printf("%d\n", access("/bin/catt", X_OK));
	printf("%d\n", access("/bin//catt", X_OK));
}
