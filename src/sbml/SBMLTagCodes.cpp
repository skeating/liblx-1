/**
 * \file    SBMLTagCodes.cpp
 * \brief   Maps SBML elements to numbers for comparing and storing
 * \author  Ben Bornstein
 *
 * $Id$
 * $Source$
 */
/* Copyright 2002 California Institute of Technology and
 * Japan Science and Technology Corporation.
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License, or
 * any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY, WITHOUT EVEN THE IMPLIED WARRANTY OF
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  The software and
 * documentation provided hereunder is on an "as is" basis, and the
 * California Institute of Technology and Japan Science and Technology
 * Corporation have no obligations to provide maintenance, support,
 * updates, enhancements or modifications.  In no event shall the
 * California Institute of Technology or the Japan Science and Technology
 * Corporation be liable to any party for direct, indirect, special,
 * incidental or consequential damages, including lost profits, arising
 * out of the use of this software and its documentation, even if the
 * California Institute of Technology and/or Japan Science and Technology
 * Corporation have been advised of the possibility of such damage.  See
 * the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 *
 * The original code contained here was initially developed by:
 *
 *     Ben Bornstein
 *     The Systems Biology Markup Language Development Group
 *     ERATO Kitano Symbiotic Systems Project
 *     Control and Dynamical Systems, MC 107-81
 *     California Institute of Technology
 *     Pasadena, CA, 91125, USA
 *
 *     http://www.cds.caltech.edu/erato
 *     mailto:sbml-team@caltech.edu
 *
 * Contributor(s):
 *   Stefan Hoops
 */


#include <iostream>
#include "common.h"


#ifdef USE_EXPAT
#  include "ExpatXMLString.h"
#else
#  include <xercesc/util/XMLString.hpp>
#  include <xercesc/util/XMLUniDefs.hpp>
#endif  // USE_EXPAT


#include "SBMLTagCodes.h"
#include "SBMLUnicodeConstants.h"


static const XMLCh* SBML_ELEMENTS[] =
{
    ELEM_ALGEBRAIC_RULE
  , ELEM_ANNOTATION
  , ELEM_ANNOTATIONS
  , ELEM_ASSIGNMENT_RULE
  , ELEM_COMPARTMENT
  , ELEM_COMPARTMENT_VOLUME_RULE
  , ELEM_DELAY
  , ELEM_EVENT
  , ELEM_EVENT_ASSIGNMENT
  , ELEM_FUNCTION_DEFINITION
  , ELEM_KINETIC_LAW
  , ELEM_LIST_OF_COMPARTMENTS
  , ELEM_LIST_OF_EVENT_ASSIGNMENTS
  , ELEM_LIST_OF_EVENTS
  , ELEM_LIST_OF_FUNCTION_DEFINITIONS
  , ELEM_LIST_OF_MODIFIERS
  , ELEM_LIST_OF_PARAMETERS
  , ELEM_LIST_OF_PRODUCTS
  , ELEM_LIST_OF_REACTANTS
  , ELEM_LIST_OF_REACTIONS
  , ELEM_LIST_OF_RULES
  , ELEM_LIST_OF_SPECIES
  , ELEM_LIST_OF_UNIT_DEFINITIONS
  , ELEM_LIST_OF_UNITS
  , ELEM_MATH
  , ELEM_MODEL
  , ELEM_MODIFIER_SPECIES_REFERENCE
  , ELEM_NOTES
  , ELEM_PARAMETER
  , ELEM_PARAMETER_RULE
  , ELEM_RATE_RULE
  , ELEM_REACTION
  , ELEM_SBML
  , ELEM_SPECIE
  , ELEM_SPECIE_CONCENTRATION_RULE
  , ELEM_SPECIE_REFERENCE
  , ELEM_SPECIES
  , ELEM_SPECIES_CONCENTRATION_RULE
  , ELEM_SPECIES_REFERENCE
  , ELEM_STOICHIOMETRY_MATH
  , ELEM_TRIGGER
  , ELEM_UNIT
  , ELEM_UNIT_DEFINITION
};


/**
 * Returns the tag code for the given SBML element.
 */
SBMLTagCode_t
SBMLTagCode_forElement (const XMLCh* name)
{
  SBMLTagCode_t hc  = TAG_UNKNOWN;
  SBMLTagCode_t lo  = TAG_ALGEBRAIC_RULE;
  SBMLTagCode_t hi  = TAG_UNIT_DEFINITION;
  SBMLTagCode_t mid;

  int cond;


  /* Proceed iff name is not NULL and name is not an empty string */
  if (name && *name)
  {
    /* Classic Binary Search */
    while (lo <= hi)
    {
      mid  = (lo + hi) / 2;
      cond = XMLString::compareString(name, SBML_ELEMENTS[mid]);
      
      if (cond < 0)
      {
        hi = mid - 1;
      }
      else if (cond > 0)
      {
        lo = mid + 1;
      }
      else
      {
        hc = mid;
        break;
      }
    }
  }

  return hc;
}
