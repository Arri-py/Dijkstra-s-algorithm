#include "plot.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "eval.h"
#include "lexer.h"
#include "rpn.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define WIDTH 80
#define HEIGHT 25
#define X_MIN 0
#define X_MAX (4 * M_PI)
#define Y_MIN -1.0
#define Y_MAX 1.0

void plot_function(const char *expression) {
    Lexer *lexer = lexer_init(expression);
    RPNExpression *rpn = shunting_yard(lexer);
    if (!rpn) {
        printf("n/a\n");
        lexer_free(lexer);
        return;
    }

    char grid[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid[i][j] = '.';
        }
    }

    for (int x_pixel = 0; x_pixel < WIDTH; x_pixel++) {
        double x = X_MIN + (X_MAX - X_MIN) * x_pixel / (WIDTH - 1);
        double y = eval_rpn(rpn, x);
        if (isnan(y) || y < Y_MIN || y > Y_MAX) continue;

        int y_pixel = (int)round((Y_MAX - y) * (HEIGHT - 1) / (Y_MAX - Y_MIN));
        if (y_pixel >= 0 && y_pixel < HEIGHT) {
            grid[y_pixel][x_pixel] = '*';
        }
    }

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            putchar(grid[i][j]);
        }
        putchar('\n');
    }

    rpn_free(rpn);
    lexer_free(lexer);
}