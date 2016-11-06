/*
 * logging.cpp
 *
 *  Created on: Oct 3, 2016
 *      Author: nullifiedcat
 */

#include "logging.h"

#include <stdarg.h>
#include <string.h>

#include "fixsdk.h"
#include <icvar.h>

namespace interfaces {
ICvar* cvar;
}

FILE* logging::handle = 0;

void logging::Initialize() {
	logging::handle = fopen("/tmp/uran.log", "w");
}

void logging::Info(const char* fmt, ...) {
	if (logging::handle == 0) return;
	char buffer[1024];
	va_list list;
	va_start(list, fmt);
	vsprintf(buffer, fmt, list);
	va_end(list);
	size_t length = strlen(buffer);
	char* result = new char[length + 9];
	sprintf(result, "[Hack] %s\n", buffer);
	fprintf(logging::handle, "%s", result);
	fflush(logging::handle);
	if (interfaces::cvar) {
		interfaces::cvar->ConsolePrintf("%s", result);
	}
	delete result;
}

void logging::Shutdown() {
	fclose(logging::handle);
	logging::handle = 0;
}