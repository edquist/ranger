#pragma once

#include <iosfwd>

#include "ranger.h"

std::ostream &operator<<(std::ostream &os, const ranger &r);
std::ostream &operator<<(std::ostream &os, const ranger::range &rr);

