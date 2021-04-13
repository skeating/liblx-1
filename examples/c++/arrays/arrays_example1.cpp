/**
 * @file    arrays_example1.cpp
 * @brief   arrays create example
 * @author  Sarah Keating
 *
 * <!--------------------------------------------------------------------------
 * This file is part of libSBML.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
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
 * in the file named "LICENSE.txt" included with this software distribution
 * and also available online as http://sbml.org/software/libsbml/license.html
 * ------------------------------------------------------------------------ -->
 */

#include <liblx/SBMLTypes.h>
#include <liblx/packages/arrays/common/ArraysExtensionTypes.h>


using namespace std;
LIBSBML_CPP_NAMESPACE_USE

int
main (int argc, char* argv[])
{
  SBMLNamespaces sbmlns(3,1,"arrays",1);

  // create the document

  SBMLDocument *document = new SBMLDocument(&sbmlns);

  // set the required attribute to true
  ArraysSBMLDocumentPlugin * docPlug = 
    static_cast<ArraysSBMLDocumentPlugin*>(document->getPlugin("arrays"));
  docPlug->setRequired(true);


  // create the Model

  Model* model=document->createModel();

  // create the parameters

  Parameter * p = model->createParameter();
  p->setId("n");
  p->setConstant(true);
  p->setValue(10);

  // second parameter
  p = model->createParameter();
  p->setId("x");
  p->setConstant(false);


  // create the Dimensions via the Plugin
  ArraysSBasePlugin * arraysPlug = 
    static_cast<ArraysSBasePlugin*>(p->getPlugin("arrays"));
  Dimension * dim = arraysPlug->createDimension();
  dim->setArrayDimension(0);
  dim->setSize("n");

  // third parameter
  p = model->createParameter();
  p->setId("y");
  p->setConstant(false);


  // create the Dimensions via the Plugin
  arraysPlug = 
    static_cast<ArraysSBasePlugin*>(p->getPlugin("arrays"));
  dim = arraysPlug->createDimension();
  dim->setArrayDimension(0);
  dim->setSize("n");


  // create the assignmentRule
  AssignmentRule *ar = model->createAssignmentRule();
  ar->setVariable("y");

  ASTNode * math = new ASTNode(AST_LINEAR_ALGEBRA_SELECTOR);
  ASTNode * ci1 = new ASTNode(AST_NAME);
  ci1->setName("x");
  ASTNode * ci2 = new ASTNode(AST_NAME);
  ci2->setName("i");
  math->addChild(ci1);
  math->addChild(ci2);
  ar->setMath(math);

  // set dimensions
  arraysPlug = 
    static_cast<ArraysSBasePlugin*>(ar->getPlugin("arrays"));
  dim = arraysPlug->createDimension();
  dim->setArrayDimension(0);
  dim->setSize("n");
  dim->setId("i");

  // set the index
  Index * ind = arraysPlug->createIndex();
  ind->setArrayDimension(0);
  ind->setReferencedAttribute("variable");

  ASTNode * indMath = SBML_parseL3Formula("9 - i");
  ind->setMath(indMath);

  writeSBML(document,"arrays_example1.xml");
 
  delete document;

  return 0;
}
