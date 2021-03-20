#include <conio.h>
#include <stdlib.h>

#include "painter.h"

int main() {
    register int timer = 0;
    register int wind_flag = TRUE;
    Painter_Init(WIDTH, HEIGHT);

    Wind_Type wind;

    Lotus_Leaf_Type Leaf_A;
    Lotus_Leaf_Type Leaf_B;
    Lotus_Leaf_Type Leaf_C;
    Lotus_Leaf_Type Leaf_D;
    Lotus_Leaf_Type Leaf_E;
    Lotus_Leaf_Type Leaf_F;

    Raindrop_Type* Rain = Rain_Create();
    Ripple_Type* Ripples = Ripples_Create();
    Spray_Type* Sprays = Sprays_Create();

    Lotus_Leaf_Init(&Leaf_A, 40, 120, 100, 150, 92, 0.5f, 0.5f);
    Lotus_Leaf_Init(&Leaf_B, 80, 140, 140, 170, 92, 0.5f, 0.5f);
    Lotus_Leaf_Init(&Leaf_C, 30, 165, 90, 195, 92, 0.5f, 0.5f);
    Lotus_Leaf_Init(&Leaf_D, 130, 185, 190, 215, 92, 0.5f, 0.5f);
    Lotus_Leaf_Init(&Leaf_E, 200, 140, 260, 170, 92, 0.5f, 0.5f);
    Lotus_Leaf_Init(&Leaf_F, 240, 175, 300, 205, 92, 0.5f, 0.5f);

    Wind_Init(&wind, FALSE, 1);

    // 按任意键退出
    while (!_kbhit()) {
        if ((timer++) > (500 + (rand() % 300))) {
            if (wind_flag) {
                Painter_CMD(NULL, &wind, NULL, NULL, "wind_off");
                Painter_CMD(NULL, &wind, NULL, NULL, "raindrop_less");
            } else {
                Painter_CMD(NULL, &wind, NULL, NULL, "wind_on");
                Painter_CMD(NULL, &wind, NULL, NULL, "raindrop_more");
            }
            wind_flag = !wind_flag;
            timer = 0;
        }

        if ((!(timer % 250)) && (rand() % 2)) {
            Painter_CMD(NULL, NULL, NULL, NULL, "flash_bang");
        }

        Painter_CMD(NULL, NULL, Ripples, NULL, "ripples");
        Painter_CMD(&Leaf_A, NULL, NULL, NULL, "lotus_leaf");
        Painter_CMD(&Leaf_B, NULL, NULL, NULL, "lotus_leaf");
        Painter_CMD(&Leaf_C, NULL, NULL, NULL, "lotus_leaf");
        Painter_CMD(&Leaf_D, NULL, NULL, NULL, "lotus_leaf");
        Painter_CMD(&Leaf_E, NULL, NULL, NULL, "lotus_leaf");
        Painter_CMD(&Leaf_F, NULL, NULL, NULL, "lotus_leaf");
        Painter_CMD(NULL, NULL, NULL, Sprays, "sprays");
        Painter_CMD(Rain, &wind, Ripples, Sprays, "rain");

        Painter_Update(15);
    }

    Painter_End(Rain, Ripples, Sprays);
}