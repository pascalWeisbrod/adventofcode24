#include <string>   // For using string

class Helper {
public:
    Helper(void);
    ~Helper(void);
   
    int readLines(void);
    std::string readInputFile(int day);

private:
    std::string read_file(std::string file_path);
    std::string get_executing_input_file(void);
};
