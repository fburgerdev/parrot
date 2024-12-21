#include "common.hh"
#include "std140_opengl.hh"

namespace Parrot {
	namespace OpenGL {
		// setSTD140
		void setSTD140(bool x, List<uchar>::iterator it) {
			*it = (x ? uchar(1) : uchar(0));
		}
		void setSTD140(int32 x, List<uchar>::iterator it) {
			memcpy(&(*it), &x, 4);
		}
		void setSTD140(uint32 x, List<uchar>::iterator it) {
			memcpy(&(*it), &x, 4);
		}
		void setSTD140(float32 x, List<uchar>::iterator it) {
			memcpy(&(*it), &x, 4);
		}
		void setSTD140(float64 x, List<uchar>::iterator it) {
			memcpy(&(*it), &x, 8);
		}
	}
}