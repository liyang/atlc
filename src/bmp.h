struct Bitmap_File_Head_Struct
{
  char   zzMagic[2];	/* 00 "BM" */
  long   bfSize;      /* 02 */
  short  zzHotX;	/* 06 */
  short  zzHotY;	/* 08 */
  long   bfOffs;      /* 0A */
  long   biSize;      /* 0E */
} Bitmap_File_Head;

struct Bitmap_Head_Struct
{
  long   biWidth;     /* 12 */
  long   biHeight;    /* 16 */
  short  biPlanes;    /* 1A */
  short  biBitCnt;    /* 1C */
  long   biCompr;     /* 1E */
  long   biSizeIm;    /* 22 */
  long   biXPels;     /* 26 */
  long   biYPels;     /* 2A */
  long   biClrUsed;   /* 2E */
  long   biClrImp;    /* 32 */
                        /* 36 */
} Bitmap_Head;
