#include "script.hpp"

namespace Managers{
    void Managers::NewScript(Managers::Script script){
        ofstream file = script.file;
        std::string filepath = script.FileName;
        std::string code = script.StartCode;
        if(code == null){
            code = "using Fractal;\n 
                    public class TestScript : FractalScript\n
                    {\n
                        public void Start() \n
                        {     \n
                            \n
                        }\n

                        public void Update(float deltatime, ref Transform transform) \n
                        {\n

                        }\n
                    }"
        }
        file.open(filepath);
        file << code ;
        file.close();
    }
    void Managers::OpenScript(Managers::Script script,std::string IDE){
        std::string command  = IDE + " " + script.FileName;
    }
};