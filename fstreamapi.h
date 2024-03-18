#include <fstream>
#include <limits>
#include <exception>

class UnableToOpenFileException : public std::exception {
    const char* what() const throw() {
        return "Unable to open file.";
    }
};

/**
 * @author Rodrigo Farinon <rfarinon@alu.ufc.br>
 * @brief A class that represents a file.
*/
class File {
    std::fstream file;
    std::string path;
    int line = 0;

    void reset(bool begin = true) {     
        file.clear();
        file.close();
        file.open(path, std::ios_base::in | std::ios_base::out);
        if(begin) {
            file.seekg(0, std::ios::beg);
            this->line = 0;   
        }
        else {
                for(int i = 0; i < line; i++) {
                file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }

public:

    /**
     * @brief Construct a new File object
     * @param path - path to the file.
     * @note The file is opened in read/write mode.
     * @note #### Example:
     * @note `File("test.txt");`
    */
    File(std::string path) {
        this->path = path;
        file.open(path, std::ios_base::in | std::ios_base::out);
        if (!file.is_open()) {
            throw UnableToOpenFileException();
        }
    }

    /**
     * @brief Set the path to the file.
     * @param path - path to the file.
     * @note #### Example:
     * @note `file.setPath("test.txt");`
    */
    void setPath(std::string path) {
        this->path = path;
        reset();
    }

    /**
     * @brief Write a string to the file.
     * @param str - string to be written.
     * @note #### Example:
     * @note `write("Hello, world!");`
    */
    void write(std::string str) {
        file << str << std::endl;
    }

    /**
     * @brief Read the next line from the file.
     * @return std::string - the line read.
     * @note #### Example:
     * @note `std::string str = file.read();`
    */
    std::string read() {
        reset(false);
        std::string str;
        std::getline(file, str);
        line++;
        return str;
    }

    /**
     * @brief Reads a specific line from the file.
     * @param line - the line to be read.
     * @return std::string - the line read.
     * @note #### Example:
     * @note `std::string str = file.readLine(5);`
    */
    std::string readLine(int Line) {
        reset();
        std::string str;
        for (int i = 0; i < Line; i++) {
            std::getline(file, str);
        }
        return str;
    }

    /**
     * @brief Reads all lines from the file.
     * @return std::string - the lines read.
     * @note #### Example:
     * @note `std::string str = file.readAll();`
    */
    std::string readAll() {
        reset();
        std::string str;
        std::string result;
        while (std::getline(file, str)) {
            result += str + "\n";
        }
        return result;
    }

    /**
     * @brief Empty the file.
     * @note #### Example:
     * @note `file.clearFile();`
    */
    void emptyFile() {
        file.close();
        file.open("test.txt", std::ios::out | std::ios::trunc);
    }

    /**
     * @brief Close the file. Destroys the object.
     * @note #### Example:
     * @note `file.close();`
    */
    void close() {
        file.close();
    }

    void operator<< (std::string str) {
        write(str);
    }

    std::string operator>> (std::string str) {
        return read();
    }
};