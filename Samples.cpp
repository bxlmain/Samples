#include <iostream>
#include <limits>
#include <iomanip>
#include <cstdlib> 
#include <ctime> 
#include <cmath>

template < typename T>
int findSecondMaxIndex(T* arr, int size) {
    if (size < 2) return -1; // Недостаточно элементов для нахождения второго максимума

    T max = std::numeric_limits<T>::min();
    T secondMax = std::numeric_limits<T>::min();
    int index = -1;

    for (int i = 0; i < size; ++i) {
        if (arr[i] > max) {
            secondMax = max;
            max = arr[i];
        }
        else if (arr[i] > secondMax && arr[i] != max) {
            secondMax = arr[i];
            index = i;
        }
    }

    return (secondMax == std::numeric_limits<T>::min()) ? -1 : index; // Возвращает -1, если второго максимума нет
}



template < typename T>
class Matrix {
private:
    T** data;
    unsigned int m;
    unsigned int n;

public:
    Matrix(unsigned int m, unsigned int n) : m(m), n(n) {
        data = new T * [m];
        for (unsigned int i = 0; i < m; ++i) {
            data[i] = new T[n];
        }
    }

    ~Matrix() {
        for (unsigned int i = 0; i < m; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

 
    void fillRandom() {
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                if constexpr (std::is_floating_point<T>::value) {
                    T randomValue = static_cast<T>(std::rand()) / static_cast<T>(RAND_MAX);
                    data[i][j] = randomValue * 10.0; 
                }
                else {
                    data[i][j] = static_cast<T>(std::rand() % 10); 
                }
            }
        }
    }

    T* operator[](unsigned int index) const {
        return data[index];
    }

    Matrix& operator+=(const Matrix& rhs) {
        
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                data[i][j] += rhs.data[i][j];
            }
        }
        return *this;
    }

    friend Matrix operator+(Matrix lhs, const Matrix& rhs) {
        lhs += rhs;
        return lhs;
    }

  
    Matrix& operator-=(const Matrix& rhs) {
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                data[i][j] -= rhs.data[i][j];
            }
        }
        return *this;
    }

    
    friend Matrix operator-(Matrix lhs, const Matrix& rhs) {
        lhs -= rhs;
        return lhs;
    }

    
    Matrix operator*(const Matrix& rhs) const {
        
    }

    bool operator==(const Matrix& rhs) const {
        
    }

    bool operator!=(const Matrix& rhs) const {
        
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        for (unsigned int i = 0; i < matrix.m; ++i) {
            for (unsigned int j = 0; j < matrix.n; ++j) {
                os << std::setw(8) << matrix.data[i][j] << " ";
            }
            os << std::endl;
        }
        return os;
    }
};

template < typename T>
class Vector {
private:
    T* data;
    unsigned int size;

public:
    
    Vector(unsigned int size) : size(size) {
        data = new T[size];
    }

    
    ~Vector() {
        delete[] data;
    }

    
    T& operator[](unsigned int index) const {
        return data[index];
    }

    
    T dot(const Vector& rhs) const {
        T result = 0;
        for (unsigned int i = 0; i < size; ++i) {
            result += data[i] * rhs.data[i];
        }
        return result;
    }

    
    Vector cross(const Vector& rhs) const {
        if (size != 3) throw std::invalid_argument("Cross product is defined only for 3D vectors.");

        Vector result(3);
        result[0] = data[1] * rhs.data[2] - data[2] * rhs.data[1];
        result[1] = data[2] * rhs.data[0] - data[0] * rhs.data[2];
        result[2] = data[0] * rhs.data[1] - data[1] * rhs.data[0];
        return result;
    }

    
    T length() const {
        T sum = 0;
        for (unsigned int i = 0; i < size; ++i) {
            sum += data[i] * data[i];
        }
        return std::sqrt(sum);
    }
};


int main() {
    
    int arr[] = { 1, 3, 5, 7, 9, 8 };
    std::cout << "Index of the second maximum is: " << findSecondMaxIndex(arr, 6) << std::endl;
    
    
    std::srand(static_cast<unsigned>(std::time(nullptr))); // Инициализация генератора случайных чисел

    // Пример использования для целых чисел
    Matrix<int> matInt(3, 3);
    matInt.fillRandom();
    std::cout << "Integer matrix:\n" << matInt << std::endl;

    // Пример использования для вещественных чисел
    Matrix<double> matDouble(3, 3);
    matDouble.fillRandom();
    std::cout << "Double matrix:\n" << matDouble << std::endl;
    Vector<double> v1(3);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;

    Vector<double> v2(3);
    v2[0] = 4; v2[1] = 5; v2[2] = 6;

    std::cout << "Dot product: " << v1.dot(v2) << std::endl;

    Vector<double> vCross = v1.cross(v2);
    std::cout << "Cross product: (" << vCross[0] << ", " << vCross[1] << ", " << vCross[2] << ")" << std::endl;

    std::cout << "Length of v1: " << v1.length() << std::endl;
 
    return 0;
}
