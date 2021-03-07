#include "../../fractal.hpp"

using namespace std;

namespace Managers{
    class Script{
    public:
        struct Script{
            string StartCode;
            string FileName;
            ofstream file;
        };
        
        void NewScript(Script script);

        void OpenScript(Script script,string IDE);
};
};
