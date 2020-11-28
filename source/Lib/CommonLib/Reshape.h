/* -----------------------------------------------------------------------------
Software Copyright License for the Fraunhofer Software Library VVdec

(c) Copyright (2018-2020) Fraunhofer-Gesellschaft zur Förderung der angewandten Forschung e.V. 

1.    INTRODUCTION

The Fraunhofer Software Library VVdec (“Fraunhofer Versatile Video Decoding Library”) is software that implements (parts of) the Versatile Video Coding Standard - ITU-T H.266 | MPEG-I - Part 3 (ISO/IEC 23090-3) and related technology. 
The standard contains Fraunhofer patents as well as third-party patents. Patent licenses from third party standard patent right holders may be required for using the Fraunhofer Versatile Video Decoding Library. It is in your responsibility to obtain those if necessary. 

The Fraunhofer Versatile Video Decoding Library which mean any source code provided by Fraunhofer are made available under this software copyright license. 
It is based on the official ITU/ISO/IEC VVC Test Model (VTM) reference software whose copyright holders are indicated in the copyright notices of its source files. The VVC Test Model (VTM) reference software is licensed under the 3-Clause BSD License and therefore not subject of this software copyright license.

2.    COPYRIGHT LICENSE

Internal use of the Fraunhofer Versatile Video Decoding Library, in source and binary forms, with or without modification, is permitted without payment of copyright license fees for non-commercial purposes of evaluation, testing and academic research. 

No right or license, express or implied, is granted to any part of the Fraunhofer Versatile Video Decoding Library except and solely to the extent as expressly set forth herein. Any commercial use or exploitation of the Fraunhofer Versatile Video Decoding Library and/or any modifications thereto under this license are prohibited.

For any other use of the Fraunhofer Versatile Video Decoding Library than permitted by this software copyright license You need another license from Fraunhofer. In such case please contact Fraunhofer under the CONTACT INFORMATION below.

3.    LIMITED PATENT LICENSE

As mentioned under 1. Fraunhofer patents are implemented by the Fraunhofer Versatile Video Decoding Library. If You use the Fraunhofer Versatile Video Decoding Library in Germany, the use of those Fraunhofer patents for purposes of testing, evaluating and research and development is permitted within the statutory limitations of German patent law. However, if You use the Fraunhofer Versatile Video Decoding Library in a country where the use for research and development purposes is not permitted without a license, you must obtain an appropriate license from Fraunhofer. It is Your responsibility to check the legal requirements for any use of applicable patents.    

Fraunhofer provides no warranty of patent non-infringement with respect to the Fraunhofer Versatile Video Decoding Library.


4.    DISCLAIMER

The Fraunhofer Versatile Video Decoding Library is provided by Fraunhofer "AS IS" and WITHOUT ANY EXPRESS OR IMPLIED WARRANTIES, including but not limited to the implied warranties fitness for a particular purpose. IN NO EVENT SHALL FRAUNHOFER BE LIABLE for any direct, indirect, incidental, special, exemplary, or consequential damages, including but not limited to procurement of substitute goods or services; loss of use, data, or profits, or business interruption, however caused and on any theory of liability, whether in contract, strict liability, or tort (including negligence), arising in any way out of the use of the Fraunhofer Versatile Video Decoding Library, even if advised of the possibility of such damage.

5.    CONTACT INFORMATION

Fraunhofer Heinrich Hertz Institute
Attention: Video Coding & Analytics Department
Einsteinufer 37
10587 Berlin, Germany
www.hhi.fraunhofer.de/vvc
vvc@hhi.fraunhofer.de
------------------------------------------------------------------------------------------- */

 /** \file     Reshape.h
     \brief    reshaping header and class (header)
 */

#ifndef __RESHAPE__
#define __RESHAPE__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CommonDef.h"
#include "Rom.h"
#include "CommonLib/Picture.h"
//! \ingroup CommonLib
//! \{
// ====================================================================================================================
// Class definition
// ====================================================================================================================

class Reshape
{
protected:
  SliceReshapeInfo        m_sliceReshapeInfo;
  bool                    m_CTUFlag;
  Pel*                    m_invLUT;
  Pel*                    m_fwdLUT;
  std::vector<int>        m_chromaAdjHelpLUT;
  std::vector<uint16_t>   m_binCW;
  uint16_t                m_initCW;
  std::vector<Pel>        m_reshapePivot;
  std::vector<Pel>        m_inputPivot;
  std::vector<int32_t>    m_fwdScaleCoef;
  std::vector<int32_t>    m_invScaleCoef;
  int                     m_reshapeLUTSize;
  int                     m_chromaScale;
  int                     m_vpduX;
  int                     m_vpduY;
public:
  Reshape();
  ~Reshape();

  void createDec();
  void destroy();

  void initSlice( Slice* pcSlice );
  void rspLine( CodingStructure &cs, int ln, const int offset ) const;
  void rspCtu ( CodingStructure &cs, int col, int ln, const int offset ) const;

  const Pel* getFwdLUT() const { return m_fwdLUT; }
  const Pel* getInvLUT() const { return m_invLUT; }

  bool getCTUFlag()              { return m_CTUFlag; }

  int  calculateChromaAdj(Pel avgLuma) const;
  int  getPWLIdxInv(int lumaVal) const;
  SliceReshapeInfo& getSliceReshaperInfo() { return m_sliceReshapeInfo; }

  void constructReshaper();
  int  calculateChromaAdjVpduNei(TransformUnit &tu, const Position pos);
  void setVPDULoc(int x, int y) { m_vpduX = x, m_vpduY = y; }
  bool isVPDUprocessed(int x, int y) { return ((x == m_vpduX) && (y == m_vpduY)); }
  void setChromaScale (int chromaScale) { m_chromaScale = chromaScale; }
  int  getChromaScale() { return m_chromaScale; }
};// END CLASS DEFINITION Reshape

//! \}
#endif // __RESHAPE__


