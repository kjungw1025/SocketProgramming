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
- Server에서 Client가 보낸 문자열을 1024의 길이로 쪼개서 recv함수를 통해 buf 배열에 받고, String형의 recvbuf에 계속 저장
- recvbuf 크기가 맨 처음에 보낸 문자열의 길이와 같아진다면 recv 중지함
- 실행 결과
<img src="https://user-images.githubusercontent.com/120318020/236194509-4bb6bacb-24ae-452b-9f1b-2ef84a9c37cb.PNG">

## Problem2-2
``` shell
문제 : Client가 보내는 계산식을 Server에서 계산하여 Client 화면에 출력
```
- Client가 작성한 Infix order 형식의 계산식을 Postfix order로 변환하여 컴퓨터에서 계산하기 쉽게끔 구성 (ex. 2+3+4 --> 23+4+)
- Postfix order로 변환한 계산식을 Stack에 넣어 계산 진행
- 계산 방법
``` shell
1.  Postfix expression을 왼쪽부터 오른쪽으로 스캔하면서 operand를 stack에 push
2.  operator를 만나면, 필요한 operand 만큼 stack으로부터 operand를 가져오는 pop 연산 수행
3.  pop한 operand에 대해 계산을 수행한 후, 결과를 다시 stack에 push
4.  이 과정을 Postfix expression을 모두 스캔할 때까지 1 ~ 3번을 반복하고, 마지막 stack의 top에 있는 값이 계산식의 결과 값
```
- 실행 결과
<img src="https://user-images.githubusercontent.com/120318020/236652797-aa346b60-6a4b-40eb-9c24-273b636293f8.PNG">
