/* The copyright in this software is being made available under the BSD
 * License, included below. This software may be subject to other third party
 * and contributor rights, including patent rights, and no such rights are
 * granted under this license.
 *
 * Copyright (c) 2010-2022, ITU/ISO/IEC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  * Neither the name of the ITU/ISO/IEC nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 \file     SEIread.h
 \brief    reading funtionality for SEI messages
 */

#ifndef __SEIREAD__
#define __SEIREAD__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <fstream>
//! \ingroup DecoderLib
//! \{

#include "CommonLib/SEI.h"
class InputBitstream;


class SEIReader: public VLCReader
{
public:
  SEIReader() {};
  virtual ~SEIReader() {};
  void parseSEImessage(InputBitstream* bs, SEIMessages& seis, const NalUnitType nalUnitType, const uint32_t nuh_layer_id, const uint32_t temporalId,const VPS *vps, const SPS *sps, HRD &hrd, std::ostream *pDecodedMessageOutputStream);
  void parseAndExtractSEIScalableNesting(InputBitstream* bs, const NalUnitType nalUnitType, const uint32_t nuh_layer_id, const VPS* vps, const SPS* sps, HRD &hrd, uint32_t payloadSize, std::vector<std::tuple<int, int, bool, uint32_t, uint8_t*, int, int>> *seiList);
  void getSEIDecodingUnitInfoDuiIdx(InputBitstream* bs, const NalUnitType nalUnitType, const uint32_t nuh_layer_id, HRD &hrd, uint32_t payloadSize, int& duiIdx);

protected:
  void xReadSEImessage                        (SEIMessages& seis, const NalUnitType nalUnitType, const uint32_t nuh_layer_id, const uint32_t temporalId, const VPS *vps, const SPS *sps, HRD &hrd, std::ostream *pDecodedMessageOutputStream);
  void xParseSEIFillerPayload                 (SEIFillerPayload &sei,                 uint32_t payloadSize,                     std::ostream *pDecodedMessageOutputStream);
  void xParseSEIuserDataUnregistered          (SEIuserDataUnregistered &sei,          uint32_t payloadSize,                     std::ostream *pDecodedMessageOutputStream);
  void xParseSEIDecodingUnitInfo              (SEIDecodingUnitInfo& sei,              uint32_t payloadSize, const SEIBufferingPeriod& bp, const uint32_t temporalId, std::ostream *pDecodedMessageOutputStream);
  void xParseSEIDecodedPictureHash            (SEIDecodedPictureHash& sei,            uint32_t payloadSize,                     std::ostream *pDecodedMessageOutputStream);
  void xParseSEIBufferingPeriod               (SEIBufferingPeriod& sei,               uint32_t payloadSize, std::ostream *pDecodedMessageOutputStream);
  void xParseSEIPictureTiming                 (SEIPictureTiming& sei,                 uint32_t payloadSize, const uint32_t temporalId, const SEIBufferingPeriod& bp, std::ostream *pDecodedMessageOutputStream);
  void xParseSEIScalableNesting               (SEIScalableNesting& sei, const NalUnitType nalUnitType, const uint32_t nuhLayerId, uint32_t payloadSize, const VPS* vps, const SPS* sps, HRD &hrd, std::ostream* decodedMessageOutputStream);
  void xParseSEIScalableNestingBinary         (SEIScalableNesting& sei, const NalUnitType nalUnitType, const uint32_t nuhLayerId, uint32_t payloadSize, const VPS* vps, const SPS* sps, HRD &hrd, std::ostream* decodedMessageOutputStream, std::vector<std::tuple<int, int, bool, uint32_t, uint8_t*, int, int>> *seiList);
  void xCheckScalableNestingConstraints       (const SEIScalableNesting& sei, const NalUnitType nalUnitType, const VPS* vps);
  void xParseSEIFrameFieldinfo                (SEIFrameFieldInfo& sei,                uint32_t payloadSize, std::ostream *pDecodedMessageOutputStream);
  void xParseSEIGreenMetadataInfo             (SEIGreenMetadataInfo& sei,             uint32_t payLoadSize,                     std::ostream *pDecodedMessageOutputStream);
  void xParseSEIDependentRAPIndication        (SEIDependentRAPIndication& sei,        uint32_t payLoadSize,                     std::ostream *pDecodedMessageOutputStream);
  void xParseSEIFramePacking                  (SEIFramePacking& sei,                  uint32_t payloadSize,                     std::ostream *pDecodedMessageOutputStream);
  void xParseSEIDisplayOrientation            (SEIDisplayOrientation& sei,            uint32_t payloadSize,                     std::ostream* pDecodedMessageOutputStream);
  void xParseSEIParameterSetsInclusionIndication(SEIParameterSetsInclusionIndication& sei, uint32_t payloadSize,                std::ostream* pDecodedMessageOutputStream);
  void xParseSEIMasteringDisplayColourVolume  (SEIMasteringDisplayColourVolume& sei,  uint32_t payloadSize,                     std::ostream *pDecodedMessageOutputStream);
  void xParseSEIAnnotatedRegions              (SEIAnnotatedRegions& sei,              uint32_t payloadSize,                     std::ostream *pDecodedMessageOutputStream);
  void xParseSEIAlternativeTransferCharacteristics(SEIAlternativeTransferCharacteristics& sei,              uint32_t payLoadSize,                     std::ostream *pDecodedMessageOutputStream);
  void xParseSEIEquirectangularProjection     (SEIEquirectangularProjection &sei,     uint32_t payloadSize,                     std::ostream *pDecodedMessageOutputStream);
  void xParseSEISphereRotation                (SEISphereRotation &sei,                uint32_t payloadSize,                     std::ostream *pDecodedMessageOutputStream);
  void xParseSEIOmniViewport                  (SEIOmniViewport& sei,                  uint32_t payloadSize,                     std::ostream *pDecodedMessageOutputStream);
  void xParseSEIRegionWisePacking             (SEIRegionWisePacking& sei,             uint32_t payloadSize,                     std::ostream *pDecodedMessageOutputStream);
  void xParseSEIGeneralizedCubemapProjection  (SEIGeneralizedCubemapProjection &sei,  uint32_t payloadSize,                     std::ostream *pDecodedMessageOutputStream);
  void xParseSEIScalabilityDimensionInfo      (SEIScalabilityDimensionInfo& sei,      uint32_t payloadSize, std::ostream *pDecodedMessageOutputStream);
  void xParseSEIMultiviewAcquisitionInfo      (SEIMultiviewAcquisitionInfo& sei,      uint32_t payloadSize, std::ostream *pDecodedMessageOutputStream);
  void xParseSEIMultiviewViewPosition         (SEIMultiviewViewPosition& sei,         uint32_t payloadSize, std::ostream *pDecodedMessageOutputStream);
  void xParseSEIAlphaChannelInfo              (SEIAlphaChannelInfo& sei,              uint32_t payloadSize,                     std::ostream *pDecodedMessageOutputStream);
  void xParseSEIDepthRepresentationInfo       (SEIDepthRepresentationInfo& sei,       uint32_t payloadSize, std::ostream *pDecodedMessageOutputStream);
  void xParseSEIDepthRepInfoElement           (double &f,std::ostream *pDecodedMessageOutputStream);
  void xParseSEISubpictureLevelInfo           (SEISubpicureLevelInfo& sei,            uint32_t payloadSize,                     std::ostream *pDecodedMessageOutputStream);
  void xParseSEISampleAspectRatioInfo         (SEISampleAspectRatioInfo& sei,         uint32_t payloadSize,                     std::ostream *pDecodedMessageOutputStream);
  void xParseSEIUserDataRegistered            (SEIUserDataRegistered& sei,            uint32_t payloadSize,                     std::ostream *pDecodedMessageOutputStream);
  void xParseSEIFilmGrainCharacteristics      (SEIFilmGrainCharacteristics& sei,      uint32_t payloadSize,                     std::ostream *pDecodedMessageOutputStream);
  void xParseSEIContentLightLevelInfo         (SEIContentLightLevelInfo& sei,         uint32_t payloadSize,                     std::ostream *pDecodedMessageOutputStream);
  void xParseSEIAmbientViewingEnvironment     (SEIAmbientViewingEnvironment& sei,     uint32_t payloadSize,                     std::ostream *pDecodedMessageOutputStream);
  void xParseSEIContentColourVolume           (SEIContentColourVolume& sei,           uint32_t payloadSize,                     std::ostream *pDecodedMessageOutputStream);
  void xParseSEIExtendedDrapIndication        (SEIExtendedDrapIndication& sei,        uint32_t payloadSize,                     std::ostream *pDecodedMessageOutputStream);
  void xParseSEIColourTransformInfo           (SEIColourTransformInfo& sei, uint32_t payloadSize, std::ostream* pDecodedMessageOutputStream);
  void xParseSEIConstrainedRaslIndication     (SEIConstrainedRaslIndication& sei,     uint32_t payLoadSize,                     std::ostream *pDecodedMessageOutputStream);
  void xParseSEIShutterInterval(SEIShutterIntervalInfo& sei, uint32_t payloadSize, std::ostream *pDecodedMessageOutputStream);
  void xParseSEINNPostFilterCharacteristics(SEINeuralNetworkPostFilterCharacteristics& sei, uint32_t payloadSize, const SPS* sps, std::ostream* pDecodedMessageOutputStream);
  void xParseSEINNPostFilterActivation(SEINeuralNetworkPostFilterActivation& sei, uint32_t payloadSize, std::ostream *pDecodedMessageOutputStream);
  void xParseSEIPhaseIndication(SEIPhaseIndication& sei, uint32_t payloadSize, std::ostream* pDecodedMessageOutputStream);
  void xParseSEIProcessingOrder               (SEIProcessingOrderInfo& sei, uint32_t payloadSize, std::ostream *decodedMessageOutputStream);

  void sei_read_scode(std::ostream *pOS, uint32_t length, int& code, const char *pSymbolName);
  void sei_read_code(std::ostream *pOS, uint32_t length, uint32_t &ruiCode, const char *pSymbolName);
  void sei_read_uvlc(std::ostream *pOS,                uint32_t& ruiCode, const char *pSymbolName);
  void sei_read_svlc(std::ostream *pOS,                int&  ruiCode, const char *pSymbolName);
  void sei_read_flag(std::ostream *pOS,                uint32_t& ruiCode, const char *pSymbolName);
  void sei_read_string(std::ostream* os, std::string& code, const char* symbolName);

protected:
  HRD m_nestedHrd;
};

#if JVET_S0257_DUMP_360SEI_MESSAGE
class SeiCfgFileDump
{
public:
  SeiCfgFileDump()
  : m_360SEIMessageDumped(false)
  {};
  virtual ~SeiCfgFileDump() {};

  void write360SeiDump (std::string decoded360MessageFileName, SEIMessages& seis, const SPS* sps);

protected:
  void xDumpSEIEquirectangularProjection     (SEIEquirectangularProjection &sei, const SPS* sps, std::string decoded360MessageFileName);
  void xDumpSEIGeneralizedCubemapProjection  (SEIGeneralizedCubemapProjection &sei, const SPS* sps, std::string decoded360MessageFileName);

  bool m_360SEIMessageDumped;

};


#endif

//! \}

#endif
