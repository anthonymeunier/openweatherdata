#include "networking.h"

namespace net = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
using net::ip::tcp;

std::string Networking::httprequest(const std::string& url, const std::string& request)
{
	tcp::resolver::results_type endpoints = resolver.resolve(url, "80");
	stream.connect(endpoints);

	http::request<http::string_body> req{http::verb::get, request, 11};
	req.set(http::field::host, url);

	http::write(stream, req);

	beast::flat_buffer buffer;
	http::response<http::string_body> res;

	http::read(stream, buffer, res);
	return res.body();
}


