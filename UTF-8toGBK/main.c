//
//  main.c
//  UTF-8toGBK
//
//  Created by wzq on 2017/6/10.
//  Copyright © 2017年 wzq. All rights reserved.
//

#include <iconv.h>
#include <stdio.h>
#include <string.h>

int code_convert(char *from_charset, char *to_charset, char *inbuf, size_t inlen,
                 char *outbuf, size_t outlen) {
    iconv_t cd;
    char **pin = &inbuf;
    char **pout = &outbuf;
    
    cd = iconv_open(to_charset, from_charset);
    if (cd == 0)
        return -1;
    memset(outbuf, 0, outlen);
    if (iconv(cd, pin, &inlen, pout, &outlen) == -1)
        return -1;
    iconv_close(cd);
    *pout = '\0';
    
    return 0;
}

int u2g(char *inbuf, size_t inlen, char *outbuf, size_t outlen) {
    return code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, outlen);
}

int g2u(char *inbuf, size_t inlen, char *outbuf, size_t outlen) {
    return code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, outlen);
}

int main(void) {
    char *s = "啊";//GBK编码为 0XBO 0XA1
    char buf[10];
    u2g(s, strlen(s), buf, sizeof(buf));
    printf("%XH %XH\n",(unsigned char)buf[0],(unsigned char)buf[1]);
    
    return 1;
}
