//
// Created by raytine on 2019/4/11.
//

#ifndef TEST_FLVTAG_H
#define TEST_FLVTAG_H


#include <cstdint>
#include <ostream>
#include <string>
#include <memory>
#include "FLVBaseTagData.h"

class FLVTag {
private:
    uint8_t tagType; //1byte
    uint32_t length; //3 bytes
    uint32_t timestamp; //3 bytes
    uint32_t streamId; //4 bytes
    std::shared_ptr<FLVBaseTagData> data;

public:

    FLVTag(uint8_t tagType, uint32_t length, uint32_t timestamp, uint32_t streamId, char *data);
    FLVTag(const FLVTag & tag);
    FLVTag &operator=(const FLVTag & tag);

    ~FLVTag();

    const std::shared_ptr<FLVBaseTagData> &getData() const;

    std::string desc() const;
    std::string typeName() const;
};

#endif //TEST_FLVTAG_H
