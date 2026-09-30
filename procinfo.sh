#!/bin/sh
cd "${0%/*}";
if [ "$OS" = "Windows_NT" ]; then
  g++ procinfo.cpp libprocinfo/libprocinfo.cpp -o procinfo.exe -I. -std=c++17 -static-libgcc -static-libstdc++ -static -lntdll -Wl,--subsystem,console; ./procinfo.exe;
elif [ `uname -s` = "Darwin" ]; then
  clang++ procinfo.cpp libprocinfo/libprocinfo.cpp -o procinfo -I. -std=c++17 -mmacos-version-min=14.0 -arch arm64 -arch x86_64; ./procinfo;
elif [ `uname -s` = "Linux" ]; then
  if [ -f "/bin/g++" ]; then
    g++ procinfo.cpp libprocinfo/libprocinfo.cpp -o procinfo -I. -std=c++17 -static-libgcc -static-libstdc++ -static; ./procinfo;
  else
    clang++ procinfo.cpp libprocinfo/libprocinfo.cpp -o procinfo -I. -std=c++17; ./procinfo;
  fi;
elif [ `uname -s` = "FreeBSD" ]; then
  clang++ procinfo.cpp libprocinfo/libprocinfo.cpp -o procinfo -I. -std=c++17 -lelf -lkvm -lpthread -static; ./procinfo;
elif [ `uname -s` = "DragonFly" ]; then
  g++ procinfo.cpp libprocinfo/libprocinfo.cpp -o procinfo -I. -std=c++17 -static-libgcc -lkvm -lpthread -static; ./procinfo;
elif [ `uname -s` = "NetBSD" ]; then
  g++ procinfo.cpp libprocinfo/libprocinfo.cpp -o procinfo -I. -std=c++17 -static-libgcc -lkvm -lpthread -static; ./procinfo;
elif [ `uname -s` = "OpenBSD" ]; then
  clang++ procinfo.cpp libprocinfo/libprocinfo.cpp -o procinfo -I. -std=c++17 -lkvm -lpthread -static; ./procinfo;
elif [ `uname -s` = "SunOS" ]; then
  if [ `uname -o` = "illumos" ]; then
    g++ procinfo.cpp libprocinfo/libprocinfo.cpp -o procinfo -I. -std=c++17 -D__illumos__ -static-libgcc -lkvm -lproc; ./procinfo;
  else
    g++ procinfo.cpp libprocinfo/libprocinfo.cpp -o procinfo -I. -std=c++17 -static-libgcc -lkvm -lproc; ./procinfo;
  fi;
fi;
