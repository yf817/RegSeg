/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef __WeightedCovarianceSampleFilter_h
#define __WeightedCovarianceSampleFilter_h

#include "itkFunctionBase.h"
#include "itkCovarianceSampleFilter.h"
#include "itkDataObjectDecorator.h"

namespace rstk
{
/** \class WeightedCovarianceSampleFilter
 * \brief Calculates the covariance matrix of the target sample data.
 *  where each measurement vector has an associated weight value
 *
 * Weight values can be specified in two ways: using a weighting function
 * or an array containing weight values. If none of these two is specified,
 * the covariance matrix is generated with equal weights.
 *
 * \sa CovarianceSampleFilter
 *
 * \ingroup ITKStatistics
 */

template< typename TSample >
class WeightedCovarianceSampleFilter:
		public itk::Statistics::CovarianceSampleFilter< TSample >
{
public:
  /** Standard class typedefs. */
  typedef WeightedCovarianceSampleFilter         Self;
  typedef itk::Statistics::CovarianceSampleFilter< TSample >
                                                 Superclass;
  typedef itk::SmartPointer< Self >              Pointer;
  typedef itk::SmartPointer< const Self >        ConstPointer;

  /** Standard Macros */
  itkTypeMacro(WeightedCovarianceSampleFilter, itk::Statistics::CovarianceSampleFilter);
  itkNewMacro(Self);

  /** Types derived from the base class */
  typedef typename Superclass::SampleType                     SampleType;
  typedef typename Superclass::MeasurementVectorType          MeasurementVectorType;
  typedef typename Superclass::MeasurementVectorSizeType      MeasurementVectorSizeType;
  typedef typename Superclass::MeasurementType                MeasurementType;

  /** Types derived from the base class */
  typedef typename Superclass::MeasurementVectorRealType      MeasurementVectorRealType;
  typedef typename Superclass::MeasurementRealType            MeasurementRealType;


  /** Type of weight values */
  typedef double WeightValueType;


  /** Array type for weights */
  typedef itk::Array< WeightValueType > WeightArrayType;

  /** Type of DataObjects to use for the weight array type */
  typedef itk::SimpleDataObjectDecorator< WeightArrayType > InputWeightArrayObjectType;

  /** Method to set the input value of the weight array */
  itkSetGetDecoratedInputMacro(Weights, WeightArrayType);


  /** Weight calculation function type */
  typedef itk::FunctionBase< MeasurementVectorType, WeightValueType > WeightingFunctionType;

  /** Type of DataObjects to use for Weight function */
  typedef itk::DataObjectDecorator< WeightingFunctionType > InputWeightingFunctionObjectType;

  /** Method to set/get the weighting function */
  itkSetGetDecoratedObjectInputMacro(WeightingFunction, WeightingFunctionType);

  virtual void SetMean(const MeasurementVectorRealType m) {
	  MeasurementVectorDecoratedType *decoratedMeanOutput =
	    itkDynamicCastInDebugMode< MeasurementVectorDecoratedType * >( this->ProcessObject::GetOutput(1) );
	  decoratedMeanOutput->Set( m );
	  this->m_MeanSet = true;
	  this->Modified();
  }


  /** Types derived from the base class */
  typedef typename Superclass::MatrixType          MatrixType;
  typedef typename Superclass::MatrixDecoratedType MatrixDecoratedType;

  /** Types derived from the base class */
  typedef typename Superclass::MeasurementVectorDecoratedType MeasurementVectorDecoratedType;
  typedef typename Superclass::OutputType                     OutputType;

protected:
  WeightedCovarianceSampleFilter();
  virtual ~WeightedCovarianceSampleFilter();
  void PrintSelf(std::ostream & os, itk::Indent indent) const;

  void GenerateData();

  /** Compute covariance matrix with weights computed from a function */
  void ComputeCovarianceMatrixWithWeightingFunction();

  /** Compute covariance matrix with weights specified in an array */
  void ComputeCovarianceMatrixWithWeights();

private:
  WeightedCovarianceSampleFilter(const Self &); //purposely not implemented
  void operator=(const Self &);                 //purposely not implemented

  bool m_MeanSet;

};  // end of class
} // end of namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include <WeightedCovarianceSampleFilter.hxx>
#endif

#endif
