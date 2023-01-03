/*[Summary]
Proxy is a structural design pattern that lets you provide a 
substitute or placeholder for another object. 
A proxy controls access to the original object, allowing you to 
perform something either before or after the request gets through 
to the original object.
*/

#include <iostream>
#include <string>
#include <format>
#include <queue>

class Downloader
{
public:
    void download(std::string url) { std::cout << "Downloading\n"; }
};

class DownloaderProxy
{
public:
    DownloaderProxy() = delete;
    DownloaderProxy(Downloader& host) :host{ host } {};
    // Same Interfaces
    void download(std::string url)
    {
        downloadCache.emplace(url); // Cache

        if (shouldFlush || downloadCache.size() > 4)
        {
            while (!this->downloadCache.empty())
            {
                auto&& target = this->downloadCache.front();
                this->host.download(target); // Parallel
                this->downloadCache.pop();
            }   
            shouldFlush = false;
        }
    }
protected:
    Downloader& host;
private:
    bool shouldFlush = false;
    std::queue<std::string> downloadCache;
};

int main(int argc, char* argv[])
{
    Downloader downloader;
    DownloaderProxy proxy{ downloader };
    proxy.download("a");
    proxy.download("b");
    proxy.download("c");
    proxy.download("d");
    proxy.download("e");
    
    return EXIT_SUCCESS;
}

