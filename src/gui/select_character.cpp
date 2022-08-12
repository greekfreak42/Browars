#include "browars/gui/select_character.hpp"

#include <fstream>

using namespace Browars;

extern unsigned width, height;

extern const std::map<std::string, sf::Font> fonts;

static const sf::Font font = fonts.at("Aquire.ttf");

static std::vector<Character> load_characters(const std::string& filepath, const unsigned horizontal_gap, const float vertical_factor);

static std::vector<std::string> load_lines_from_file(std::ifstream& file);

static void parse_names_and_texture_filenames(const std::vector<std::string>& lines, std::vector<std::string>& names, std::vector<std::string>& filenames);

SelectCharacterGUI::SelectCharacterGUI()
  : m_txt_campaign("Campaign", font, 50), m_txt_select_character("Select a character", font, 70), m_txt_basic_characters("Basic characters", font, 40),
    m_txt_heroes("Heroes", font, 40)
{
    m_txt_campaign.setFillColor(sf::Color::Red);
    m_txt_select_character.setPosition(width / 2 - m_txt_select_character.getLocalBounds().width / 2, height * 0.1);

    m_txt_basic_characters.setPosition(0, height * 0.25);

    m_txt_heroes.setPosition(0, height * 0.65);

    const std::string filepath_base = "../assets/textures/characters/";
    const char *filepath_end = "/characters.csv";

    m_basic_characters = load_characters(filepath_base + "basic" + filepath_end, 200, 0.3);
    m_heroes = load_characters(filepath_base + "heroes" + filepath_end, 300, 0.7);
}


static std::vector<Character> load_characters(const std::string& filepath, const unsigned horizontal_gap, const float vertical_factor)
{
    std::ifstream characters_file(filepath);

    std::vector<std::string> lines = load_lines_from_file(characters_file);

    characters_file.close();

    std::vector<std::string> character_names, texture_filenames;

    parse_names_and_texture_filenames(lines, character_names, texture_filenames);
    
    std::vector<Character> loaded_characters;
    loaded_characters.reserve(lines.size());

    constexpr unsigned horizontal_border_margin = 25;
    constexpr unsigned vertical_gap_between_figure_position_and_text = 270;

    for (unsigned i = 0; i < lines.size(); i++)
    {
        sf::Text character_name_as_text(character_names[i], font);
        character_name_as_text.setPosition(i*horizontal_gap + horizontal_border_margin, height*vertical_factor + vertical_gap_between_figure_position_and_text);

        sf::Texture *character_texture_ptr = new sf::Texture;
        const std::string texture_filepath_base = "../assets/textures/characters/";
        if (!character_texture_ptr->loadFromFile(texture_filepath_base + texture_filenames[i]))
        {
            throw std::runtime_error("Couldn't load texture at: " + texture_filepath_base + texture_filenames[i]);
        }

        sf::Sprite character_sprite(*character_texture_ptr);
        character_sprite.setPosition(i*horizontal_gap + horizontal_border_margin, height * vertical_factor);

        loaded_characters.emplace_back(character_name_as_text, character_texture_ptr, character_sprite);
    }

    return loaded_characters;
}

static std::vector<std::string> load_lines_from_file(std::ifstream& file)
{
    std::string line;
    std::vector<std::string> loaded_lines;

    while (std::getline(file, line)) { loaded_lines.push_back(line); }

    return loaded_lines;
}

static void parse_names_and_texture_filenames(const std::vector<std::string>& lines, std::vector<std::string>& names, std::vector<std::string>& filenames)
{
    names.reserve(lines.size());
    filenames.reserve(lines.size());

    for (const std::string& line : lines)
    {
        bool is_writing_to_filenames = false;
        std::string name, filename;

        for (const char c : line)
        {
            if (c == ' ' && is_writing_to_filenames) { continue; }
            if (c == ',')
            {
                is_writing_to_filenames = true;
                continue;
            }

            if (is_writing_to_filenames)
            {
                filename += c;
            } else
            {
                name += c;
            }
        }

        names.push_back(name);
        filenames.push_back(filename);
    }
}

void SelectCharacterGUI::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(m_txt_campaign, states);
    window.draw(m_txt_select_character, states);
    window.draw(m_txt_basic_characters, states);
    window.draw(m_txt_heroes, states);

    for (const Character& character : m_basic_characters)
    {
        window.draw(character.sprite, states);
        window.draw(character.name_as_text, states);
    }

    for (const Character& hero : m_heroes)
    {
        window.draw(hero.sprite, states);
        window.draw(hero.name_as_text, states);
    }
}