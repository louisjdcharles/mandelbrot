#include <iostream>
#include <math.h>
#include <fstream>

int MAX_ITER = 100;

struct Complex {
	double real;
	double imag;

	Complex(double r, double i) {
		this->real = r;
		this->imag = i;
	}

	Complex(double r) {
		this->real = r;
		this->imag = 0;
	}

	Complex operator + (const Complex other) {
		return Complex(
			this->real + other.real, 
			this->imag + other.imag
		);
	}

	Complex square() {
		return Complex(
			this->real * this->real - this->imag * this->imag,
			2 * this->real * this->imag
		);

		// (a + bi)(a + bi)
		// a^2 + 2abi - b^2
		// real = a^2 - b^2
		// imag = 2abi
	}
};

int expr(Complex z, Complex c, int depth) {

	z = z.square() + c;

	if (abs(z.imag) > 2 || abs(z.real) > 2)
		return depth;
	else if (depth == MAX_ITER)
		return depth;
	else
		return expr(z, c, ++depth);
}

int mandelbrot(Complex c) {
	Complex z(0, 0);

	return expr(z, c, 0);
}

int main() {

	const int width = 1000, height = 1000;

	std::ofstream image("output.ppm");
	// file header
	image << "P3" << std::endl;
	image << width << " " << height << std::endl;
	image << "255" << std::endl;

	// image data
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int iterations = mandelbrot(Complex(((double)x - 500) / 250, ((double)y - 500) / 250));

			int colour = (int)((1 - (double)iterations / MAX_ITER) * 254);
			image << colour << " " << colour << " " << colour << std::endl;
		}
	}
	return 0;
}