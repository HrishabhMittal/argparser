#include <map>
#include <string>
#include <vector>
typedef std::map<char,bool> flags;
typedef std::map<std::string,std::string> args;
#include <iostream>

class ArgParser {
    int argc;
    char**argv;
    flags f;
    args a;
    std::map<char,std::string> flagmap;
    std::map<std::string,std::string> descmap;
    std::vector<std::string> others;
public:
    ArgParser(int argc,char**argv): argc(argc),argv(argv) {}
    const flags& Flags() const {
        return f;
    }
    const args& Args() const {
        return a;
    }
    const std::vector<std::string>& Others() const {
        return others;
    }
    void addArg(std::string flag,char charflag='_',std::string description="",std::string _default="") {
        a[flag]=_default;
        if (charflag!='_') flagmap[charflag]=flag;
        if (description!="") descmap[flag]=description;
    }
    void addFlag(char c) {
        f[c]=0;
    }
    void addHelp() {
        addArg("help",'h',"");
    }
    std::string getHelpMessage() {
        std::string msg="Options:\n";
        for (const auto& p:a) {
            msg+="  --"+p.first;
            for (const auto& q:flagmap) {
                if (q.second==p.first) {
                    msg+=", -";
                    msg+=q.first;
                    msg+="    ";
                    msg+=descmap[p.first];
                    break;
                }
            }
            msg+="\n";
        }
        return msg;
    }
    bool parse() {
        for (int i=0;i<argc;i++) {
            std::string arg=argv[i];
            if (arg.size()==0) continue;
            if (arg[0]=='-') {
                if (arg.size()==1) {
                    return false;
                } else if (arg[1]=='-') {
                    int eq=arg.find('=');
                    if (eq!=std::string::npos) {
                        std::string key=arg.substr(2,eq-2);
                        std::string value=arg.substr(eq+1);
                        if (a.count(key)==0) return false;
                        a[key]=value;
                    } else {
                        std::string key=arg.substr(2);
                        if (i+1>=argc) return false;
                        if (a.count(key)==0) return false;
                        a[key]=argv[++i];
                    }
                } else {
                    if (arg.size()>2) {
                        if (flagmap.count(arg[1])==0) return false;
                        a[flagmap[arg[1]]]=arg.substr(2);
                    } else {
                        if (f.count(arg[1])) {
                            f[arg[1]]=1;
                        } else {
                            if (i+1>=argc) return false;
                            if (flagmap.count(arg[1])==0) return false;
                            a[flagmap[arg[1]]]=argv[++i];
                        }
                    }
                }
            } else {
                others.push_back(arg);
            }
        }
        return true;
    }
};