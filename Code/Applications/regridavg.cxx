// This file is part of RegSeg
//
// Copyright 2014-2017, Oscar Esteban <code@oscaresteban.es>
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.

#include "regridavg.h"

#include <iostream>


int main(int argc, char *argv[]) {
	std::string ifname, ofname;
	std::vector<size_t> grid_size;
	std::vector<float> origin;

	bpo::options_description all_desc("Usage");
	all_desc.add_options()
			("help,h", "show help message")
			("input,i", bpo::value < std::string > (&ifname)->multitoken()->required(), "input image file")
			("output,o", bpo::value < std::string > (&ofname)->multitoken()->required(), "output image file")
			("grid-size,g", bpo::value< std::vector<size_t> >(&grid_size)->multitoken(), "size of grid of bspline control points");


	bpo::variables_map vm;
	try {
		bpo::store(	bpo::parse_command_line( argc, argv, all_desc ), vm);
		if (vm.count("help") || vm.size() == 0 ) {
			std::cout << all_desc << std::endl;
			return 1;
		}
		bpo::notify(vm);
	} catch ( bpo::error& e ) {
		std::cerr << "Error: " << e.what() << std::endl << std::endl;
		std::cerr << all_desc << std::endl;
		return 1;
	}


	ReaderPointer r = ImageReader::New();
	r->SetFileName(ifname);
	r->Update();

	InputPointer im = r->GetOutput();

	InputImageType::PointType ref_o = im->GetOrigin();
	InputImageType::SpacingType ref_sp = im->GetSpacing();
	InputImageType::SizeType ref_sz = im->GetLargestPossibleRegion().GetSize();
	InputImageType::DirectionType ref_dir = im->GetDirection();

	std::cout << "Input origin=" << ref_o << std::endl;

	OutputImageType::SizeType new_sz;
	OutputImageType::SpacingType new_sp;
	OutputImageType::PointType new_o;

	double extent[DIMENSION];

	for (size_t i = 0; i < DIMENSION; i++) {
		new_sz[i] = grid_size[i];
		extent[i] = ref_sp[i] * ref_sz[i];
		new_sp[i] = extent[i] / new_sz[i];
		new_o[i] = -(0.5 * new_sz[i]) * new_sp[i];
	}
	new_o = ref_dir * new_o;

	std::cout << "Output origin=" << new_o << std::endl;


	ResampleFilterPointer s = ResampleFilterType::New();
	s->SetInput(r->GetOutput());
	s->SetSize( new_sz );
	s->SetOutputOrigin( new_o );
	s->SetOutputSpacing( new_sp );
	s->SetOutputDirection( ref_dir );
	s->SetDefaultPixelValue( 0.0 );
	s->Update();

	WriterPointer w = ImageWriter::New();
	w->SetInput(s->GetOutput());
	w->SetFileName(ofname);
	w->Update();

	return EXIT_SUCCESS;
}
