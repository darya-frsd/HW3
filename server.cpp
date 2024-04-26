#include <iostream>
#include <vector>
#include <boost/asio.hpp>
#include "asn_files/RRCSpecification.h"

using boost::asio::ip::tcp;

class RRCHandler {
public:
    void handleRequest(tcp::socket& socket) {
        try {
            std::vector<uint8_t> request_buffer(1024);
            size_t request_length = socket.read_some(boost::asio::buffer(request_buffer));

            RRCSpecification::RRCConnectionSetupRequest request;
            request.decode(std::vector<uint8_t>(request_buffer.begin(), request_buffer.begin() + request_length));

            std::cout << "Received request from client: ";
            for (auto byte : request_buffer) {
                std::cout << byte;
            }
            std::cout << std::endl;

            RRCSpecification::RRCConnectionSetupComplete response;
            response.subscriberId = request.subscriberId;

            std::vector<uint8_t> response_buffer;
            response.encode(response_buffer);

            boost::asio::write(socket, boost::asio::buffer(response_buffer));
        } catch (std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }
};

int main() {
    try {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 1234));

        std::cout << "Server is running..." << std::endl;

        while (true) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            std::cout << "Connection established with client!" << std::endl;

            RRCHandler handler;
            handler.handleRequest(socket);
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
