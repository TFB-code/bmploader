#ifndef _BMPLOADER
#define _BMPLOADER

#include <stdio.h>
#include <stdlib.h>

typedef struct fileheader {
    char id[2];
    unsigned int size;
    char reserved1[2];
    char reserved2[2];
    unsigned int offset;
} fileheader;

struct header {
    fileheader filehdr;
} header;

void _failnow() {
    fprintf(stderr,"invalid file type");
    exit(0);
}

FILE* openfile(char* filename) {
    FILE* fileptr=fopen(filename,"rb");
    if (fileptr==NULL) {
    _failnow();
    }
    return fileptr;
}

void closefile(FILE* fileptr) {
    fclose(fileptr);
}

void readfileheader(FILE* fileptr) {
    fread(&header.filehdr.id, 2, 1, fileptr);
    fread(&header.filehdr.size, 4, 1, fileptr);
    fread(&header.filehdr.reserved1, 2, 1, fileptr);
    fread(&header.filehdr.reserved2, 2, 1, fileptr);
    fread(&header.filehdr.offset, 4, 1, fileptr);

    if (!(header.filehdr.id[0] == 'B' && header.filehdr.id[1] == 'M')) {
        _failnow();
    }
}

void* loadbmp(char *filename) {

    FILE* fileptr=openfile(filename);

    // read bmp header
    readfileheader(fileptr);

    long int dibsize = header.filehdr.size - sizeof(fileheader);

    void* datablock = calloc(1,dibsize);
    fread(datablock,dibsize,1,fileptr);
    
    closefile(fileptr);

    return datablock;
}

void freebmp(void* bitmap) {
    free(bitmap);
}

#endif