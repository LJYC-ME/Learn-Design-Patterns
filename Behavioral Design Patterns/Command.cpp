/*[Summary]
Command is a behavioral design pattern that turns a request into a 
stand-alone object that contains all information about the request. 
This transformation lets you parameterize methods with different 
requests, delay or queue a request’s execution, and support undoable 
operations.
*/

#include <iostream>
#include <string>
#include <string_view>
#include <format>
#include <unordered_map>
#include <memory>
#include <cassert>

class Command
{
public:
    Command(std::string_view command) :command{ command } {};
    virtual void execute() { std::cout << command << '\n'; };
protected:
    std::string command;
};

class Button
{
public:
    virtual void click() 
    { 
        assert(this->command && "No commands bind to this button!");
        this->command->execute(); 
    }
protected:
    std::shared_ptr<Command> command = nullptr;
};

class CommandPool // Prototype
{
public:
    void addCommand(std::string_view id, std::shared_ptr<Command> command) 
    {
        this->commands[id.data()] = command;
    }

    std::shared_ptr<Command>& getCommand(const std::string commandID)
    {
        assert(this->commands.find(commandID) != this->commands.end() 
            && "Nonexistent commmand!");
        return this->commands[commandID];
    }
protected:
    std::unordered_map<std::string, std::shared_ptr<Command>> commands;
};

class Invoker
{
public:
    void addCommand(std::weak_ptr<Command> command)
    {
        this->buffer.emplace_back(command);
    }

    void invoke()
    {
        for (auto&& command : this->buffer) 
            command.lock()->execute();
        this->buffer.clear();
    }
protected:
    std::vector<std::weak_ptr<Command>> buffer;
};

int main(int argc, char* argv[])
{
    CommandPool commandPool{};
    commandPool.addCommand("copy", std::make_shared<Command>("Copy something!"));
    commandPool.addCommand("redo", std::make_shared<Command>("Redo something!"));

    Invoker commandBuffer{};
    // Each operation of the user will store in the command buffer with all of the request parameters
    commandBuffer.addCommand(commandPool.getCommand("copy"));
    commandBuffer.addCommand(commandPool.getCommand("redo"));
    commandBuffer.addCommand(commandPool.getCommand("copy"));

    commandBuffer.invoke();

    return EXIT_SUCCESS;
}

