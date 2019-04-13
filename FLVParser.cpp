//
// Created by raytine on 2019/4/9.
//

#include "FLVParser.h"
#include "FLVHeader.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <iomanip>
#include "FLVTag.h"

char* readBytesFromStream(std::ifstream &in, const size_t length) noexcept(false) {
    char* bytes = new char[length];
    in.read(bytes, sizeof(char) * length);
	if (length > in.gcount()) {
	    throw std::string("Reach the end of the file");
	}
	return bytes;
	//or return std::shared_ptr<char>(bytes, std::unique_ptr<char>(std::default_delete<char[]>()
	// std::make_shared<char>(bytes); is wrong!! ref: https://stackoverflow.com/questions/43631415/using-shared-ptr-with-char
}

template <class T>
T readFromStream(std::ifstream &in, const size_t length_ = -1) noexcept(false) {
    size_t length = (length_ == -1 ? sizeof(T) : length_);

    char *bytes = readBytesFromStream(in, length);
    T sum = 0;
    for (int i = 0; i < length; ++i) {
        sum += ((uint8_t)*(bytes+i) << (8 * (length - i - 1)));
    }
    delete[](bytes);
    return sum;
}

std::shared_ptr<FLVHeader> parseHeader(std::ifstream &in) {
	char* fileType = readBytesFromStream(in, 3);
	auto version = readFromStream<int8_t>(in);
    auto info = readFromStream<int8_t>(in);
    auto length = readFromStream<int32_t>(in);

    return std::make_shared<FLVHeader>(fileType, version, info, length, nullptr);
}

std::shared_ptr<FLVTag> parseTag(std::ifstream &in) {
    auto type = readFromStream<uint8_t>(in);
    auto length = readFromStream<uint32_t>(in, 3);
    auto timestamp = readFromStream<uint32_t>(in, 3);
    uint32_t timestampExtended = readFromStream<uint8_t>(in);
    if (timestampExtended > 0) {
        timestamp = (timestampExtended << 24) + timestamp;
    }
    auto streamId = readFromStream<uint32_t>(in, 3);
    char *data = readBytesFromStream(in, length);

    return std::make_shared<FLVTag>(type, length, timestamp, streamId, data);
}

void FLVParser::parse() {
	std::ifstream in(filePath, std::ios::binary);
    if (in.is_open()) {
		auto header = parseHeader(in);
		header->show();
        int tagIndex = 0;
		while (true) {
		    try {
                auto previousTagSize = readFromStream<int32_t>(in);
                auto tag = parseTag(in);
                std::cout << "[" << ++tagIndex << "] \t" << tag->desc() << std::endl;
		    } catch (std::string & error) {
		        std::cout << "Exception: " << error << ", stop parsing.." << std::endl;
                break;
		    }
		}

		in.close();
    } else {
        std::cout << "can not open file :" << filePath << std::endl;
    }
}
