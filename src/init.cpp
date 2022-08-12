#include "browars/init.hpp"
#include "browars/gui/planet.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <random>

extern std::mt19937 randint;
extern unsigned width, height;

void Browars::init_space_bg(sf::Texture& star_texture, sf::Texture& bg, std::vector<sf::Sprite>& stars)
{

    sf::RenderTexture render_bg;
    render_bg.create(width, height);
    render_bg.clear();
    unsigned n_stars = 1000 + randint() % 1200;

    std::vector<sf::Vertex> vertices;
    vertices.reserve(n_stars);

    for (unsigned i = 0; i < n_stars; i++)
    {
        vertices.emplace_back(sf::Vector2f(randint() % width, randint() % height), sf::Color::White);
    }

    render_bg.draw(vertices.data(), vertices.size(), sf::PrimitiveType::Points);

    render_bg.display();

    bg = sf::Texture(render_bg.getTexture());

    n_stars = 300 + randint() % 500;

    stars.reserve(n_stars);

    std::map<std::string, sf::Texture> space_textures = Browars::load_space_textures();

    star_texture = space_textures["star.png"];

    for (unsigned i = 0; i < n_stars; i++)
    {
        sf::Sprite star(star_texture);
        star.setPosition(randint() % width, randint() % height);
        stars.push_back(star);
    }
}


sfe::Movie Browars::load_intro_movie()
{
    sfe::Movie movie;

    if (!movie.openFromFile("../assets/intro/intro.mp4")) { throw std::runtime_error("Couldnt't open file \"assets/intro/vid.mp4\"!"); }

    movie.fit(0, 0, width, height);

    return movie;
}

std::map<std::string, sf::Font> Browars::load_fonts()
{
    system("ls ../assets/fonts > filenames.tmp");

    std::ifstream file("filenames.tmp");
    if (!file.is_open()) { throw std::runtime_error("Couldn't open internal file: \"filenames.tmp\""); }

    std::string filename;
    std::vector<std::string> filenames;
    while (std::getline(file, filename)) { filenames.push_back(filename); }

    file.close();

    std::map<std::string, sf::Font> fonts;
    
    for (const std::string& filename : filenames)
    {
        sf::Font font;
        font.loadFromFile("../assets/fonts/" + filename);

        fonts.emplace(filename, font);
    }

    system("rm filenames.tmp");

    return fonts;
}

std::map<std::string, sf::Texture> Browars::load_space_textures()
{
    system("ls ../assets/textures/space > filenames.tmp");

    std::ifstream file("filenames.tmp");
    if (!file.is_open()) { throw std::runtime_error("Couldn't open internal file: \"filenames.tmp\""); }

    std::string filename;
    std::vector<std::string> filenames;

    while (std::getline(file, filename)) { filenames.push_back(filename); }

    file.close();

    std::map<std::string, sf::Texture> textures;

    for (const std::string& filename : filenames)
    {
        sf::Texture texture;
        texture.loadFromFile("../assets/textures/space/" + filename);

        textures.emplace(filename, texture);
    }

    system("rm filenames.tmp");

    return textures;
}

std::map<std::string, sf::Texture> Browars::load_planet_textures()
{
    std::ifstream planets_file("../assets/planets/planets.csv");

    std::string line;
    std::vector<std::string> lines;
    while (std::getline(planets_file, line)) { lines.push_back(line); }

    std::map<std::string, sf::Texture> textures;

    for (const std::string& line : lines)
    {
        std::string name;
        std::string filepath;

        bool is_reading_filepath = false;
        for (const char c : line)
        {
            if (c == ',') { is_reading_filepath = true; continue; }
            if (is_reading_filepath)
            {
                if (c == ' ') { continue; }
                filepath += c;
                continue;
            }
            name += c;
        }

        sf::Texture texture;
        
        if (!texture.loadFromFile("../assets/textures/space/" + filepath)) { throw std::runtime_error("File \"" + filepath + "\" not found!"); }

        textures.insert(std::make_pair(name, texture));
    }

    return textures;
}

std::vector<Browars::Planet> Browars::load_planets(const sf::Font& font, const std::map<std::string, sf::Texture>& planet_textures)
{
    std::ifstream planets_file("../assets/planets/planets.csv");

    std::string line;
    std::vector<std::string> lines;
    while (std::getline(planets_file, line)) { lines.push_back(line); }
    planets_file.close();

    std::vector<Planet> planets;
    planets.reserve(lines.size());

    unsigned i = 0;
    for (const std::string& line : lines)
    {
        std::string planet_name;

        for (const char c : line)
        {
            if (c == ',') { break; }
            planet_name += c;
        }

        sf::Text planet_txt(planet_name, font);

        const sf::Texture& planet_texture = planet_textures.at(planet_name);

        sf::Sprite planet_icon(planet_texture);

        constexpr float planet_margin = 200;
        constexpr float txt_margin = 7;

        const sf::FloatRect icon_bounds = planet_icon.getLocalBounds();
        const sf::FloatRect txt_bounds  = planet_txt.getLocalBounds();
        planet_icon.setPosition(width / 2 - icon_bounds.width / 2 + (planet_margin + icon_bounds.width) * i, height / 2 - icon_bounds.height / 2);
        planet_txt.setPosition(width / 2 - txt_bounds.width / 2 + (planet_margin + icon_bounds.width) * i, height / 2 + icon_bounds.height / 2 + txt_margin);

        planets.emplace_back(planet_icon, planet_txt);
        i++;
    }

    return planets;
}

sf::Texture Browars::load_map_texture(const std::string& planet_name)
{
    const std::string filepath = "../assets/textures/maps/" + planet_name + ".png";

    sf::Texture map_texture;
    if (!map_texture.loadFromFile(filepath)) { throw std::runtime_error("Couldn't load texture at " + filepath); }

    return map_texture;
}
