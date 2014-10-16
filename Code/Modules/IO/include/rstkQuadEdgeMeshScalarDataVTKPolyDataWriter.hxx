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
#ifndef __rstkQuadEdgeMeshScalarDataVTKPolyDataWriter_hxx
#define __rstkQuadEdgeMeshScalarDataVTKPolyDataWriter_hxx

#include "rstkQuadEdgeMeshScalarDataVTKPolyDataWriter.h"

using namespace itk;
namespace rstk
{
//
// Constructor
//
template< typename TMesh >
QuadEdgeMeshScalarDataVTKPolyDataWriter< TMesh >
::QuadEdgeMeshScalarDataVTKPolyDataWriter()
{
  m_CellDataName = "celldatascalar";
  m_PointDataName = "pointdatascalar";
}

//
// Destructor
//
template< typename TMesh >
QuadEdgeMeshScalarDataVTKPolyDataWriter< TMesh >
::~QuadEdgeMeshScalarDataVTKPolyDataWriter()
{}

template< typename TMesh >
void
QuadEdgeMeshScalarDataVTKPolyDataWriter< TMesh >
::GenerateData()
{
  this->Superclass::GenerateData();
  this->WriteCellData();
  this->WritePointData();
}

template< typename TMesh >
void
QuadEdgeMeshScalarDataVTKPolyDataWriter< TMesh >
::WriteCellData()
{
  CellDataContainerConstPointer celldata = this->m_Input->GetCellData();

  if ( celldata )
    {
    if ( celldata->Size() != 0 )
      {
      std::ofstream outputFile(this->m_FileName.c_str(), std::ios_base::app);

      outputFile << "CELL_DATA " << this->m_Input->GetNumberOfFaces() << std::endl;
      outputFile << "SCALARS ";
      outputFile << m_CellDataName << " double 1" << std::endl;
      outputFile << "LOOKUP_TABLE default" << std::endl;

      CellsContainerConstPointer  cells = this->m_Input->GetCells();
      CellsContainerConstIterator it = cells->Begin();

      CellDataContainerConstIterator c_it = celldata->Begin();

      while ( c_it != celldata->End() )
        {
        CellType *cellPointer = it.Value();
        if ( cellPointer->GetType() != 1 )
          {
          outputFile << c_it.Value() << std::endl;
          }
        ++c_it;
        ++it;
        }
      outputFile << std::endl;
      outputFile.close();
      }
    }
}

template< typename TMesh >
void
QuadEdgeMeshScalarDataVTKPolyDataWriter< TMesh >
::WritePointData()
{
  PointDataContainerConstPointer pointdata = this->m_Input->GetPointData();

  if ( pointdata )
    {
    std::ofstream outputFile(this->m_FileName.c_str(), std::ios_base::app);

    outputFile << "POINT_DATA " << this->m_Input->GetNumberOfPoints() << std::endl;
    outputFile << "SCALARS ";
    outputFile << m_PointDataName << " double 1" << std::endl;
    outputFile << "LOOKUP_TABLE default" << std::endl;

    PointDataContainerIterator c_it = pointdata->Begin();

    while ( c_it != pointdata->End() )
      {
      outputFile << c_it.Value() << std::endl;
      ++c_it;
      }

    outputFile << std::endl;
    outputFile.close();
    }
}
}

#endif
