/**
 * @file    XMLError.cpp
 * @brief   Represents errors (and messages) encountered during an XML parse
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

#include <iostream>
#include <iomanip>
#include <sstream>

#include <liblx/xml/common/common.h>
#include <liblx/xml/XMLError.h>
#include <liblx/xml/XMLAttributes.h>
#include <liblx/xml/XMLConstructorException.h>
#include <liblx/xml/LibLXError.h>
#include <liblx/xml/operationReturnValues.h>

/** @cond doxygenIgnored */
using namespace std;
/** @endcond */

LIBLX_CPP_NAMESPACE_BEGIN
#ifdef __cplusplus

/** @cond doxygenLibsbmlInternal **/

static const xmlErrorTableEntry errorTable[] =
{
  // 0
  { XMLUnknownError, LIBSBXML_CAT_INTERNAL, LIBLX_SEV_FATAL,
    "Unknown error",
    "Unrecognized error encountered internally." },


  // System diagnostics:

  // 0001
  { XMLOutOfMemory, LIBSBXML_CAT_SYSTEM, LIBLX_SEV_FATAL,
    "Out of memory",
    "Out of memory." },

  // 0002
  { XMLFileUnreadable, LIBSBXML_CAT_SYSTEM, LIBLX_SEV_ERROR,
    "File unreadable",
    "File unreadable." },

  // 0003
  { XMLFileUnwritable, LIBSBXML_CAT_SYSTEM, LIBLX_SEV_ERROR,
    "File unwritable",
    "File unwritable." },

  // 0004
  { XMLFileOperationError, LIBSBXML_CAT_SYSTEM, LIBLX_SEV_ERROR,
    "File operation error",
    "Error encountered while attempting file operation." },

  // 0005
  { XMLNetworkAccessError, LIBSBXML_CAT_SYSTEM, LIBLX_SEV_ERROR,
    "Network access error",
    "Network access error." },


  // Internal diagnostics:

  // 0101
  { InternalXMLParserError, LIBSBXML_CAT_INTERNAL, LIBLX_SEV_FATAL,
    "Internal XML parser error",
    "Internal XML parser state error." },

  // 0102
  { UnrecognizedXMLParserCode, LIBSBXML_CAT_INTERNAL, LIBLX_SEV_FATAL,
    "Unrecognized XML parser code",
    "XML parser returned an unrecognized error code." },

  // 0102
  { XMLTranscoderError, LIBSBXML_CAT_INTERNAL, LIBLX_SEV_FATAL,
    "Transcoder error",
    "Character transcoder error." },


  // Diagnostics about XML content:

  // 1001
  { MissingXMLDecl, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Missing XML declaration",
    "Missing XML declaration at beginning of XML input." },

  // 1002
  { MissingXMLEncoding, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Missing XML encoding attribute",
    "Missing encoding attribute in XML declaration." },

  // 1003
  { BadXMLDecl, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Bad XML declaration",
    "Invalid or unrecognized XML declaration or XML encoding." },

  // 1004
  { BadXMLDOCTYPE, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Bad XML DOCTYPE",
    "Invalid, malformed or unrecognized XML DOCTYPE declaration." },

  // 1005
  { InvalidCharInXML, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Invalid character",
    "Invalid character in XML content." },

  // 1006
  { BadlyFormedXML, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Badly formed XML",
    "XML content is not well-formed." },

  // 1007
  { UnclosedXMLToken, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Unclosed token",
    "Unclosed XML token." },

  // 1008
  { InvalidXMLConstruct, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Invalid XML construct",
    "XML construct is invalid or not permitted." },

  // 1009
  { XMLTagMismatch, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "XML tag mismatch",
    "Element tag mismatch or missing tag." },

  // 1010
  { DuplicateXMLAttribute, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Duplicate attribute",
    "Duplicate XML attribute." },

  // 1011
  { UndefinedXMLEntity, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Undefined XML entity",
    "Undefined XML entity." },

  // 1012
  { BadProcessingInstruction, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Bad XML processing instruction",
    "Invalid, malformed or unrecognized XML processing instruction." },

  // 1013
  { BadXMLPrefix, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Bad XML prefix",
    "Invalid or undefined XML namespace prefix." },

  // 1014
  { BadXMLPrefixValue, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Bad XML prefix value",
    "Invalid XML namespace prefix value." },

  // 1015
  { MissingXMLRequiredAttribute, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Missing required attribute",
    "Missing a required XML attribute." },

  // 1016
  { XMLAttributeTypeMismatch, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Attribute type mismatch",
    "Data type mismatch for the value of an attribute." },

  // 1017
  { XMLBadUTF8Content, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Bad UTF8 content",
    "Invalid UTF8 content." },

  // 1018
  { MissingXMLAttributeValue, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Missing attribute value",
    "Missing or improperly formed attribute value." },

  // 1019
  { BadXMLAttributeValue, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Bad attribute value",
    "Invalid or unrecognizable attribute value." },

  // 1020
  { BadXMLAttribute, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Bad XML attribute",
    "Invalid, unrecognized or malformed attribute." },

  // 1021
  { UnrecognizedXMLElement, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Unrecognized XML element",
    "Element either not recognized or not permitted." },

  // 1022
  { BadXMLComment, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Bad XML comment",
    "Badly formed XML comment." },

  // 1023
  { BadXMLDeclLocation, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Bad XML declaration location",
    "XML declaration not permitted in this location." },

  // 1024
  { XMLUnexpectedEOF, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Unexpected EOF",
    "Reached end of input unexpectedly." },

  // 1025
  { BadXMLIDValue, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Bad XML ID value",
    "Value is invalid for XML ID, or has already been used." },

  // 1026
  { BadXMLIDRef, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Bad XML IDREF",
    "XML ID value was never declared." },

  // 1027
  { UninterpretableXMLContent, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Uninterpretable XML content",
    "Unable to interpret content." },

  // 1028
  { BadXMLDocumentStructure, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Bad XML document structure",
    "Bad XML document structure." },

  // 1029
  { InvalidAfterXMLContent, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Invalid content after XML content",
    "Encountered invalid content after expected content." },

  // 1031
  { XMLExpectedQuotedString, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Expected quoted string",
    "Expected to find a quoted string." },

  // 1032
  { XMLEmptyValueNotPermitted, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Empty value not permitted",
    "An empty value is not permitted in this context." },

  // 1033
  { XMLBadNumber, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Bad number",
    "Invalid or unrecognized number." },

  // 1034
  { XMLBadColon, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Colon character not permitted",
    "Colon characters are invalid in this context." },

  // 1035
  { MissingXMLElements, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Missing XML elements",
    "One or more expected elements are missing." },

  // 1036
  { XMLContentEmpty, LIBSBXML_CAT_XML, LIBLX_SEV_ERROR,
    "Empty XML content",
    "Main XML content is empty." },

};


/*
 * Table of strings corresponding to the values from XMLErrorSeverity_t.
 * Be careful that the enum is used to index into this table.
 * This approach is not very object oriented and someday we should do better.
 */
const char * xmlSeverityStringTable[] =
{
  "Informational"                       // LIBLX_SEV_INFO
, "Warning"                             // LIBLX_SEV_WARNING
, "Error"                               // LIBLX_SEV_ERROR
, "Fatal"                               // LIBLX_SEV_FATAL
};


/*
 * Table of strings corresponding to the values from XMLErrorCategory_t.
 * Be careful that the enum is used to index into this table.
 * This approach is not very object oriented and someday we should do better.
 */
const char * xmlCategoryStringTable[] =
{
  "Internal"                            // LIBSBXML_CAT_INTERNAL
, "Operating system"                    // LIBSBXML_CAT_SYSTEM
, "XML content"                         // LIBSBXML_CAT_XML
};
/** @endcond **/


/*
 * XMLErrorLog will check if line & column = 0 and attempt to fill in
 * the line and column by consulting the parser.  This constructor
 * purposefully doesn't do that.
 */
XMLError::XMLError (  const int errorId
                    , const std::string details
                    , const unsigned int line
                    , const unsigned int column
                    , const unsigned int severity
                    , const unsigned int category ) :
    mErrorId( (unsigned int)errorId )
  , mLine   ( line    )
  , mColumn ( column  )
  , mValidError ( true )
  , mPackage ("")
  , mErrorIdOffset (0)
{
  // Check if the given id is one we have in our table of error codes.  If
  // it is, fill in the fields of the error object with the appropriate
  // content.  If it's not in the table, take the content as-is.

  if ( errorId >= 0 && errorId < XMLErrorCodesUpperBound )
  {
    unsigned int tableSize = sizeof(errorTable)/sizeof(errorTable[0]);    

    for ( unsigned int i = 0; i < tableSize; i++ )
    {
      if ( errorTable[i].code == errorId )
      {
        mMessage      = errorTable[i].message;
        mShortMessage = errorTable[i].shortMessage;

        if ( !details.empty() )
        {
          mMessage.append(" ");
          mMessage.append(details);
        }
        mMessage += "\n";

        mSeverity = errorTable[i].severity;
        mCategory = errorTable[i].category;
        
        mSeverityString = stringForSeverity(mSeverity);
        mCategoryString = stringForCategory(mCategory);

        return;
      }
    }

    // The id is in the range of error numbers that are supposed to be in
    // the XML layer, but it's NOT in our table.  This is an internal error.

    //// Unfortunately, we don't have an error log or anywhere to report it
    //// except the measure of last resort: the standard error output.
    //
    //
    //cerr << "Internal error: unknown error code '" << errorId
    //     << "' encountered while processing error" << endl;

    // Changed this behaviour

    // Now we log the error as an UnKnown Error and mark it as invalid

    mMessage      = errorTable[0].message;
    mMessage += "\n";
    mShortMessage = errorTable[0].shortMessage;

    if ( !details.empty() )
    {
      mMessage.append(" ");
      mMessage.append(details);
      mMessage.append("\n");
    }

    mSeverity = LIBLX_SEV_WARNING;
    mCategory = errorTable[0].category;
    
    mSeverityString = stringForSeverity(mSeverity);
    mCategoryString = stringForCategory(mCategory);

    mValidError = false;
    return;

  }

  // It's not an error code in the XML layer, so assume the caller has
  // filled in all the relevant additional data.  (If they didn't, the
  // following ends up merely assigning the defaults.)

  mMessage  = details;

  // The following is just a default that seems more sensible than setting
  // an empty string for the short message.

  mShortMessage = mMessage;

  // Other initializations.

  if (severity == LIBLX_SEV_UNKNOWN) {
    mSeverity = LIBLX_SEV_ERROR;
  }
  else {
    mSeverity = severity;
  }
  mSeverityString = stringForSeverity(severity);

  mCategory       = category;
  mCategoryString = stringForCategory(category);
}


/*
 * Copy Constructor
 */
XMLError::XMLError(const XMLError& orig)
  : mErrorId        ( orig.mErrorId )
  , mMessage        ( orig.mMessage )
  , mShortMessage   ( orig.mShortMessage )
  , mSeverity       ( orig.mSeverity )
  , mCategory       ( orig.mCategory )
  , mLine           ( orig.mLine )
  , mColumn         ( orig.mColumn )
  , mSeverityString ( orig.mSeverityString )
  , mCategoryString ( orig.mCategoryString )
  , mValidError     ( orig.mValidError )
  , mPackage        ( orig.mPackage )
  , mErrorIdOffset  ( orig.mErrorIdOffset )
{
}


/*
 * Assignment operator
 */
XMLError& 
XMLError::operator=(const XMLError& rhs)
{
  if(&rhs!=this)
  {
    mErrorId        = rhs.mErrorId;
    mMessage        = rhs.mMessage;
    mShortMessage   = rhs.mShortMessage;
    mSeverity       = rhs.mSeverity;
    mCategory       = rhs.mCategory;
    mLine           = rhs.mLine;
    mColumn         = rhs.mColumn;
    mSeverityString = rhs.mSeverityString;
    mCategoryString = rhs.mCategoryString;
    mPackage        = rhs.mPackage;
    mErrorIdOffset  = rhs.mErrorIdOffset;
  }

  return *this;
}


/*
 * Destroys this XMLError.
 */
XMLError::~XMLError ()
{
}


/** @cond doxygenLibsbmlInternal **/
/*
 * Clone function.
 */
XMLError* 
XMLError::clone() const
{
  return new XMLError(*this);
}
/** @endcond **/


/*
 * @return the id of this XMLError.
 */
unsigned int
XMLError::getErrorId () const
{
  return mErrorId;
}


/*
 * @return the message text of this XMLError.
 */
const string&
XMLError::getMessage () const
{
  return mMessage;
}


/*
 * @return the short message text of this XMLError.
 */
const string&
XMLError::getShortMessage () const
{
  return mShortMessage;
}


/*
 * @return the line number where this XMLError ocurred.
 */
unsigned int
XMLError::getLine () const
{
  return mLine;
}


/*
 * @return the column number where this XMLError occurred.
 */
unsigned int
XMLError::getColumn () const
{
  return mColumn;
}


/*
 * @return the severity of this XMLError.  XMLError severity levels
 * correspond to those defined in the XML specification (with the addition
 * of Info for informational messages).
 */
unsigned int
XMLError::getSeverity () const
{
  return mSeverity;
}


/*
 * @return a string explaining the severity code for this XMLError.
 * XMLError severity levels correspond to those defined in the XML
 * specification (with the addition of Info for informational messages).
 */
const std::string& 
XMLError::getSeverityAsString() const
{
  return mSeverityString;
}


/*
 * @return the category of this XMLError.  A category is a string, similiar
 * in spirit to an XML namespace, which can be used to partition errors
 * into distinct groups.  Among other things, this can be used to prevent
 * id conflicts by uniquely identifying an XMLError by both id and
 * category.
 */
unsigned int
XMLError::getCategory () const
{
  return mCategory;
}


/*
 * @return a string explaining the category code for this XMLError.
 */
const std::string& 
XMLError::getCategoryAsString() const
{
  return mCategoryString;
}

const std::string& 
XMLError::getPackage() const
{
  return mPackage;
}

unsigned int
XMLError::getErrorIdOffset () const
{
  return mErrorIdOffset;
}




/*
 * @return @c true if this XMLError is for informational purposes only,
 * false otherwise.
 */
bool
XMLError::isInfo () const
{
  return (mSeverity == LIBLX_SEV_INFO);
}


/*
 * @return @c true if this XMLError is a warning, false otherwise.
 */
bool
XMLError::isWarning () const
{
  return (mSeverity == LIBLX_SEV_WARNING);
}


/*
 * @return @c true if this XMLError is an error, false otherwise.
 */
bool
XMLError::isError () const
{
  return (mSeverity == LIBLX_SEV_ERROR);
}


/*
 * @return @c true if this XMLError is a fatal error, false otherwise.
 */
bool
XMLError::isFatal () const
{
  return (mSeverity == LIBLX_SEV_FATAL);
}


/*
 * Predicate returning @c true or @c false depending on whether 
 * this XMLError resulted from the operating system.
 *
 * @return @c true or @c false
 */
bool
XMLError::isSystem () const
{
  return (mCategory == LIBSBXML_CAT_SYSTEM);
}


/*
 * Predicate returning @c true or @c false depending on whether this
 * XMLError resulted from a problem at the raw XML level (e.g., an XML
 * syntax error).
 *
 * @return @c true or @c false
 */
bool
XMLError::isXML () const
{
  return (mCategory == LIBSBXML_CAT_XML);
}


/*
 * Predicate returning @c true or @c false depending on whether this
 * XMLError resulted from an internal program error.
 *
 * @return @c true or @c false
 */
bool
XMLError::isInternal () const
{
  return (mCategory == LIBSBXML_CAT_INTERNAL);
}


/*
 * Predicate returning @c true or @c false depending on whether this
 * XMLError resulted from an internal program error.
 *
 * @return @c true or @c false
 */
bool
XMLError::isValid () const
{
  return mValidError;
}


/*
 * Sets the line number where this XMLError occurred.
 */
int
XMLError::setLine (unsigned int line)
{
  mLine = line;
  return LIBLX_OPERATION_SUCCESS;
}


/*
 * Sets the column number where this XMLError occurred.
 */
int
XMLError::setColumn (unsigned int column)
{
  mColumn = column;
  return LIBLX_OPERATION_SUCCESS;
}


/*
 * Given an XMLError::Code, return a copy of the error text.
 * 
 * @return the message text 
 */
const string
XMLError::getStandardMessage (const int code)
{
  string msg;

  if ( code >= 0 && code < XMLErrorCodesUpperBound )
  {
    unsigned int tableSize = sizeof(errorTable)/sizeof(errorTable[0]);    

    for ( unsigned int i = 0; i < tableSize; i++ )
      if ( errorTable[i].code == code )
        msg.append(errorTable[i].message);
  }
  
  return msg;
}


/** @cond doxygenLibsbmlInternal **/
/*
 * @return the severity as a string for the given @n code.
 */
std::string XMLError::stringForSeverity(unsigned int code) const
{
  if ( code >= LIBLX_SEV_INFO && code <= LIBLX_SEV_FATAL)
    return xmlSeverityStringTable[code];
  else 
    return "";
}
/** @endcond **/


/** @cond doxygenLibsbmlInternal **/
/*
 * @return the category as a string for the given @n code.
 */
std::string XMLError::stringForCategory(unsigned int code) const
{
  if ( code >= LIBSBXML_CAT_INTERNAL && code <= LIBSBXML_CAT_XML )
    return xmlCategoryStringTable[code];
  else 
    return "";
}
/** @endcond **/


/** @cond doxygenLibsbmlInternal **/
/*
 * Prints this XMLError to stream @p s in the following format (and followed
 * by a newline):
 *
 *   line: (error_id [severity]) message
 *
 * Implementation note:
 * The following code was originally written before the implementation of
 * xmlSeverityStringTable[] and getSeverityAsString().  It previously used
 * hard-code strings, and for LIBLX_SEV_INFO, it printed "Advisory"
 * instead of "Information".  However, an inspection of the libSBML code
 * showed that nothing ever used LIBLX_SEV_INFO!  Therefore, changing the
 * severity string used here to be the same as what getSeverityAsString()
 * returns should not break any caller code.
 */
void
XMLError::print(std::ostream& s) const
{
  s << "line " << getLine() << ": ("
    << setfill('0') << setw(5) << getErrorId()
    << " [" << getSeverityAsString() << "]) "
    << getMessage() << endl;
}
/** @endcond **/


/*
 * Outputs the given XMLError (or the derived class (e.g. SBMLError) ) to stream
 * by invoking the print function which is implemented as a virtual function in
 * the class.
 *
 */
ostream& operator<< (ostream& s, const XMLError& error)
{
  error.print(s);

  return s;
}


#endif /* __cplusplus */
/** @cond doxygenIgnored */
LIBLX_EXTERN
XMLError_t*
XMLError_create (void)
{
  return new(nothrow) XMLError;
}


LIBLX_EXTERN
XMLError_t*
XMLError_createWithIdAndMessage (unsigned int errorId, const char * message)
{
  if (message == NULL) return NULL;
  return new(nothrow) XMLError((int)errorId, message);
}

//LIBLX_EXTERN
//XMLError_t*
//XMLError_createWithAll (unsigned int errorId, const char * message, XMLError_Severity severity,
//                        const char * category, unsigned int line, unsigned int column)
//{
//  XMLError::Severity s;
//  switch (severity)
//  {
//  case Info:
//    s = XMLError::Severity::Info;
//    break;
//  case Warning:
//    s = XMLError::Severity::Warning;
//    break;
//  case Error:
//    s = XMLError::Severity::Error;
//    break;
//  case Fatal:
//    s = XMLError::Severity::Fatal;
//    break;
//  default:
//    s = XMLError::Severity::Error;
//    break;
//  }
//  return new(nothrow) XMLError(errorId, message, s, category, line, column);
//}


LIBLX_EXTERN
void
XMLError_free(XMLError_t* error)
{
  if (error == NULL) return;
  delete static_cast<XMLError*>(error);
}

LIBLX_EXTERN
unsigned int
XMLError_getErrorId (const XMLError_t *error)
{
  if (error == NULL) return SBML_INT_MAX;
  return error->getErrorId();
}


LIBLX_EXTERN
const char *
XMLError_getMessage (const XMLError_t *error)
{
  if (error == NULL) return NULL;
  return error->getMessage().empty() ? NULL : error->getMessage().c_str();
}


LIBLX_EXTERN
const char *
XMLError_getShortMessage (const XMLError_t *error)
{
  if (error == NULL) return NULL;
  return error->getShortMessage().empty() ? NULL : error->getShortMessage().c_str();
}


LIBLX_EXTERN
unsigned int
XMLError_getLine (const XMLError_t *error)
{
  if (error == NULL) return 0;
  return error->getLine();
}


LIBLX_EXTERN
unsigned int
XMLError_getColumn (const XMLError_t *error)
{
  if (error == NULL) return 0;
  return error->getColumn();
}


LIBLX_EXTERN
unsigned int
XMLError_getSeverity (const XMLError_t *error)
{
  if (error == NULL) return SBML_INT_MAX;
  return error->getSeverity();
}


LIBLX_EXTERN
const char *
XMLError_getSeverityAsString (const XMLError_t *error)
{
  if (error == NULL) return NULL;
  return error->getSeverityAsString().empty() ? NULL : 
                            error->getSeverityAsString().c_str();
}


LIBLX_EXTERN
unsigned int
XMLError_getCategory (const XMLError_t *error)
{
  if (error == NULL) return SBML_INT_MAX;
  return error->getCategory();
}


LIBLX_EXTERN
const char *
XMLError_getCategoryAsString (const XMLError_t *error)
{
  if (error == NULL) return NULL;
  return error->getCategoryAsString().empty() ? NULL : 
                             error->getCategoryAsString().c_str();
}


LIBLX_EXTERN
int
XMLError_isInfo (const XMLError_t *error)
{
  if (error == NULL) return (int)false;
  return static_cast<int>( error->isInfo() );
}


LIBLX_EXTERN
int
XMLError_isWarning (const XMLError_t *error)
{
  if (error == NULL) return (int)false;
  return static_cast<int>( error->isWarning() );
}


LIBLX_EXTERN
int
XMLError_isError (const XMLError_t *error)
{
  if (error == NULL) return (int)false;
  return static_cast<int>( error->isError() );
}


LIBLX_EXTERN
int
XMLError_isFatal (const XMLError_t *error)
{
  if (error == NULL) return (int)false;
  return static_cast<int>( error->isFatal() );
}


LIBLX_EXTERN
void
XMLError_print (const XMLError_t *error, FILE *stream)
{
  if (error == NULL || stream == NULL) return;

  ostringstream os;
  os << *(static_cast<const XMLError*>(error));

  fprintf(stream, "%s", os.str().c_str());

}

LIBLX_CPP_NAMESPACE_END
/** @endcond */

