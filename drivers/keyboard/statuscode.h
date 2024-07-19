#ifndef _STATUS_CODE_H
#define _STATUS_CODE_H
#include <stdint.h>

static const int8_t OK = 1;
static const int8_t CONTROLLER_SELF_TEST_FAILED = -1;
static const int8_t INTERFACE_TEST_FAILED = -2;
static const int8_t RESET_DEVICE_FAILED = -3;
static const int8_t DISABLE_CAPSLOCK_FAILED = -4;

#endif