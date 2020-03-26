#include "common.h"
#include <cerrno>
#include "thread.h"
#include "base64.h"
#include "socket.h"
#include "packet.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#if defined __linux__ || defined __CYGWIN__
#include <unistd.h>
#endif
#include "map.h"

void base64_test();
void safe_base64_test();
void random_s_test();
void uuid_test();
void map_test();
void socket_server_test();
void socket_client_test();
void new_thread_test();
void listened(int *fd);
void block();
void recv_data(int *fd);

int listen_flag = 0;

int
main()
{
	uuid_test();
	random_s_test();
	base64_test();
	safe_base64_test();
	map_test();
//	new_thread_test();
	socket_server_test();
	socket_client_test();
	block();
	return 0;
}

void 
random_s_test()
{
	printf("\nrandom_s test: \n");
	int ret_err = 0;
	int ret = random_s(-200, -100, &ret_err);
	printf("random_s: %d\n", ret);
	printf("\n");
}

void
uuid_test()
{
	printf("\nUUID genration test: \n");
	char *uuid_str = (char *)malloc(37);
	memset(uuid_str, 0, 37);
	uuid(uuid_str);
	printf("UUID: %s\n\n", uuid_str);
	free(uuid_str);
}

void
base64_test()
{
	/********************* encode ************************/
	printf("\nbase64 encode test: \n");

	//Set text.
	const char *base64_in = "This is a test message.";

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
	const char *base64_in = "This is a test messages.";

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

void 
map_test()
{
	printf("\nMap test begin: \n");
	EdtpMap map = {NULL, 0};
	map_insert(&map, "key1", "value1", -1);
	map_insert(&map, "key2", "value2", -1);
	map_insert(&map, "key3", "value3", -1);
	lestring value1 = map_value(&map, "key1");
	lestring value2 = map_value(&map, "key2");
	lestring value3 = map_value(&map, "key3");
	printf("value: %s, value len: %d\n", value1.str, value1.size);
	printf("value: %s, value len: %d\n", value2.str, value2.size);
	printf("value: %s, value len: %d\n", value3.str, value3.size);
	map_set(&map, "key1", "reset_value1", -1);
	value1 = map_value(&map, "key1");
	printf("value: %s, value len: %d\n", value1.str, value1.size);
	lestring test = map_value(&map, "none");
	if (test.str == NULL)
		printf("if none exist map_value will return empty lestring.\n");
	map_erase(&map, "key2");
	test = map_value(&map, "key2");
	if (test.str == NULL) {
		printf("key2: %s, value: %s\n", "NULL", "NULL");
	} else {
		printf("erase error! \n");
	}

	map_insert(&map, "key2", "value2", -1);
	map_insert(&map, "key4", "value4", -1);
	MapElement *begin = map_begin(&map);
	MapElement *end = map_end(&map);
	printf("\n");
	printf("The first value of map: %s\n", begin->value);
	printf("The last value of map: %s\n", end->value);
	printf("\nprint whole map value: \n");
	for (MapElement *i = map_begin(&map); i != NULL; i = map_next(i)) {
		printf("%s\n", i->value);
	}

	return ;
}

void 
socket_server_test()
{
	printf("\n\nSocket server test begin: ");
	
	/* The first examples. */
	printf("\nThe first examples of socket server: \n");
	int fd = listen(25678, (void *)listened, 256);
	if (fd == -1) {
		printf("Sock test error! listen failed! \n");
		return;
	}
	/***********************/
	
	

	/* The second examples. 
	 This method will block the main thread! 
	printf("\nThe second examples of socket server: \n");
	sockaddr_in saddr_in;
	int fd2 = listen(25679, NULL, 256);
	if (fd == -1) {
		printf("Sock test error! listen failed! \n");
		return;
	}

	accept(fd, &saddr_in, (void *)recv_data);
	***********************/
}

void 
listened(int *fd)
{
	sockaddr_in saddr_in;
	listen_flag = 1;
	int fd_con = accept(*fd, &saddr_in, (void *)recv_data);
	if (fd_con == -1) {
		listen_flag = 0;
		printf("Thread: Socket test error! accept failed! \n");
	} else {
		printf("Thread: Accept successfully! \n");
	}
}

void
recv_data(int *fd)
{
	printf("Function recv data.\n");
	char *buf = (char *)malloc(25);

	int ret = 0;
	while (ret < 11) {
		ret = ret + recv(*fd, buf + ret, 11, 0);
	}

	printf("recv: %s\n", buf);
	free(buf);
}

void 
socket_client_test()
{
	while (!listen_flag) sleep(1);
	sleep(1);
	printf("Socket client test begin: \n");
	int sfd = connect("127.0.0.1", 25678);
	if (sfd == -1) {
		printf("connect failed!\n");
	} else {
		printf("connect succeeds!\n");
	}
	int ret = send(sfd, "123456789\n", 11, 0);
	close(sfd);

}

void 
thread1()
{
	for(int i = 0; i < 300; i++)
		printf("%d  ", i);
}

void 
new_thread_test()
{
	new_thread((void *)thread1, NULL, 0);
	new_thread((void *)thread1, NULL, 0);
}

void
block()
{
	printf("Function block");
	for (;;) sleep(1);
	return;
}
