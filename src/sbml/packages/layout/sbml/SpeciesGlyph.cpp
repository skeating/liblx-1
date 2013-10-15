/**
 * @file    SpeciesGlyph.cpp
 * @brief   Implementation of SpeciesGlyph for SBML Layout.
 * @author  Ralph Gauges
 * 
 * <!--------------------------------------------------------------------------
 * Description : SBML Layout SpeciesGlyph source
 * Organization: European Media Laboratories Research gGmbH
 * Created     : 2004-07-15
 *
 * Copyright 2004 European Media Laboratories Research gGmbH
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
 * European Media Laboratories Research gGmbH have no obligations to
 * provide maintenance, support, updates, enhancements or modifications.
 * In no event shall the European Media Laboratories Research gGmbH be
 * liable to any party for direct, indirect, special, incidental or
 * consequential damages, including lost profits, arising out of the use of
 * this software and its documentation, even if the European Media
 * Laboratories Research gGmbH have been advised of the possibility of such
 * damage.  See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The original code contained here was initially developed by:
 *
 *     Ralph Gauges
 *     Bioinformatics Group
 *     European Media Laboratories Research gGmbH
 *     Schloss-Wolfsbrunnenweg 31c
 *     69118 Heidelberg
 *     Germany
 *
 *     http://www.eml-research.de/english/Research/BCB/
 *     mailto:ralph.gauges@eml-r.villa-bosch.de
 *
 * Contributor(s):
 *
 *     Akiya Jouraku <jouraku@bio.keio.ac.jp>
 *     Modified this file for package extension in libSBML5
 *
 */


#include <sbml/packages/layout/sbml/SpeciesGlyph.h>
#include <sbml/packages/layout/sbml/Layout.h>
#include <sbml/packages/layout/util/LayoutUtilities.h>
#include <sbml/packages/layout/extension/LayoutExtension.h>
#include <sbml/xml/XMLNode.h>
#include <sbml/xml/XMLToken.h>
#include <sbml/xml/XMLAttributes.h>
#include <sbml/xml/XMLInputStream.h>
#include <sbml/xml/XMLOutputStream.h>

#include <sbml/packages/layout/validator/LayoutSBMLError.h>
LIBSBML_CPP_NAMESPACE_BEGIN

void
SpeciesGlyph::renameSIdRefs(const std::string& oldid, const std::string& newid)
{
  GraphicalObject::renameSIdRefs(oldid, newid);
  if (isSetSpeciesId() && mSpecies == oldid) 
  {
    mSpecies = newid;
  }
}

/*
 * Creates a new SpeciesGlyph with the given SBML level, version, and package version
 * and the id of the associated species set to the empty string.
 */        
SpeciesGlyph::SpeciesGlyph (unsigned int level, unsigned int version, unsigned int pkgVersion)
  : GraphicalObject(level,version,pkgVersion)
  , mSpecies("")
{
  //
  // (NOTE) Developers don't have to invoke setSBMLNamespacesAndOwn function as follows (commentted line)
  //        in this constuctor because the function is properly invoked in the constructor of the
  //        base class (GraphicalObject).
  //

  //setSBMLNamespacesAndOwn(new LayoutPkgNamespaces(level,version,pkgVersion));  
}


/*
 * Creates a new SpeciesGlyph with the given LayoutPkgNamespaces 
 * and the id of the associated species set to the empty string.
 */        
SpeciesGlyph::SpeciesGlyph (LayoutPkgNamespaces* layoutns)
  : GraphicalObject(layoutns)
  , mSpecies("")
{
  //
  // (NOTE) Developers don't have to invoke setElementNamespace function as follows (commentted line)
  //        in this constuctor because the function is properly invoked in the constructor of the
  //        base class (LineSegment).
  //

  // setElementNamespace(layoutns->getURI());

  //
  // load package extensions bound with this object (if any) 
  //
  loadPlugins(layoutns);
}


/*
 * Creates a new SpeciesGlyph with the given @p id.
 */ 
SpeciesGlyph::SpeciesGlyph (LayoutPkgNamespaces* layoutns, const std::string& sid)
 : GraphicalObject(layoutns, sid )
  ,mSpecies("")
{
  //
  // (NOTE) Developers don't have to invoke setElementNamespace function as follows (commentted line)
  //        in this constuctor because the function is properly invoked in the constructor of the
  //        base class (LineSegment).
  //

  // setElementNamespace(layoutns->getURI());

  //
  // load package extensions bound with this object (if any) 
  //
  loadPlugins(layoutns);
}

/*
 * Creates a new SpeciesGlyph with the given @p id and the id of the
 * associated species object set to the second argument.
 */ 
SpeciesGlyph::SpeciesGlyph (LayoutPkgNamespaces* layoutns, const std::string& sid,
                            const std::string& speciesId) 
 : GraphicalObject( layoutns, sid )
  ,mSpecies        ( speciesId )
{
  //
  // (NOTE) Developers don't have to invoke setElementNamespace function as follows (commentted line)
  //        in this constuctor because the function is properly invoked in the constructor of the
  //        base class (LineSegment).
  //

  // setElementNamespace(layoutns->getURI());

  //
  // load package extensions bound with this object (if any) 
  //
  loadPlugins(layoutns);
}

/*
 * Creates a new SpeciesGlyph from the given XMLNode
 */
SpeciesGlyph::SpeciesGlyph(const XMLNode& node, unsigned int l2version)
 : GraphicalObject(node, l2version)
  ,mSpecies("")
{
    const XMLAttributes& attributes=node.getAttributes();
    ExpectedAttributes ea;
    addExpectedAttributes(ea);
    this->readAttributes(attributes,ea);
}

/*
 * Copy constructor.
 */
SpeciesGlyph::SpeciesGlyph(const SpeciesGlyph& source):GraphicalObject(source)
{
    this->mSpecies=source.getSpeciesId();
}

/*
 * Assignment operator.
 */
SpeciesGlyph& SpeciesGlyph::operator=(const SpeciesGlyph& source)
{
  if(&source!=this)
  {
    GraphicalObject::operator=(source);
    this->mSpecies=source.getSpeciesId();    
  }
  
  return *this;
}


/*
 * Destructor.
 */ 
SpeciesGlyph::~SpeciesGlyph ()
{
} 


/*
 * Returns the id of the associated species object.
 */ 
const std::string&
SpeciesGlyph::getSpeciesId () const
{
  return this->mSpecies;
}


/*
 * Sets the id of the associated species object.
 */ 
void
SpeciesGlyph::setSpeciesId (const std::string& id)
{
  this->mSpecies=id;
} 


/*
 * Returns true if the id of the associated species object is not the empty
 * string.
 */ 
bool
SpeciesGlyph::isSetSpeciesId () const
{
  return ! this->mSpecies.empty();
}


/*
 * Calls initDefaults from GraphicalObject.
 */ 
void SpeciesGlyph::initDefaults ()
{
  GraphicalObject::initDefaults();
}

/*
 * Returns the XML element name of
 * this SBML object.
 */
const std::string& SpeciesGlyph::getElementName () const 
{
  static const std::string name = "speciesGlyph";
  return name;
}

/*
 * @return a (deep) copy of this SpeciesGlyph.
 */
SpeciesGlyph* 
SpeciesGlyph::clone () const
{
    return new SpeciesGlyph(*this);
}


/** @cond doxygenLibsbmlInternal */
SBase*
SpeciesGlyph::createObject (XMLInputStream& stream)
{
  SBase*        object = 0;

  object=GraphicalObject::createObject(stream);
  
  return object;
}
/** @endcond */

/** @cond doxygenLibsbmlInternal */
void
SpeciesGlyph::addExpectedAttributes(ExpectedAttributes& attributes)
{
  GraphicalObject::addExpectedAttributes(attributes);

  attributes.add("species");
}
/** @endcond */

/** @cond doxygenLibsbmlInternal */
void SpeciesGlyph::readAttributes (const XMLAttributes& attributes,
                                   const ExpectedAttributes& expectedAttributes)
{
	const unsigned int sbmlLevel   = getLevel  ();
	const unsigned int sbmlVersion = getVersion();

	unsigned int numErrs;

	/* look to see whether an unknown attribute error was logged
	 * during the read of the listOfSpeciesGlyphs - which will have
	 * happened immediately prior to this read
	*/

  bool loSubGlyphs = false;
  if (getParentSBMLObject() != NULL
    && getParentSBMLObject()->getElementName() == "listOfSubGlyphs")
  {
    loSubGlyphs = true;
  }

	if (getErrorLog() != NULL &&
	    static_cast<ListOfSpeciesGlyphs*>(getParentSBMLObject())->size() < 2)
	{
		numErrs = getErrorLog()->getNumErrors();
		for (int n = numErrs-1; n >= 0; n--)
		{
			if (getErrorLog()->getError(n)->getErrorId() == UnknownPackageAttribute)
			{
				const std::string details =
				      getErrorLog()->getError(n)->getMessage();
				getErrorLog()->remove(UnknownPackageAttribute);
        if (loSubGlyphs == true)
        {
				  getErrorLog()->logPackageError("layout", 
                                    LayoutLOSubGlyphAllowedAttribs,
				            getPackageVersion(), sbmlLevel, sbmlVersion, details);
        }
        else
        {
				  getErrorLog()->logPackageError("layout", 
                                    LayoutLOSpeciesGlyphAllowedAttributes,
				            getPackageVersion(), sbmlLevel, sbmlVersion, details);
        }
			}
			else if (getErrorLog()->getError(n)->getErrorId() == UnknownCoreAttribute)
			{
				const std::string details =
				           getErrorLog()->getError(n)->getMessage();
				getErrorLog()->remove(UnknownCoreAttribute);
        if (loSubGlyphs == true)
        {
				  getErrorLog()->logPackageError("layout", 
                                    LayoutLOSubGlyphAllowedAttribs,
				            getPackageVersion(), sbmlLevel, sbmlVersion, details);
        }
        else
        {
				  getErrorLog()->logPackageError("layout", 
                                    LayoutLOSpeciesGlyphAllowedAttributes,
				            getPackageVersion(), sbmlLevel, sbmlVersion, details);
        }
			}
		}
	}

	GraphicalObject::readAttributes(attributes, expectedAttributes);

	// look to see whether an unknown attribute error was logged
	if (getErrorLog() != NULL)
	{
		numErrs = getErrorLog()->getNumErrors();
		for (int n = numErrs-1; n >= 0; n--)
		{
			if (getErrorLog()->getError(n)->getErrorId() == UnknownPackageAttribute)
			{
				const std::string details =
				                  getErrorLog()->getError(n)->getMessage();
				getErrorLog()->remove(UnknownPackageAttribute);
				getErrorLog()->logPackageError("layout", LayoutSGAllowedAttributes,
				               getPackageVersion(), sbmlLevel, sbmlVersion, details);
			}
			else if (getErrorLog()->getError(n)->getErrorId() == UnknownCoreAttribute)
			{
				const std::string details =
				                  getErrorLog()->getError(n)->getMessage();
				getErrorLog()->remove(UnknownCoreAttribute);
				getErrorLog()->logPackageError("layout", LayoutSGAllowedCoreAttributes,
				               getPackageVersion(), sbmlLevel, sbmlVersion, details);
			}
		}
	}

	bool assigned = false;

	//
	// species SIdRef   ( use = "optional" )
	//
	assigned = attributes.readInto("species", mSpecies);

	if (assigned == true && getErrorLog() != NULL)
	{
		// check string is not empty and correct syntax

		if (mSpecies.empty() == true)
		{
			logEmptyString(mSpecies, getLevel(), getVersion(), "<SpeciesGlyph>");
		}
		else if (SyntaxChecker::isValidSBMLSId(mSpecies) == false)
		{
			getErrorLog()->logPackageError("layout", LayoutSGSpeciesSyntax,
				             getPackageVersion(), sbmlLevel, sbmlVersion);
		}
	}

}
/** @endcond */

/** @cond doxygenLibsbmlInternal */
void SpeciesGlyph::writeElements (XMLOutputStream& stream) const
{
  GraphicalObject::writeElements(stream);

  //
  // (EXTENSION)
  //
  SBase::writeExtensionElements(stream);
}
/** @endcond */

/** @cond doxygenLibsbmlInternal */
void SpeciesGlyph::writeAttributes (XMLOutputStream& stream) const
{
  GraphicalObject::writeAttributes(stream);
  if(this->isSetSpeciesId())
  {
    stream.writeAttribute("species", getPrefix(), mSpecies);
  }

  //
  // (EXTENSION) will be written by GraphicalObject!
  //
  //SBase::writeExtensionAttributes(stream);

}
/** @endcond */


/*
 * Returns the package type code for this object.
 */
int
SpeciesGlyph::getTypeCode () const
{
  return SBML_LAYOUT_SPECIESGLYPH;
}

/*
 * Creates an XMLNode object from this.
 */
XMLNode SpeciesGlyph::toXML() const
{
 return getXmlNodeForSBase(this);
}





/**
 * Creates a new SpeciesGlyph and returns the pointer to it.
 */
LIBSBML_EXTERN
SpeciesGlyph_t *
SpeciesGlyph_create (void)
{
  return new(std::nothrow) SpeciesGlyph;
}


/**
 * Create a new SpeciesGlyph object from a template.
 */
LIBSBML_EXTERN
SpeciesGlyph_t *
SpeciesGlyph_createFrom (const SpeciesGlyph_t *temp)
{
  return new(std::nothrow) SpeciesGlyph(*temp);
}


/**
 * Creates a new SpeciesGlyph with the given @p id
 */
LIBSBML_EXTERN
SpeciesGlyph_t *
SpeciesGlyph_createWith (const char *id)
{
  LayoutPkgNamespaces layoutns;
  return new(std::nothrow) SpeciesGlyph(&layoutns, id ? id : "", "");
}


/**
 * Creates a new SpeciesGlyph referencing with the give species id.
 */
LIBSBML_EXTERN
SpeciesGlyph_t *
SpeciesGlyph_createWithSpeciesId (const char *sid, const char *speciesId)
{
  LayoutPkgNamespaces layoutns;
  return new(std::nothrow) SpeciesGlyph(&layoutns, sid ? sid : "", speciesId ? speciesId : "");
}


/**
 * Frees the memory taken by the given compartment glyph.
 */
LIBSBML_EXTERN
void
SpeciesGlyph_free (SpeciesGlyph_t *sg)
{
  delete sg;
}


/**
 * Sets the associated species id. 
 */
LIBSBML_EXTERN
void
SpeciesGlyph_setSpeciesId (SpeciesGlyph_t *sg, const char *id)
{
    static_cast<SpeciesGlyph*>(sg)->setSpeciesId( id ? id : "" );
}


/**
 * Gets the the id of the associated species.
 */
LIBSBML_EXTERN
const char *
SpeciesGlyph_getSpeciesId (const SpeciesGlyph_t *sg)
{
    return sg->isSetSpeciesId() ? sg->getSpeciesId().c_str() : NULL ;
}



/**
 * Returns 0 if the  id of the associated species is the empty string.
 * otherwise.
 */
LIBSBML_EXTERN
int
SpeciesGlyph_isSetSpeciesId (const SpeciesGlyph_t *sg)
{
  return static_cast<int>( sg->isSetSpeciesId() );
}


/**
 * Calls initDefaults from GraphicalObject.
 */ 
LIBSBML_EXTERN
void
SpeciesGlyph_initDefaults (SpeciesGlyph_t *sg)
{
  sg->initDefaults();
}


/**
 * @return a (deep) copy of this SpeciesGlyph.
 */
LIBSBML_EXTERN
SpeciesGlyph_t *
SpeciesGlyph_clone (const SpeciesGlyph_t *m)
{
  return static_cast<SpeciesGlyph*>( m->clone() );
}

LIBSBML_CPP_NAMESPACE_END

