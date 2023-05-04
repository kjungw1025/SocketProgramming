# SocketProgramming
## Environment
```shell
$ uname -a
```
Linux user-virtual-machine 5.19.0-41-generic #42~22.04.1-Ubuntu SMP PREEMPT_DYNAMIC Tue Apr 18 17:40:00 UTC 2 x86_64 x86_64 x86_64 GNU/Linux

```shell
$ gcc -v
```
Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-linux-gnu/11/lto-wrapper
OFFLOAD_TARGET_NAMES=nvptx-none:amdgcn-amdhsa
OFFLOAD_TARGET_DEFAULT=1
Target: x86_64-linux-gnu
Thread model: posix
Supported LTO compression algorithms: zlib zstd
gcc version 11.3.0 (Ubuntu 11.3.0-1ubuntu1~22.04)

### Problem1
- Client에서 보낸 문자열을 Server에서 문자열의 각 문자들을 ASCII Code로 변환하여 Client 화면에 출력
- 실행 결과
<img src="https://user-images.githubusercontent.com/120318020/236194509-4bb6bacb-24ae-452b-9f1b-2ef84a9c37cb.PNG">
