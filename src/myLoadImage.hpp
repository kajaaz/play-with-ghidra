#ifndef MYLOADIMAGE_HPP
#define MYLOADIMAGE_HPP

#include <cstring>
#include <vector>
#include "loadimage.hh"

class MyLoadImage : public LoadImage {
    std::vector<uint8_t> binaryData;
public:
    MyLoadImage(const std::string &name, const std::vector<uint8_t> &data)
    : LoadImage(name), binaryData(data) {}

    virtual void loadFill(uint1 *ptr, int4 size, const Address &addr) override {
        memcpy(ptr, binaryData.data(), std::min(size, static_cast<int4>(binaryData.size())));
    }
}

#endif // MYLOADIMAGE_HPP