//
// Created by raytine on 2019/4/10.
//

#include "FLVHeader.h"
#include <cstdio>
#include <cstring>
#include <iostream>

FLVHeader::FLVHeader():fileType(nullptr), extraData(nullptr), version(0), streamInfo('\0'), length(0) {}

FLVHeader::FLVHeader(char *fileType_, int8_t version, int8_t streamInfo, int32_t length, char *extraData_) :
    version(version), streamInfo(streamInfo), length(length) {
    size_t fileTypeLength = std::strlen(fileType_);
    fileType = new char[fileTypeLength + 1];
    std::strcpy(fileType, fileType_);
    fileType[fileTypeLength] = '\0';

    if (extraData_ != nullptr) {
        size_t extraDataLength = std::strlen(extraData_);
        extraData = new char[extraDataLength + 1];
        std::strcpy(extraData, extraData_);
        extraData[extraDataLength] = '\0';
    } else {
		extraData = nullptr;
	}
}

FLVHeader::FLVHeader(const FLVHeader & header) {
	size_t fileTypeLength = std::strlen(header.fileType);
	fileType = new char[fileTypeLength + 1];
	std::strcpy(fileType, header.fileType);
	fileType[fileTypeLength] = '\0';

	if (header.extraData != nullptr) {
		size_t extraDataLength = std::strlen(header.extraData);
		extraData = new char[extraDataLength + 1];
		std::strcpy(extraData, header.extraData);
		extraData[extraDataLength] = '\0';
	} else {
		extraData = nullptr;
	}

	this->version = header.version;
	this->streamInfo = header.streamInfo;
	this->length = header.length;
}

FLVHeader& FLVHeader::operator=(const FLVHeader &header) {
    if (this != &header) {
        delete[](fileType);
        delete[](extraData);

        size_t fileTypeLength = std::strlen(header.fileType);
        fileType = new char[fileTypeLength + 1];
        std::strcpy(fileType, header.fileType);
        fileType[fileTypeLength] = '\0';

        if (header.extraData == nullptr) {
            extraData = nullptr;
        } else {
            size_t extraDataLength = std::strlen(header.extraData);
            extraData = new char[extraDataLength + 1];
            std::strcpy(extraData, header.extraData);
            extraData[extraDataLength] = '\0';
        }

        this->version = header.version;
        this->streamInfo = header.streamInfo;
        this->length = header.length;
    }
    return *this;
}

FLVHeader::~FLVHeader() {
    delete[](fileType);
	if (extraData != nullptr) {
		delete[](extraData);
	}
}

void FLVHeader::show() const {
	std::cout << "FLV header: "
	        //"\n\tfiletype: " << fileType << std::endl
	        //<< "\tversion:" << (int)version << std::endl
	        << "\tstream info: [audio: " << (hasAudio() ? "true" : "false")
	        << ", video: " << (hasVideo() ? "true" : "false") << "]"
	        //<< "\tlength:" << length
	        << std::endl;
}
