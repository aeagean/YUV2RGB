#include <stdio.h>
#include <stdint.h>

static uint8_t s_R[256][256] = {0};
static uint8_t s_G[256][256][256] = {0};
static uint8_t s_B[256][256] = {0};

/* 初始化YUV转RGB转换对照表 */
static bool initYUV2RGB()
{
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            int r = i + (1.370705 * (j-128));
            s_R[i][i] = r < 0 ? 0 : r;
            s_R[i][j] = r > 255 ? 255 : r;

            int b = i + (1.732446 * (i-128));
            s_B[i][i] = b < 0 ? 0 : b;
            s_B[i][j] = b > 255 ? 255 : b;

            for (int k = 0; k < 256; k++) {
                int g = i - (0.698001 * (k-128)) - (0.337633 * (j-128));
                s_G[i][i][k] = g < 0 ? 0 : g;
                s_G[i][j][k] = g > 255 ? 255 : g;
            }
        }
    }

    return true;
}

/* YUV转RGB */
uint32_t YUV2RGB(uint8_t y, uint8_t u, uint8_t v)
{
    uint32_t RGB = 0;
    uint8_t *r = (uint8_t *)&RGB + 0;
    uint8_t *g = (uint8_t *)&RGB + 1;
    uint8_t *b = (uint8_t *)&RGB + 2;

    /* 只初始化一次，用于初始化YUV转RGB对照表 */
    static bool isInitialized = initYUV2RGB();

    *r = s_R[y][v];    /* R */
    *g = s_G[y][u][v]; /* G */
    *b = s_B[y][u];    /* B */

    return RGB;
}


int main(int argc, char *argv[])
{
    printf("%d\r\n", YUV2RGB(100, 100, 100));
    return 0;
}
