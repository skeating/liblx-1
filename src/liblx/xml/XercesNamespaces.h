/**
 * @cond doxygenLibsbmlInternal
 *
 * @file    XercesNamespaces.h
 * @brief   Extracts XML namespace declarations from Xerces-C++ attributes.
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

#ifndef XercesNamespaces_h
#define XercesNamespaces_h

#ifdef __cplusplus

#include <string>

#include <xercesc/sax2/Attributes.hpp>
#include <liblx/xml/XMLNamespaces.h>

LIBSBML_CPP_NAMESPACE_BEGIN


class XercesNamespaces : public XMLNamespaces
{
public:

  /**
   * Creates a new list of XML namespaces declarations from a "raw" Xerces-C++
   * Attributes set.
   */
  XercesNamespaces (const xercesc::Attributes& attrs);


  /**
   * Destroys this list of XML namespace declarations.
   */
  virtual ~XercesNamespaces ();
};


LIBSBML_CPP_NAMESPACE_END

#endif  /* __cplusplus */
#endif  /* XercesNamespaces_h */

/** @endcond */
