#include <common.h>
#include <base64.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

void base64_test();
void safe_base64_test();

int
main()
{
	base64_test();
	safe_base64_test();

	return 0;
}

void base64_test()
{
	printf("\nbase64 encode test: \n");
	char *base64_in = "This is a test message.";
	size_t in_size = strlen(base64_in);
	size_t out_size = in_size % 3 == 0 ? in_size / 3 * 4 : (in_size / 3 + 1) * 4;
	char *out = (char *)malloc(sizeof(char) * out_size + 1);
	memset(out, 0, sizeof(char) * out_size + 1);
	out_size = base64_encode((const u_char*)base64_in, in_size, out);
	printf("in_size: %d\n", in_size);
	printf("out_size: %d\n", out_size);
	printf("text: %s\n", base64_in);
	printf("encode: %s\n", out);
	printf("bytes: ");
	for (int i = 0; i < out_size; i++) {
		printf("%d ", out[i]);
	}
	printf("\n\n");

	printf("base64 decode test: \n");
	in_size = strlen(out);
	out_size = in_size / 4 * 3;
	char *text = (char *)malloc(sizeof(char) * out_size + 1);
	memset(text, 0, sizeof(char) * out_size + 1);
	out_size = base64_decode((const u_char*)out, in_size, text);
	printf("in_size: %d\n", in_size);
	printf("out_size: %d\n", out_size);
	printf("ciphertext: %s\n", out);
	printf("decode: %s\n", text);
	printf("bytes: ");
	for (int i = 0; i < out_size; i++) {
		printf("%d ", text[i]);
	}
	printf("\n\n");

	free(out);
	free(text);
	return;
}

void safe_base64_test()
{
	printf("\nbase64 safe encode test: \n");
	char *base64_in = "This is a test messages.";
	size_t in_size = strlen(base64_in);
	size_t out_size = in_size % 3 == 0 ? in_size / 3 * 4 : (in_size / 3 + 1) * 4;
	char *out = (char *)malloc(sizeof(char) * out_size + 1);
	memset(out, 0, sizeof(char) * out_size + 1);
	out_size = base64_safe_encode((const u_char*)base64_in, in_size, out);
	printf("in_size: %d\n", in_size);
	printf("out_size: %d\n", out_size);
	printf("test: %s\n", base64_in);
	printf("safe encode: %s\n", out);
	printf("bytes: ");
	for (int i = 0; i < out_size; i++) {
		printf("%d ", out[i]);
	}
	printf("\n\n");

	printf("safe base64 decode test: \n");
	in_size = strlen(out);
	out_size = in_size / 4 * 3;
	char *text = (char *)malloc(sizeof(char) * out_size + 1);
	memset(text, 0, sizeof(char) * out_size + 1);
	out_size = base64_decode((const u_char*)out, in_size, text);
	printf("in_size: %d\n", in_size);
	printf("out_size: %d\n", out_size);
	printf("ciphertext: %s\n", out);
	printf("safe decode: %s\n", text);
	printf("bytes: ");
	for (int i = 0; i < out_size; i++) {
		printf("%d ", text[i]);
	}
	printf("\n\n");

	free(out);
	return;
}
