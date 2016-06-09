udp2http
========

某些场合，我们发起的http请求必须非阻塞，但是返回结果我们并不关心，如应用程序异常报警等。这时直接使用libcurl的http接口可能会阻塞，所以可以在本机启一个udp服务，应用程序的通过简单的udp协议接口把请求发给udp服务程序，udp服务程序同步的把请求用http协议发给http服务器。 udp2http就是这样的一个服务器实现，并提供了客户调用接口 include/u2h_udp_send.hpp:u2h_udp_send. 
调用示例见 test/udp_client.cpp

项目已基本稳定，可考虑用于生产环境。

