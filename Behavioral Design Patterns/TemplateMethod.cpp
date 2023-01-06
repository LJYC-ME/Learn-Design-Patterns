/*[ Summary ]
Template Method is a behavioral design pattern that defines the skeleton of 
an algorithm in the superclass but lets subclasses override specific steps of 
the algorithm without changing its structure.

Note: Similar to Builder whereas the Builder is a Creational Pattern.
*/

#include <iostream>
#include <string>
#include <string_view>
#include <format>
#include <vector>
#include <memory>

class DataMiner
{
public:
    virtual void hook_Preprocessing() {}; // Hooks are optional steps with empty bodies and do not have to be overriden.

    virtual bool readData(std::string_view filePath) = 0; // Fixed step 1
    virtual void analyze() = 0; // Fixed step 2

    virtual void optional_MinerVersion() const // Optional steps should have a default implementation
    { std::cout << "My Data Miner 1.0.0\n"; } 
};

class PDFDataMiner
    :public DataMiner
{
public:
    bool readData(std::string_view filePath) override
    {
        auto suffix = filePath.rfind('.');
        if (filePath.substr(suffix + 1) != "pdf")
        {
            std::cerr << "Not a PDF file\n";
            return false;
        }
        this->data = "The data read from the specific PDF file";
        return true;
    }
    void analyze() override
    {
        std::cout << std::format("[Analyze PDF] >> {}\n", this->data);
    }
protected:
    std::string data;
};

class CSVDataMiner
    :public DataMiner
{
public:
    bool readData(std::string_view filePath) override
    {
        auto suffix = filePath.rfind('.');
        if (filePath.substr(suffix + 1) != "csv")
        {
            std::cerr << "Not a CSV file\n";
            return false;
        }
        this->data = "The data read from the specific CSV file";
        return true;
    }
    void analyze() override
    {
        std::cout << std::format("[Analyze CSV] >> {}\n", this->data);
    }
protected:
    std::string data;
};

int main(int argc, char* argv[])
{
    std::string book = "A Tour of C++.pdf";

    CSVDataMiner miner_csv{};
    PDFDataMiner miner_pdf{};

    if (miner_csv.readData(book))
        miner_csv.analyze();
    else if (miner_pdf.readData(book))
        miner_pdf.analyze();
    else std::cerr << "Failed to find a proper miner!\n";
    
    return EXIT_SUCCESS;
}

