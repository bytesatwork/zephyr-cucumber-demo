#include <cucumber-cpp/internal/CukeEngineImpl.hpp>
#include <cucumber-cpp/internal/connectors/wire/WireProtocol.hpp>
#include <cucumber-cpp/internal/connectors/wire/WireServer.hpp>
#include <iostream>

#include <zephyr/kernel.h>
#include <posix_board_if.h>

#define CUCUMBER_THREAD_STACKSIZE 0x1000
#define CUCUMBER_THREAD_PRIORITY  5

namespace
{

void cucumber_server_thread(void *, void *, void *)
{
	const std::string IP = "127.0.0.1";
	const unsigned short PORT = 3900;

	{
		::cucumber::internal::CukeEngineImpl cukeEngine;
		::cucumber::internal::JsonWireMessageCodec wireCodec;
		::cucumber::internal::WireProtocolHandler protocolHandler(wireCodec, cukeEngine);
		::cucumber::internal::TCPSocketServer tcpServer(&protocolHandler);
		tcpServer.listen(asio::ip::tcp::endpoint(asio::ip::address::from_string(IP), PORT));

		std::clog << "Listening on " << tcpServer.listenEndpoint() << std::endl;
		tcpServer.acceptOnce();
	}

	std::clog << "Disconnected. Exiting." << std::endl;
	posix_exit(0);
}

K_THREAD_DEFINE(cucumber_tid, CUCUMBER_THREAD_STACKSIZE, cucumber_server_thread, NULL, NULL, NULL,
		CUCUMBER_THREAD_PRIORITY, 0, 0);

}
