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

#include <libprocinfo/libprocinfo.hpp>
#if defined(__libprocinfo_supported__)
#include <stdio.h>
#endif
int main() {
  #if defined(__libprocinfo_supported__)
  procid_t *pid_buf = 0; 
  std::size_t pid_len = 0; 
  procid_enum(&pid_buf, &pid_len);
  for (std::size_t i = 0; i < pid_len; i++) {
    printf("%s%zu%s%lu%s%lu\n", "pid[", i, "]: ", (unsigned long)pid_buf[i], ", pid: ", (unsigned long)pid_buf[i]);
    char *exe_buf = exe_from_procid(pid_buf[i]);
    if (exe_buf) {
      printf("%s%zu%s%lu%s%s\n", "pid[", i, "]: ", (unsigned long)pid_buf[i], ", exe: ", exe_buf);
      exe_free(exe_buf);
    }
    char *cwd_buf = cwd_from_procid(pid_buf[i]);
    if (cwd_buf) {
      printf("%s%zu%s%lu%s%s\n", "pid[", i, "]: ", (unsigned long)pid_buf[i], ", cwd: ", cwd_buf);
      cwd_free(cwd_buf);
    }
    char *comm_buf = comm_from_procid(pid_buf[i]);
    if (comm_buf) {
      printf("%s%zu%s%lu%s%s\n", "pid[", i, "]: ", (unsigned long)pid_buf[i], ", comm: ", comm_buf);
      comm_free(comm_buf);
    }
    procid_t *ppid_buf = 0; 
    std::size_t ppid_len = 0;
    pprocid_from_procid(pid_buf[i], &ppid_buf, &ppid_len);
    for (std::size_t j = 0; j < ppid_len; j++) {
      printf("%s%zu%s%lu%s%lu\n", "pid[", i, "]: ", (unsigned long)pid_buf[i], ", ppid: ", (unsigned long)ppid_buf[j]);
    }
    pprocid_free(ppid_buf);
    procid_t *cpid_buf = 0; 
    std::size_t cpid_len = 0;
    procid_from_pprocid(pid_buf[i], &cpid_buf, &cpid_len);
    for (std::size_t j = 0; j < cpid_len; j++) {
      printf("%s%zu%s%lu%s%zu%s%lu\n", "pid[", i, "]: ", (unsigned long)pid_buf[i], ", cpid[", j, "]: ", (unsigned long)cpid_buf[j]);
    }
    procid_free(cpid_buf);
    char **cmd_buf;
    std::size_t cmd_len = 0;
    cmdline_from_procid(pid_buf[i], &cmd_buf, &cmd_len);
    for (std::size_t j = 0; j < cmd_len; j++) {
      printf("%s%zu%s%lu%s%zu%s%s\n", "pid[", i, "]: ", (unsigned long)pid_buf[i], ", cmd[", j, "]: ", cmd_buf[j]);
    }
    cmdline_free(cmd_buf, cmd_len);
    char **env_buf;
    std::size_t env_len = 0;
    environ_from_procid(pid_buf[i], &env_buf, &env_len);
    for (std::size_t j = 0; j < env_len; j++) {
      printf("%s%zu%s%lu%s%zu%s%s\n", "pid[", i, "]: ", (unsigned long)pid_buf[i], ", env[", j, "]: ", env_buf[j]);
    }
    environ_free(env_buf, env_len);
  }
  procid_enum_free(pid_buf);
  #endif
  return 0;
}
