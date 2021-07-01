#include <iostream>

using namespace std;

class error{
    bool syst;
    int errCode;
    char *comment;

    static char* strdup(const char* str){
        char* res = new char[strlen(str) + 1];
        strcpy(res, str);
        return res;
    }

public:
    error(const char *cmt, bool exsyst=0){
        syst = exsyst;
        errCode = errno;
        comment = strdup(cmt);
    }

    error(const error &other){
        syst = other.syst;
        errCode = other.errCode;
        comment = strdup(other.comment);
    }

    ~error(){
        delete[] comment;
    }

    bool IsSyst() const{
        return syst;
    }

    const char* GetComment() const{
        return comment;
    }

    int GetErrno() const{
        return errCode;
    }
};

class matrix {

    int mrows;
    int cols;
    double ** elem;

public:

    matrix(int n=3, int m=3){
        if((n < 1) || (m < 1)){
            throw error("Invalid size of matrix");
        }
        mrows = n;
        cols = m;
        elem = new double*[n];
        for (int i = 0;i < n; i++){
            elem[i] = new double[m];
            for (int j = 0; j < m; j++)
                elem[i][j] = 0.0;
        }
    }

    matrix(double n){
        mrows = 1;
        cols = 1;
        elem = new double*[1];
        elem[0] = new double[1];
        elem[0][0] = n;
    }

    matrix(double* s, int m){
        if(!s){
            throw error("Can\'t make matrix from NULL pointer");
        }
        if(m < 1){
            throw error("Invalid size of matrix");
        }
        cols = m;
        mrows = 1;
        elem = new double*[1];
        elem[0] = new double[m];
        for(int i = 0; i < m; ++i){
            elem[0][i] = s[i];
        }
    } 

    matrix(int n, double* s){
        if(!s){
            throw error("Can\'t make matrix from NULL pointer");
        }
        if(n < 1){
            throw error("Invalid size of matrix");
        }
        cols = 1;
        mrows = n;
        elem = new double*[n];
        for(int i = 0; i < n; ++i){
            elem[i] = new double[1];
            elem[i][0] = s[i];
        }
    }

    matrix(char* s);

    matrix(const matrix &other);

    ~matrix(){
        for (int i = 0; i < mrows; i++){
            delete[] elem[i];
        }
        delete[] elem;
    }
    
    matrix operator[](int i) const;

    friend ostream& operator<<(ostream& s, const matrix& M){
        for (int i = 0; i < M.mrows; i++){
            for(int j = 0; j < M.cols; j++)
                cout << M.elem[i][j] << " ";
            cout << endl;
        }
        return s;
    }

    static matrix identity(int n);
    static matrix diagonal(double* vals, int n);

    int rows() const{
        return mrows;
    }
    int columns() const{
        return cols;
    }

    void set(int i, int j, double val){
        if((i >= mrows) || (j >= cols) || (i < 0) || (j < 0)){
            throw error("Invalid matrix index");
        }
        elem[i][j] = val;
    }

    matrix operator*(double sc) const{
        matrix T(mrows, cols);
        for (int i = 0; i < mrows; i++){
            for (int j = 0; j < cols; j++){
                T.elem[i][j] = elem[i][j] * sc;
            }
        }
        return T;
    }

    const matrix& operator*=(double sc){
        for (int i = 0; i < mrows; i++){
            for (int j = 0; j < cols; j++)
                elem[i][j] *= sc;
        }
        return *this;
    }

    const matrix& operator=(const matrix& nT);
};