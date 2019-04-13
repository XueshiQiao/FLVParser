//
// Created by raytine on 2019/4/11.
//

#include <algorithm>
#include <iostream>
#include <cstring>
#include "FLVVideoTag.h"

FLVVideoTag::FLVVideoTag(char *data, uint32_t length_) {
    char* pt = data;
    frameType = (*pt >> 4) & 0b00001111;
    codecId = *pt & 0b00001111;
    pt++;
    if (codecId == 7) { //AVC
        avcPacketType = (uint8_t)*pt;
        pt++;

        compositionTime = (*pt << 16) + (*(pt+1) << 8) + *(pt+2);
        pt += 3;
    }

    size_t length = length_ - (pt - data);
    body = new char[length];
    std::copy(pt, data+ length_, body);
    delete[](data);
}

FLVVideoTag::FLVVideoTag(const FLVVideoTag &tag) {
    frameType = tag.frameType;
    codecId = tag.codecId;
    avcPacketType = tag.avcPacketType;
    compositionTime = tag.compositionTime;
    bodyLength = tag.bodyLength;
    body = new char[bodyLength];
    std::copy(tag.body, tag.body + bodyLength, body);
}

FLVVideoTag &FLVVideoTag::operator=(const FLVVideoTag &tag) {
    if (this == &tag) {
        delete[](body);

        frameType = tag.frameType;
        codecId = tag.codecId;
        avcPacketType = tag.avcPacketType;
        compositionTime = tag.compositionTime;
        bodyLength = tag.bodyLength;
        body = new char[bodyLength];
        std::copy(tag.body, tag.body + bodyLength, body);
    }
    return *this;
}

FLVVideoTag::~FLVVideoTag() {
    delete[](body);
}

std::string FLVVideoTag::desc() const {
    return "Format:" + codecName() + ", " + frameTypeName();
}

std::string FLVVideoTag::frameTypeName() const {
    switch (frameType) {
        case 1:
            return "Key Frame";
        case 2:
            return "Inter Frame";
        case 3:
            return "Disposable Inter Frame";
        case 4:
            return "Generated Key Frame";
        case 5:
            return "Video info / command frame";
        default:
            return "Unknown frame type";
    }
}

std::string FLVVideoTag::codecName() const {
    switch (codecId) {
        case 7:
            return "AVC";
        default:
            return "Other";
    }
}
