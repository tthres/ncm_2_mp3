#ifndef MODEL_H
#define MODEL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>

#include "aes.h"
#include "cJSON.h"

int readFileData(const char* fileName);

#ifdef __cplusplus
}
#endif

#endif // MODEL_H
