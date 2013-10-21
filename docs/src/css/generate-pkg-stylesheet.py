#!/usr/bin/env python
#
# @file    generate-pkg-stylesheet.py
# @brief   Create a stylesheet for libSBML package extensions
# @author  Michael Hucka
#
# Usage:
#   generate-pkg-stylesheet.py PACKAGE-SRC-DIR > libsbml-package-stylesheet.css
#
# where
#   PACKAGE-SRC-DIR = the path to the libSBML src/sbml/packages directory
#
# This program looks in the root of the libSBML source directory for package
# plug-ins that are distributed with libSBML (i.e., for accepted SBML Level 3
# packages) and generates a CSS stylesheet for both the Doxygen-based and
# Javadoc-based API documentation.  To do the desired styling for the Javadoc
# documentation, this program has to know the object classes that are defined
# by each libSBML package plug-in.  Since this may change over time, it
# is better to look in the source directory for the current class definitions
# than to hard code them in a CSS file or this file.  That is the motivation
# for this program.
#
# <!--------------------------------------------------------------------------
# This file is part of libSBML.  Please visit http://sbml.org for more
# information about SBML, and the latest version of libSBML.
#
# Copyright (C) 2009-2013 jointly by the following organizations: 
#     1. California Institute of Technology, Pasadena, CA, USA
#     2. EMBL European Bioinformatics Institute (EBML-EBI), Hinxton, UK
#  
# Copyright (C) 2006-2008 by the California Institute of Technology,
#     Pasadena, CA, USA 
#  
# Copyright (C) 2002-2005 jointly by the following organizations: 
#     1. California Institute of Technology, Pasadena, CA, USA
#     2. Japan Science and Technology Agency, Japan
# 
# This library is free software; you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation.  A copy of the license agreement is provided
# in the file named "LICENSE.txt" included with this software distribution
# and also available online as http://sbml.org/software/libsbml/license.html
# ---------------------------------------------------------------------- -->*/

import os, sys
from os.path import join

color_table = [
    # Name, 	red, 	green, 	blue
    ['comp',	'190', 	'200', 	'231'],
    ['fbc',	'185', 	'255',	'210'],
    ['layout',	'233',	'176',	'149'],
    ['qual',	'140', 	'220',	'250'],
    ['multi',	'223',	'189',	'30'],
    ['groups',	'250',	'170',	'210'],
    ['arrays',	'55',	'221',	'177'],
    ['distrib',	'243',	'250',	'134'],
    ['spatial',	'0',	'150',	'132'],
    ['req',	'100',	'100',	'100'],
    ['render',	'225',	'225',	'225']
]


header_template = '''/**
 * WARNING -- THIS FILE IS AUTO-GENERATED -- DO NOT EDIT THIS FILE
 *
 * @file    libsbml-package-stylesheet.css
 * @brief   Stylesheet used by libSBML for L3 package plug-in docs.
 * @author  libSBML Team <libsbml-team@caltech.edu>
 *
 * This file is generated by generate-pkg-stylesheet.py in the
 * libSBML documentation source directory.  DO NOT EDIT THIS FILE DIRECTLY
 * BECAUSE YOUR CHANGES WILL BE LOST WHEN THE FILE IS REGENERATED.
 *
 * This file is part of libSBML.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 */
'''


pkg_separator_template = '''
/* Styling for package '{}' used in libSBML Javadoc output */
'''


pkg_style_template = '''.pkg-color-{0} 
{{
    border: 1px solid rgb({1}, {2}, {3});
    background-color: rgba({1}, {2}, {3}, 0.35);
}}
'''


before_template = '''{{
    content: "\\25cf";
    color: rgb({1}, {2}, {3}) !important;
    margin-right: 0.25em;
}}
'''


after_template = '''{{
    content: "{0}";
    background-color: rgba({1}, {2}, {3}, 0.35);
    border: 1px solid rgb({1}, {2}, {3});
    border-radius: 5px;
    -moz-border-radius: 5px;
    -webkit-border-radius: 5px;
    margin-left: 1em;
    padding: 0px 3px;
    min-width: 40px;
    width: 40px;
    text-align: center;
    font-size: 80%;
    font-style: italic;
    color: #333 !important;
}}
'''


def find_classes_in_file(filename):
    classes = []
    stream = open(filename)
    for line in stream.readlines():
        start = line.find('@class')
        if start < 0:
            continue
        name = line[start + 6:].strip()
        classes.append(name)

    stream.close()
    return classes


def find_classes(files):
    classes = []
    for f in files:
        classes += find_classes_in_file(f)
    return classes


def main(args):
    if len(args) != 2:
	print "Must be given one argument: the path to the package source dir"
        sys.exit(1)

    src_dir = args[1]

    # First, write out an informative file header.

    print header_template

    # Next, write out the .pkg-color-x CSS classes:

    for entry in color_table:
        print pkg_style_template.format(entry[0], entry[1], entry[2], entry[3])

    # Next, read the source dir to find out the L3 packages available, and
    # extract the names of the libSBML object classes in each package.

    known_pkgs = [entry[0] for entry in color_table]
    top_root, top_level_dirs, top_level_files = os.walk(src_dir).next()
    found_pkgs = [pkg for pkg in known_pkgs if pkg in top_level_dirs]

    # Now generate CSS styling that uses attribute selectors specialized to
    # our Javadoc output.  These styles are ignored by our Doxygen output
    # (because the CSS code doesn't match anything there), so technically we
    # could split this into a separate file for Javadoc-only styling, but
    # it's easier to write all our package CSS code into one file.

    for pkg in found_pkgs:
        print pkg_separator_template.format(pkg)

        color = next(entry for entry in color_table if entry[0] == pkg)

        files = []
        for root, dir, pkg_files in os.walk(os.path.join(src_dir, pkg)):
            for tail in pkg_files:
                files.append(os.path.join(root, tail))
                files = [f for f in files if f.endswith('.h')]
                files = filter(lambda x: not x.endswith('fwd.h'), files)
                files = filter(lambda x: not x.endswith('ExtensionTypes.h'), files)

        classes = find_classes(files)
        last = classes[-1]

        for c in classes:
            comma = (',' if c != last else '')
            print 'font a[href="org/sbml/libsbml/{}.html"]:before{}'.format(c, comma)
        print before_template.format(pkg, color[1], color[2], color[3])

        for c in classes:
            comma = (',' if c != last else '')
            print 'font a[href="org/sbml/libsbml/{}.html"]:after{}'.format(c, comma)
        print after_template.format(pkg, color[1], color[2], color[3])


if __name__ == '__main__':
  main(sys.argv)

