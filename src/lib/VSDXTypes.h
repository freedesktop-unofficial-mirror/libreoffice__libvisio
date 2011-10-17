/* libvisio
 * Version: MPL 1.1 / GPLv2+ / LGPLv2+
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License or as specified alternatively below. You may obtain a copy of
 * the License at http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * Major Contributor(s):
 * Copyright (C) 2011 Fridrich Strba <fridrich.strba@bluewin.ch>
 * Copyright (C) 2011 Eilidh McAdam <tibbylickle@gmail.com>
 *
 *
 * All Rights Reserved.
 *
 * For minor contributions see the git repository.
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPLv2+"), or
 * the GNU Lesser General Public License Version 2 or later (the "LGPLv2+"),
 * in which case the provisions of the GPLv2+ or the LGPLv2+ are applicable
 * instead of those above.
 */

#ifndef VSDXTYPES_H
#define VSDXTYPES_H

namespace libvisio {
struct XForm
{
  double pinX;
  double pinY;
  double height;
  double width;
  double pinLocX;
  double pinLocY;
  double angle;
  bool flipX;
  bool flipY;
  double x;
  double y;
  XForm() : pinX(0.0), pinY(0.0), height(0.0), width(0.0),
            pinLocX(0.0), pinLocY(0.0), angle(0.0),
            flipX(false), flipY(false), x(0.0), y(0.0) {}
};

// Utilities
struct ChunkHeader
{
  unsigned chunkType;  // 4 bytes
  unsigned id;         // 4 bytes
  unsigned list;       // 4 bytes
  unsigned dataLength; // 4 bytes
  unsigned short level;      // 2 bytes
  unsigned char unknown;    // 1 byte
  unsigned trailer; // Derived
};

struct Colour
{
  Colour(unsigned red, unsigned char green, unsigned char blue, unsigned char alpha)
  : r(red), g(green), b(blue), a(alpha) {}
  Colour() : r(0), g(0), b(0), a(0) {}
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;
};

struct NURBSData
{
  double lastKnot;
  unsigned degree;
  unsigned char xType;
  unsigned char yType;
  std::vector<double> knots;
  std::vector<double> weights;
  std::vector<std::pair<double, double> > points;
  NURBSData()
  : lastKnot(0.0),
    degree(0),
	xType(0x00),
	yType(0x00),
	knots(),
	weights(),
	points() {}
  NURBSData(const NURBSData &data)
  : lastKnot(data.lastKnot),
    degree(data.degree),
	xType(data.xType),
	yType(data.yType),
	knots(data.knots),
	weights(data.weights),
	points(data.points) {}
  NURBSData &operator=(const NURBSData &data)
  {
    lastKnot = data.lastKnot;
    degree = data.degree;
	xType = data.xType;
	yType = data.yType;
	knots = data.knots;
	weights = data.weights;
	points = data.points;
	return *this;
  }
};

struct PolylineData
{
  unsigned char xType;
  unsigned char yType;
  std::vector<std::pair<double, double> > points;
  PolylineData()
  : xType(0x00),
    yType(0x00),
	points() {}
  PolylineData(const PolylineData &data)
  : xType(data.xType),
    yType(data.yType),
	points(data.points) {}
  PolylineData &operator=(const PolylineData &data)
  {
    xType = data.xType;
    yType = data.yType;
	points = data.points;
	return *this;
  }
};

struct CharFormat
{
  CharFormat() :
    charCount(0),
    faceID(0),
    colour(),
    langID(0),
    size(12.0/72.0),
    bold(false),
    italic(false),
    underline(false),
    doubleunderline(false),
    strikeout(false),
    doublestrikeout(false),
    allcaps(false),
    initcaps(false),
    smallcaps(false),
    superscript(false),
    subscript(false),
    face("Arial") {}
  CharFormat(unsigned cc, unsigned short id, Colour c, unsigned lang, double s, bool b, bool i, bool u, bool du, bool so, bool dso, bool ac, bool ic, bool sc, bool super, bool sub, WPXString f) :
    charCount(cc),
    faceID(id),
    colour(c),
    langID(lang),
    size(s),
    bold(b),
    italic(i),
    underline(u),
    doubleunderline(du),
    strikeout(so),
    doublestrikeout(dso),
    allcaps(ac),
    initcaps(ic),
    smallcaps(sc),
    superscript(super),
    subscript(sub),
    face(f) {}
  unsigned charCount;
  unsigned short faceID;
  Colour colour;
  unsigned langID;
  double size;
  bool bold;
  bool italic;
  bool underline;
  bool doubleunderline;
  bool strikeout;
  bool doublestrikeout;
  bool allcaps;
  bool initcaps;
  bool smallcaps;
  bool superscript;
  bool subscript;
  WPXString face;
};

struct ParaFormat
{
  ParaFormat() :
    charCount(0),
    indFirst(0.0),
    indLeft(0.0),
    indRight(0.0),
    spLine(-1.2),
    spBefore(0.0),
    spAfter(0.0),
    align(1) {}
  ParaFormat(unsigned cc, double ifst, double il, double ir, double sl, double sb, double sa, double a) :
    charCount(cc),
    indFirst(ifst),
    indLeft(il),
    indRight(ir),
    spLine(sl),
    spBefore(sb),
    spAfter(sa),
    align(a) {}
  unsigned charCount;
  double indFirst;
  double indLeft;
  double indRight;
  double spLine;
  double spBefore;
  double spAfter;
  unsigned char align;
};

struct TextBlockFormat
{
  TextBlockFormat() :
    leftMargin(0.0),
    rightMargin(0.0),
    topMargin(0.0),
    bottomMargin(0.0),
    verticalAlign(0),
    textBkgndColourId(0),
    textBkgndColour(0xff,0xff,0xff,0),
    defaultTabStop(0.5),
    textDirection(0) {}
  TextBlockFormat(double lm, double rm, double tm, double bm, unsigned char va, unsigned char bgClrId, Colour bgClr, double defTab, unsigned char td) :
    leftMargin(lm),
    rightMargin(rm),
    topMargin(tm),
    bottomMargin(bm),
    verticalAlign(va),
    textBkgndColourId(bgClrId),
    textBkgndColour(bgClr),
    defaultTabStop(defTab),
    textDirection(td) {}
  double leftMargin;
  double rightMargin;
  double topMargin;
  double bottomMargin;
  unsigned char verticalAlign;
  unsigned char textBkgndColourId;
  Colour textBkgndColour;
  double defaultTabStop;
  unsigned char textDirection;
};

struct ForeignData
{
  unsigned typeId;
  unsigned dataId;
  unsigned typeLevel;
  unsigned dataLevel;
  unsigned type;
  unsigned format;
  WPXBinaryData data;
  ForeignData()
  : typeId(0),
    dataId(0),
    typeLevel(0),
    dataLevel(0),
    type(0),
    format(0),
    data() {}
  ForeignData(const ForeignData &fd)
  : typeId(fd.typeId),
    dataId(fd.dataId),
    typeLevel(fd.typeLevel),
    dataLevel(fd.dataLevel),
    type(fd.type),
    format(fd.format),
    data(fd.data) {}
};

enum TextFormat { VSD_TEXT_ANSI, VSD_TEXT_UTF16 };

} // namespace libvisio

#endif /* VSDXTYPES_H */
