#include <common.h>
#include <base64.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

int
main()
{
	char *out = (char *)malloc(sizeof(char) * 8);
	memset(out, 0, sizeof(char) * 8);
	size_t outSize = base64_encode((const u_char*)"test", 5, out);
	printf("outSize: %d\n", outSize);
	printf("encode: %s\n", out);
	for (int i = 0; i < 8; i++) {
		printf("%d ", out[i]);
	}
	return 0;
}
