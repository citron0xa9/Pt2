#include <iostream>
#include <cassert>
#include <cmath>
#include <stdlib.h>     
#include <time.h>       

#include <vector>
class Vector3d {
public:
	//ctor's
	Vector3d(): x_{0.0}, y_{0.0}, z_{0.0} {}
	Vector3d(double x, double y, double z): x_{x}, y_{y}, z_{z} {}
	Vector3d(const Vector3d &v): x_{v[0]}, y_{v[1]}, z_{v[2]} {} //copy ctor
	//dtor
	virtual ~Vector3d() {}

	//operators
	double operator[](uint8_t i) const
	{
		assert(i<3);
		switch(i) {
			case 0: return x_;
			case 1: return y_;
			case 2: return z_;
			default: assert(0);	//should never be reached
		}
	}

	Vector3d operator+(const Vector3d& v) const
	{
		return Vector3d{x_+v[0], y_+v[1], z_+v[2]};
	}

	Vector3d operator-(const Vector3d& v) const
	{
		return Vector3d{x_-v[0], y_-v[1], z_-v[2]};
	}

	Vector3d operator-() const
	{
		return Vector3d{-x_, -y_, -z_};
	}	

	Vector3d operator*(double scalar) const
	{
		return Vector3d{x_*scalar, y_*scalar, z_*scalar};
	}

	Vector3d operator/(double scalar) const
	{
		assert(scalar);
		return Vector3d{x_/scalar, y_/scalar, z_/scalar};
	}

	Vector3d& operator=(const Vector3d& v)
	{
		x_ = v[0];
		y_ = v[1];
		z_ = v[2];
		return *this;
	}

	Vector3d& operator+=(const Vector3d &v)
	{
		*this = *this + v;
		return *this;
	}

	Vector3d& operator-=(const Vector3d &v)
	{
		*this = *this - v;
		return *this;
	}

	Vector3d& operator*=(double scalar)
	{
		*this = *this*scalar;
		return *this;
	}

	Vector3d& operator/=(double scalar)
	{
		*this = *this/scalar;
		return *this;
	}

	bool operator!=(const Vector3d& v) const
	{
		return ( (x_!=v[0]) ||
		     (y_!=v[1]) ||
		     (z_!=v[2]) );
	}

	inline bool operator==(const Vector3d& v) const
	{
		//simply call operator!=
		//with inline it is also performant
		return ( !(*this!=v) );
	}


	//functions

	//because a function based on an object seems a good thing but the test function looks like a static function should be used
	//both versions are implemented below
	Vector3d cross(const Vector3d& v) const
	{
		return Vector3d{
			y_*v[2] - z_*v[1],
			z_*v[0] - x_*v[2],
			x_*v[1] - y_*v[0]};
	}
	
	static Vector3d cross(const Vector3d& v1, const Vector3d &v2)
	{
		return Vector3d{
			v1[1]*v2[2] - v1[2]*v2[1],
			v1[2]*v2[0] - v1[0]*v2[2],
			v1[0]*v2[1] - v1[1]*v2[0]};
	}

	double dot(const Vector3d& v) const
	{
		return x_*v[0] + y_*v[1] + z_*v[2];
	}

	static double dot(const Vector3d& v1, const Vector3d &v2)
	{
		return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
	}

	double length() const
	{
		return std::sqrt(this->dot(*this));
	}

	void normalize()
	{
		double len = length();
		*this = *this/len;
	}

private:
	double x_;
	double y_;
	double z_;
};

inline std::ostream& operator<<(std::ostream& os, Vector3d& v)
{
	os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
}

inline Vector3d operator*(const double scalar, const Vector3d &v)
{
	//simply "replace" call with operator* on v
	return v*scalar;
}

 

void test() {
// test default constructor
    Vector3d v1;  
    std::cout << "test: default ctor" << std::endl;
    std::cout << "(0.0,0.0,0.0):\t" << v1 << std::endl; 
    assert(v1[0]==0.0 && v1[1]==0.0 && v1[2]==0.0); 

    // test init-list
    std::cout << "\ntest: init-list ctor" << std::endl;
    Vector3d v2 {2.0, 3.0, 4.0};
    std::cout << "(2.0,3.0,4.0):\t" << v2 << std::endl; 
    assert(v2[0]==2.0 && v2[1]==3.0 && v2[2]==4.0); 

    // test assignment
    std::cout << "\ntest: assignment" << std::endl;
    Vector3d v3; 
    v3 = v2; 
    std::cout << "(2.0,3.0,4.0):\t" << v3 << std::endl; 
    assert(v3[0]==2.0 && v3[1]==3.0 && v3[2]==4.0); 

    // test init-list for containers
    std::cout << "\ntest: init list for container" << std::endl;
    std::cout << "the x, y, and z axis:" << std::endl;
    std::vector<Vector3d> vc {{1.0,0.0,0.0}, {0.0,1.0,0.0}, {0.0,0.0,1.0}};
    for(auto v : vc) std::cout << v << "\t"; std::cout << std::endl;
    assert(vc[0][0]==1.0 && vc[0][1]==0.0 && vc[0][2]==0.0); 
    assert(vc[1][0]==0.0 && vc[1][1]==1.0 && vc[1][2]==0.0); 
    assert(vc[2][0]==0.0 && vc[2][1]==0.0 && vc[2][2]==1.0); 

    // scalar multiplication 
    std::cout << "\ntest: scalar scaling" << std::endl;
    std::cout << "scaling by 0.5" << std::endl;
    for(auto& v : vc) v = 0.5*v; 
    for(auto v : vc) std::cout << v << "\t"; std::cout << std::endl;
    assert(vc[0][0]==0.5 && vc[0][1]==0.0 && vc[0][2]==0.0); 
    assert(vc[1][0]==0.0 && vc[1][1]==0.5 && vc[1][2]==0.0); 
    assert(vc[2][0]==0.0 && vc[2][1]==0.0 && vc[2][2]==0.5); 

    // normalization 
    std::cout << "\ntest: normalization" << std::endl;
    std::cout << "scaling by 0.5" << std::endl;
    for(auto& v : vc) v.normalize();
    for(auto v : vc) std::cout << v << "\t"; std::cout << std::endl;

    // vector addition 
    std::cout << "\ntest: addition" << std::endl;
    Vector3d v4 {0,0,0};
    for(auto& v : vc) v4 += v;
    for(auto v : vc) std::cout << v << "\t"; 
    std::cout << " all added ==> " << v4 << std::endl;
    assert(v4[0]==1.0 && v4[1]==1.0 && v4[2]==1.0); 
    
    // vector substraction 
    std::cout << "\ntest: substraction" << std::endl;
    Vector3d v5 {0,0,0};
    for(auto& v : vc) v5 -= v;
    for(auto v : vc) std::cout << v << "\t"; 
    std::cout << " all substracted ==> " << v5 << std::endl;
    assert(v5[0]==-1.0 && v5[1]==-1.0 && v5[2]==-1.0); 

    // unary minus 
    std::cout << "\ntest: unary minus" << std::endl;
    Vector3d v7 {1,2,3};
    Vector3d v8;
    v8 = -v7;
    std::cout << "-" << v7 << " = " << v8 << std::endl;
    assert(v8[0]==-1.0 && v8[1]==-2.0 && v8[2]==-3.0); 

    // cross product 
    std::cout << "\ntest: cross product" << std::endl;
    Vector3d v100 {1,0,0};
    Vector3d v010 {0,1,0};
    Vector3d v001 = Vector3d::cross(v100, v010); 
    std::cout << v100 << "x" << v010 << " = " << v001 << std::endl;
    assert(v001[0]==0.0 && v001[1]==0.0 && v001[2]==1.0); 

    // scalar product
    std::cout << "\ntest: dot product" << std::endl;
    double sp1 = Vector3d::dot(v100,v010);
    std::cout << v100 << "." << v010 << " = " << sp1 << std::endl;
    assert(sp1==0); 
    double sp2 = Vector3d::dot(v100,v100);
    std::cout << v100 << "." << v100 << " = " << sp2 << std::endl;
    assert(sp2==1);  
}


int main()
{
    test();
	std::cout << "\nSuccessfully finished test" << std::endl;
	return 0;
}
