#ifndef __PAINTER_H
#define __PAINTER_H

#include "config.h"
#include "marco.h"

// HSL��ɫ�ṹ��
typedef struct {
    float H;
    float S;
    float L;
} HSL_Color_Type;

// ��νṹ��
typedef struct {
    char label[20];  // �ṹ���ǩ/����

    int position_start[2];    // ��ʼ���� [x, y]
    int position_height_end;  // ��ֹ�߶� [x, y]

    int step;

    int is_on : 1;             // �Ƿ�����(������)
    HSL_Color_Type color_HSL;  // ��ɫ
} Raindrop_Type;

Raindrop_Type* Rain_Create();

// ��Ҷ�ṹ��
typedef struct {
    char label[20];  // �ṹ���ǩ/����

    int position_rect[4];      // ��Բ���� [left, top, right, bottom]
    HSL_Color_Type color_HSL;  // ��ɫ
} Lotus_Leaf_Type;

// ��ṹ��
typedef struct {
    char label[20];  // �ṹ���ǩ/����

    int is_on : 1;  // �Ƿ��з�
    int speed;      // �ٶ�
} Wind_Type;

// �����ṹ��
typedef struct {
    char label[20];  // �ṹ���ǩ/����

    int raindrop_speed;
    int is_on : 1;
    int position_rect[4];  // ��Բ���� [left, top, right, bottom]

} Ripple_Type;

// ˮ���ṹ��
typedef struct {
    char label[20];  // �ṹ���ǩ/����

    int raindrop_speed;
    int is_on : 1;
    int positioin_start[2];  // ��ʼ���� [x, y]

} Spray_Type;

/**
 * @brief ��Ҷ��ʼ������
 *
 * @param lotusLeaf  ��Ҷ���
 * @param left ��Ҷ����λ�� ���Ͻ�X������
 * @param top ��Ҷ����λ�� ���Ͻ�Y������
 * @param right ��Ҷ����λ�� ���½�X������
 * @param bottom ��Ҷ����λ�� ���½�Y������
 * @param H ��ҶHSL H
 * @param S ��ҶHSL S
 * @param L ��ҶHSL L
 */
void Lotus_Leaf_Init(Lotus_Leaf_Type*, int left, int top, int right, int bottom,
                     float H, float S, float L);

/**
 * @brief ���ʼ������
 *
 * @param wind  ����
 * @param is_on  �Ƿ�����
 * @param speed  ����
 */
void Wind_Init(Wind_Type*, int is_on, int speed);

/**
 * @brief ������������
 */
Ripple_Type* Ripples_Create();

/**
 * @brief ˮ����������
 */
Spray_Type* Sprays_Create();

/**
 * @brief Painter��ʼ������
 *
 * @param width �������
 * @param height �����߶�
 */
void Painter_Init(int width, int height);

/**
 * @brief Painterָ��̨
 *
 * @param handle ��Ҫ�������
 * @param wind ����
 * @param ripples �������
 * @param sprays ˮ�����
 * @param cmd ָ���ַ���
 */
void Painter_CMD(void* handle, Wind_Type* wind, Ripple_Type* ripples,
                 Spray_Type* sprays, const char* cmd);

/**
 * @brief Painter������º���
 *
 * @param delay_ms �����ˢ��ʱ��(��λ����)
 */
void Painter_Update(int delay_ms);

/**
 * @brief Painter�����ͷź���
 *
 * @param rain ����
 * @param ripples �������
 * @param sprays ˮ�����
 *
 */
void Painter_End(Raindrop_Type* rain, Ripple_Type* ripples, Spray_Type* sprays);
#endif
