#pragma once
#include "BigFloat.h"

extern void reprToValue(BigFloat* res, char* repr, unsigned base);
extern void valueToRepr(char* repr, BigFloat *value, unsigned base);