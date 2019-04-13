//
// Created by raytine on 2019/4/11.
//

#include "FLVAudioTag.h"
#include <algorithm>
#include <iostream>

FLVAudioTag::FLVAudioTag(char *data, uint32_t length_) {
    char *pt = data;
    soundFlags = *pt++;
    int soundFormat = (soundFlags >> 4) & 0b00001111;
    if (soundFormat == 10) { //AAC
        aacPacketType = *pt++;
    } else {
        aacPacketType = 0;
    }

    size_t length = length_ - (pt - data);
    body = new char[length];
    std::copy(pt, pt + length, body);
    delete[](data);
}

FLVAudioTag::FLVAudioTag(const FLVAudioTag &tag) {
    soundFlags = tag.soundFlags;
    aacPacketType = tag.aacPacketType;
    body = new char[tag.bodyLength];
    std::copy(tag.body, tag.body + tag.bodyLength, body);
}

FLVAudioTag &FLVAudioTag::operator=(const FLVAudioTag &tag) {
    if (this == &tag) {
        delete[](body);

        soundFlags = tag.soundFlags;
        aacPacketType = tag.aacPacketType;
        body = new char[tag.bodyLength];
        std::copy(tag.body, tag.body + tag.bodyLength, body);
    }
    return *this;
}

FLVAudioTag::~FLVAudioTag() {
    delete[](body);
}

std::string FLVAudioTag::soundFormatName() const {
    int soundFormat = (soundFlags >> 4) & 0b00001111;
    switch (soundFormat) {
        case 0:
            return "Linear PCM, platform endian";
        case 1:
            return "ADPCM";
        case 2:
            return "MP3";
        case 3:
            return "Linear PCM, litter endian";
        case 4:
        case 5:
        case 6:
            return "Nellymoser";
        case 7:
        case 8:
            return "G.711";
        case 9:
            return "Reserverd";
        case 10:
            return "AAC";
        case 11:
            return "Speex";
        case 14:
            return "MP3 8kHz";
        case 15:
            return "Device-Specific sound";
        default:
            return "Unknown sound format " + soundFormat;
    }
}

std::string FLVAudioTag::soundRateName() const {
    int sampleRate = (soundFlags & 0b00001100) >> 2;
    switch (sampleRate) {
        case 0:
            return "5.5kHz";
        case 1:
            return "11 kHz";
        case 2:
            return "22 kHz";
        case 3:
            return "44 kHz";
        default:
            return "Unknow sample rate type: " + sampleRate;
    }
}

std::string FLVAudioTag::soundSizeName() const {
    int bitDepth = (soundFlags & 0b00000010) >> 1;
    switch (bitDepth) {
        case 0:
            return "8-bit samples";
        case 1:
            return "16-bit samples";
        default:
            return "Unknow bit depth type:" + bitDepth;
    }
}

std::string FLVAudioTag::desc() const {
    return "Format:" + soundFormatName() + ", " + soundRateName() + ", " + soundSizeName()
        + ", " + (isStereo() ? "Stereo" : "Mono");
}

bool FLVAudioTag::isStereo() const {
    return soundFlags & 0b00000001;
}
