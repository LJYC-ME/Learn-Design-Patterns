/*[Summary]
Flyweight is a structural design pattern that lets you fit more objects into the 
available amount of RAM by sharing common parts of state between multiple objects 
instead of keeping all of the data in each object.
*/

#include <iostream>
#include <string>
#include <format>
#include <unordered_map>
#include <vector>

enum class TreeType { treeA, treeB };

struct ExtrinsicState
{
    std::string color;
    std::string area;
};

struct IntrinsicState
{
    double height;
    double age;
};

class TreeEncyclopaedia // Factor Method
{
public:

    static void init()
    {
        TreeEncyclopaedia::encyclopaedia[TreeType::treeA] = ExtrinsicState{ .color = "red", .area = "China" };
        TreeEncyclopaedia::encyclopaedia[TreeType::treeB] = ExtrinsicState{ .color = "purple", .area = "Japan" };
    }

    static const ExtrinsicState& lookUpExtrinsicState(TreeType type)
    {
        return TreeEncyclopaedia::encyclopaedia[type];
    }
protected:
    static std::unordered_map<TreeType, ExtrinsicState> encyclopaedia;
};
std::unordered_map<TreeType, ExtrinsicState> TreeEncyclopaedia::encyclopaedia{}; // init

class Tree
{
public:
    Tree() = delete;
    Tree(IntrinsicState state, TreeType type) :type{ type }, state{ state } {};

    void showInfo() const
    {
        auto&& extrinsicInfo = TreeEncyclopaedia::lookUpExtrinsicState(this->type);
        std::cout << std::format("[State]\n Height = {}\n Age = {}\n Color = {}\n Area = {}\n",
            this->state.height, this->state.age, extrinsicInfo.color, extrinsicInfo.area);
    }
protected:
    IntrinsicState state;
    TreeType type;
};

class Forest
{
public:
    void addTree(Tree tree) { this->trees.emplace_back(tree); }
    const Tree& getTree(size_t idx) { return this->trees[idx]; }
protected:
    std::vector<Tree> trees;
};

int main(int argc, char* argv[])
{
    TreeEncyclopaedia::init();

    Forest forest;
    for (int i = 0; i < 10000; ++i)
        forest.addTree(Tree(
                IntrinsicState{
                .height = 1.2,
                .age = 2.3 }, 
                static_cast<TreeType>(i % 2)));
    
    auto&& tree = forest.getTree(1);
    tree.showInfo();

    return EXIT_SUCCESS;
}

