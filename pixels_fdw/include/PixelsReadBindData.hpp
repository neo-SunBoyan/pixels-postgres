//
// Created by liyu on 3/27/23.
//

#ifndef EXAMPLE_C_PIXELSREADBINDDATA_HPP
#define EXAMPLE_C_PIXELSREADBINDDATA_HPP


#include "PixelsReader.h"
#include "PixelsFilter.hpp"


struct PixelsReadBindData {
	std::shared_ptr<PixelsReader> initialPixelsReader;
	std::shared_ptr<TypeDescription> fileSchema;
	std::vector<std::string> files;
	std::vector<PixelsFilter*> filters;
	std::atomic<uint64_t> curFileId;
};

#endif // EXAMPLE_C_PIXELSREADBINDDATA_HPP