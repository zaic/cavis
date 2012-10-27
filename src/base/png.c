#include <png.h>

#include "log.h"
#include "png.h"
#include "util.h"

Arr* pngRead(const char *path) {
    RAII_VAR(FILE*, fD, fopen(path, "r"), fclose);
    Arr* ar = pngFRead(fD);
    if (!ar)
        ELOG("error while reading %s\n", path);
    return ar;
}

Arr* pngFRead(FILE *fD) {
    if (!fD) {
        ELOG("null file descriptor");
        return NULL;
    }
    png_byte header[PNG_HEADER_SIZE];
    fread(header, 1, PNG_HEADER_SIZE, fD);
    if (png_sig_cmp(header, 0, PNG_HEADER_SIZE)) {
        ELOG("not a png file");
        return NULL;
    }
    png_struct *pngPtr = png_create_read_struct
        (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!pngPtr) {
        ELOG("can't init libpng stuff (read_struct)\n");
        return NULL;
    }
    png_info *infoPtr = png_create_info_struct(pngPtr);
    if (!infoPtr) {
        ELOG("can't init libpng stuff (info_struct)\n");
        png_destroy_read_struct(&pngPtr, NULL, NULL);
        return NULL;
    }
    png_init_io(pngPtr, fD);
    png_set_sig_bytes(pngPtr, PNG_HEADER_SIZE);
    png_read_info(pngPtr, infoPtr);

    int height = png_get_image_height(pngPtr, infoPtr);
    int width = png_get_image_width(pngPtr, infoPtr);
    int eSize = png_get_rowbytes(pngPtr, infoPtr) / width;
    Arr* ar = arrAlloc(eSize, 2, height, width);

    /* FIXME initialize array via set function */
    int rowSize = width * eSize;
    int maxRow = height * rowSize;
    for (int row = 0; row < maxRow; row += rowSize)
        png_read_row(pngPtr, ar->data + row, NULL);

    png_destroy_read_struct(&pngPtr, &infoPtr, NULL);
    return ar;
}

int pngWrite(Arr* ar, const char *path) {
    RAII_VAR(FILE*, fD, fopen(path, "w"), fclose);
    int er = pngFWrite(ar, fD);
    if (er)
        ELOG("error while writing %s\n", path);
    return er;
}

int pngFWrite(Arr *ar, FILE *fD) {
    if (!fD)
        return -1;
    png_struct *pngPtr = png_create_write_struct
        (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!pngPtr)
        return -1;
    png_info *infoPtr = png_create_info_struct(pngPtr);
    if (!infoPtr) {
        png_destroy_write_struct(&pngPtr, NULL);
        return -1;
    }
    png_init_io(pngPtr, fD);

    int eSize = ar->eSize;
    int height = ar->size[0];
    int width = ar->size[1];
    png_set_IHDR
        ( pngPtr
        , infoPtr
        , width
        , height
        , 8
        , PNG_COLOR_TYPE_RGB
        , PNG_INTERLACE_NONE
        , PNG_COMPRESSION_TYPE_DEFAULT
        , PNG_FILTER_TYPE_DEFAULT
        );
    png_write_info(pngPtr, infoPtr);

    /* FIXME initialize image via array get function */
    int rowSize = width * eSize;
    int maxRow = height * rowSize;
    for (int row = 0; row < maxRow; row += rowSize)
        png_write_row(pngPtr, ar->data + row);

    png_write_end(pngPtr, NULL);
    png_destroy_write_struct(&pngPtr, &infoPtr);
    return 0;
}
