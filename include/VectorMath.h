#ifndef VectorMath_h
#define VectorMath_h
/**
VectorMath library for ArdIU
*/

#include <math.h>
//#include "Arduino.h"

enum StockVector {
	V_ZEROES,
	V_ONES,
	V_X,
	V_Y,
	V_Z
};

class QuatF; // pre-declare so we can use it in VectorF

// using the Printable interface here burns an additional 2 bytes to point to a VFtable;
// whether that is worth the convenience is an open quesiton; looking into better ways
class __attribute__((packed)) VectorF/*: public Printable*/ {
  public:
	float x, y, z;
	VectorF(float xval, float yval, float zval);
	VectorF(StockVector v);
	VectorF(QuatF q);
	VectorF();

//	size_t printTo(Print&) const;

	float magSq() const;
	float mag() const;
	VectorF negate() const;
	inline VectorF operator - () const { return negate(); }
	VectorF add(VectorF other) const;
	inline VectorF operator + (VectorF other) const { return add(other); }
	inline VectorF operator - (VectorF other) const { return add(-other); }
	VectorF scale(float s) const;
	inline VectorF operator * (float s) const { return scale(s); }
	inline VectorF normalize() const { return scale(1/mag()); }
	float dot(const VectorF &other) const;
	VectorF cross(const VectorF &other) const;
	VectorF rotate(const QuatF &q) const;
};

class __attribute__((packed)) QuatF/*: public Printable*/ {
  public:
	float w, x, y, z;
	QuatF(float wval, float xval, float yval, float zval);
	QuatF(const VectorF& lv);
	QuatF();

	static QuatF fromAngleAxis(const VectorF& aa);
	
//	size_t printTo(Print& to) const;
	
	QuatF conj() const;
	inline QuatF operator ~ () const { return conj(); }
	QuatF mult(const QuatF& other) const;
	inline QuatF operator * (const QuatF& other) const { return mult(other); }
};

#endif