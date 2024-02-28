#ifndef MYLOADIMAGE_HPP
#define MYLOADIMAGE_HPP

#include <cstring>
#include <vector>
#include <iostream>
#include "loadimage.hh"

using namespace std;

namespace ghidra {

class MyLoadImage : public LoadImage {
    std::vector<uint8_t> binaryData;
public:
    MyLoadImage(const std::string &name, const std::vector<uint8_t> &data)
    : LoadImage(name), binaryData(data) {}

    virtual void loadFill(uint1 *ptr, int4 size, const Address &addr) override {
        cout << "Loading data at address: " << addr.getOffset() << " with size: " << size << endl;
        memcpy(ptr, binaryData.data(), std::min(size, static_cast<int4>(binaryData.size())));
    }

    virtual std::string getArchType(void) const override {
        return "x86-64"; 
    }

    virtual void adjustVma(long adjust) override { }
    
};

}

#endif // MYLOADIMAGE_HPP