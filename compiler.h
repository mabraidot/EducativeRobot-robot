#ifndef COMPILER_H
#define COMPILER_H

class Compiler {

    public:
        
        Compiler() {};

        void init(void);
        void run(void);
    
    private:
    
        byte _action = 0;
        
};

extern Compiler compiler;

#endif //COMPILER_H