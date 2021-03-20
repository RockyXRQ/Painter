#ifndef __PAINTER_H
#define __PAINTER_H

#include "config.h"
#include "marco.h"

// HSL颜色结构体
typedef struct {
    float H;
    float S;
    float L;
} HSL_Color_Type;

// 雨滴结构体
typedef struct {
    char label[20];  // 结构体标签/名称

    int position_start[2];    // 起始坐标 [x, y]
    int position_height_end;  // 终止高度 [x, y]

    int step;

    int is_on : 1;             // 是否落下(被画出)
    HSL_Color_Type color_HSL;  // 颜色
} Raindrop_Type;

Raindrop_Type* Rain_Create();

// 荷叶结构体
typedef struct {
    char label[20];  // 结构体标签/名称

    int position_rect[4];      // 椭圆坐标 [left, top, right, bottom]
    HSL_Color_Type color_HSL;  // 颜色
} Lotus_Leaf_Type;

// 风结构体
typedef struct {
    char label[20];  // 结构体标签/名称

    int is_on : 1;  // 是否有风
    int speed;      // 速度
} Wind_Type;

// 涟漪结构体
typedef struct {
    char label[20];  // 结构体标签/名称

    int raindrop_speed;
    int is_on : 1;
    int position_rect[4];  // 椭圆坐标 [left, top, right, bottom]

} Ripple_Type;

// 水花结构体
typedef struct {
    char label[20];  // 结构体标签/名称

    int raindrop_speed;
    int is_on : 1;
    int positioin_start[2];  // 起始坐标 [x, y]

} Spray_Type;

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
void Lotus_Leaf_Init(Lotus_Leaf_Type*, int left, int top, int right, int bottom,
                     float H, float S, float L);

/**
 * @brief 风初始化函数
 *
 * @param wind  风句柄
 * @param is_on  是否开启风
 * @param speed  风速
 */
void Wind_Init(Wind_Type*, int is_on, int speed);

/**
 * @brief 涟漪工厂函数
 */
Ripple_Type* Ripples_Create();

/**
 * @brief 水花工厂函数
 */
Spray_Type* Sprays_Create();

/**
 * @brief Painter初始化函数
 *
 * @param width 画布宽度
 * @param height 画布高度
 */
void Painter_Init(int width, int height);

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
                 Spray_Type* sprays, const char* cmd);

/**
 * @brief Painter画面更新函数
 *
 * @param delay_ms 画面间刷新时间(单位毫秒)
 */
void Painter_Update(int delay_ms);

/**
 * @brief Painter结束释放函数
 *
 * @param rain 雨句柄
 * @param ripples 涟漪句柄
 * @param sprays 水花句柄
 *
 */
void Painter_End(Raindrop_Type* rain, Ripple_Type* ripples, Spray_Type* sprays);
#endif
