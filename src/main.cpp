#include "myLoadImage.hpp"
#include "sleigh.hh"
#include "emulate.hh"
#include "context.hh"
#include <iostream>
#include <vector>

using namespace std;
using namespace ghidra;

class MyAssemblyEmit : public AssemblyEmit {
public:
    virtual void dump(const Address &addr, const std::string &mnem, const std::string &body) override {
        std::cout << addr.getShortcut() << ":" << addr.getOffset() << " " << mnem << " " << body << std::endl;
    }
};

void translateToPcode(const std::vector<uint8_t> &binaryData) {
    MyLoadImage loadImage("test_program", binaryData);
    ContextInternal context;

    Sleigh sleigh(&loadImage, &context);
    string sleighfilename = "/home/kgorna/Documents/test/play-with-ghidra/src/x86-64.sla";

    DocumentStorage docstorage;
    cout << "Opening SLEIGH file: " << sleighfilename << endl;
    Element *sleighroot = docstorage.openDocument(sleighfilename)->getRoot();
    if (sleighroot == nullptr) {
        cerr << "Failed to open or parse the SLEIGH file: " << sleighfilename << endl;
        return; // or exit
    }
    cout << "SLEIGH file loaded successfully." << endl;
    docstorage.registerTag(sleighroot);
    sleigh.initialize(docstorage);

    AddrSpace *space = sleigh.getSpaceByName("ram");
    if (space == nullptr) {
        cerr << "Failed to find 'ram' space." << endl;
        return; 
    }
    cout << "Using address space: " << space->getName() << endl;
    Address addr(space, 0x0);

    MyAssemblyEmit assemEmit;
    sleigh.printAssembly(assemEmit, addr);
}

int main() {
    std::vector<uint8_t> binaryData = {
        0xB8, 0xD2, 0x04, 0x00, 0x00, // mov eax, 1234 ; Move the value 1234 into the EAX register
        0xC3                          // ret           ; Return from the function
    };
    

    MyLoadImage loadImage("test_program", binaryData);
    ContextInternal context;
    std::string archi = loadImage.getArchType();
    cout << archi << endl;

    try {
        translateToPcode(binaryData);
    }
     catch (const ghidra::LowlevelError& e) {
        cerr << "LowlevelError: " << e.explain << endl;
    } catch (const std::exception& e) {
        cerr << "Standard Exception: " << e.what() << endl;
    } catch (...) {
        cerr << "An unknown exception occurred." << endl;
    }

    return 0;
    
}