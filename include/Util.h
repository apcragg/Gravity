#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Util
{
    public:
        static std::string load_file(const std::string& p_file_name, const std::string& p_file_extension)
        {
            std::string file_text;
            std::ifstream in_file;

            std::string path = std::string("./res/");

            in_file.open(path.append(p_file_name).append(p_file_extension).c_str());

            if(in_file.is_open())
            {
                while(in_file.good())
                {
                    std::string line;
                    std::getline(in_file, line);
                    file_text.append(line + "\n");
                }
            }

            in_file.close();

            return file_text;
        }

        static size_t find_first_char(const std::string& p_search_string)
        {
            for(size_t i = 0; i < p_search_string.size(); i++)
            {
                char cmp = p_search_string.at(i);

                if(cmp == ' ');
                else
                    return i;

            }

            return p_search_string.size();
        }

        static size_t find_first_whitespace(const std::string& p_search_string, size_t p_pos = 0)
        {
            for(size_t i = p_pos; i < p_search_string.size(); i++)
            {
                char cmp = p_search_string.at(i);

                if(cmp != ' ');
                else
                    return i;

            }

            return p_search_string.size();
        }

        static std::string num_to_str(float p_num)
        {
            std::stringstream s;
            s << p_num;
            return s.str();
        }
    protected:
    private:
};

#endif // UTIL_H
