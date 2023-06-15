#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "short_test.h"
#include "thinkgear_test.h"

#define BUFFERSIZE 512
#define FILENAME "/dev/tnt1"

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
    FILE *fp = fopen(FILENAME, "ab");
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

int main()
{
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
        printf("Buffer [%i] = 0x%X\n", buf.pos, buf.data[buf.pos] );
    }
    return 0;
}