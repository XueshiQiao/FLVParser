//
// Created by raytine on 2019/4/11.
//

#ifndef TEST_FLVAUDIOTAG_H
#define TEST_FLVAUDIOTAG_H

#include <cstdint>
#include "FLVBaseTagData.h"
#include <string>

class FLVAudioTag : public FLVBaseTagData {
private:
    uint8_t soundFlags;
    uint8_t aacPacketType;
    char *body;
    uint32_t bodyLength;

public:
    FLVAudioTag(char *data, uint32_t length);
    FLVAudioTag(const FLVAudioTag & tag);
    FLVAudioTag &operator= (const FLVAudioTag &tag);
    ~FLVAudioTag();

    std::string desc() const override;
    std::string soundFormatName() const;
    std::string soundRateName() const;
    std::string soundSizeName() const;
    bool isStereo() const;

};


#endif //TEST_FLVAUDIOTAG_H
