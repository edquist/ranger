#pragma once

#include <string>

struct ranger;

void persist(std::string &s, const ranger &r);
void persist_slice(std::string &s, const ranger &r, int start, int back);
void persist_range(std::string &s, const ranger &r, const ranger::range &rr);
int load(ranger &r, const char *s);

