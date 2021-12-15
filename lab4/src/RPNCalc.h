#pragma once
#define BUF_SIZE 1024
#define SEP ','

extern void createRPN(char* src, char* dst, size_t size);
extern int evalRPN(char* rpn, size_t size);
