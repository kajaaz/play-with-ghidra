# play-with-ghidra

### Config before use
```
cd ghidra/Ghidra/Features/Decompiler/src/decompile/cpp/
make libdecomp.a
```
### Build
```
g++ -std=c++11 -I/path/to/play-with-ghidra/ghidra/Ghidra/Features/Decompiler/src/decompile/cpp -o myPcodeTranslator main.cpp -static /path/to/play-with-ghidra/ghidra/Ghidra/Features/Decompiler/src/decompile/cpp/libdecomp.a 
```