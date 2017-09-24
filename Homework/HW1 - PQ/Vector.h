// Alvin Quach, 300793745
// CS5550 F17 - HW1 PQ

#pragma once
#include <type_traits>

template<typename T, int SIZE>
class Vector {

	static_assert(std::is_arithmetic<T>::value, "Template type T in Vector must be numeric.");

public:

	/// <summary>Returns the dot product of a and b.</summary>
	static T Dot(Vector<T, SIZE>& a, Vector<T, SIZE>& b) {
		T result = 0;
		for (int i = 0; i < SIZE; i++) {
			result += a[i] * b[i];
		}
		return result;
	}

	/// <summary>Returns the distance between a and b.</summary>
	static float Distance(Vector<T, SIZE>& a, Vector<T, SIZE>& b) {
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
	float getMagnitude() {
		T magnitudeSquared = 0;
		for (int i = 0; i < SIZE; i++) {
			magnitudeSquared += pow(components[i], 2);
		}
		return sqrt(magnitudeSquared);
	}

	/// <summary>Make the vector have the specified magnitude.</summary>
	/// <param name='magnitude'>The vector's new magnitude.</param>
	void setMagnitude(T magnitude) {
		float prevMagnitude = getMagnitude();
		if (prevMagnitude > 0) {
			scale(magnitude / prevMagnitude);
		}
	}

	/// <summary>Reflects this vector accross a normal vector.</summary>
	/// <param name='normal'>The normal vector to reflect accross. Does not need to be normalized.</param>
	void reflect(Vector<T, SIZE>& normal) {
		normal.normalize();
		float dotProduct = Dot(*this, normal);
		for (int i = 0; i < SIZE; i++) {
			components[i] = components[i] - 2 * dotProduct * normal[i];
		}
	}

	/// <summary>Make the vector have a magnitude of 1.</summary>
	void normalize() {
		setMagnitude(1);
	}

	// Vector addition operator overload 
	Vector<T, SIZE> operator +(Vector<T, SIZE>& anotherVector) {
		Vector<T, SIZE> result = Vector<T, SIZE>();
		for (int i = 0; i < SIZE; i++) {
			result[i] = components[i] + anotherVector[i];
		}
		return result;
	}

	// Vector subtraction operator overload 
	Vector<T, SIZE> operator -(Vector<T, SIZE>& anotherVector) {
		Vector<T, SIZE> result = Vector<T, SIZE>();
		for (int i = 0; i < SIZE; i++) {
			result[i] = components[i] - anotherVector[i];
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
