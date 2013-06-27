// --------------------------------------------------------------------------------------
// File:          VectorBSplinesBasisFunction.h
// Date:          Jun 7, 2013
// Author:        code@oscaresteban.es (Oscar Esteban)
// Version:       1.0 beta
// License:       GPLv3 - 29 June 2007
// Short Summary:
// --------------------------------------------------------------------------------------
//
// Copyright (c) 2013, code@oscaresteban.es (Oscar Esteban)
// with Signal Processing Lab 5, EPFL (LTS5-EPFL)
// and Biomedical Image Technology, UPM (BIT-UPM)
// All rights reserved.
//
// This file is part of ACWE-Reg
//
// ACWE-Reg is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// ACWE-Reg is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with ACWE-Reg.  If not, see <http://www.gnu.org/licenses/>.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#ifndef VECTORBSPLINESBASISFUNCTION_H_
#define VECTORBSPLINESBASISFUNCTION_H_

#include "itkNumericTraits.h"
#include <cmath>

namespace rstk {
namespace RBF {


template< class TPixel, class TScalarType = double, unsigned int NDimensions = 3>
class VectorBSplinesBasisFunction: RadialBasisFunction< TPixel, TScalarType, NDimensions >
{
public:
	typedef VectorBSplinesBasisFunction          Self;
	typedef TPixel                          PixelType;
	typedef typename PixelType::VectorType  VectorType;

	itkStaticConstMacro( Dimension, unsigned int, NDimensions );

	VectorBSplinesBasisFunction() {
		m_eps = vnl_math::eps;
		m_factor = 2.0;
	};
	~VectorBSplinesBasisFunction(){};

	inline TScalarType GetWeight( const TPixel &center, const TPixel &point ) const {
		VectorType dist = center-point;
		for( size_t i = 0; i< Dimension; i++)
			dist[i] = dist[i] / (0.5*this->m_width[i]);

		TScalarType w = dist.GetNorm();

        double sqrValue = vnl_math_sqr( w );
	    if ( w  < 1.0 ) {
		    w = ( 4.0 - 6.0 * sqrValue + 3.0 * sqrValue * w ) / 6.0;
		} else if ( w < 2.0 ) {
		    w = ( 8.0 - 12 * w + 6.0 * sqrValue - sqrValue * w ) / 6.0;
		} else {
		    w = 0.0;
		}
		assert( w <= 1.0 );
		return w;
	}

	void SetWidth( const PointType f ) { this->m_width = f; }
	PointType GetWidth(void) { return this->m_width; }


private:
	TScalarType m_eps;
	PointType m_width;

};
}
}

#endif /* VECTORBSPLINESBASISFUNCTION_H_ */