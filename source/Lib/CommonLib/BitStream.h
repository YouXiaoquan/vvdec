/* -----------------------------------------------------------------------------
The copyright in this software is being made available under the BSD
License, included below. No patent rights, trademark rights and/or 
other Intellectual Property Rights other than the copyrights concerning 
the Software are granted under this license.

For any license concerning other Intellectual Property rights than the software, 
especially patent licenses, a separate Agreement needs to be closed. 
For more information please contact:

Fraunhofer Heinrich Hertz Institute
Einsteinufer 37
10587 Berlin, Germany
www.hhi.fraunhofer.de/vvc
vvc@hhi.fraunhofer.de

Copyright (c) 2018-2020, Fraunhofer-Gesellschaft zur Förderung der angewandten Forschung e.V. 
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
 * Neither the name of Fraunhofer nor the names of its contributors may
   be used to endorse or promote products derived from this software without
   specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
THE POSSIBILITY OF SUCH DAMAGE.


------------------------------------------------------------------------------------------- */

/** \file     BitStream.h
    \brief    class for handling bitstream (header)
*/

#ifndef __BITSTREAM__
#define __BITSTREAM__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdint.h>
#include <vector>
#include <stdio.h>
#include "CommonDef.h"

//! \ingroup CommonLib
//! \{

// ====================================================================================================================
// Class definition
// ====================================================================================================================
/**
 * Model of an input bitstream that extracts bits from a predefined
 * bytestream.
 */
class InputBitstream
{
protected:
  std::vector<uint8_t>  m_fifo;   /// FIFO for storage of complete bytes
  std::vector<uint32_t> m_emulationPreventionByteLocation;

  uint32_t m_fifo_idx = 0;   /// Read index into m_fifo

  uint32_t m_num_held_bits = 0;
  uint8_t  m_held_bits     = 0;
  uint32_t m_numBitsRead   = 0;

public:
  /**
   * Create a new bitstream reader object that reads from buf.
   */
  InputBitstream()                            = default;
  ~InputBitstream()                           = default;
  InputBitstream( const InputBitstream& src ) = default;
  InputBitstream( InputBitstream&& src )      = default;

  void resetToStart();

  // interface for decoding
  void pseudoRead( uint32_t uiNumberOfBits, uint32_t& ruiBits );
  void read      ( uint32_t uiNumberOfBits, uint32_t& ruiBits );
  void readByte  ( uint32_t& ruiBits )
  {
    ruiBits = m_fifo[m_fifo_idx++];
#if ENABLE_TRACING
    m_numBitsRead += 8;
#endif
  }

  void peekPreviousByte( uint32_t& byte ) { byte = m_fifo[m_fifo_idx - 1]; }

  uint32_t         readOutTrailingBits();
  uint8_t          getHeldBits() { return m_held_bits; }
  uint32_t         getByteLocation() { return m_fifo_idx; }

  // Peek at bits in word-storage. Used in determining if we have completed reading of current bitstream and therefore
  // slice in LCEC.
  uint32_t peekBits( uint32_t uiBits )
  {
    uint32_t tmp;
    pseudoRead( uiBits, tmp );
    return tmp;
  }

  // utility functions
  uint32_t read( uint32_t numberOfBits )
  {
    uint32_t tmp;
    read( numberOfBits, tmp );
    return tmp;
  }
  uint32_t readByte()
  {
    uint32_t tmp;
    readByte( tmp );
    return tmp;
  }
  uint32_t        getNumBitsUntilByteAligned()            { return m_num_held_bits & ( 0x7 ); }
  uint32_t        getNumBitsLeft()                        { return 8 * ( (uint32_t) m_fifo.size() - m_fifo_idx ) + m_num_held_bits; }
  uint32_t        getNumBitsRead()                        { return m_numBitsRead; }
  uint32_t        readByteAlignment();
  InputBitstream* extractSubstream( uint32_t uiNumBits );   // Read the nominated number of bits, and return as a bitstream.

  void                         pushEmulationPreventionByteLocation( uint32_t pos )                    { m_emulationPreventionByteLocation.push_back( pos ); }
  uint32_t                     numEmulationPreventionBytesRead()                                      { return (uint32_t) m_emulationPreventionByteLocation.size(); }
  uint32_t                     getEmulationPreventionByteLocation( uint32_t idx )                     { return m_emulationPreventionByteLocation[idx]; }
  const std::vector<uint32_t>& getEmulationPreventionByteLocation() const                             { return m_emulationPreventionByteLocation; }
  void                         setEmulationPreventionByteLocation( const std::vector<uint32_t>& vec ) { m_emulationPreventionByteLocation = vec; }
  void                         clearEmulationPreventionByteLocation()                                 { m_emulationPreventionByteLocation.clear(); }

  const std::vector<uint8_t>& getFifo() const { return m_fifo; }
        std::vector<uint8_t>& getFifo()       { return m_fifo; }
  void                        clearFifo()     { m_fifo.clear(); }
};

//! \}

#endif
