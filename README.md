# nankaiQTnetwork

含有三个大作业的代码（仅实现基本功能），偶尔可能有小bug，欢迎发issue并修改
考虑到网上还没有QT版的比较成型的代码，故发布之，水平有限请多指教。



## 作业1

一个基于udp协议的服务器端和客户端程序。

客户端发送任意信息给服务器端，服务器端解析信息后，如果是time则返回时间，如果是date则返回日期。

socket11是客户端，socket12是服务器端。



## 作业2

一个SMTP服务器的服务器端。基于TCP

经过outlook2016测试通过，可以实现base64编码的附件的系统默认方式打开（QT:process）



## 作业3

一个文件传输协议，基于UDP实现对多个客户端的同时可靠传输，暂时只支持纯文本（对于非纯文本，由于UTF-8的编码异常会产生bug，如需修改可以替换这个函数或者使用base64）。这个版本暂无超时重传（如需要可以自行添加），但是有逻辑重传。每个数据包设定为1432字节。

### 协议步骤

#### Step1

- 服务器端主线程监听默认端口ph=7005（作为主线程的接收端口），等待客户端访问
- 服务器端主线程发现客户端请求<hello，客户端监听端口cp>后，选一个端口ps，开一个子线程监听该端口，发送一个UDP报文，包括<子线程所占端口ps>信息给客户端。
- 客户端收到该信息后返回\<get>到ps，服务器端子线程向cp发送信息\<filelist>，服务器端子线程发现端口收到信息后，向主线程发送信号，将其初始化。
- 服务器端子线程发送一个文本串，信息如下<序号，文件名>

#### Step2

- 客户端发送序号给服务器端，请求下载
- 服务器端发送<start,所选文件大小>给客户端，然后从第0部分发送文件，考虑到UDP的数据大小问题，定义所用的数据包数量为【文件大小/1432+1】，每发送一个1432字节的文件，客户端都要发回一个计数，再发送下一个1432字节。最后客户端先验证大小再点击保存将其载入硬盘。



## 特殊说明

部分QT版本可能存在无法正常编译的效果，本人使用的是5.13.1（对应Creator4.10.0），如果有问题请自己建工程（选上MSVC32或64）,然后导入头，源文件即可，pro文件里需要加上QT +=network。
