#include "myctype.h"

int my_isdigit(char c) { return c >= '0' && c <= '9'; }

int my_isalpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }