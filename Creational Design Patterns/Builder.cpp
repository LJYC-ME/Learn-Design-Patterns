/*[Summary]
Builder is a creational design pattern that lets you construct
complex objects step by step. The pattern allows you to produce
different types and representations of an object using the same
construction code.
*/

#include <iostream>
#include <vector>
#include <string>

using Coord2D = std::pair<int, int>;

class PatternBuilder;
class Pattern
{
    friend PatternBuilder;
public:
    Pattern() = default;

    std::vector<Coord2D> coordinates;
    std::vector<char> elements;
};

class PatternBuilder
{
public:
    PatternBuilder& drawElement(Coord2D coordinate, char element)
    {
        this->pattern.coordinates.emplace_back(coordinate);
        this->pattern.elements.emplace_back(element);
        return *this;
    }

   Pattern build()
    {
       // pattern.reset();
        return pattern;
    }
private:
    Pattern pattern;
};

class PatternDirector
{
public:
    PatternDirector& drawCross(PatternBuilder& builder, Coord2D center)
    {
        builder.drawElement(center, '*')
                .drawElement({ center.first - 1, center.second }, '+')
                .drawElement({ center.first + 1, center.second }, '+')
                .drawElement({ center.first, center.second - 1 }, '+')
                .drawElement({ center.first, center.second + 1 }, '+');
        return *this;
    }
};

class Canvas
{
public:
    Canvas() = delete;
    Canvas(uint32_t width, uint32_t height)
    {
        this->canvas.resize(height);
        for (auto& row : this->canvas) row = std::string(width, ' ');
    }

    void drawSomething(const Pattern& pattern)
    {
        for (size_t i = 0; i < pattern.coordinates.size(); ++i)
        {
            const Coord2D& coord = pattern.coordinates[i];
            this->canvas[coord.second][coord.first] = pattern.elements[i];
        }
    }

    void render()
    {
        for (const auto& row : canvas) std::cout << row << std::endl;
    }
private:
    std::vector<std::string> canvas;
};

int main(int argc, char argv[])
{
    Canvas canvas{ 10,5 };

    PatternBuilder pattern_builder;
    PatternDirector pattern_director;
    pattern_director.drawCross(pattern_builder, { 1,1 })
                    .drawCross(pattern_builder, { 7,3 });
    Pattern stars = pattern_builder.build();

    canvas.drawSomething(stars);
    canvas.render();

    return EXIT_SUCCESS;
}