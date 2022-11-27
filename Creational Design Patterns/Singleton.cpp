/*[Summary]
Singleton is a creational design pattern that lets you ensure that a class 
has only one instance, while providing a global access point to this instance.
*/

#include <iostream>

class Database
{
public:
	static Database& getInstance() // Note that you should add thread lock while working in multithread.
	{
		static Database database{};
		return database;
	}

	void showVersion() { std::cout << this->VERSION << std::endl; }

private:
	const char* VERSION = "V1";

private:
	Database() {};
	~Database() {};
	Database(const Database& copier) = delete;
	Database& operator=(const Database& another) = delete;
};

int main(int argc, char* argv[])
{
	Database::getInstance().showVersion();

	return EXIT_SUCCESS;
}