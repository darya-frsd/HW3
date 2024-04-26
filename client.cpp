#include <iostream>
#include <vector>
#include <boost/asio.hpp>
#include "asn_files/RRCSpecification.h"

using boost::asio::ip::tcp;

class RRCClient {
public:
    void sendRequest(const std::string &message) {
        boost::asio::io_context io_context;
        tcp::socket socket(io_context);
        tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234);

        try {
            socket.connect(endpoint);

            RRCSpecification::RRCConnectionSetupRequest request;
            request.subscriberId = std::vector<uint8_t>(message.begin(), message.end());

            std::vector<uint8_t> buffer;
            request.encode(buffer);

            boost::asio::write(socket, boost::asio::buffer(buffer));

            std::cout << "Request sent successfully!" << std::endl;

            std::vector<uint8_t> response_buffer(1024);
            size_t response_length = socket.read_some(boost::asio::buffer(response_buffer));

            RRCSpecification::RRCConnectionSetupComplete response;
            response.decode(std::vector<uint8_t>(response_buffer.begin(), response_buffer.begin() + response_length));

            std::cout << "Response from server: ";
            for (auto byte: response_buffer) {
                std::cout << byte;
            }
            std::cout << std::endl;

            socket.close();
        } catch (std::exception &e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }
};

int main() {
    RRCClient client;
    client.sendRequest("Hello server");
    return 0;
}
