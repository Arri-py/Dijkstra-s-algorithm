#include <stdio.h>
#include <string.h>

#include "plot.h"

int main() {
    char expression[256];
    if (fgets(expression, sizeof(expression), stdin)) {
        expression[strcspn(expression, "\n")] = '\0';
        plot_function(expression);
    } else {
        printf("n/a\n");
    }
    return 0;
}