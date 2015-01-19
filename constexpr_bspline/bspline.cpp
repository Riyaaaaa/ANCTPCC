#include<iostream>
#include<fstream>
#include<array>

struct point{
    double x,y;
};

constexpr int ORDER=3; //curve dimention + 1
constexpr int CONTROL_POINTS=5;

template <typename T, int LENGTH>
struct array{
     T v[LENGTH];
      constexpr T& operator[](size_t l){ //accessor
            return v[l];
             }
      constexpr T const& operator[](size_t l)const{ //accessor (allow writing)
             return v[l];
              }
};

constexpr double BSplineFunction(int Pi,int dim,double t,array<double,ORDER+CONTROL_POINTS> knots){
    double value_1=0,value_2=0;
    if(dim>1){
        value_1 = (t-knots[Pi])*BSplineFunction(Pi,dim-1,t,knots); //recursive
        if(knots[Pi + dim-1] - knots[Pi] == 0){
            value_1 = 0;
        } else {
            value_1 /= knots[Pi + dim - 1] - knots[Pi];
        }
        value_2 = (knots[Pi + dim] - t) * BSplineFunction(Pi+1,dim-1,t,knots);
        if(knots[Pi + dim] - knots[Pi + 1] == 0){
            value_2 = 0;
        } else {
            value_2 /= knots[Pi + dim] - knots[Pi + 1];
        }
        return value_1 + value_2;
    }
    else { // dimention 0 B-spline
        if(knots[Pi] <= t && t < knots[Pi + 1]){
            return 1;
        }
        else {
            return 0; //otherwise
        }
    }
}

template<typename T,int COLS,int ROWS>
constexpr array<array<T,COLS>,ROWS> CalmBSplineArray(int dim,array<double,CONTROL_POINTS+ORDER> knots){
    array<array<T,COLS>,ROWS> basis_functions = array<array<T,COLS>,ROWS>();
    double t_min = 0;
    double t_max = COLS - 1 - dim + 1;
    
    for(int i=0;i<ROWS;i++){
            double t = t_min + i / static_cast<double>(ROWS) * (t_max - t_min); //parametor
         for(int j=0;j<COLS;j++){
           basis_functions[i][j] = BSplineFunction(j,ORDER,t,knots); //Calm B-Spline Basis Function 
         }
    }

    return basis_functions;
}

int main(){

    constexpr int STEPS=(CONTROL_POINTS - 1 - ORDER + 2)*20; //parametor steps
    constexpr array<double,CONTROL_POINTS+ORDER> knots = {0,0,0,1,1,2,2,2}; //knot vector
    constexpr auto basis_functions = CalmBSplineArray<double,CONTROL_POINTS,STEPS>(ORDER,knots); // Partial evaluation
    point curve;
    point control_points[CONTROL_POINTS];

    std::ifstream ifs("points.txt");
    std::ofstream ofs("curve.txt");

    for(int i=0;i<CONTROL_POINTS;i++){ //input points
        ifs >> control_points[i].x;
        ifs >> control_points[i].y;
    }
    std::cout << basis_functions[0][0] << std::endl;
    
    for(int i=0;i<STEPS;i++){ //calm curve
        curve.x = curve.y = 0;
        for(int j=0;j<CONTROL_POINTS;j++){
            curve.x += basis_functions[i][j] * control_points[j].x;
            curve.y += basis_functions[i][j] * control_points[j].y;
        }
        ofs << curve.x << ' ' << curve.y << std::endl; //output
    }
    for(int i=STEPS-1;i>=0;i--){ // flip horizontal 
        curve.x = curve.y = 0;
        for(int j=0;j<CONTROL_POINTS;j++){
            curve.x += basis_functions[i][j] * control_points[j].x;
            curve.y += basis_functions[i][j] * control_points[j].y;
        }
        ofs << -curve.x << ' ' << curve.y << std::endl;
    }

    return 0;
}

