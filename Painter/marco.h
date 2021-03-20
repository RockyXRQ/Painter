#ifndef __MARCO_H
#define __MARCO_H

#include <string.h>

#define TRUE 1
#define FALSE 0

#define CMD_IS_SAME(cmd_a, cmd_b) (strcmp((cmd_a), (cmd_b)) == 0)

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#endif
