#include <iostream>
#include <boost/asio.hpp>
#include <thread>

using boost::asio::ip::tcp;

void receiveMessages(tcp::socket& socket) {
    try {
        while (true) {
            char response[1024];
            size_t len = socket.read_some(boost::asio::buffer(response));
            if (len > 0) {
                std::cout << "RECEIVED: " << std::string(response, len) << std::endl;
            } else {
                break;
            }
        }
    } catch (std::exception& e) {
        std::cerr << "Exception in receiveMessages: " << e.what() << std::endl;
    }
}

void sendMessage(tcp::socket& socket) {
    try {
        std::string message;
        while (true) {
            std::getline(std::cin, message);
            boost::asio::write(socket, boost::asio::buffer(message));

            if (message == "/quit") {
                break;
            }
        }
    } catch (std::exception& e) {
        std::cerr << "Exception in sendMessage: " << e.what() << std::endl;
    }
}

int main() {
    try {
        boost::asio::io_service io_service;
        tcp::socket socket(io_service);
        tcp::resolver resolver(io_service);

        boost::asio::connect(socket, resolver.resolve({"127.0.0.1", "8080"}));

        std::thread receive_thread([&]() {
            receiveMessages(socket);
        });

        std::thread send_thread([&]() {
            sendMessage(socket);
        });

        receive_thread.join();
        send_thread.join();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}