#pragma once
#include <stdlib.h>
#include <string.h>

typedef struct { int x, y; } vec2i;
typedef struct { double x, y; } vec2d;
typedef struct { double re, im; } compd;

static char atobuf[64]; /* used by ato functions (do not touch) */

/*	returns vec2i conversion of string containing two integral numbers
	returns zero-initialized vec2i if no valid conversion is perfermod */
vec2i atovec2i(const char *str, const char *delim) {
	vec2i result; int t1; char *k;
	strcpy(atobuf, str);
	k = strtok(atobuf, delim);
	if(k == NULL)return result;
	t1 = atoi(k);
	k = strtok(NULL, "");
	if(k == NULL) return result;
	result.y = atoi(k);
	result.x = t1; 
	return result;
}

vec2d atovec2d(const char *str, const char *delim) {
	vec2d result; double t1; char *k;
	strcpy(atobuf, str);
	k = strtok(atobuf, delim);
	if(k == NULL)return result;
	t1 = atof(k);
	k = strtok(NULL, "");
	if(k == NULL) return result;
	result.y = atof(k);
	result.x = t1; 
	return result;
}

compd atocompd(const char *str, const char *delim) {
	compd result; double t1; char *k;
	strcpy(atobuf, str);
	k = strtok(atobuf, delim);
	if(k == NULL)return result;
	t1 = atof(k);
	k = strtok(NULL, "");
	if(k == NULL) return result;
	result.im = atof(k);
	result.re = t1; 
	return result;
}
