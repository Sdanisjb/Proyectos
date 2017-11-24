#include <iostream>
#include <vector>
#include <algorithm>
#include <cstddef>

//Clase Matriz con template para poder usarla tanto
//con enteros como con floats
template <typename Type> class Matrix{
    //Propiedades fiias y columnas y
    //una matriz dinamica de tipo variable
    private:
        int rows, columns;

    public:
        Type** TheMatrix;

        //Constructor
        Matrix(int filas,int columnas):
            TheMatrix(NULL),
            rows(filas),
            columns(columnas)
        {};

        //obtener filas
        int getRows(){
            return rows;
        }

        //obtener colunas
        int getColumns(){
            return columns;
        }

        //construir la Matriz
        void buildMatrix(){
            TheMatrix = new Type*[rows];

            for(int i=0;i<rows;i++){
                TheMatrix[i] = new Type[columns];
            }
        }

        //limpiar la Matriz
        void cleanMatrix(){
            for(int i=0;i<rows;i++){
                for(int j=0;j<columns;j++){
                    TheMatrix[i][j]= 0.0;
                }
            }
        }

        //insertar los datos de la matriz
        void insertData(){
            Type element;
            for(int i=0;i<rows;i++){
                for(int j= 0;j<columns;j++){
                    std::cin>>element;
                    TheMatrix[i][j] = element;
                }
            }
        }

        //imprimir la Matriz
        void printMatrix(){
            for(int i=0;i<rows;i++){
                for(int j=0;j<columns;j++){
                    std::cout<<TheMatrix[i][j]<<" ";
                }
            std::cout<<std::endl;
            }
        }



        //Ordenar la matriz
        void sortMatrix(bool desc=false){
            //inserta todos los elementos en un vector
            std::vector<Type> temp;
            for(int i=0;i<rows;i++){
                for(int j=0;j<columns;j++){
                    temp.push_back(TheMatrix[i][j]);
                }
            }

            //ordena el vector
            std::sort(temp.begin(),temp.end());

            if(desc){
                std::reverse(temp.begin(),temp.end());
            }

            //reinserta los elementos
            for(int i=0;i<rows;i++){
                for(int j=0;j<columns;j++){
                    TheMatrix[i][j] = temp[(i*rows)+j];
                }
            }



        }

        //Libera el espacio usado por la matriz
       void deleteMatrix(){
            for(int i=0;i<rows;i++){
                delete []TheMatrix[i];
            }

            delete []TheMatrix;
       }

        //Sobracarga del + pṕara sumar matrices
        Matrix operator+(Matrix<Type>& Matrix2){
            Matrix<Type> MatrixR(Matrix2.getRows(), Matrix2.getColumns());
            MatrixR.buildMatrix();
            MatrixR.cleanMatrix();
            for(int i=0;i<Matrix2.getRows();i++){
                for(int j=0;j<Matrix2.getColumns();j++){
                    MatrixR.TheMatrix[i][j] = TheMatrix[i][j] + Matrix2.TheMatrix[i][j];
                }
            }

            return MatrixR;
        }

        //Sobrecarga del - para restar matrices
        Matrix operator-(Matrix<Type>& Matrix2){
            Matrix<Type> MatrixR(Matrix2.getRows(), Matrix2.getColumns());
            MatrixR.buildMatrix();
            MatrixR.cleanMatrix();
            for(int i=0;i<Matrix2.getRows();i++){
                for(int j=0;j<Matrix2.getColumns();j++){
                    MatrixR.TheMatrix[i][j] = TheMatrix[i][j] - Matrix2.TheMatrix[i][j];
                }
            }

            return MatrixR;
        }

        //sobrecarga del * para multiplicar matrices
        Matrix operator*(Matrix<Type>& Matrix2){
            Matrix<Type> MatrixR(rows,Matrix2.getColumns());
            MatrixR.buildMatrix();
            MatrixR.cleanMatrix();
            for(int i=0;i<rows;i++){
                for(int j=0;j<Matrix2.getColumns();j++){
                    for(int k=0;k<columns;k++){
                        MatrixR.TheMatrix[i][j] = MatrixR.TheMatrix[i][j] + (TheMatrix[i][k] * Matrix2.TheMatrix[k][j]);
                    }

                }
            }

            return MatrixR;
        }

        //Sobrecarga del | para hallar el promedio de 2 matrices
        Matrix operator|(Matrix<Type>& Matrix2){
            Matrix<Type> MatrixR(Matrix2.getRows(), Matrix2.getColumns());
            MatrixR.buildMatrix();
            MatrixR.cleanMatrix();
            for(int i=0;i<Matrix2.getRows();i++){
                for(int j=0;j<Matrix2.getColumns();j++){
                    MatrixR.TheMatrix[i][j] = (TheMatrix[i][j] + Matrix2.TheMatrix[i][j])/2;
                }
            }

            return MatrixR;
        }




};



//Clase Calculadora de tipo variable
template <typename Type> class Calculator{
//tiene como miembros tres matrices que nos permitiran hacer los calculos
    private:
        Matrix<Type> Matrix1;
        Matrix<Type> Matrix2;
        Matrix<Type> MatrixR;
    public:
        Calculator(int filas1,int columnas1,int filas2,int columnas2):
            Matrix1(filas1,columnas1),
            Matrix2(filas2,columnas2),
            MatrixR(0,0) {};

        //in iciar matrices uno y 2
        void setMatrix1(){
            Matrix1.buildMatrix();
            std::cout<<"Inserte elementos de la matriz 1"<<std::endl;
            Matrix1.insertData();
        }

        void setMatrix2(){
            Matrix2.buildMatrix();
            std::cout<<"Inserte elementos de la matriz 2"<<std::endl;
            Matrix2.insertData();
        }

        //Sumar matrices con el operador +
        void addMatrix(){
            setMatrix1();
            setMatrix2();
            MatrixR = Matrix1 + Matrix2;
            std::cout<<"Matriz Resultante: "<<std::endl;
            MatrixR.printMatrix();
            Matrix1.deleteMatrix();
            Matrix2.deleteMatrix();
            MatrixR.deleteMatrix();
        }

        //REstar Matrices
        void restMatrix(){
            setMatrix1();
            setMatrix2();
            MatrixR = Matrix1- Matrix2;
            std::cout<<"Matriz Resultante: "<<std::endl;
            MatrixR.printMatrix();
            Matrix1.deleteMatrix();
            Matrix2.deleteMatrix();
            MatrixR.deleteMatrix();

        }

        //Multiplicar matrices
        void multiplyMatrix(){
            setMatrix1();
            setMatrix2();
            MatrixR = Matrix1 * Matrix2;
            std::cout<<"Matriz Resultante: "<<std::endl;
            MatrixR.printMatrix();
            Matrix1.deleteMatrix();
            Matrix2.deleteMatrix();
            MatrixR.deleteMatrix();
        }

        //Sacar el promedio de las matrices
        void promMatrix(){
            setMatrix1();
            setMatrix2();
            MatrixR = Matrix1 | Matrix2;
            std::cout<<"Matriz Resultante: "<<std::endl;
            MatrixR.printMatrix();
            Matrix1.deleteMatrix();
            Matrix2.deleteMatrix();
            MatrixR.deleteMatrix();
        }

       //ordenar la matriz
        void sortMatrix(){
            char type;
            setMatrix1();
            std::cout<<"Ordenamiento ascendiente(a) o descendiente(d)?"<<std::endl;
            std::cin>>type;

            if(type=='a'){
                Matrix1.sortMatrix(false);
            }
            else{
                Matrix1.sortMatrix(true);
            }
            std::cout<<"Matriz Resultante: "<<std::endl;
            Matrix1.printMatrix();
            Matrix1.deleteMatrix();
        }

        //imprimir el menu de seleccion
        void printMenu(){
            std::cout<<"Seleccione operacion:"<<std::endl;
            std::cout<<"1 para Suma"<<std::endl;
            std::cout<<"2 para Resta"<<std::endl;
            std::cout<<"3 para Multiplicacion"<<std::endl;
            std::cout<<"4 para Promedio"<<std::endl;
            std::cout<<"5 para ordenar la Matriz"<<std::endl;
        }

};




int main()
{
    char type;
    std::cout<<"Trabajo con enteros(e) o con flotantes(f)?";
    std::cin>>type;

    int filas1, columnas1, filas2, columnas2;

    std::cout<<"Numero de filas Matriz 1 :";
    std::cin>>filas1;

    std::cout<<"Numero de columnas Matriz 1 :";
    std::cin>>columnas1;

    std::cout<<"Numero de filas Matriz 2 :";
    std::cin>>filas2;

    std::cout<<"Numero de columnas Matriz 2 :";
    std::cin>>columnas2;

    if(type=='e'){
    //SEparar el espacio de memoria para una o utra calculadora
        Calculator<int> *miCalculadora = new Calculator<int>(filas1,columnas1,filas2,columnas2);
        int operacion;

        miCalculadora->printMenu();
        std::cin>>operacion;

        if(operacion==1){
            miCalculadora->addMatrix();
        }
        else if(operacion==2){
            miCalculadora->restMatrix();
        }
        else if(operacion==3){
            miCalculadora->multiplyMatrix();
        }
        else if(operacion==4){
            miCalculadora->promMatrix();
        }
        else if(operacion==5){
            miCalculadora->sortMatrix();
        }

        delete miCalculadora;
    }
    else{
        Calculator<float> *miCalculadora = new Calculator<float>(filas1,columnas1,filas2,columnas2);
        int operacion;

        miCalculadora->printMenu();
        std::cin>>operacion;

        if(operacion==1){
            miCalculadora->addMatrix();
        }
        else if(operacion==2){
            miCalculadora->restMatrix();
        }
        else if(operacion==3){
            miCalculadora->multiplyMatrix();
        }
        else if(operacion==4){
            miCalculadora->promMatrix();
        }
        else if(operacion==5){
            miCalculadora->sortMatrix();
        }

        delete miCalculadora;

    }

    return 0;
}
