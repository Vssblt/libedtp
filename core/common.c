#include "common.h"
#include <time.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#ifdef _WIN32
  #include <windows.h>
  #ifndef _WIN32_WCE
    #define RtlGenRandom SystemFunction036
    BOOLEAN NTAPI RtlGenRandom(PVOID RandomBuffer, ULONG RandomBufferLength);
    #pragma comment(lib, "advapi32.lib")
  #endif /*_WIN32_WCE*/
#else
  #if defined __linux__ || defined __CYGWIN__
    #include <fcntl.h>
    #include <unistd.h>
  #endif
#endif /*_WIN32*/

uint32_t
timestamp() 
{
	time_t t = time(NULL);
	uint32_t ii = (uint32_t)time(&t);
	return ii;
}

int
random_s(int min, int max, int *err) 
{
	int r = 0;
	int ret = random_mem((u_char*)&r, sizeof(r));
	if (err == NULL) {
		if (ret == -1) {
			goto ret_zero;
		} else {
			goto ret_int;
		}
	} else {
		*err = ret;
		if (ret != -1) {
			goto ret_int;
		} else {
			goto ret_zero;
		}
	}

ret_int:   return (u_char)r % (max - min) + min;
ret_zero:  return 0;

}

int
is_little_endian() 
{
	union w
	{
		int a;
		char b;
	}c;
	c.a = 1;
	return (c.b == 1);
}

uint32_t
mhash(const char* str, uint32_t len) 
{
	uint32_t hash = 0;
	uint32_t x = 0;
	uint32_t i = 0;
	for (i = 0; i < len; str++, i++) {
		hash = (hash << 4) + (*str);
		if ((x = hash & 0xF0000000L) != 0){
			hash ^= (x >> 24);
		}
		hash &= ~x;
	}
	return hash;
}

void
print_time() 
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[128];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S", timeinfo);
	printf("%s", buffer);
}

int
random_mem(u_char *mem, uint32_t len) 
{
	int i = -1;
#ifdef _WIN32
  #ifdef _WIN32_WCE
	int ret = CeGenRandom(len, (BYTE *)mem);
	ret ? i = 0 : 0;
  #else
	int ret = RtlGenRandom(mem, (ULONG)len);
	ret ? i = 0 : 0;
  #endif	
#else
  #if defined __linux__ || defined __CYGWIN__
	int fd = open("/dev/urandom", O_RDONLY);
	if (fd != -1) {
		read(fd, mem, len);
		close(fd);
		i = 0;
	}
  #endif
#endif
	return i;
}

void
bin2hex(const u_char *data, uint32_t size, char *out) 
{
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
uuid(char *_uuid) 
{
	int line[] = {12, 16, 20, 24,};
	u_char *data = (u_char *)malloc(16);
	random_mem(data, 16);

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

void 
lestring_copy(lestring *dst, lestring *srt, int type)
{
	if (type == COPY) {
		memcpy(dst->str, srt->str, srt->size);
		dst->size = srt->size;
	} else if (type == COPY_AND_NEW) {
		dst->str = (char *)malloc(sizeof(char) * srt->size);
		dst->size = srt->size;
		memcpy(dst->str, srt->str, srt->size);
	}
}

void 
lestring_copy(lestring *dst, const char *str, int size, int type)
{
	if (type == COPY) {
		memcpy(dst->str, str, size);
		dst->size = size;
	} else if (type == COPY_AND_NEW) {
		dst->str = (char *)malloc(sizeof(char) * size);
		dst->size = size;
		memcpy(dst->str, str, size);
	}
}

void
lestring_free(lestring *str)
{
	if (str->size != 0) {
		free(str->str);
		str->size = 0;
	}
}
