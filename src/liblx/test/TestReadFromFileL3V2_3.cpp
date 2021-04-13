/**
 * \file    TestReadFromFileL3V2_2.cpp
 * \brief   Reads test-data/l3v2-empty-lo-2.xml into memory and tests it.
 * \author  Sarah Keating
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
 * in the file named "LICENSE.txt" included with this software distribution
 * and also available online as http://sbml.org/software/libsbml/license.html
 * ---------------------------------------------------------------------- -->*/

#include <liblx/common/common.h>

#include <liblx/SBMLReader.h>
#include <liblx/SBMLWriter.h>
#include <liblx/SBMLTypes.h>

#include <string>

#include <check.h>

LIBSBML_CPP_NAMESPACE_USE

BEGIN_C_DECLS


extern char *TestDataDirectory;

static bool
equals (const char* expected, const char* actual)
{
  if ( !strcmp(expected, actual) ) return true;

  printf( "\nStrings are not equal:\n"  );
  printf( "Expected:\n[%s]\n", expected );
  printf( "Actual:\n[%s]\n"  , actual   );

  return false;
}



START_TEST (test_read_l3v2_empty_lo_2)
{
  SBMLReader        reader;
  SBMLDocument*     d;
  Model*            m;
  std::string filename(TestDataDirectory);
  filename += "l3v2-empty-lo-2.xml";


  d = reader.readSBML(filename);

  if (d == NULL)
  {
    fail("readSBML(\"l3v2-empty-lo-2.xml\") returned a NULL pointer.");
  }



  //
  // <sbml level="3" version="2" ...>
  //
  fail_unless( d->getLevel  () == 3, NULL );
  fail_unless( d->getVersion() == 2, NULL );


  m = d->getModel();
  fail_unless( m != NULL, NULL );

  fail_unless(m->getNumUnitDefinitions() == 1);
  fail_unless(m->getNumFunctionDefinitions() == 0);
  fail_unless(m->getNumCompartments() == 0);
  fail_unless(m->getNumSpecies() == 0);
  fail_unless(m->getNumParameters() == 0);
  fail_unless(m->getNumRules() == 0);
  fail_unless(m->getNumInitialAssignments() == 0);
  fail_unless(m->getNumConstraints() == 0);
  fail_unless(m->getNumReactions() == 1);
  fail_unless(m->getNumEvents() == 1);

  UnitDefinition * ud = m->getUnitDefinition(0);

  fail_unless( ud != NULL);
  fail_unless( ud->getNumUnits() == 0);
  fail_unless( ud->getListOfUnits()->hasOptionalAttributes() == true);
  fail_unless( ud->getListOfUnits()->hasOptionalElements() == false);
  fail_unless( ud->getListOfUnits()->isSetMetaId() == true);
  fail_unless( ud->getListOfUnits()->getMetaId() == "dd");

  Reaction * r = m->getReaction(0);

  fail_unless( r != NULL);
  
  fail_unless( r->getNumReactants() == 0);
  fail_unless( r->getListOfReactants()->hasOptionalAttributes() == true);
  fail_unless( r->getListOfReactants()->hasOptionalElements() == false);
  fail_unless(r->getListOfReactants()->isSetId() == true);
  fail_unless(r->getListOfReactants()->getId() == "d");

  fail_unless( r->getNumProducts() == 0);
  fail_unless(r->getListOfProducts()->isSetName() == true);
  fail_unless(r->getListOfProducts()->getName() == "ss");

  fail_unless( r->getNumModifiers() == 0);
  fail_unless(r->getListOfModifiers()->isSetSBOTerm() == true);
  fail_unless(r->getListOfModifiers()->getSBOTerm() == 2);

  KineticLaw * kl = r->getKineticLaw();

  fail_unless( kl != NULL);
  fail_unless( kl->getNumLocalParameters() == 0);
  fail_unless( kl->getListOfLocalParameters()->hasOptionalAttributes() == false);
  fail_unless( kl->getListOfLocalParameters()->hasOptionalElements() == true);
  fail_unless( kl->getListOfLocalParameters()->isSetNotes() == true);
  fail_unless( kl->getListOfLocalParameters()->isSetAnnotation() == false);

  Event * e = m->getEvent(0);

  fail_unless( e != NULL);
  fail_unless( e->getNumEventAssignments() == 0);
  fail_unless( e->getListOfEventAssignments()->hasOptionalAttributes() == false);
  fail_unless( e->getListOfEventAssignments()->hasOptionalElements() == true);
  fail_unless( e->getListOfEventAssignments()->isSetNotes() == false);
  fail_unless( e->getListOfEventAssignments()->isSetAnnotation() == true);

  delete d;
}
END_TEST

START_TEST(test_echo_l3v2_empty_lo_2)
{
  const char *expected = 
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version2/core\" "
    "level=\"3\" version=\"2\">\n" 
    "  <model substanceUnits=\"mole\" timeUnits=\"second\" volumeUnits=\"litre\" "
        "areaUnits=\"metre\" lengthUnits=\"metre\" extentUnits=\"mole\" "
        "conversionFactor=\"p\">\n"
    "    <listOfUnitDefinitions>\n"
    "      <unitDefinition id=\"nonsense\">\n"
    "        <listOfUnits metaid=\"dd\"/>\n"
    "      </unitDefinition>\n"
    "    </listOfUnitDefinitions>\n"
    "    <listOfReactions>\n"
    "      <reaction id=\"in\" reversible=\"false\" compartment=\"comp\">\n"
    "        <listOfReactants id=\"d\"/>\n"
    "        <listOfProducts name=\"ss\"/>\n"
    "        <listOfModifiers sboTerm=\"SBO:0000002\"/>\n"
    "        <kineticLaw>\n"
    "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
    "            <apply>\n"
    "              <times/>\n"
    "              <ci> k1 </ci>\n"
    "              <ci> X0 </ci>\n"
    "              <ci> cell </ci>\n"
    "            </apply>\n"
    "          </math>\n"
    "          <listOfLocalParameters>\n"
    "            <notes>\n"
    "              <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
    "                <center>\n"
    "                  <h2>A Simple Mitotic Oscillator</h2>\n"
    "                </center>\n"
    "                <p>A minimal cascade model for the mitotic oscillator involving cyclin and cdc2 kinase</p>\n"
    "              </body>\n"
    "            </notes>\n"
    "          </listOfLocalParameters>\n"
    "        </kineticLaw>\n"
    "      </reaction>\n"
    "    </listOfReactions>\n"
    "    <listOfEvents>\n"
    "      <event sboTerm=\"SBO:0000231\" id=\"e1\" useValuesFromTriggerTime=\"true\">\n"
    "        <trigger initialValue=\"false\" persistent=\"false\">\n"
    "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
    "            <true/>\n"
    "          </math>\n"
    "        </trigger>\n"
    "        <listOfEventAssignments>\n"
    "          <annotation>\n"
    "            <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" "
             "xmlns:dc=\"http://purl.org/dc/elements/1.1/\" "
             "xmlns:dcterms=\"http://purl.org/dc/terms/\" "
             "xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\" "
             "xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" "
             "xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\">\n"
    "              <rdf:Description rdf:about=\"#_000002\">\n"
    "                <bqbiol:is>\n"
    "                  <rdf:Bag>\n"
    "                    <rdf:li rdf:resource=\"http://www.geneontology.org/#GO:0007274\"/>\n"
    "                    <rdf:li rdf:resource=\"http://www.geneontology.org/#GO:0015464\"/>\n"
    "                    <rdf:li rdf:resource=\"http://www.genome.jp/kegg/pathway/#hsa04080\"/>\n"
    "                    <rdf:li rdf:resource=\"http://www.ncbi.nlm.nih.gov/Taxonomy/#7787\"/>\n"
    "                  </rdf:Bag>\n"
    "                </bqbiol:is>\n"
    "              </rdf:Description>\n"
    "            </rdf:RDF>\n"
    "          </annotation>\n"
    "        </listOfEventAssignments>\n"
    "      </event>\n"
    "    </listOfEvents>\n"
    "  </model>\n"
    "</sbml>\n";

  std::string filename(TestDataDirectory);
  filename += "l3v2-empty-lo-2.xml";

  std::string fileout(TestDataDirectory);
  fileout += "tempOut.xml";

  SBMLDocument* d = readSBML(filename.c_str());

  if (d == NULL)
  {
    fail("readSBML(\"l3v2-empty-lo-2.xml\") returned a NULL pointer.");
  }

  writeSBML(d, fileout.c_str());

  SBMLDocument* outD = readSBML(fileout.c_str());

  Model * m = outD->getModel();
  fail_unless( m != NULL, NULL );

  fail_unless(m->getNumUnitDefinitions() == 1);
  fail_unless(m->getNumFunctionDefinitions() == 0);
  fail_unless(m->getNumCompartments() == 0);
  fail_unless(m->getNumSpecies() == 0);
  fail_unless(m->getNumParameters() == 0);
  fail_unless(m->getNumRules() == 0);
  fail_unless(m->getNumInitialAssignments() == 0);
  fail_unless(m->getNumConstraints() == 0);
  fail_unless(m->getNumReactions() == 1);
  fail_unless(m->getNumEvents() == 1);

  UnitDefinition * ud = m->getUnitDefinition(0);

  fail_unless( ud != NULL);
  fail_unless( ud->getNumUnits() == 0);
  fail_unless( ud->getListOfUnits()->isSetMetaId() == true);
  fail_unless( ud->getListOfUnits()->getMetaId() == "dd");

  Reaction * r = m->getReaction(0);

  fail_unless( r != NULL);
  
  fail_unless( r->getNumReactants() == 0);
  fail_unless(r->getListOfReactants()->isSetId() == true);
  fail_unless(r->getListOfReactants()->getId() == "d");

  fail_unless( r->getNumProducts() == 0);
  fail_unless(r->getListOfProducts()->isSetName() == true);
  fail_unless(r->getListOfProducts()->getName() == "ss");

  fail_unless( r->getNumModifiers() == 0);
  fail_unless(r->getListOfModifiers()->isSetSBOTerm() == true);
  fail_unless(r->getListOfModifiers()->getSBOTerm() == 2);

  KineticLaw * kl = r->getKineticLaw();

  fail_unless( kl != NULL);
  fail_unless( kl->getNumLocalParameters() == 0);
  fail_unless( kl->getListOfLocalParameters()->isSetNotes() == true);
  fail_unless( kl->getListOfLocalParameters()->isSetAnnotation() == false);

  Event * e = m->getEvent(0);

  fail_unless( e != NULL);
  fail_unless( e->getNumEventAssignments() == 0);
  fail_unless( e->getListOfEventAssignments()->isSetNotes() == false);
  fail_unless( e->getListOfEventAssignments()->isSetAnnotation() == true);

  char * S = writeSBMLToString(outD);

  fail_unless( equals(expected, S) );

  safe_free(S);

  delete d;
  delete outD;
}
END_TEST


Suite *
create_suite_TestReadFromFileL3V2_3 (void)
{ 
  Suite *suite = suite_create("test-data/l3v2-empty-lo-2.xml");
  TCase *tcase = tcase_create("test-data/l3v2-empty-lo-2.xml");


  tcase_add_test(tcase, test_read_l3v2_empty_lo_2);
  tcase_add_test(tcase, test_echo_l3v2_empty_lo_2);

  suite_add_tcase(suite, tcase);

  return suite;
}


END_C_DECLS
