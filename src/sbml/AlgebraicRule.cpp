/**
 * \file   AlgebraicRule.cpp
 * \brief  Class implementing the SBML AlgebraicRule
 * \author Ben Bornstein
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
 *     http://www.sbml.org
 *     mailto:sbml-team@caltech.edu
 *
 * Contributor(s):
 */


#include "SBMLVisitor.h"
#include "AlgebraicRule.h"


/**
 * Creates a new AlgebraicRule, optionally with its formula attribute set.
 */
LIBSBML_EXTERN
AlgebraicRule::AlgebraicRule (const std::string& formula) : Rule(formula)
{
  init(SBML_ALGEBRAIC_RULE);
}


/**
 * Creates a new AlgebraicRule with its math attribute set.
 */
LIBSBML_EXTERN
AlgebraicRule::AlgebraicRule (ASTNode* math) : Rule((ASTNode*) math)
{
  init(SBML_ALGEBRAIC_RULE);
}


/**
 * Destroys this AlgebraicRule.
 */
LIBSBML_EXTERN
AlgebraicRule::~AlgebraicRule ()
{
}


/**
 * Accepts the given SBMLVisitor.
 *
 * @return the result of calling <code>v.visit()</code>, which indicates
 * whether or not the Visitor would like to visit the Model's next Rule
 * (if available).
 */
LIBSBML_EXTERN
bool
AlgebraicRule::accept (SBMLVisitor& v) const
{
  return v.visit(*this);
}


/**
 * Creates a new AlgebraicRule and returns a pointer to it.
 */
LIBSBML_EXTERN
AlgebraicRule_t *
AlgebraicRule_create (void)
{
  return new(std::nothrow) AlgebraicRule;
}


/**
 * Creates a new AlgebraicRule with the given \a formula and returns a
 * pointer to it.  This convenience function is functionally equivalent to:
 * \code
 *   AlgebraicRule_t *ar = AlgebraicRule_create();
 *   Rule_setFormula((Rule_t *) ar, formula);
 * \endcode
 */
LIBSBML_EXTERN
AlgebraicRule_t *
AlgebraicRule_createWith (const char *formula)
{
  return new(std::nothrow) AlgebraicRule(formula ? formula : "");
}


/**
 * Creates a new AlgebraicRule with the given \a math and returns a pointer
 * to it.  This convenience function is functionally equivalent to:
 * \code
 *   AlgebraicRule_t *ar = AlgebraicRule_create();
 *   Rule_setMath((Rule_t *) ar, math);
 * \endcode
 * The node <em>is not copied</em> and this AlgebraicRule <em>takes
 * ownership</em> of it; i.e. subsequent calls to this function or a call to
 * AlgebraicRule_free() will free the ASTNode (and any child nodes).
 */
LIBSBML_EXTERN
AlgebraicRule_t *
AlgebraicRule_createWithMath (ASTNode_t* math)
{
  return new(std::nothrow) AlgebraicRule( static_cast<ASTNode*>(math) );
}


/**
 * Frees the AlgebraicRule given by \a ar.
 */
LIBSBML_EXTERN
void
AlgebraicRule_free (AlgebraicRule_t *ar)
{
  delete static_cast<AlgebraicRule*>(ar);
}
