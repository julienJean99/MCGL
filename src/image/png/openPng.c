/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Mon 11 Mar 17:07:17 CET 2019 */
/* // open png file */
/* // */

#include <png.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "modular/raise.h"
#include "internal/drawable/imagepr.h"
#include "internal/server_connection.h"

static void chechFile(
    FILE *file)
{
    unsigned char nbr[8] = "";

    fread(nbr, 1, 8, file);
    if (png_sig_cmp(nbr, 0, 8) != 0) {
        raise("not a Png file");
    }
}

static char parsePng(
    FILE *file,
    mc_imagePr *image)
{
    char *data = NULL;
    png_struct *pngPtr = png_create_read_struct(
        PNG_LIBPNG_VER_STRING,
        NULL, NULL, NULL);
    png_info *pngInfo = NULL;
    int readFlag =
        PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND |
        PNG_TRANSFORM_SWAP_ENDIAN | PNG_TRANSFORM_BGR |
        PNG_TRANSFORM_SHIFT | PNG_TRANSFORM_STRIP_16;
    int colorType = 0;
    int interlaceMethod = 0;
    int rowBytes = 0;
    png_uint_32 index = 0;
    png_bytepp rowPointers = NULL;
    png_uint_32 width = 0;
    png_uint_32 height = 0;
    int bitDepth = 0;
    Display *dys = getDisplay();

    if (!pngPtr) {
        return (0);
    } else if (!(pngInfo = png_create_info_struct(pngPtr))) {
        png_destroy_read_struct(&pngPtr, NULL, NULL);
        return (0);
    }
    if (setjmp(png_jmpbuf(pngPtr))) {
        png_destroy_read_struct(&pngPtr, &pngInfo, NULL);
        return (0);
    }
    png_init_io(pngPtr, file);
    png_set_sig_bytes(pngPtr, 8);
    png_read_png(pngPtr, pngInfo, readFlag, NULL);
    png_get_IHDR(pngPtr,
                 pngInfo,
                 &width, &height,
                 &bitDepth,
                 &colorType,
                 &interlaceMethod,
                 NULL,
                 NULL);
    png_set_filler(pngPtr, 0xffff, PNG_FILLER_AFTER);
    rowBytes = png_get_rowbytes(pngPtr, pngInfo);
    data = malloc(rowBytes * height);
    if (!data) {
        png_destroy_read_struct(&pngPtr, &pngInfo, NULL);
        return (0);
    }
    rowPointers = png_get_rows(pngPtr, pngInfo);
    while (index < height) {
        memcpy(data + (index * rowBytes),
               rowPointers[index],
               rowBytes);
        ++index;
    }
    image->image = XCreateImage(
        dys,
        CopyFromParent,
        DefaultDepth(
            dys,
            DefaultScreen(dys)),
        ZPixmap,
        0,
        data,
        width,
        height,
        bitDepth,
        rowBytes);
    png_destroy_info_struct(pngPtr, &pngInfo);
    png_destroy_read_struct(&pngPtr, &pngInfo, NULL);
    return (1);
}

char readPng(
    const char *path,
    mc_imagePr *image)
{
    FILE *fd = fopen(path, "r");
    char res = 0;

    if (!fd) {
        raise("file not found\n");
    }
    chechFile(fd);
    res = parsePng(
        fd,
        image);
    fclose(fd);
    return (res);
}
