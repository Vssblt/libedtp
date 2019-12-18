#include "common.h"
#include <time.h>
#include <stdio.h>
#include <malloc.h>

uint32_t
timestamp() {
	time_t t = time(NULL);
	uint32_t ii = (uint32_t)time(&t);
	return ii;
}

int
random(int min, int max) {
	return 0;
}

int
is_little_endian() {
	union w
	{
		int a;
		char b;
	}c;
	c.a = 1;
	return (c.b == 1);
}

uint32_t
mhash(const char* str, uint32_t len) {
	uint32_t hash = 0;
	uint32_t x = 0;
	uint32_t i = 0;
	for (i = 0; i < len; str++, i++){
		hash = (hash << 4) + (*str);
		if ((x = hash & 0xF0000000L) != 0){
			hash ^= (x >> 24);
		}
		hash &= ~x;
	}
	return hash;
}

void
print_time() {
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[128];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S", timeinfo);
	printf("%s", buffer);
}

void
mt_random_mem(u_char *mem, unsigned int len) {
	/*
	auto timeNow = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch());
	std::mt19937 rdm((uint)timeNow.count());
	std::uniform_int_distribution<int> rng(0, 255);
	for ( uint32_t i = 0; i < len; i++)
	{
		mem[i] = static_cast<u_char>(rng(rdm));
	}
	*/
}

void
bin2hex(const u_char *data, uint32_t size, char *out) {
	for (uint32_t i = 0; i < size; i++){
		u_char low = (u_char)((u_char)(data[i] << 4) >> 4);
		u_char high = (u_char)(data[i] >> 4);

		if (low < 10){
			out[i * 2 + 1] = (char)(low + 0x30);
		}else{
			out[i * 2 + 1] = (char)(low - 10 + 0x41);
		}if (high < 10){
			out[i * 2] = (char)(high + 0x30);
		}else{
			out[i * 2] = (char)(high - 10 + 0x41);
		}
	}
}

void
uuid(char *_uuid) {
	int line[] = {12, 16, 20, 24,};
	u_char *data = (u_char *)malloc(16);
	mt_random_mem(data, 16);

	data[6] = 0x40 | (data[6] & 0xf);
	data[8] = 0x80 | (data[8] & 0x3f);

	bin2hex(data, 16, _uuid);

	int j = 0;
	for (int i = 31; i > 6; i--)
	{
		if (31 - i == line[j])
		{
			_uuid[i + 4 - j] = '-';
			j++;
		}
		_uuid[i + 4 - j] = _uuid[i];
	}
	free(data);
}
