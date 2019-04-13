//
// Created by raytine on 2019/4/13.
//

#ifndef TEST_FLVDATATAGFACTORY_H
#define TEST_FLVDATATAGFACTORY_H

#include <cstdint>
#include <memory>
#include "FLVBaseTagData.h"

class FLVDataTagFactory {
public:
    static std::shared_ptr<FLVBaseTagData> createTagDataWith(uint8_t type, char *data, uint32_t length);

};


#endif //TEST_FLVDATATAGFACTORY_H
