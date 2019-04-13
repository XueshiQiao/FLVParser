//
// Created by raytine on 2019/4/11.
//

#ifndef TEST_FLVVIDEOTAG_H
#define TEST_FLVVIDEOTAG_H

#include <cstdint>
#include "FLVBaseTagData.h"

class FLVVideoTag : public FLVBaseTagData {
private:
    /**
     * 1: Key frame
     * 2:
     */
    uint8_t frameType;

    /**
     * 2: Sorenson H.263
     * 3: Screen Video
     * 4: On2 VP6
     * 7: AVC
     */
    uint8_t codecId;

    /**
     *  0: AVC header
     *  1: AVC NALU
     *  2: AVC end of sequence
     */
    uint8_t avcPacketType;
    uint32_t compositionTime;
    char *body;
    uint32_t bodyLength;

public:
    FLVVideoTag(char *data, uint32_t length);
    FLVVideoTag(const FLVVideoTag &tag);
    FLVVideoTag &operator=(const FLVVideoTag &tag);
    ~FLVVideoTag();

    std::string desc() const override;
    std::string frameTypeName() const;
    std::string codecName() const;
};


#endif //TEST_FLVVIDEOTAG_H
