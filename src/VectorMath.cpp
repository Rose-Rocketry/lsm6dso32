#include "VectorMath.h"

VectorF::VectorF( float xval,  float yval,  float zval): VectorF() {
    x = xval;
    y = yval;
    z = zval;
}
VectorF::VectorF(StockVector v): VectorF() {
	switch(v) {
		case V_ZEROES:
			x = 0; y = 0; z = 0;
			break;
		case V_ONES:
			x = 1; y = 1; z = 1;
			break;
		case V_X:
			x = 1; y = 0; z = 0;
			break;
		case V_Y:
			x = 0; y = 1; z = 0;
			break;
		case V_Z:
			x = 0; y = 0; z = 1;
			break;
	}
}
VectorF::VectorF(QuatF q): VectorF(q.x, q.y, q.z) {}
VectorF::VectorF() {}

// size_t VectorF::printTo(Print& to) const {
	// return to.print("[")+to.print(x)+to.print(" ")
						// +to.print(y)+to.print(" ")
						// +to.print(z)+to.print("]");
// }

float VectorF::magSq() const {
	return x*x + y*y + z*z;
}
float VectorF::mag() const {
	return sqrt(magSq());
}
VectorF VectorF::negate() const {
	return VectorF(-x, -y, -z);
}
VectorF VectorF::add(VectorF other) const {
	return VectorF(x+other.x, y+other.y, z+other.z);
}
VectorF VectorF::scale(float s) const {
	return VectorF(s*x, s*y, s*z);
}
float VectorF::dot(const VectorF &other) const {
    return x*other.x + y*other.y + z*other.z;
}

VectorF VectorF::cross(const VectorF &other) const {
    VectorF newV;
	newV.x = y*other.z - z*other.y;
	newV.y = z*other.x - x*other.z;
	newV.z = x*other.y - y*other.x;
	return newV;
}

VectorF VectorF::rotate(const QuatF& q) const {
	return VectorF(q * QuatF(*this) * ~q);
}

/**
 QuatF functions
 */

QuatF::QuatF(float wval, float xval, float yval, float zval) {
	w = wval;
	x = xval;
	y = yval;
	z = zval;
}
QuatF::QuatF(const VectorF& lv) {
	w = 0;
	x = lv.x;
	y = lv.y;
	z = lv.z;
}
QuatF::QuatF() {}

QuatF QuatF::fromAngleAxis(const VectorF& aa) {
	float theta = aa.mag();
	if(theta > 0) {
		return QuatF(
			cos(theta/2),
			aa.x/theta * sin(theta/2),
			aa.y/theta * sin(theta/2),
			aa.z/theta * sin(theta/2) // surely the compiler memoizes this?
		);
	} else {
		return QuatF(1, 0, 0, 0);
	}
}

// size_t QuatF::printTo(Print& to) const {
	// return to.print("[")+to.print(w)+to.print(" ")
						// +to.print(x)+to.print(" ")
						// +to.print(y)+to.print(" ")
						// +to.print(z)+to.print("]");
// }
QuatF QuatF::conj() const {
	return QuatF(w, -x, -y, -z);
}
QuatF QuatF::mult(const QuatF& other) const {
	QuatF newQ;
	newQ.w = w*other.w - x*other.x - y*other.y - z*other.z;
	newQ.x = w*other.x + x*other.w + y*other.z - z*other.y;
	newQ.y = w*other.y + y*other.w + z*other.x - x*other.z;
	newQ.z = w*other.z + z*other.w + x*other.y - y*other.x;
	return newQ;
}