#include <stdlib.h>
#include <stdio.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "short_test.h"
#include "thinkgear_test.h"

#define BUFFERSIZE 512
#define FILENAME "/dev/tnt1"

static char* portname;

typedef struct _buffer_t buffer_t;
typedef struct _tg_t tg_t;
void readBuffer(unsigned char* data, int size);
void Buffer_Write(buffer_t *buf, unsigned char c);
void TG_Parse(tg_t *tg, unsigned char c);

typedef struct _buffer_t {
    int pos;
    int size;
    unsigned char data[BUFFERSIZE];
    void (*write)(buffer_t *buf, unsigned char c);
} buffer_t;

typedef struct _tg_t {
    int counter;
    char reading;
    char counting;
    buffer_t *buf;
} tg_t;

/**
* Solution from https://gist.github.com/GoaLitiuM/aff9fbfa4294fa6c1680
*/
#ifdef _WIN32
unsigned long currentResolution = 0;

unsigned long setHighestTimerResolution(unsigned long timer_res_us)
{
    unsigned long timer_current_res = ULONG_MAX;
    const HINSTANCE ntdll = LoadLibrary("NTDLL.dll");
    if (ntdll != NULL)
    {
        typedef long(NTAPI* pNtSetTimerResolution)(unsigned long RequestedResolution, BOOLEAN Set, unsigned long* ActualResolution);

        pNtSetTimerResolution NtSetTimerResolution = (pNtSetTimerResolution)GetProcAddress(ntdll, "NtSetTimerResolution");
        if (NtSetTimerResolution != NULL)
        {
            // bounds are validated and set to the highest allowed resolution
            NtSetTimerResolution(timer_res_us, TRUE, &timer_current_res);
        }
        // we can decrement the internal reference count by one
        // and NTDLL.DLL still remains loaded in the process
        FreeLibrary(ntdll);
    }

    return timer_current_res;
}
void usleep(__int64 usec)
{
    HANDLE timer;
    LARGE_INTEGER period;

    if (currentResolution == 0)
        currentResolution = setHighestTimerResolution(1);

    // negative values are for relative time
    period.QuadPart = -(10 * usec);

    timer = CreateWaitableTimer(NULL, TRUE, NULL);
    SetWaitableTimer(timer, &period, 0, NULL, NULL, 0);
    WaitForSingleObject(timer, INFINITE);
    CloseHandle(timer);
}
/**
* 
*/
#endif
void readBuffer(unsigned char* data, int size) {
    printf("Read size: %i\n", size);
    for (int i=0; i<size; i++) {
        printf(" 0x%02X ", data[i]);
    }
    printf("\n");
}

void Buffer_Write(buffer_t *buf, unsigned char c) {
    buf->data[buf->pos]=c;
    (buf->pos)++;
}

void writeToFile(unsigned char *buf, int size) {
    printf("Writing to %s\n", portname);
    FILE *fp = fopen(portname, "ab");
    fwrite(buf, 1, size, fp);
    fclose(fp);
}

void TG_Parse(tg_t *tg, unsigned char c) {

    int *pos = &(tg->buf->pos);
    unsigned char *data = tg->buf->data;

    if (tg->reading==0 && c!=0xAA && (*pos) == 0) return;

    if (*pos > 2 && tg->counter == 0 && tg->reading!=0) {
        tg->buf->write(tg->buf, c);
        tg->reading=0;
        if(*pos==8) {
            usleep(138*6);
        }
        //
        readBuffer(data, (*pos));
        writeToFile(data, (*pos));
        //
        *pos = 0;
        return;
    }
    if (tg->reading==0 && c!=0xAA && (*pos) != 0) {
        return;
    }
    if (tg->reading==0 && c==0xAA) {
        tg->reading=0xFF;
    }
    if (tg->reading && *pos==2) {
        tg->counter = c;
        tg->counting = 0xFF;
        //data[*pos] = c;
        //(*pos)++;
        tg->buf->write(tg->buf, c);
        return;
    }
    tg->buf->write(tg->buf, c);
    if (tg->reading && (*pos) > 2) tg->counter--;
}

int main(int argc, char* argv[])
{
    char *helpMsg="ThinkGear simulator is a simple tool\n"
                  "for emulating and testing on virtual serial port.\n"
                  "You can use tty0tty or com0com to emulating port.\n\n"
                  "If are you ready, type in command line\n"
                  "./thinkGearSimulator [portname], where portname can be\n"
                  "for UNIX /dev/tnt0 or Window COM0\n";

    if (argc < 2) {
        printf("USAGE:\n");
        printf("%s\n", helpMsg);
        return 0;
    } else {
        portname = argv[1];
        printf("Choosed port: %s", portname);
    }
    
    tg_t tg;
    buffer_t buf;
    buf.pos=0;
    buf.size=BUFFERSIZE;
    tg.counter=0;
    tg.counting=0;
    tg.reading=0;
    tg.buf=&buf;
    buf.write=Buffer_Write;

    for (int i=0; i<thinkgear_test_len; i++) {
        TG_Parse(&tg, thinkgear_test[i]);
        usleep(138);
        //printf("Buffer [%i] = 0x%X\n", buf.pos, buf.data[buf.pos] );
    }
    return 0;
}
