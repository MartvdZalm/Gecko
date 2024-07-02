#include <iostream>
#include <boost/asio.hpp>
#include <thread>

void receive_messages(boost::asio::ip::tcp::socket& socket)
{
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
        std::cerr << "Exception in receive_messages: " << e.what() << std::endl;
    }
}

void send_message(boost::asio::ip::tcp::socket& socket)
{
    try {
        std::string message;
        while (true) {
            std::getline(std::cin, message);
            boost::asio::write(socket, boost::asio::buffer(message));
        }
    } catch (std::exception& e) {
        std::cerr << "Exception in send_message: " << e.what() << std::endl;
    }
}

int main()
{
    std::cout << "Welcome to Gecko!" << std::endl;

    try {
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::socket socket(io_service);
        boost::asio::ip::tcp::resolver resolver(io_service);

        boost::asio::connect(socket, resolver.resolve({"127.0.0.1", "8080"}));

        if (!socket.is_open()) {
            std::cout << "Connection Failed." << std::endl;
        }

        std::thread receive_thread([&]() {
            receive_messages(socket);
        });

        std::thread send_thread([&]() {
            send_message(socket);
        });

        receive_thread.join();
        send_thread.join();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}