#include"sb7.h"
#include"vmath.h"
#include<iostream>
using namespace vmath;

//二次贝塞尔
vec4 quadratic_bezier(vec4 A, vec4 B, vec4 C, float t)
{
	vec4 D = mix(A, B, t);
	vec4 E = mix(B, C, t);
	vec4 P = mix(D, E, t);

	return P;
}

//三次贝塞尔
vec4 cubic_bezier(vec4 A, vec4 B, vec4 C, vec4 D, float t)
{
	vec4 E = mix(A, B, t);
	vec4 F = mix(B, C, t);
	vec4 G = mix(C, D, t);

	return quadratic_bezier(E, F, G, t);
}

vec4 cubic_bspline_10(vec4 cp[10], float t)
{
	float f = t * 3.0;
	int i = int(float(f));
	float s = t - int(t);

	if (t <= 0.0)
		return cp[0];

	if (t >= 1.0)
		return cp[9];

	vec4 A = cp[i * 3];
	vec4 B = cp[i * 3 + 1];
	vec4 C = cp[i * 3 + 2];
	vec4 D = cp[i * 3 + 3];

	return cubic_bezier(A, B, C, D, s);
}


int main()
{
	vmath::vec3 a(1.0f, 2.0f, 3.0f);
	vmath::vec3 b(4.0f, 5.0f, 6.0f);
	vmath::vec3 c;

	//点乘 1*4 + 2*5 + 3*6 = 32
	std::cout << "dot: " << vmath::dot(a, b) << std::endl;


	//叉乘 
	std::cout << "cross: " << vmath::cross(a, b)[0] << std::endl;

	vec4 A(1.0f, 2.0f, 0.0f, 1.0f);
	vec4 B(2.0f, 3.0f, 0.0f, 1.0f);
	vec4 C(3.0f, 4.0f, 0.0f, 1.0f);

	float t = 0.3;

	//(5, 6, 0, 1) 二次bezier曲线 P = A + t(B-A)
	vec4 P1 = quadratic_bezier(A, B, C, t);

	std::cout << P1[0] << " " << P1[1] << " " << P1[2] << " " << P1[3] << std::endl;

	vec4 D(4.0f, 5.0f, 0.0f, 1.0f);

	vec4 P2 = cubic_bezier(A, B, C, D, t);

	//三次bezier曲线组成的B样条
	vec4 cp[10] = { A, B, C, D, vec4{5.0f,6.0f,0.0f,1.0f}, vec4{6.0f, 7.0f, 0.0f, 1.0f},  vec4{7.0f, 8.0f, 0.0f, 1.0f},
	vec4{8.0f, 9.0f, 0.0f, 1.0f}, vec4{9.0f, 10.0f, 0.0f, 1.0f}, vec4{10.0f, 11.0f, 0.0f, 1.0f} };
	vec4 P_bsp = cubic_bspline_10(cp, t);
	std::cout << P_bsp[0] << " " << P_bsp[1] << " " << P_bsp[2] << " " << P_bsp[3] << std::endl;

	return 0;
}