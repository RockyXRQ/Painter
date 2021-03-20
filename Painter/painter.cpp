#include "painter.h"

#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#pragma comment(lib, "Winmm.lib")

/**
 * @brief 雨滴初始化函数(静态函数)
 *
 * @param raindrop  雨滴句柄
 * @param x 雨滴出生位置 X轴坐标
 * @param y 雨滴出生位置 Y轴坐标
 * @param height_end 雨滴结束下落时的 Y轴坐标
 * @param step 雨滴下落速度
 * @param H 雨滴颜色 H
 * @param S 雨滴颜色 S
 * @param L 雨滴颜色 L
 * @param is_on 该雨滴是否要被绘制
 */
static Raindrop_Type* Raindrop_Init(Raindrop_Type* raindrop, int x, int y,
                                    int height_end, int step, float H, float S,
                                    float L, int is_on) {
    strcpy_s(raindrop->label, 9, "Raindrop");

    raindrop->position_start[0] = x;
    raindrop->position_start[1] = y;

    raindrop->position_height_end = height_end;

    raindrop->step = step;

    raindrop->color_HSL.H = H;
    raindrop->color_HSL.S = S;
    raindrop->color_HSL.L = L;

    raindrop->is_on = is_on;

    return raindrop;
}

/**
 * @brief 雨数组(句柄)工厂函数
 */
Raindrop_Type* Rain_Create() {
    Raindrop_Type* rain =
        (Raindrop_Type*)malloc(MAX_RAINDROP_NUM * sizeof(Raindrop_Type));
    for (int i = 0; i < MAX_RAINDROP_NUM; i++) {
        int x = rand() % (5 * WIDTH) - WIDTH;
        int y = rand() % (HEIGHT / 3);
        int step = (rand() % 5000) / 1000.0 + 1;
        int height_end = rand() % (HEIGHT / 3) + ((HEIGHT / 3) * 2) * step / 5;
        int H = rand() % 360;
        float S = (float)(rand() % 90) + 0.1;
        float L = step + 3;

        int is_on = TRUE;
        if (i >= START_RAINDROP_NUM) {
            is_on = FALSE;
        }

        Raindrop_Init(rain + i, x, y, height_end, step, H, S, L, is_on);
    }
    return rain;
}

/**
 * @brief 荷叶绘制函数(静态函数)
 *
 * @param lotusLeaf  荷叶句柄
 */
static void Lotus_Leaf_Draw(Lotus_Leaf_Type* lotusLeaf) {
    setlinecolor(HSLtoRGB(lotusLeaf->color_HSL.H, lotusLeaf->color_HSL.S,
                          MAX(lotusLeaf->color_HSL.L - 0.2f, 0)));
    setfillstyle(BS_SOLID);
    setfillcolor(HSLtoRGB(lotusLeaf->color_HSL.H, lotusLeaf->color_HSL.S,
                          lotusLeaf->color_HSL.L));
    fillellipse(lotusLeaf->position_rect[0], lotusLeaf->position_rect[1],
                lotusLeaf->position_rect[2], lotusLeaf->position_rect[3]);
}

/**
 * @brief 风初始化函数
 *
 * @param wind  风句柄
 * @param is_on  是否开启风
 * @param speed  风速
 */
void Wind_Init(Wind_Type* wind, int is_on, int speed) {
    strcpy_s(wind->label, 5, "Wind");

    wind->is_on = is_on;
    wind->speed = speed;
}

/**
 * @brief 切换风开启状态(静态函数)
 *
 * @param wind  风句柄
 * @param is_on  是否开启风
 */
static void Wind_Switch(Wind_Type* wind, int on_off) { wind->is_on = on_off; }

/**
 * @brief 涟漪初始化函数(静态函数)
 *
 * @param ripple 荷叶句柄
 * @param left 涟漪绘制位置 左上角X轴坐标
 * @param top 涟漪绘制位置 左上角Y轴坐标
 * @param right 涟漪绘制位置 右下角X轴坐标
 * @param bottom 涟漪绘制位置 右下角Y轴坐标
 * @param raindrop_speed 雨滴下落速度
 * @param is_on 是否绘制此涟漪
 */
static void Ripple_Init(Ripple_Type* ripple, int left, int top, int right,
                        int bottom, int raindrop_speed, int is_on) {
    strcpy_s(ripple->label, 7, "Ripple");

    ripple->position_rect[0] = left;
    ripple->position_rect[1] = top;
    ripple->position_rect[2] = right;
    ripple->position_rect[3] = bottom;

    ripple->raindrop_speed = raindrop_speed;

    ripple->is_on = is_on;
}

/**
 * @brief 涟漪工厂函数
 */
Ripple_Type* Ripples_Create() {
    Ripple_Type* ripples =
        (Ripple_Type*)malloc(MAX_RAINDROP_NUM * sizeof(Ripple_Type));
    for (int i = 0; i < MAX_RAINDROP_NUM; i++) {
        Ripple_Init(ripples + i, 0, 0, 0, 0, 0, FALSE);
    }

    return ripples;
}

/**
 * @brief 涟漪注册启动函数(静态函数)
 *
 * @param ripple 涟漪句柄
 * @param left 涟漪绘制位置 左上角X轴坐标
 * @param top 涟漪绘制位置 左上角Y轴坐标
 * @param right 涟漪绘制位置 右下角X轴坐标
 * @param bottom 涟漪绘制位置 右下角Y轴坐标
 * @param raindrop_speed 雨滴下落速度
 */
static void Ripples_Register(Ripple_Type* ripples, int left, int top, int right,
                             int bottom, int raindrop_speed) {
    for (int i = 0; i < MAX_RAINDROP_NUM; i++) {
        if (!(ripples + i)->is_on) {
            Ripple_Init(ripples + i, left, top, right, bottom, raindrop_speed,
                        TRUE);
            break;
        }
    }
}

/**
 * @brief 涟漪绘制函数(静态函数)
 *
 * @param ripple 涟漪句柄
 */
static void Ripples_Draw(Ripple_Type* ripples) {
    for (int i = 0; i < MAX_RAINDROP_NUM; i++) {
        if ((ripples + i)->is_on) {
            setlinecolor(0);
            ellipse((ripples + i)->position_rect[0],
                    (ripples + i)->position_rect[1],
                    (ripples + i)->position_rect[2],
                    (ripples + i)->position_rect[3]);
        }

        if ((ripples + i)->is_on) {
            setlinecolor(RGB((ripples + i)->raindrop_speed * 20,
                             (ripples + i)->raindrop_speed * 20,
                             (ripples + i)->raindrop_speed * 20));

            (ripples + i)->position_rect[0] -=
                2 * (ripples + i)->raindrop_speed;
            (ripples + i)->position_rect[1] -= (ripples + i)->raindrop_speed;
            (ripples + i)->position_rect[2] +=
                2 * (ripples + i)->raindrop_speed;
            (ripples + i)->position_rect[3] += (ripples + i)->raindrop_speed;

            ellipse((ripples + i)->position_rect[0],
                    (ripples + i)->position_rect[1],
                    (ripples + i)->position_rect[2],
                    (ripples + i)->position_rect[3]);

            (ripples + i)->raindrop_speed -= 1;

            if ((ripples + i)->raindrop_speed <= 0) {
                (ripples + i)->is_on = FALSE;
                setlinecolor(0);
                ellipse((ripples + i)->position_rect[0],
                        (ripples + i)->position_rect[1],
                        (ripples + i)->position_rect[2],
                        (ripples + i)->position_rect[3]);
            }
        }
    }
}

/**
 * @brief 水花初始化函数(静态函数)
 *
 * @param spray 水花句柄
 * @param x 水花出生位置 X轴坐标
 * @param y 水花出生位置 Y轴坐标
 * @param raindrop_speed 雨滴下落速度
 * @param is_on 是否绘制此水花
 */
static void Spray_Init(Spray_Type* spray, int x, int y, int raindrop_speed,
                       int is_on) {
    strcpy_s(spray->label, 6, "Spray");

    spray->positioin_start[0] = x;
    spray->positioin_start[1] = y;

    spray->raindrop_speed = raindrop_speed;

    spray->is_on = is_on;
}

/**
 * @brief 水花工厂函数
 */
Spray_Type* Sprays_Create() {
    Spray_Type* sprays =
        (Spray_Type*)malloc(MAX_RAINDROP_NUM * sizeof(Spray_Type));
    for (int i = 0; i < MAX_RAINDROP_NUM; i++) {
        Spray_Init(sprays + i, 0, 0, 0, FALSE);
    }

    return sprays;
}

/**
 * @brief 水花注册启动函数(静态函数)
 *
 * @param spray 水花句柄
 * @param x 水花出生位置 X轴坐标
 * @param y 水花出生位置 Y轴坐标
 * @param raindrop_speed 雨滴下落速度
 */
static void Sprays_Register(Spray_Type* sprays, int x, int y,
                            int raindrop_speed) {
    for (int i = 0; i < MAX_RAINDROP_NUM; i++) {
        if (!(sprays + i)->is_on) {
            Spray_Init(sprays + i, x, y, raindrop_speed, TRUE);
            break;
        }
    }
}

/**
 * @brief 水花绘制函数(静态函数)
 *
 * @param spray 水花句柄
 */
static void Sprays_Draw(Spray_Type* sprays) {
    for (int i = 0; i < MAX_RAINDROP_NUM; i++) {
        int step = MAX(10 - (sprays + i)->raindrop_speed, 0);

        if ((sprays + i)->is_on) {
            putpixel((sprays + i)->positioin_start[0] - step,
                     (sprays + i)->positioin_start[1] - step, 0);
            putpixel((sprays + i)->positioin_start[0] + step,
                     (sprays + i)->positioin_start[1] - step, 0);
            putpixel((sprays + i)->positioin_start[0],
                     (sprays + i)->positioin_start[1] - step, 0);
        }

        if ((sprays + i)->is_on) {
            (sprays + i)->raindrop_speed -= 1;
            step = MAX(10 - (sprays + i)->raindrop_speed, 0);

            putpixel((sprays + i)->positioin_start[0] - step,
                     (sprays + i)->positioin_start[1] - step,
                     RGB(step * 20, step * 20, step * 20));
            putpixel((sprays + i)->positioin_start[0] + step,
                     (sprays + i)->positioin_start[1] - step,
                     RGB(step * 20, step * 20, step * 20));
            putpixel((sprays + i)->positioin_start[0],
                     (sprays + i)->positioin_start[1] - step,
                     RGB(step * 20, step * 20, step * 20));

            if ((sprays + i)->raindrop_speed <= 0) {
                (sprays + i)->is_on = FALSE;
                putpixel((sprays + i)->positioin_start[0] - step,
                         (sprays + i)->positioin_start[1] - step, 0);
                putpixel((sprays + i)->positioin_start[0] + step,
                         (sprays + i)->positioin_start[1] - step, 0);
                putpixel((sprays + i)->positioin_start[0],
                         (sprays + i)->positioin_start[1] - step, 0);
            }
        }
    }
}

/**
 * @brief Painter初始化函数
 *
 * @param width 画布宽度
 * @param height 画布高度
 */
void Painter_Init(int width, int height) {
    srand((unsigned)time(NULL));  // 随机种子
    initgraph(width, height);     // 创建绘图窗口
}

/**
 * @brief 雨绘制函数(静态函数)
 *
 * @param rain 雨句柄
 * @param rqrd_raindrop_num  所绘制雨滴的数量
 * @param ripples 涟漪句柄
 * @param sprays 水花句柄
 * @param wind 风句柄
 */
static int Rain_Draw(Raindrop_Type* rain, int rqrd_raindrop_num,
                     Ripple_Type* ripples, Spray_Type* sprays,
                     Wind_Type* wind) {
    static int is_first_raindrop = TRUE;
    static int real_raindrop_num = START_RAINDROP_NUM;
    static int raindrop_leaf_count = 0;

    for (int i = 0; i < MAX_RAINDROP_NUM; i++) {
        putpixel((rain + i)->position_start[0], (rain + i)->position_start[1],
                 0);
        if ((rain + i)->is_on) {
            (rain + i)->position_start[1] =
                MIN((rain + i)->position_start[1] + (rain + i)->step,
                    (rain + i)->position_height_end);

            if (wind->is_on) {
                (rain + i)->position_start[0] += (rain + i)->step;
            }
        }

        if ((rain + i)->is_on &&
            (rain + i)->position_start[1] >= (rain + i)->position_height_end) {
            (rain + i)->is_on = FALSE;
            real_raindrop_num--;
            //**************************** 雨滴重生 ****************************
            int x = rand() % WIDTH;
            int y = rand() % (HEIGHT / 3);
            int height_end = rand() % (HEIGHT / 3) + ((HEIGHT / 3) * 2);
            int step = (rand() % 5000) / 1000.0 + 1;
            int H = rand() % 360;
            float S = (float)(rand() % 90) + 0.1;
            float L = step + 3;

            int is_on = TRUE;
            if (real_raindrop_num >= rqrd_raindrop_num) {
                is_on = FALSE;
            }
            real_raindrop_num += is_on;

            if (getpixel((rain + i)->position_start[0],
                         (rain + i)->position_start[1]) != 0) {
                if (++raindrop_leaf_count > 25) {
                    mciSendString("close rl", NULL, 0, NULL);
                    mciSendString("open raindrop_leaf.mp3 alias rl", NULL, 0,
                                  NULL);
                    mciSendString("play rl", NULL, 0, NULL);
                    raindrop_leaf_count = 0;
                }

                Sprays_Register(sprays, (rain + i)->position_start[0],
                                (rain + i)->position_start[1],
                                (rain + i)->step);
            } else {
                if (is_first_raindrop) {
                    mciSendString("open raindrop_water.mp3 alias rw", NULL, 0,
                                  NULL);
                    mciSendString("play rw repeat", NULL, 0, NULL);
                    is_first_raindrop = FALSE;
                }

                Ripples_Register(ripples, (rain + i)->position_start[0],
                                 (rain + i)->position_start[1],
                                 (rain + i)->position_start[0],
                                 (rain + i)->position_start[1],
                                 (rain + i)->step);
            }

            Raindrop_Init((rain + i), x, y, height_end, step, H, S, L, is_on);
        }
        if ((!(rain + i)->is_on) && real_raindrop_num < rqrd_raindrop_num) {
            (rain + i)->is_on = TRUE;
            real_raindrop_num++;
        }

        if ((rain + i)->is_on) {
            putpixel((rain + i)->position_start[0],
                     (rain + i)->position_start[1],
                     HSLtoRGB((rain + i)->color_HSL.H, (rain + i)->color_HSL.S,
                              (rain + i)->color_HSL.L));
        }
    }

    return real_raindrop_num;
}

/**
 * @brief 荷叶初始化函数
 *
 * @param lotusLeaf  荷叶句柄
 * @param left 荷叶绘制位置 左上角X轴坐标
 * @param top 荷叶绘制位置 左上角Y轴坐标
 * @param right 荷叶绘制位置 右下角X轴坐标
 * @param bottom 荷叶绘制位置 右下角Y轴坐标
 * @param H 荷叶HSL H
 * @param S 荷叶HSL S
 * @param L 荷叶HSL L
 */
void Lotus_Leaf_Init(Lotus_Leaf_Type* lotusLeaf, int left, int top, int right,
                     int bottom, float H, float S, float L) {
    strcpy_s(lotusLeaf->label, 11, "Lotus_Leaf");

    lotusLeaf->position_rect[0] = left;
    lotusLeaf->position_rect[1] = top;
    lotusLeaf->position_rect[2] = right;
    lotusLeaf->position_rect[3] = bottom;

    lotusLeaf->color_HSL.H = H;
    lotusLeaf->color_HSL.S = S;
    lotusLeaf->color_HSL.L = L;
}

static void Flash_Bang_Draw() {
    setfillcolor(WHITE);
    solidrectangle(0, 0, WIDTH, HEIGHT);

    mciSendString("close fb", NULL, 0, NULL);
    mciSendString("open flash_bang.mp3 alias fb", NULL, 0, NULL);
    mciSendString("play fb", NULL, 0, NULL);

    Sleep(50);
    setfillcolor(BLACK);
    solidrectangle(0, 0, WIDTH, HEIGHT);
    Sleep(20);
    setfillcolor(WHITE);
    solidrectangle(0, 0, WIDTH, HEIGHT);
    setfillcolor(BLACK);
    solidrectangle(0, 0, WIDTH, HEIGHT);
}

/**
 * @brief Painter指令台
 *
 * @param handle 主要操作句柄
 * @param wind 风句柄
 * @param ripples 涟漪句柄
 * @param sprays 水花句柄
 * @param cmd 指令字符串
 */
void Painter_CMD(void* handle, Wind_Type* wind, Ripple_Type* ripples,
                 Spray_Type* sprays, const char* cmd) {
    static int rqrd_raindrop_num = 40;

    if (CMD_IS_SAME(cmd, "lotus_leaf")) {
        Lotus_Leaf_Draw((Lotus_Leaf_Type*)handle);
    } else if (CMD_IS_SAME(cmd, "rain")) {
        Rain_Draw((Raindrop_Type*)handle, rqrd_raindrop_num, ripples, sprays,
                  wind);
    } else if (CMD_IS_SAME(cmd, "wind_on")) {
        Wind_Switch(wind, TRUE);
    } else if (CMD_IS_SAME(cmd, "wind_off")) {
        Wind_Switch(wind, FALSE);
    } else if (CMD_IS_SAME(cmd, "ripples")) {
        Ripples_Draw(ripples);
    } else if (CMD_IS_SAME(cmd, "sprays")) {
        Sprays_Draw(sprays);
    } else if (CMD_IS_SAME(cmd, "raindrop_more")) {
        rqrd_raindrop_num += rand() % 35 + 45;
        rqrd_raindrop_num = MIN(rqrd_raindrop_num, MAX_RAINDROP_NUM);
    } else if (CMD_IS_SAME(cmd, "raindrop_less")) {
        rqrd_raindrop_num -= rand() % 45 + 35;
        rqrd_raindrop_num = MAX(rqrd_raindrop_num, 20);
    } else if (CMD_IS_SAME(cmd, "flash_bang")) {
        Flash_Bang_Draw();
    }
}

/**
 * @brief Painter画面更新函数
 *
 * @param delay_ms 画面间刷新时间(单位毫秒)
 */
void Painter_Update(int delay_ms) { Sleep(delay_ms); }

/**
 * @brief Painter结束释放函数
 *
 * @param rain 雨句柄
 * @param ripples 涟漪句柄
 * @param sprays 水花句柄
 */
void Painter_End(Raindrop_Type* rain, Ripple_Type* ripples,
                 Spray_Type* sprays) {
    free(rain);
    free(ripples);
    free(sprays);
    closegraph();
}