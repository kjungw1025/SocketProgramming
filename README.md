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
<hr/>

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
<hr/>

## Problem2-1
```shell
문제 : Client가 읽고자 하는 파일을 입력하면, Server에서 해당 파일을 찾아 파일 내용을 Client에 보내주고
       Client가 쓰고자 하는 파일의 이름과 내용을 입력하면, Server에 해당 파일을 생성
       
입력 양식
"R: filename" -> 파일이름에 대한 내용을 읽어냄
"W: filename" -> client가 보낸 내용을 해당 파일이름에 쓰라는 의미
```
- 서버측에서 vector&lt;string&gt; 형태의 데이터를 클라이언트로 전송하기 위해서 데이터 직렬화(serialize)를 하여 네트워크로 전송하고, 클라이언트측에서는 받은 데이터를 역직렬화(deserialize)하여 vector&lt;string&gt; 형태로 복원하는 방식으로 작성함
- Lyrics.txt : 파일 읽기를 위한 예시 파일
<div>
	<img src="https://github.com/kjungw1025/SocketProgramming/assets/120318020/77d38f6d-7378-459b-bd75-69e94fdaba48">
</div>
<div>
	<p>실행 결과 (빨간색 박스 : 입력 / 노란색 박스 : 결과)</p>
	<img src="https://github.com/kjungw1025/SocketProgramming/assets/120318020/4bb23799-0fdf-449b-8ecb-2ad1392d20d7">
	<img src="https://github.com/kjungw1025/SocketProgramming/assets/120318020/03b889e2-78ab-4ea2-a00d-b3cf1dfbe6f3">
	<img src="https://github.com/kjungw1025/SocketProgramming/assets/120318020/e377aa3f-9670-436f-a1b1-82623963c6c7">
</div>

<hr/>

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
<hr/>

## Problem3
``` shell
문제 : 간단한 DNS 서버를 구현하기
Server와 Client는 루프백 주소('127.0.0.1')가 아닌, 서로 다른 IP 주소를 가져야함.
Server는 아래와 같은 구조의 테이블을 구성하고
	Domain | IP
	amazon   123.133.12.45
Client에서 아래와 같은 입력을 했을 때, 서버에서 결과 값을 return
	'D: www.naver.com'  -> DB에서 Domain에 해당하는 IP 주소를 받아, 서버에서 IP주소 return
	'I: 123.456.789.123' -> DB에서 IP에서 해당하는 Domain을 받아, 서버에서 Domain return
	'W: www.naver.com 123.456.789.123' -> DB에 등록
```
- createdb.cpp를 통해 C++에서 Mysql에 접속하고 problem3라는 이름의 데이터베이스 생성 및 DNS라는 이름의 테이블 생성
- 생성한 DNS 테이블에 초기 세팅 값들을 INSERT문을 통해 넣어줌
<div>
	<img src="https://github.com/kjungw1025/SocketProgramming/assets/120318020/566bc05c-859d-4038-80d1-9997bf39e92e">
	<img src="https://github.com/kjungw1025/SocketProgramming/assets/120318020/39d297b6-e06f-4ccc-8767-377b2407f1a3">
<div/>
<div>
	<br/>
	<p>Server쪽 IP</p>
	<img src="https://github.com/kjungw1025/SocketProgramming/assets/120318020/7c374cb7-3268-417c-a892-3d09e4a3d412">
<div/>
<div>
	<br/>
	<p>Client쪽 IP</p>
	<img src="https://github.com/kjungw1025/SocketProgramming/assets/120318020/cbff1dca-d4b9-433a-a7fb-d8a2c4150aa4">
<div/>
<div>
	<br/>
	<p>Server 실행</p>
	<img src="https://github.com/kjungw1025/SocketProgramming/assets/120318020/b3ff7f4f-5cc3-4893-b997-e506b7dc68ca">
<div/>
<div>
	<br/>
	<p>Client 실행 (빨간색 박스 : 입력 / 노란색 박스 : 결과)</p>
	<img src="https://github.com/kjungw1025/SocketProgramming/assets/120318020/b3a95fce-aca7-4208-a693-ce8087ac5582">
	<img src="https://github.com/kjungw1025/SocketProgramming/assets/120318020/518f3000-d967-4673-81a3-8253922cec91">
<div/>
<div>
	<br/>
	<p>Client 실행 후, 업데이트 된 Server쪽 DB 확인</p>
	<img src="https://github.com/kjungw1025/SocketProgramming/assets/120318020/19b71ee1-092d-49e0-8dcf-1d0c1ca24cd2">
	<p>Client가 입력한 "W: www.daum.net 678.901.234.567"이 Server DB에 잘 적용된 것을 확인할 수 있다.</p>
<div/>

### 실행 영상
https://www.youtube.com/watch?v=K9PUi6IJ_IY
