/*Summary
Memento is a behavioral design pattern that lets you save and 
restore the previous state of an object without revealing 
the details of its implementation.
*/

#include <iostream>
#include <string>
#include <string_view>
#include <format>
#include <memory>
#include <unordered_map>
#include <chrono>
using namespace std::chrono_literals;
#include <stack>

class EditorUser;

class Editor
{
    friend EditorUser;
private:
    struct State
    {
        std::string text;
        std::string font;
        friend std::ostream& operator<<(std::ostream& os, const State& state)
        {
            os << std::format("Text: {}\nFont: {}\n", state.text, state.font);
            return os;
        }
    };
public:
    class Memento
    {
        friend Editor; // Only originator has access to all field inside the memonto
    public:
        Memento() = delete;
        Memento(const State& state) 
            :snapshot{ state }, 
            record_time{ std::chrono::system_clock::now() }
        {}
    private:
        State snapshot;
        std::chrono::system_clock::time_point record_time;
    };
public:
    Memento saveSnapshot()
    {
        return Memento{ this->state };
    }

    void restoreFromSnapshot(Memento& memo)
    {
        this->state = memo.snapshot;
    }
protected:
    State state;
};

class EditorUser
{
public:
    EditorUser() = delete;
    EditorUser(Editor& editor) :editor{ editor } {};
public:
    const Editor::State& getState() const { return this->editor.state; }
    void setText(std::string_view text)
    { 
        saveMemento();
        this->editor.state.text = text; 
    }
    void setFont(std::string_view font)
    {
        saveMemento();
        this->editor.state.font = font;
    }
    void undo()
    {
        if (this->histories.empty())
        {
            std::cerr << "No histories!\n";
            return;
        }
        this->editor.restoreFromSnapshot(this->histories.top());
        this->histories.pop();
    }
protected:
    void saveMemento()
    {
        this->histories.emplace(this->editor.saveSnapshot());
    }
protected:
    Editor& editor;
    std::stack<Editor::Memento> histories;
};

int main(int argc, char* argv[])
{
    Editor myTextEditor{};
    EditorUser user{ myTextEditor };

    user.undo();
    user.setFont("Arial");
    user.setText("Hello Word");
    std::cout << user.getState();
    // Found Error
    user.undo();
    user.setText("Hello World");
    std::cout << user.getState();

    return EXIT_SUCCESS;
}

