#pragma once
#include <type_traits>

template<typename T, int SIZE>
class Vector {

	static_assert(std::is_arithmetic<T>::value, "Template type T in Vector must be numeric.");

public:

	/// <summary>Returns the dot product of a and b.</summary>
	static T Dot(Vector<T, SIZE> a, Vector<T, SIZE> b) {
		T result = 0;
		for (int i = 0; i < SIZE; i++) {
			result += a[i] * b[i];
		}
		return result;
	}

	/// <summary>Returns the distance between a and b.</summary>
	static float Distance(Vector<T, SIZE> a, Vector<T, SIZE> b) {
		Vector<T, SIZE> c = a - b;
		return c.getMagnitude();
	}

	/// <summary>Scale the vector's magnitude by the specified amount.</summary>
	/// <param name='scale'>The scaling factor.</param>
	void scale(T scale) {
		for (int i = 0; i < SIZE; i++) {
			components[i] *= scale;
		}
	}

	/// <summary>Return the vector's current magnitude.</summary>
	float Vector<T, SIZE>::getMagnitude() {
		T magnitudeSquared = 0;
		for (int i = 0; i < SIZE; i++) {
			magnitudeSquared += pow(components[i], 2);
		}
		return sqrt(magnitudeSquared);
	}

	/// <summary>Make the vector have the specified magnitude.</summary>
	/// <param name='magnitude'>The vector's new magnitude.</param>
	void Vector<T, SIZE>::setMagnitude(T magnitude) {
		scale(magnitude / getMagnitude());
	}

	/// <summary>Make the vector have a magnitude of 1.</summary>
	void normalize() {
		setMagnitude(1);
	}

	/// <summary>Returns a unit vector with the same direction as this vector.</summary>
	Vector<T, SIZE> unitVector() {
		Vector<T, SIZE> result = Vector<T, SIZE>();
		for (int i = 0; i < SIZE; i++) {
			result[i] = components[i] / getMagnitude();
		}
		return result;
	}

	// Vector addition operator overload
	Vector<T, SIZE> operator +(Vector<T, SIZE> anotherVector) {
		Vector<T, SIZE> result = Vector<T, SIZE>();
		for (int i = 0; i < SIZE; i++) {
			result[i] = components[i] + anotherVector[i];
		}
		return result;
	}

	// Vector subtraction operator overload
	Vector<T, SIZE> operator -(Vector<T, SIZE> anotherVector) {
		Vector<T, SIZE> result = Vector<T, SIZE>();
		for (int i = 0; i < SIZE; i++) {
			result[i] = components[i] - anotherVector[i];
		}
		return result;
	}

	// Scalar division operator overload
	Vector<T, SIZE> operator /(float scalar) {
		Vector<T, SIZE> result = Vector<T, SIZE>();
		for (int i = 0; i < SIZE; i++) {
			result[i] = vector[i] / scalar;
		}
		return result;
	}

protected:

	T components[SIZE];

	// Index accessor  operator overload
	T& operator [](int i) {
		return components[i];
	}

};
