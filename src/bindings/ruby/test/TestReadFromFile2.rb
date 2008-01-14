#
# @file    TestReadFromFile2.rb
# @brief   Reads tests/l1v1-units.xml into memory and tests it.
# @author  Akiya Jouraku (Ruby conversion)
# @author  Ben Bornstein 
#
# $Id$
# $Source$
#
# This test file was converted from src/sbml/test/TestReadFromFile2.c
# wiht the help of conversion sciprt (ctest_converter.pl).
#
#<!---------------------------------------------------------------------------
# This file is part of libSBML.  Please visit http://sbml.org for more
# information about SBML, and the latest version of libSBML.
#
# Copyright 2005-2008 California Institute of Technology.
# Copyright 2002-2005 California Institute of Technology and
#                     Japan Science and Technology Corporation.
# 
# This library is free software; you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation.  A copy of the license agreement is provided
# in the file named "LICENSE.txt" included with this software distribution
# and also available online as http://sbml.org/software/libsbml/license.html
#--------------------------------------------------------------------------->*/
#
require 'test/unit'
require 'libSBML'

class TestReadFromFile2 < Test::Unit::TestCase

  def test_create_l1v1_units
    d = LibSBML::SBMLDocument.new
    m = LibSBML::Model.new
    d.setModel(m)
    ud = m.createUnitDefinition
    ud.setName( "substance")
    u = m.createUnit
    u.setKind(LibSBML::UNIT_KIND_MOLE)
    u.setScale(-3)
    ud = m.createUnitDefinition
    ud.setName( "mls")
    u = m.createUnit
    u.setKind(LibSBML::UNIT_KIND_MOLE)
    u.setScale(-3)
    u = m.createUnit
    u.setKind(LibSBML::UNIT_KIND_LITER)
    u.setExponent(-1)
    u = m.createUnit
    u.setKind(LibSBML::UNIT_KIND_SECOND)
    u.setExponent(-1)
    c = m.createCompartment
    c.setName( "cell")
    s = m.createSpecies
    s.setName( "x0")
    s.setCompartment( "cell")
    s.setInitialAmount(1)
    s = m.createSpecies
    s.setName( "x1")
    s.setCompartment( "cell")
    s.setInitialAmount(1)
    s = m.createSpecies
    s.setName( "s1")
    s.setCompartment( "cell")
    s.setInitialAmount(1)
    s = m.createSpecies
    s.setName( "s2")
    s.setCompartment( "cell")
    s.setInitialAmount(1)
    p = m.createParameter
    p.setName( "vm")
    p.setUnits( "mls")
    p.setValue(2)
    p = m.createParameter
    p.setName( "km")
    p.setValue(2)
    r = m.createReaction
    r.setName( "v1")
    sr = m.createReactant
    sr.setSpecies( "x0")
    sr = m.createProduct
    sr.setSpecies( "s1")
    kl = m.createKineticLaw
    kl.setFormula( "(vm * s1)/(km + s1)")
    r = m.createReaction
    r.setName( "v2")
    sr = m.createReactant
    sr.setSpecies( "s1")
    sr = m.createProduct
    sr.setSpecies( "s2")
    kl = m.createKineticLaw
    kl.setFormula( "(vm * s2)/(km + s2)")
    r = m.createReaction
    r.setName( "v3")
    sr = m.createReactant
    sr.setSpecies( "s2")
    sr = m.createProduct
    sr.setSpecies( "x1")
    kl = m.createKineticLaw
    kl.setFormula( "(vm * s1)/(km + s1)")
  end

  def test_read_l1v1_units
    filename = "../../sbml/test/test-data/l1v1-units.xml"
    d = LibSBML::readSBML(filename)
    if (d == nil)
    end
    assert( d.getLevel == 1 )
    assert( d.getVersion == 1 )
    m = d.getModel
    assert( m.getNumUnitDefinitions == 2 )
    ud = m.getUnitDefinition(0)
    assert ((  "substance" == ud.getName ))
    ud = m.getUnitDefinition(1)
    assert ((  "mls" == ud.getName ))
    ud = m.getUnitDefinition(0)
    assert( ud.getNumUnits == 1 )
    u = ud.getUnit(0)
    assert( u.getKind == LibSBML::UNIT_KIND_MOLE )
    assert( u.getExponent == 1 )
    assert( u.getScale == -3 )
    ud = m.getUnitDefinition(1)
    assert( ud.getNumUnits == 3 )
    u = ud.getUnit(0)
    assert( u.getKind == LibSBML::UNIT_KIND_MOLE )
    assert( u.getExponent == 1 )
    assert( u.getScale == -3 )
    u = ud.getUnit(1)
    assert( u.getKind == LibSBML::UNIT_KIND_LITER )
    assert( u.getExponent == -1 )
    assert( u.getScale == 0 )
    u = ud.getUnit(2)
    assert( u.getKind == LibSBML::UNIT_KIND_SECOND )
    assert( u.getExponent == -1 )
    assert( u.getScale == 0 )
    assert( m.getNumCompartments == 1 )
    c = m.getCompartment(0)
    assert ((  "cell" == c.getName ))
    assert( m.getNumSpecies == 4 )
    s = m.getSpecies(0)
    assert ((  "x0"    == s.getName ))
    assert ((  "cell"  == s.getCompartment ))
    assert( s.getInitialAmount == 1 )
    assert( s.getBoundaryCondition == false )
    s = m.getSpecies(1)
    assert ((  "x1"    == s.getName ))
    assert ((  "cell"  == s.getCompartment ))
    assert( s.getInitialAmount == 1 )
    assert( s.getBoundaryCondition == false )
    s = m.getSpecies(2)
    assert ((  "s1"    == s.getName ))
    assert ((  "cell"  == s.getCompartment ))
    assert( s.getInitialAmount == 1 )
    assert( s.getBoundaryCondition == false )
    s = m.getSpecies(3)
    assert ((  "s2"    == s.getName ))
    assert ((  "cell"  == s.getCompartment ))
    assert( s.getInitialAmount == 1 )
    assert( s.getBoundaryCondition == false )
    assert( m.getNumParameters == 2 )
    p = m.getParameter(0)
    assert ((  "vm"   == p.getName ))
    assert ((  "mls"  == p.getUnits ))
    assert( p.getValue == 2 )
    p = m.getParameter(1)
    assert ((  "km"   == p.getName ))
    assert( p.getValue == 2 )
    assert( m.getNumReactions == 3 )
    r = m.getReaction(0)
    assert ((  "v1" == r.getName ))
    assert( r.getReversible != false )
    assert( r.getFast == false )
    r = m.getReaction(1)
    assert ((  "v2" == r.getName ))
    assert( r.getReversible != false )
    assert( r.getFast == false )
    r = m.getReaction(2)
    assert ((  "v3" == r.getName ))
    assert( r.getReversible != false )
    assert( r.getFast == false )
    r = m.getReaction(0)
    assert( r.getNumReactants == 1 )
    assert( r.getNumProducts == 1 )
    sr = r.getReactant(0)
    assert ((  "x0" == sr.getSpecies ))
    assert( sr.getStoichiometry == 1 )
    assert( sr.getDenominator == 1 )
    sr = r.getProduct(0)
    assert ((  "s1" == sr.getSpecies ))
    assert( sr.getStoichiometry == 1 )
    assert( sr.getDenominator == 1 )
    kl = r.getKineticLaw
    assert ((  "cell * (vm * s1)/(km + s1)" == kl.getFormula ))
    r = m.getReaction(1)
    assert( r.getNumReactants == 1 )
    assert( r.getNumProducts == 1 )
    sr = r.getReactant(0)
    assert ((  "s1" == sr.getSpecies ))
    assert( sr.getStoichiometry == 1 )
    assert( sr.getDenominator == 1 )
    sr = r.getProduct(0)
    assert ((  "s2" == sr.getSpecies ))
    assert( sr.getStoichiometry == 1 )
    assert( sr.getDenominator == 1 )
    kl = r.getKineticLaw
    assert ((  "cell * (vm * s2)/(km + s2)" == kl.getFormula ))
    r = m.getReaction(2)
    assert( r.getNumReactants == 1 )
    assert( r.getNumProducts == 1 )
    sr = r.getReactant(0)
    assert ((  "s2" == sr.getSpecies ))
    assert( sr.getStoichiometry == 1 )
    assert( sr.getDenominator == 1 )
    sr = r.getProduct(0)
    assert ((  "x1" == sr.getSpecies ))
    assert( sr.getStoichiometry == 1 )
    assert( sr.getDenominator == 1 )
    kl = r.getKineticLaw
    assert ((  "cell * (vm * s1)/(km + s1)" == kl.getFormula ))
  end

end
