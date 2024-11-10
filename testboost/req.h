#pragma once

#include <boost/beast.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>


const static std::string MAIN_API = "ip-api.com";
const static std::string API_ARGUMENTS = "/json";

namespace http = boost::beast::http;

class Client {
public:
    static std::string getResponse(std::string ip, std::string domain, std::string path) {
        boost::asio::io_context io;
        boost::asio::ip::tcp::resolver resolver(io);
        boost::asio::ip::tcp::socket socket(io);

        // Подключение к серверу
        boost::asio::connect(socket, resolver.resolve(domain, "80"));

        // Создание HTTP-запроса GET
        http::request<http::string_body> req(http::verb::get, path, 11);
        req.set(http::field::host, domain);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        // Отправка запроса
        http::write(socket, req);

        // Чтение ответа
        boost::beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        http::read(socket, buffer, res);

        // Преобразование ответа в строку
        std::string response = boost::beast::buffers_to_string(res.body().data());

        // Закрытие сокета
        socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);

        return response;
    }
    static std::string postResponse(std::string domain, std::string path, std::string postData) {
        boost::asio::io_context io;
        boost::asio::ip::tcp::resolver resolver(io);
        boost::asio::ip::tcp::socket socket(io);

        // Подключение к серверу
        boost::asio::connect(socket, resolver.resolve(domain, "80"));

        // Создание HTTP-запроса GET
        http::request<http::string_body> req(http::verb::post, path, 11);
        req.set(http::field::host, domain);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        req.set(http::field::content_type, "application/json");
        req.body() = postData;
        req.prepare_payload();

        // Отправка запроса
        http::write(socket, req);

        // Чтение ответа
        boost::beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        http::read(socket, buffer, res);

        // Преобразование ответа в строку
        std::string response = boost::beast::buffers_to_string(res.body().data());

        // Закрытие сокета
        socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);

        return response;
    }
};