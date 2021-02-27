#ifndef NETWORKING_H
#define NETWORKING_H

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <string>

class Networking
{
	public:
		Networking() : resolver(context), stream(context)
		{
		}

		std::string httprequest(const std::string& url, const std::string& request);
	private:
		boost::asio::io_context context;
		boost::asio::ip::tcp::resolver resolver;
		boost::beast::tcp_stream stream;
};

#endif // NETWORKING_H
