/*[Summary]
Decorator is a structural design pattern that lets you attach new 
behaviors to objects by placing these objects inside special wrapper 
objects that contain the behaviors.

Note: A Primary Component and several optional layers ( Decorators )
*/
#include <iostream>
#include <string>
#include <format>
#include <vector>
#include <memory>

class DataSource // interface
{
public:
    virtual void write(std::string data) = 0;
    virtual std::string& read() = 0;
};

class StringDataSource
    :public DataSource
{
public:
    StringDataSource(std::string data) :data{ data } {};

    virtual void write(std::string data) override { this->data += data; }
    virtual std::string& read() override { return this->data; }
protected:
    std::string data;
};

class BaseDecorator
{
public:
    BaseDecorator() = delete;
    BaseDecorator(std::shared_ptr<DataSource>& data) : wrapper{ data } {};

    virtual void write(std::string data) { this->wrapper->write(data); }
    virtual std::string& read() { return this->wrapper->read(); }
protected:
    std::shared_ptr<DataSource>& wrapper;
};

class CompresssDecorator
    :public BaseDecorator
{
public:
    CompresssDecorator() = delete;
    CompresssDecorator(std::shared_ptr<DataSource>& data) : BaseDecorator{ data } 
    {
        auto& d = this->wrapper->read();
        this->wrapper->write("[COMPRESSED] ");
    };

    virtual void write(std::string data) override 
    {
        data = "[COMPRESSED] " + data;
        this->wrapper->write(data); 
    }
    virtual std::string& read() override
    { 
        auto& data = this->wrapper->read(); 
        size_t oft = sizeof("[COMPRESSED] ");
        data = data.substr(0, data.size() - sizeof("[COMPRESSED] ") + 1);
        return data;
    }
};

int main(int argc, char* argv[])
{
    std::shared_ptr<DataSource> ds = std::make_shared<StringDataSource>("asd");

    CompresssDecorator compressedData{ ds };

    std::cout << compressedData.read(); // The clients will not get compressed data directly.

    return EXIT_SUCCESS;
}