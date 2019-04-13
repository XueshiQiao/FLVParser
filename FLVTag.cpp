//
// Created by raytine on 2019/4/11.
//

#include "FLVTag.h"
#include <iostream>
#include <iomanip>
#include "FLVDataTagFactory.h"

FLVTag::FLVTag(uint8_t tagType, uint32_t length, uint32_t timestamp, uint32_t streamId,
               char *data) : tagType(tagType), length(length), timestamp(timestamp), streamId(streamId),
               data(FLVDataTagFactory::createTagDataWith(tagType & 0b00011111, data, length)) {}

FLVTag::FLVTag(const FLVTag &tag) {
    tagType = tag.tagType;
    length = tag.length;
    timestamp = tag.timestamp;
    streamId = tag.streamId;
    data = std::make_shared<FLVBaseTagData>(*tag.data.get());
}

FLVTag & FLVTag::operator=(const FLVTag &tag) {
    if (this != &tag) {
        data = nullptr;

        tagType = tag.tagType;
        length = tag.length;
        timestamp = tag.timestamp;
        streamId = tag.streamId;
        data = std::make_shared<FLVBaseTagData>(*tag.data.get());
    }
    return *this;
}

FLVTag::~FLVTag() {
}

std::string FLVTag::typeName() const {
    switch (tagType & 0b00011111) {
        case 18:
            return "Script Tag";
        case 8:
            return "Audio Tag";
        case 9:
            return "Video Tag";
        default:
            return "!Unknown Tag";
    };
}

std::string FLVTag::desc() const {
    std::string out_string;
    std::stringstream ss;
    ss << length;

    return typeName() + ": " + data->desc() + ", \tsize:" + ss.str();
              //<< ": \n\ttype:" << (int)(std::stringtagType &0b00011111) << std::endl
              //<< ": " << data->desc() << ", \tsize:" << length << std::endl;
              //<< "\ttimestamp:" << timestamp
              //<< "\tstreamId:" << streamId << std::endl
              //<< "\tdetail:" << std::endl;

}

const std::shared_ptr<FLVBaseTagData> &FLVTag::getData() const {
    return data;
}

