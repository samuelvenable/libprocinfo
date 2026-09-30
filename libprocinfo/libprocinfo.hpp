/*

MIT License

Copyright © 2021-2026 Samuel Venable

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#pragma once
#if ((defined(_WIN32) || defined(_WIN64)) || (defined(__APPLE__) && defined(__MACH__)) || (defined(__linux__) || defined(__ANDROID__)) || (defined(__FreeBSD__) || defined(__FreeBSD_kernel__)) || defined(__DragonFly__) || defined(__NetBSD__) || defined(__OpenBSD__) || (defined(__sun) && defined(__SVR4)))
#include <stdint.h>
#if (defined(__sun) && defined(__SVR4))
#if (((defined(INTPTR_MAX) && defined(INT64_MAX)) && INTPTR_MAX != INT64_MAX) || (!defined(INTPTR_MAX) || !defined(INT64_MAX)))
#error "Unsupported Platform! Only 64-bit Architectures are Supported on Solaris and illumos."
#endif
#endif
#if (defined(__APPLE__) && defined(__MACH__))
#include <TargetConditionals.h>
#if (!defined(TARGET_OS_OSX) || !TARGET_OS_OSX)
#error "Unsupported Platform! Supported Platforms: Windows, macOS, GNU/Linux, FreeBSD, DragonFly BSD, NetBSD, OpenBSD, Solaris, illumos, and Android."
#endif
#endif
#else
#error "Unsupported Platform! Supported Platforms: Windows, macOS, GNU/Linux, FreeBSD, DragonFly BSD, NetBSD, OpenBSD, Solaris, illumos, and Android."
#endif
#if ((defined(_WIN32) || defined(_WIN64)) || ((defined(__APPLE__) && defined(__MACH__)) && (defined(TARGET_OS_OSX) && TARGET_OS_OSX)) || (defined(__linux__) || defined(__ANDROID__)) || (defined(__FreeBSD__) || defined(__FreeBSD_kernel__)) || defined(__DragonFly__) || defined(__NetBSD__) || defined(__OpenBSD__) || ((defined(__sun) && defined(__SVR4)) && ((defined(INTPTR_MAX) && defined(INT64_MAX)) && (INTPTR_MAX == INT64_MAX))))
#if !defined(__libprocinfo_supported__)
#define __libprocinfo_supported__
#endif
#if (!defined(_WIN32) && !defined(_WIN64))
typedef int procid_t;
#else
typedef unsigned long procid_t;
#endif
#if defined(__cplusplus)
#include <vector>
#include <string>
namespace procinfo {
  procid_t procid_from_self();
  std::vector<procid_t> procid_enum();
  bool procid_exists(procid_t procid);
  bool procid_suspend(procid_t procid);
  bool procid_resume(procid_t procid);
  bool procid_kill(procid_t procid);
  std::vector<procid_t> pprocid_from_procid(procid_t procid);
  std::vector<procid_t> procid_from_pprocid(procid_t pprocid);
  std::string exe_from_procid(procid_t procid);
  std::string cwd_from_procid(procid_t procid);
  std::string comm_from_procid(procid_t procid);
  std::vector<std::string> cmdline_from_procid(procid_t procid);
  std::vector<std::string> environ_from_procid(procid_t procid);
  std::string envvar_value_from_procid(procid_t procid, std::string name);
  bool envvar_exists_from_procid(procid_t procid, std::string name);
} // namespace procinfo
#endif
#if (defined(_WIN32) || defined(_WIN64))
#define EXPORTED_FUNCTION extern "C" __declspec(dllexport)
#else
#define EXPORTED_FUNCTION extern "C" __attribute__((visibility("default")))
#endif

EXPORTED_FUNCTION  inline procid_t procid_from_self() {
  return procinfo::procid_from_self();
}

EXPORTED_FUNCTION  inline void procid_enum(procid_t **buf, std::size_t *len) {
  std::vector<procid_t> procid = procinfo::procid_enum();
  procid_t *pid = (procid_t *)malloc(procid.size() * sizeof(procid_t));
  if (buf) {
    for (std::size_t i = 0; i < procid.size(); i++) {
      pid[i] = procid[i];
    }
  }
  *buf = pid;
  *len = procid.size();
}

EXPORTED_FUNCTION inline void procid_enum_free(procid_t *buf) {
  free(buf);
}

EXPORTED_FUNCTION  inline bool procid_exists(procid_t procid) {
  return procinfo::procid_exists(procid);
}

EXPORTED_FUNCTION  inline bool procid_suspend(procid_t procid) {
  return procinfo::procid_suspend(procid);
}

EXPORTED_FUNCTION  inline bool procid_resume(procid_t procid) {
  return procinfo::procid_resume(procid);
}

EXPORTED_FUNCTION  inline bool procid_kill(procid_t procid) {
  return procinfo::procid_kill(procid);
}

EXPORTED_FUNCTION  inline void pprocid_from_procid(procid_t procid, procid_t **buf, std::size_t *len) {
  std::vector<procid_t> pprocid = procinfo::pprocid_from_procid(procid);
  procid_t *ppid = (procid_t *)malloc(pprocid.size() * sizeof(procid_t));
  if (buf) {
    for (std::size_t i = 0; i < pprocid.size(); i++) {
      ppid[i] = pprocid[i];
    }
  }
  *buf = ppid;
  *len = pprocid.size();
}

EXPORTED_FUNCTION  inline void pprocid_free(procid_t *pprocid) {
  free(pprocid);
}

EXPORTED_FUNCTION  inline void procid_from_pprocid(procid_t pprocid, procid_t **buf, std::size_t *len) {
  std::vector<procid_t> procid = procinfo::procid_from_pprocid(pprocid);
  procid_t *pid = (procid_t *)malloc(procid.size() * sizeof(procid_t));
  if (buf) {
    for (std::size_t i = 0; i < procid.size(); i++) {
      pid[i] = procid[i];
    }
  }
  *buf = pid;
  *len = procid.size();
}

EXPORTED_FUNCTION  inline void procid_free(procid_t *procid) {
  free(procid);
}

EXPORTED_FUNCTION  inline char *exe_from_procid(procid_t procid) {
  return strdup(procinfo::exe_from_procid(procid).c_str());
}

EXPORTED_FUNCTION  inline void exe_free(char *exe) {
  free(exe);
} 

EXPORTED_FUNCTION  inline char *cwd_from_procid(procid_t procid) {
  return strdup(procinfo::cwd_from_procid(procid).c_str());
}

EXPORTED_FUNCTION  inline void cwd_free(char *cwd) {
  free(cwd);
} 

EXPORTED_FUNCTION  inline char *comm_from_procid(procid_t procid) {
  return strdup(procinfo::comm_from_procid(procid).c_str());
}

EXPORTED_FUNCTION  inline void comm_free(char *comm) {
  free(comm);
} 

EXPORTED_FUNCTION  inline void cmdline_from_procid(procid_t procid, char ***buf, std::size_t *len) {
  std::vector<std::string> cmdline = procinfo::cmdline_from_procid(procid);
  *len = cmdline.size();
  char **arr = (char **)malloc(*len * sizeof(char *));
  if (!arr) return;
  for (std::size_t i = 0; i < *len; i++) {
    arr[i] = strdup(cmdline[i].c_str());
    if (!arr[i]) {
      for (int j = 0; j < i; j++) {
        free(arr[j]);
      }
      free(arr);
      return;
    }
  }
  *buf = arr;
}

EXPORTED_FUNCTION  inline void cmdline_free(char **buf, std::size_t len) {
  for (std::size_t i = 0; i < len; i++) {
    free(buf[i]);
  }
  free(buf);
}

EXPORTED_FUNCTION  inline void environ_from_procid(procid_t procid, char ***buf, std::size_t *len) {
  std::vector<std::string> environ = procinfo::environ_from_procid(procid);
  *len = environ.size();
  char **arr = (char **)malloc(*len * sizeof(char *));
  if (!arr) return;
  for (std::size_t i = 0; i < *len; i++) {
    arr[i] = strdup(environ[i].c_str());
    if (!arr[i]) {
      for (int j = 0; j < i; j++) {
        free(arr[j]);
      }
      free(arr);
      return;
    }
  }
  *buf = arr;
}

EXPORTED_FUNCTION  inline void environ_free(char **buf, std::size_t len) {
  for (std::size_t i = 0; i < len; i++) {
    free(buf[i]);
  }
  free(buf);
}

EXPORTED_FUNCTION  inline char *envvar_value_from_procid(procid_t procid, const char *name) {
  return strdup(procinfo::envvar_value_from_procid(procid, name).c_str());
}

EXPORTED_FUNCTION  inline void envvar_value_free(char *value) {
  free(value);
}

EXPORTED_FUNCTION  inline bool envvar_exists_from_procid(procid_t procid, const char *name) {
  return procinfo::envvar_exists_from_procid(procid, name);
}
#endif
