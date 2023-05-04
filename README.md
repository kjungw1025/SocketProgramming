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

## Problem1
```shell
문제 : Client에서 보낸 문자열을 Server에서 문자열의 각 문자들을 ASCII Code로 변환하여 Client 화면에 출력
```
- Vector, String을 통해 동적 할당
- Client가 입력한 문자열을 보내기 전, Server에 Client가 입력한 문자열의 길이를 우선적으로 보냄
- 긴 문자열의 경우, Client에서 1024의 길이로 쪼개서 Server에 전송하도록 구현
- Server에서 1024 크기씩 쪼개진 문자열을 recv함수를 통해 buf 배열에 받고, String형의 recvbuf에 계속 저장
- recvbuf 크기가 맨 처음에 보낸 문자열의 길이와 같아진다면 recv 중지함
- 실행 결과
<img src="https://user-images.githubusercontent.com/120318020/236194509-4bb6bacb-24ae-452b-9f1b-2ef84a9c37cb.PNG">
