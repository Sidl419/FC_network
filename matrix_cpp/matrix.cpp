#include "matrix.h"


matrix::matrix(char* s){
    if(s[0] != '{'){
        throw error("Invalid string initialization of matrix");
    }
        
    mrows = 0;
    for(int i = 1; i < strlen(s); ++i){
        mrows += s[i] == '{';
    }
    if(mrows == 0) throw error("Invalid string initialization of matrix");

    cols = 1;
    for(int i = 1; (s[i] != '}') && (i < strlen(s)); ++i){
        cols += s[i] == ',';
    }

    int k = 0;

    elem = new double*[mrows];

    ++k;
    for(int i = 0; i < mrows; ++i){
        elem[i] = new double[cols];
        ++k;
        for(int j = 0; j < cols; ++j){
            double dec = 0;

            while((k < strlen(s)) && (s[k] <= '9') && (s[k] >= '0')){
                dec = dec * 10 + (s[k] - '0');
                ++k;
            }
            
            if(k >= strlen(s)) error("Invalid string initialization of matrix");
            if(s[k] == '.'){
                ++k;
                double frac = 0.1;
                
                while((k < strlen(s)) && (s[k] <= '9') && (s[k] >= '0')){
                    dec += (s[k] - '0') * frac;
                    frac *= 0.1;
                    ++k;
                }
            }
                
            elem[i][j] = dec;
            ++k;
        }
        ++k;
    }
}

const matrix& matrix::operator=(const matrix& nT){
    for (int i = 0; i < mrows; i++){
        delete[] elem[i];
    }
    delete[] elem;

    mrows = nT.mrows;
    cols = nT.cols;

    elem = new double*[nT.mrows];
    for (int i = 0; i < nT.mrows; i++){
        elem[i] = new double[nT.cols];
        for (int j = 0; j < nT.cols; j++)
            elem[i][j] = nT.elem[i][j];
    }

    return *this;
}

matrix matrix::identity(int n){
    matrix I(n, n);
    for(int i = 0; i < n; ++i){
        I.elem[i][i] = 1;
    }
    return I;
}

matrix matrix::diagonal(double* vals, int n){
    if(!vals){
        throw error("Can\'t make matrix from NULL pointer");
    }
    matrix D(n, n);
    for(int i = 0; i < n; ++i){
        D.elem[i][i] = vals[i];
    }
    return D;
}

matrix matrix::operator[](int i) const{
    if(mrows > i){ //return row
        return matrix(elem[i], cols);
    }else{ //return column
        double* temp = new double[mrows];
        for(int j = 0; j < mrows; ++j){
            temp[j] = elem[j][i];
        }
        matrix T(mrows, temp);
        delete[] temp;
        return T;
    }

    throw error("Invalid index");
}

matrix::matrix(const matrix &other){
    mrows = other.mrows;
    cols = other.cols;

    elem = new double*[other.mrows];
    for (int i = 0; i < other.mrows; i++){
        elem[i] = new double[other.cols];
        for (int j = 0; j < other.cols; j++)
            elem[i][j] = other.elem[i][j];
    }
}