// socketio-client-cpp-demo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <sio_client.h>
#include <sio_message.h>
#include <sio_socket.h>
#include <vector>


using namespace sio;
using namespace std;

std::mutex _lock;
std::condition_variable_any _cond;
bool connect_finish = false;

void OnMessage(sio::event&)
{
    std::cout << "OnMessage!\n";
}



class connection_listener
{
    sio::client& handler;

public:

    connection_listener(sio::client& h) :
        handler(h)
    {
    }


    void on_connected()
    {
        _lock.lock();
        _cond.notify_all();
        connect_finish = true;
        _lock.unlock();
    }
    void on_close(client::close_reason const& reason)
    {
        std::cout << "sio closed " << std::endl;
        exit(0);
    }

    void on_fail()
    {
        std::cout << "sio failed " << std::endl;
        exit(0);
    }
};


int main()
{
    socket::ptr current_socket;
    sio::client h;
    //connection_listener l(h);
    //h.set_open_listener(std::bind(&connection_listener::on_connected, &l));
    //h.set_close_listener(std::bind(&connection_listener::on_close, &l, std::placeholders::_1));
    //h.set_fail_listener(std::bind(&connection_listener::on_fail, &l));

    //h.socket()->on("from server", &OnMessage);

    h.connect("http://127.0.0.1:5000");
    //_lock.lock();
    //if (!connect_finish)
    //{
    //    _cond.wait(_lock);
    //}
    //_lock.unlock();
    current_socket = h.socket();
    //测试发送消息
    current_socket->emit("message_empty");
    string data_str = "哒哒哒哒哒哒";

    //string_message e = sio::string_message(data_str);
    message::list li("sports");
    li.push(string_message::create("economics"));

    current_socket->emit("message_two", li);
    //current_socket->on("connect", &OnMessage);
    while (true) {

    }

    std::cout << "Hello World!\n";
    h.sync_close();
    h.clear_con_listeners();
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
