#pragma once
#include "BigFloat.h"

extern void reprToValue(BigFloat* res, char* repr, unsigned int base);
extern void valueToRepr(char* res, BigFloat *value, unsigned int base);
