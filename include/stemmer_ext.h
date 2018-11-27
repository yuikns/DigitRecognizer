#ifndef __STEMMER_EXT_H__
#define __STEMMER_EXT_H__

#include "stemmer.h"
#include <vector>
#include <string>

std::vector<std::string> stemfile(const char * filename,struct stemmer * z);

std::vector<std::string> stemmail(const char * filename,struct stemmer * z);

#endif // __STEMMER_EXT_H__


