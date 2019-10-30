#pragma once

#include <string>

struct ranger;

void persist(std::string &s, const ranger &r);
int load(ranger &r, const char *s);

