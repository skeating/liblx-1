/**
 * @cond doxygenLibsbmlInternal
 *
 * @file    XercesAttributes.cpp
 * @brief   Creates new XMLAttributes from "raw" Xerces-C++ attributes.
 * @author  Ben Bornstein
 * 
 * <!--------------------------------------------------------------------------
 * This file is part of libSBML.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 *
 * Copyright (C) 2019 jointly by the following organizations:
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. University of Heidelberg, Heidelberg, Germany
 *
 * Copyright (C) 2013-2018 jointly by the following organizations:
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. EMBL European Bioinformatics Institute (EMBL-EBI), Hinxton, UK
 *     3. University of Heidelberg, Heidelberg, Germany
 *
 * Copyright (C) 2009-2013 jointly by the following organizations: 
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. EMBL European Bioinformatics Institute (EMBL-EBI), Hinxton, UK
 *  
 * Copyright (C) 2006-2008 by the California Institute of Technology,
 *     Pasadena, CA, USA 
 *  
 * Copyright (C) 2002-2005 jointly by the following organizations: 
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. Japan Science and Technology Agency, Japan
 * 
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation.  A copy of the license agreement is provided
 * in the file named "LICENSE.txt" included with this software distribution and
 * also available online as http://sbml.org/software/libsbml/license.html
 * ---------------------------------------------------------------------- -->*/

#include <liblx/xml/XercesTranscode.h>
#include <liblx/xml/XercesAttributes.h>

using namespace std;
using namespace xercesc;

LIBSBML_CPP_NAMESPACE_BEGIN


/**
 * Creates a new XMLAttributes set that wraps the given "raw" Xerces-C++
 * Attributes set.
 */
XercesAttributes::XercesAttributes (const Attributes& attrs,
				    const string elementName)
{
  unsigned int size = attrs.getLength();

  mNames .reserve(size);
  mValues.reserve(size);

  for (unsigned int n = 0; n < size; ++n)
  {
    const string            uri   = XercesTranscode( attrs.getURI      (n) );
    const string            name  = XercesTranscode( attrs.getLocalName(n) );
    const string            qname = XercesTranscode( attrs.getQName    (n) );
    const string            value = XercesTranscode( attrs.getValue    (n) );
    const string::size_type pos   = qname.find(":", 0);

    const string prefix = (pos != string::npos) ? qname.substr(0, pos) : "";

    //
    // Skip XML namespace declarations
    //
    if (prefix != "xmlns" && name != "xmlns")
    {
      mNames .push_back( XMLTriple(name, uri, prefix) );
      mValues.push_back( value );
    }
  }

  mElementName = elementName;
}


/**
 * Destroys this XercesAttributes set.
 */
XercesAttributes::~XercesAttributes ()
{
}


LIBSBML_CPP_NAMESPACE_END

/** @endcond */

