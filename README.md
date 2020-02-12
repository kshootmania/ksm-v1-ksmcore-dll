# ksmcore.dll
A library used in K-Shoot MANIA v1.xx.

## Compilation (with Visual Studio)
```
git clone https://github.com/m4saka/ksmcore-dll.git
git submodule update -i --recursive
mkdir build
cd build
cmake -A Win32 ..
devenv /build Release ksmcore.sln
```
