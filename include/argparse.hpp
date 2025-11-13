#include <map>
#include <string>
#include <vector>
typedef std::map<char,bool> flags;
typedef std::map<std::string,std::string> args;

class ArgParser {
    int argc;
    char**argv;
    flags f;
    args a;
    std::map<char,std::string> flagmap;
    std::map<std::string,std::string> descmap;
    std::vector<std::string> others;
public:
    ArgParser(int argc,char**argv);
    const flags& Flags() const;
    const args& Args() const;
    const std::vector<std::string>& Others() const;
    void addArg(std::string flag,char charflag='_',std::string description="",std::string _default="");
    void addFlag(char c,std::string description="");
    void addHelp();
    std::string getHelpMessage();
    bool parse();
};
