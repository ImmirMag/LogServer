#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/File.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using Poco::File;


int main(int argc, char** argv)
{

    Poco::Net::ServerSocket srv(8080); // создаём сокет TCP сервера

    string logfile_name;// /var/log/dpkg.log
    File file;

    do // Проверка на существование файла базы данных
    {
        cout << "Enter path/logfile: ";
        cin >> logfile_name;
        file = logfile_name;

        if (!file.exists())
        {
            cout << "Cannot open" << endl;
        }


    }while (!file.exists());


    cout << "Server is work ..." << endl;

    while (true)
    {
        string data_from_log = "";
        char buff[255];

        ifstream logfile(logfile_name);

        while (logfile.getline(buff,255))// считать построчно лог-файла до конца
            data_from_log = string(buff) + "<br>" + data_from_log; //добавлять эти строки в data_from_log

        Poco::Net::StreamSocket ss = srv.acceptConnection(); // создаёт соединение со следующим в порядке очереди клиентом
        Poco::Net::SocketStream str(ss); // создание объекта потока для ввода данных
        str << "HTTP/1.0 200 OK\r\n"
               "Content-Type: text/html\r\n"
               "\r\n"
               "<html>"
               "<head><title>LogInfo</title></head>"

                    "<body style='background-color: black; padding: 8px'>"
                        "<font style='color: #00FF00; font-family: Ubuntu Light'> "
                            "<b>" + data_from_log + "</b>"
                        "</font>"
                    "</body>"

               "</html>"
            << std::flush;

        logfile.close();/**/
    }

    return 0;
}






