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

void
base64_test()
{
	/********************* encode ************************/
	printf("\nbase64 encode test: \n");

	//Set text.
	char *base64_in = "This is a test message.";

	//Calculated input and output size. 
	size_t in_size = strlen(base64_in);
	size_t out_size = base64_sizeof(in_size);
	
	//Initialize memory. 
	char *out = (char *)malloc(out_size + 1);
	memset(out, 0, out_size + 1);

	//Encode.
	out_size = base64_encode((const u_char*)base64_in, in_size, out);

	//Print information. 
	printf("in_size: %d\n", in_size);
	printf("out_size: %d\n", out_size);
	printf("text: %s\n", base64_in);
	printf("encode: %s\n", out);
	printf("bytes: ");
	for (int i = 0; i < out_size; i++) {
		printf("%d ", out[i]);
	}
	printf("\n\n");

	/********************* decode ************************/
	printf("base64 decode test: \n");

	//Calculated input and output size. 
	in_size = strlen(out);
	out_size = in_size / 4 * 3;

	//Initialize memory. 
	char *text = (char *)malloc(out_size + 1);
	memset(text, 0, out_size + 1);

	//Decode. 
	out_size = base64_decode((const u_char*)out, in_size, text);

	//Print information.
	printf("in_size: %d\n", in_size);
	printf("out_size: %d\n", out_size);
	printf("ciphertext: %s\n", out);
	printf("decode: %s\n", text);
	printf("bytes: ");
	for (int i = 0; i < out_size; i++) {
		printf("%d ", text[i]);
	}
	printf("\n\n");

	//free
	free(out);
	free(text);
	return;
}

void
safe_base64_test()
{
	/********************* encode ************************/
	printf("\nbase64 safe encode test: \n");

	//Set text.
	char *base64_in = "This is a test messages.";

	//Calculated input and output size. 
	size_t in_size = strlen(base64_in);
	size_t out_size = in_size % 3 == 0 ? in_size / 3 * 4 : (in_size / 3 + 1) * 4;

	//Initialize memory. 
	char *out = (char *)malloc(out_size + 1);
	memset(out, 0, out_size + 1);

	//Encode.
	out_size = base64_safe_encode((const u_char*)base64_in, in_size, out);

	//Print Infomation.
	printf("in_size: %d\n", in_size);
	printf("out_size: %d\n", out_size);
	printf("test: %s\n", base64_in);
	printf("safe encode: %s\n", out);
	printf("bytes: ");
	for (int i = 0; i < out_size; i++) {
		printf("%d ", out[i]);
	}
	printf("\n\n");

	/********************* decode ************************/
	printf("safe base64 decode test: \n");

	//Calculated input and output size. 
	in_size = strlen(out);
	out_size = in_size / 4 * 3;

	//Initialize memory. 
	char *text = (char *)malloc(out_size + 1);
	memset(text, 0, out_size + 1);

	//Decode. 
	out_size = base64_decode((const u_char*)out, in_size, text);

	//Print information.
	printf("in_size: %d\n", in_size);
	printf("out_size: %d\n", out_size);
	printf("ciphertext: %s\n", out);
	printf("safe decode: %s\n", text);
	printf("bytes: ");
	for (int i = 0; i < out_size; i++) {
		printf("%d ", text[i]);
	}
	printf("\n\n");

	//free
	free(out);
	free(text);
	return;
}
