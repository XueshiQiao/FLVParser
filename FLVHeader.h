//
// Created by raytine on 2019/4/10.
//

#ifndef TEST_FLVHEADER_H
#define TEST_FLVHEADER_H


#include <cstdint>

class FLVHeader {

private:
    char *fileType; //3bytes;
    int8_t version; //1byte
    int8_t streamInfo; //1byte
    int32_t length; //4 byte
    char *extraData; //maybe zero


public:
    FLVHeader();
    FLVHeader(char *fileType, int8_t version, int8_t streamInfo, int32_t length, char *extraData);
    FLVHeader(const FLVHeader &header);
    FLVHeader & operator=(const FLVHeader & header);
    ~FLVHeader();

    bool hasVideo() const { return streamInfo & 0b00000001; }

    inline bool hasAudio() const { return streamInfo & 0b00000100;}
	
	void show() const;

};


#endif //TEST_FLVHEADER_H
