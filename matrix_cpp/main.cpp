#include "matrix.h"
#include <stdio.h>

#define SIZE 3

void handlr(int i){

    exit(0);
}

int main(int argc, char* argv[]){  

    signal(SIGINT, handlr);
    signal(SIGSTOP, handlr);

    if((argc > 1) && (!strcmp(argv[1], "test"))){
        int line;

        try{

            line = 11;
            matrix M("{{1,0,0},{0,1,0.5}}");
            cerr << "Input: \n    matrix M(\"{{1,0,0},{0,1,0.5}}\");\nOutput: \n";
            cerr << M << endl << endl;

            line += 5;
            M = M * 6;
            cerr << "Input: \n    M = M * 6;\nOutput: \n";
            cerr << M << endl << endl;
            
            line += 5;
            matrix A(6.7);
            cerr << "Input: \n    matrix A(6.7);\nOutput: \n";
            cerr << A << endl << endl;

            double* vals = new double[SIZE];
            for(int i = 0; i < SIZE; ++i){
                vals[i] = i;
            }
            line += 9;
            matrix B(vals, SIZE);  
            line += 2;
            matrix C(SIZE, vals);
            cerr << "Input: \n    matrix B(vals, SIZE);\n    matrix C(SIZE, vals);    \\\\ vals - array of double\nOutput: \n";
            cerr << B << endl << C << endl << endl;

            line += 5;
            matrix D(M);
            cerr << "Input: \n    matrix D(M);\nOutput: \n";
            cerr << D << endl << endl;

            cerr << "Input: \n    M[1]    M[2]    M[1][2]\nOutput: \n";
            line += 6;
            cerr << M[1] << endl << M[2]<< endl << M[1][2] << endl << endl;

            line += 3;
            D *= 6;
            cerr << "Input: \n    D *= 6;\nOutput: \n";
            cerr << D << endl << endl;

            line += 5;
            A = matrix::identity(SIZE);
            cerr << "Input: \n    A = matrix::identity(SIZE);\nOutput: \n";
            cerr << A << endl << endl;

            line += 5;
            B = matrix::diagonal(vals, SIZE);
            cerr << "Input: \n    B = matrix::diagonal(vals, SIZE);\nOutput: \n";
            cerr << B << endl << endl;

            cerr << "Input: \n    B.rows() B.columns()\nOutput: \n";
            line += 6;
            cerr << B.rows() << ' ' << B.columns() << endl << endl;

            line += 2;
            B.set(0, 0, 8);
            cerr << "Input: \n    B.set(0, 0, 8);\nOutput: \n";
            cerr << B << endl << endl;

        }catch(error er){
            cerr << "line " << line << endl;
            if(er.IsSyst()){
                cerr << strerror(er.GetErrno()) << endl;
            }else{
                cerr << er.GetComment() << endl;
            }
        }

    }else{
        char c;
        int size, cur;
        char *str;
        char *tempstr;
        cout << "Enter matrix in string format" << endl;
        for(;;){
            try{
                size = 16;
                cur = 0;
                str = new char[size];
                cout << "Input: ";
                c = getchar();

                if(c == '\\'){
                    char* comm = new char[5];
                    cin.getline(comm, 5);
                    comm[4] = '\0';
                    if(!strcmp(comm, "exit")){
                        delete[] comm;
                        delete[] str;

                        return 0;
                    }
                    if(!strcmp(comm, "help")){
                        cout << "Example: {{1,0,0},{0,1,0.5}} >> | 1 0   0 |\n                                | 0 1 0.5 |" << endl;
                        fflush(stdin);
                    }else{
                        cout << "Such command doesn\'t exist" << endl;
                        fflush(stdin);
                    }

                }else{

                    while(c != '\n'){
                        str[cur] = c;
                        ++cur;
                        if(cur == size){
                            size *= 2;
                            tempstr = new char[size];
                            for(int j = 0; j < cur; ++j){
                                tempstr[j] = str[j];
                            }
                            delete[] str;
                            str = tempstr;
                        }
                        c = getchar();
                    }
                    str[cur] = '\0';

                    matrix Out(str);
                    cerr << "Input: " << str << endl;
                    cerr << "Output: \n" << Out << endl;
                    delete[] str;

                }
            }catch(error er){
                cerr << "line " << 139 << endl;
                if(er.IsSyst()){
                    cerr << strerror(er.GetErrno()) << endl;
                }else{
                    cerr << er.GetComment() << endl;
                }
            }
        }
    }

    return 0;
}