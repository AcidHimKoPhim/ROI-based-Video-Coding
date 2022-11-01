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

/** \file     CommonDef.h
    \brief    Defines version information, constants and small in-line functions
*/

#ifndef __COMMONDEF__
#define __COMMONDEF__

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <limits>


#if _MSC_VER > 1000
// disable "signed and unsigned mismatch"
#pragma warning( disable : 4018 )
// disable bool coercion "performance warning"
#pragma warning( disable : 4800 )
#endif // _MSC_VER > 1000

#include "CommonSimdCfg.h"
#include "TypeDef.h"
#include "version.h"

// MS Visual Studio before 2014 does not support required C++11 features
#ifdef _MSC_VER
#if _MSC_VER < 1900
#error "MS Visual Studio version not supported. Please upgrade to Visual Studio 2015 or higher (or use other compilers)"
#endif

#include <intrin.h>
#endif

//! \ingroup CommonLib
//! \{

// ====================================================================================================================
// Platform information
// ====================================================================================================================

#ifdef __clang__
#define NVM_COMPILEDBY  "[clang %d.%d.%d]", __clang_major__, __clang_minor__, __clang_patchlevel__
#ifdef __IA64__
#define NVM_ONARCH    "[on 64-bit] "
#else
#define NVM_ONARCH    "[on 32-bit] "
#endif
#elif __GNUC__
#define NVM_COMPILEDBY  "[GCC %d.%d.%d]", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__
#ifdef __IA64__
#define NVM_ONARCH    "[on 64-bit] "
#else
#define NVM_ONARCH    "[on 32-bit] "
#endif
#endif

#ifdef __INTEL_COMPILER
#define NVM_COMPILEDBY  "[ICC %d]", __INTEL_COMPILER
#elif  _MSC_VER
#define NVM_COMPILEDBY  "[VS %d]", _MSC_VER
#endif

#ifndef NVM_COMPILEDBY
#define NVM_COMPILEDBY "[Unk-CXX]"
#endif

#ifdef _WIN32
#define NVM_ONOS        "[Windows]"
#elif  __linux
#define NVM_ONOS        "[Linux]"
#elif  __CYGWIN__
#define NVM_ONOS        "[Cygwin]"
#elif __APPLE__
#define NVM_ONOS        "[Mac OS X]"
#else
#define NVM_ONOS "[Unk-OS]"
#endif

#define NVM_BITS          "[%d bit] ", (sizeof(void*) == 8 ? 64 : 32) ///< used for checking 64-bit O/S

typedef enum
{
  AFFINEMODEL_4PARAM,
  AFFINEMODEL_6PARAM,
  AFFINE_MODEL_NUM
} EAffineModel;

static constexpr int    AFFINE_ME_LIST_SIZE    =                        4;
static constexpr int    AFFINE_ME_LIST_SIZE_LD =                        3;
static constexpr double AFFINE_ME_LIST_MVP_TH  =                        1.0;

// ====================================================================================================================
// Common constants
// ====================================================================================================================
static constexpr uint64_t MAX_UINT64 =                  0xFFFFFFFFFFFFFFFFU;
static constexpr uint32_t MAX_UINT =                            0xFFFFFFFFU; ///< max. value of unsigned 32-bit integer
static constexpr int      MAX_INT =                              2147483647; ///< max. value of signed 32-bit integer
static constexpr uint8_t  MAX_UCHAR =                                   255;
static constexpr uint8_t  MAX_SCHAR =                                   127;
static constexpr double   MAX_DOUBLE =                             1.7e+308; ///< max. value of double-type value

static constexpr Distortion MAX_DISTORTION = std::numeric_limits<Distortion>::max();

// ====================================================================================================================
// Coding tool configuration
// ====================================================================================================================
// Most of these should not be changed - they resolve the meaning of otherwise magic numbers.

static constexpr int MAX_GOP =                                         64; ///< max. value of hierarchical GOP size
static constexpr int MAX_NUM_REF_PICS =                                29; ///< max. number of pictures used for reference
static constexpr int MAX_NUM_REF =                                     16; ///< max. number of entries in picture reference list
static constexpr int MAX_QP =                                          63;
static constexpr int NOT_VALID =                                       -1;


static constexpr int AMVP_MAX_NUM_CANDS =                               2; ///< AMVP: advanced motion vector prediction - max number of final candidates
static constexpr int AMVP_MAX_NUM_CANDS_MEM =                           3; ///< AMVP: advanced motion vector prediction - max number of candidates
static constexpr int AMVP_DECIMATION_FACTOR =                           2;
static constexpr int MRG_MAX_NUM_CANDS =                                6; ///< MERGE
static constexpr int AFFINE_MRG_MAX_NUM_CANDS =                         5; ///< AFFINE MERGE
static constexpr int IBC_MRG_MAX_NUM_CANDS =                            6; ///< IBC MERGE

static constexpr int MAX_TLAYER =                                       7; ///< Explicit temporal layer QP offset - max number of temporal layer

static constexpr int ADAPT_SR_SCALE =                                   1; ///< division factor for adaptive search range

static constexpr int MIN_TB_LOG2_SIZEY = 2;
static constexpr int MAX_TB_LOG2_SIZEY = 6;

static constexpr int MIN_TB_SIZEY = 1 << MIN_TB_LOG2_SIZEY;
static constexpr int MAX_TB_SIZEY = 1 << MAX_TB_LOG2_SIZEY;

static constexpr int MAX_NESTING_NUM_LAYER =                           64;

static constexpr int MAX_VPS_LAYERS =                                  64;
static constexpr int MAX_VPS_SUBLAYERS =                                7;
static constexpr int MAX_NUM_OLSS =                                   256;
static constexpr int MAX_VPS_OLS_MODE_IDC =                             2;

static constexpr int MAX_NUM_NN_POST_FILTERS =                          8;

static constexpr int MIP_MAX_WIDTH =                                   MAX_TB_SIZEY;
static constexpr int MIP_MAX_HEIGHT =                                  MAX_TB_SIZEY;

static constexpr int MAX_NUM_ALF_ALTERNATIVES_CHROMA =                  8;
static constexpr int MAX_NUM_ALF_CLASSES         =                     25;
static constexpr int MAX_NUM_ALF_LUMA_COEFF      =                     13;
static constexpr int MAX_NUM_ALF_CHROMA_COEFF    =                      7;
static constexpr int MAX_ALF_FILTER_LENGTH       =                      7;
static constexpr int MAX_ALF_PADDING_SIZE        =                      4;
#define MAX_NUM_CC_ALF_FILTERS                                      4
static constexpr int MAX_NUM_CC_ALF_CHROMA_COEFF    =               8;
static constexpr int CCALF_DYNAMIC_RANGE            =               6;
static constexpr int CCALF_BITS_PER_COEFF_LEVEL     =               3;

static constexpr int ALF_FIXED_FILTER_NUM        =                     64;
static constexpr int ALF_CTB_MAX_NUM_APS         =                      8;
static constexpr int NUM_FIXED_FILTER_SETS       =                     16;

static constexpr int MAX_BDOF_APPLICATION_REGION =                     16;

static constexpr int MAX_CPB_CNT =                                     32; ///< Upper bound of (cpb_cnt_minus1 + 1)
static constexpr int MAX_NUM_LAYER_IDS =                               64;
static constexpr int COEF_REMAIN_BIN_REDUCTION =                        5; ///< indicates the level at which the VLC transitions from Golomb-Rice to TU+EG(k)
static constexpr int CU_DQP_TU_CMAX =                                   5; ///< max number bins for truncated unary
static constexpr int CU_DQP_EG_k =                                      0; ///< expgolomb order

static constexpr int SBH_THRESHOLD =                                    4; ///< value of the fixed SBH controlling threshold

static constexpr int MAX_NUM_VPS =                                     16;
static constexpr int MAX_NUM_SPS =                                     16;
static constexpr int MAX_NUM_PPS =                                     64;
static constexpr int MAX_NUM_APS =                                     32;  //Currently APS ID has 5 bits
static constexpr int NUM_APS_TYPE_LEN =                                 3;  //Currently APS Type has 3 bits
static constexpr int MAX_NUM_APS_TYPE =                                 8;  //Currently APS Type has 3 bits so the max type is 8

static constexpr int MAX_TILE_COLS = 30;   // Maximum number of tile columns
static constexpr int MAX_TILES     = 990;  // Maximum number of tiles
static constexpr int MAX_SLICES    = 1000; // Maximum number of slices per picture

static constexpr int MLS_GRP_NUM =                                   1024; ///< Max number of coefficient groups, max(16, 256)

static constexpr int MLS_CG_SIZE =                                      4; ///< Coefficient group size of 4x4; = MLS_CG_LOG2_WIDTH + MLS_CG_LOG2_HEIGHT


static constexpr int RVM_VCEGAM10_M =                                   4;

static constexpr int MAX_REF_LINE_IDX =                                 3; //highest refLine offset in the list
static constexpr int MRL_NUM_REF_LINES =                                3; //number of candidates in the array
static constexpr int MULTI_REF_LINE_IDX[4] =               { 0, 1, 2, 0 };

static constexpr int PRED_REG_MIN_WIDTH =                               4;  // Minimum prediction region width for ISP subblocks

static constexpr int NUM_DIR                 = 16;
static constexpr int NUM_INTRA_ANGULAR_MODES = 4 * NUM_DIR + 1;
static constexpr int ANGULAR_BASE            = 2;   // First two modes and planar and DC
static constexpr int NUM_LUMA_MODE           = ANGULAR_BASE + NUM_INTRA_ANGULAR_MODES;
static constexpr int NUM_LMC_MODE            = 1 + 2;   // LMC + MDLM_T + MDLM_L
static constexpr int NUM_INTRA_MODE          = NUM_LUMA_MODE + NUM_LMC_MODE;

static constexpr int NUM_EXT_LUMA_MODE =                               28;

static constexpr int PLANAR_IDX = 0;                              ///< index for intra PLANAR mode
static constexpr int DC_IDX     = 1;                              ///< index for intra DC     mode
static constexpr int HOR_IDX    = (1 * NUM_DIR + ANGULAR_BASE);   ///< index for intra HORIZONTAL mode
static constexpr int DIA_IDX    = (2 * NUM_DIR + ANGULAR_BASE);   ///< index for intra DIAGONAL   mode
static constexpr int VER_IDX    = (3 * NUM_DIR + ANGULAR_BASE);   ///< index for intra VERTICAL   mode
static constexpr int VDIA_IDX   = (4 * NUM_DIR + ANGULAR_BASE);   ///< index for intra VDIAGONAL  mode
static constexpr int BDPCM_IDX  = (5 * NUM_DIR + ANGULAR_BASE);   ///< index for intra BDPCM  mode
static constexpr int NOMODE_IDX = MAX_UCHAR;                      ///< indicating uninitialized elements

static constexpr int NUM_CHROMA_MODE = (5 + NUM_LMC_MODE); ///< total number of chroma modes
static constexpr int LM_CHROMA_IDX = NUM_LUMA_MODE; ///< chroma mode index for derived from LM mode
static constexpr int MDLM_L_IDX =                          LM_CHROMA_IDX + 1; ///< MDLM_L
static constexpr int MDLM_T_IDX =                          LM_CHROMA_IDX + 2; ///< MDLM_T
static constexpr int DM_CHROMA_IDX =                       NUM_INTRA_MODE; ///< chroma mode index for derived from luma intra mode

static constexpr uint32_t  NUM_TRAFO_MODES_MTS =                            6; ///< Max Intra CU size applying EMT, supported values: 8, 16, 32, 64, 128
static constexpr uint32_t  MTS_INTRA_MAX_CU_SIZE =                         32; ///< Max Intra CU size applying EMT, supported values: 8, 16, 32, 64, 128
static constexpr uint32_t  MTS_INTER_MAX_CU_SIZE =                         32; ///< Max Inter CU size applying EMT, supported values: 8, 16, 32, 64, 128
static constexpr int NUM_MOST_PROBABLE_MODES = 6;
static constexpr int LM_SYMBOL_NUM = (1 + NUM_LMC_MODE);

static constexpr int MAX_NUM_MIP_MODE =                                32; ///< maximum number of MIP pred. modes
static constexpr int FAST_UDI_MAX_RDMODE_NUM = (NUM_LUMA_MODE + MAX_NUM_MIP_MODE); ///< maximum number of RD comparison in fast-UDI estimation loop

static constexpr int MAX_LFNST_COEF_NUM =                              16;

static constexpr int LFNST_LAST_SIG_LUMA =                              1;
static constexpr int LFNST_LAST_SIG_CHROMA =                            1;

static constexpr int NUM_LFNST_NUM_PER_SET =                            3;

static constexpr int CABAC_INIT_PRESENT_FLAG =                          1;

static constexpr int MV_FRACTIONAL_BITS_INTERNAL = 4;
static constexpr int MV_FRACTIONAL_BITS_SIGNAL   = 2;
static constexpr int MV_FRACTIONAL_BITS_DIFF     = MV_FRACTIONAL_BITS_INTERNAL - MV_FRACTIONAL_BITS_SIGNAL;
static constexpr int LUMA_INTERPOLATION_FILTER_SUB_SAMPLE_POSITIONS_SIGNAL = 1 << MV_FRACTIONAL_BITS_SIGNAL;
static constexpr int MV_FRAC_BITS_LUMA                                     = MV_FRACTIONAL_BITS_INTERNAL;
static constexpr int MV_FRAC_BITS_CHROMA                                   = MV_FRACTIONAL_BITS_INTERNAL + 1;
static constexpr int MV_FRAC_MASK_LUMA                                     = (1 << MV_FRAC_BITS_LUMA) - 1;
static constexpr int MV_FRAC_MASK_CHROMA                                   = (1 << MV_FRAC_BITS_CHROMA) - 1;
static constexpr int LUMA_INTERPOLATION_FILTER_SUB_SAMPLE_POSITIONS        = 1 << MV_FRAC_BITS_LUMA;
static constexpr int CHROMA_INTERPOLATION_FILTER_SUB_SAMPLE_POSITIONS      = 1 << MV_FRAC_BITS_CHROMA;

static constexpr int MAX_NUM_SUB_PICS =                         (1 << 16);
static constexpr int MAX_NUM_LONG_TERM_REF_PICS =                      33;
static constexpr int NUM_LONG_TERM_REF_PIC_SPS =                        0;


static constexpr int MAX_QP_OFFSET_LIST_SIZE =                          6; ///< Maximum size of QP offset list is 6 entries
static constexpr int MAX_NUM_CQP_MAPPING_TABLES =                       3; ///< Maximum number of chroma QP mapping tables (Cb, Cr and joint Cb-Cr)
static constexpr int MIN_QP_VALUE_FOR_16_BIT   =                      -48; ////< Minimum value for QP (-6*(bitdepth - 8) ) for bit depth 16 ; actual minimum QP value is bit depth dependent
static constexpr int MAX_NUM_QP_VALUES =    MAX_QP + 1 - MIN_QP_VALUE_FOR_16_BIT; ////< Maximum number of QP values possible - bit depth dependent

// Cost mode support
static constexpr int LOSSLESS_AND_MIXED_LOSSLESS_RD_COST_TEST_QP =      0; ///< QP to use for lossless coding.
static constexpr int LOSSLESS_AND_MIXED_LOSSLESS_RD_COST_TEST_QP_PRIME =4; ///< QP' to use for mixed_lossy_lossless coding.
static constexpr int RExt__GOLOMB_RICE_ADAPTATION_STATISTICS_SETS = MAX_NUM_COMPONENT;

static constexpr int RExt__PREDICTION_WEIGHTING_ANALYSIS_DC_PRECISION = 0; ///< Additional fixed bit precision used during encoder-side weighting prediction analysis. Currently only used when high_precision_prediction_weighting_flag is set, for backwards compatibility reasons.

static constexpr int MAX_TIMECODE_SEI_SETS =                            3; ///< Maximum number of time sets

static constexpr int MAX_CU_DEPTH                                     = 7;   // log2(CTUSize)
static constexpr int MAX_CU_SIZE =                        1<<MAX_CU_DEPTH;
static constexpr int MIN_CU_LOG2 =                                      2;
static constexpr int MIN_PU_SIZE =                                      4;
static constexpr int MAX_NUM_PARTS_IN_CTU =                         ( ( MAX_CU_SIZE * MAX_CU_SIZE ) >> ( MIN_CU_LOG2 << 1 ) );
static constexpr int MAX_NUM_TUS =                                     16; ///< Maximum number of TUs within one CU. When max TB size is 32x32, up to 16 TUs within one CU (128x128) is supported
static constexpr int MAX_LOG2_DIFF_CU_TR_SIZE =                         3;
static constexpr int MAX_CU_TILING_PARTITIONS = 1 << ( MAX_LOG2_DIFF_CU_TR_SIZE << 1 );

static constexpr int PIC_MARGIN = 16;

static constexpr int JVET_C0024_ZERO_OUT_TH =                          32;

static constexpr int MAX_NUM_PART_IDXS_IN_CTU_WIDTH = MAX_CU_SIZE/MIN_PU_SIZE; ///< maximum number of partition indices across the width of a CTU (or height of a CTU)
static constexpr int SCALING_LIST_REM_NUM =                             6;

static constexpr int QUANT_SHIFT =                                     14; ///< Q(4) = 2^14
static constexpr int IQUANT_SHIFT =                                     6;

static constexpr int    SCALE_BITS      = 15;   // Precision for fractional bit estimates
static constexpr double FRAC_BITS_SCALE = 1.0 / (1 << SCALE_BITS);

static constexpr int SCALING_LIST_PRED_MODES = 2;
static constexpr int SCALING_LIST_NUM = MAX_NUM_COMPONENT * SCALING_LIST_PRED_MODES; ///< list number for quantization matrix

static constexpr int SCALING_LIST_START_VALUE =                         8; ///< start value for dpcm mode
static constexpr int MAX_MATRIX_COEF_NUM =                             64; ///< max coefficient number for quantization matrix
static constexpr int MAX_MATRIX_SIZE_NUM =                              8; ///< max size number for quantization matrix
static constexpr int SCALING_LIST_BITS =                                8; ///< bit depth of scaling list entries
static constexpr int LOG2_SCALING_LIST_NEUTRAL_VALUE =                  4; ///< log2 of the value that, when used in a scaling list, has no effect on quantisation
static constexpr int SCALING_LIST_DC =                                 16; ///< default DC value

static constexpr int LAST_SIGNIFICANT_GROUPS =                         14;

static constexpr int AFFINE_SUBBLOCK_SIZE = 4;   // Minimum affine MC block size

static constexpr int MMVD_REFINE_STEP =                                 8; ///< max number of distance step
static constexpr int MMVD_MAX_REFINE_NUM =                              (MMVD_REFINE_STEP * 4); ///< max number of candidate from a base candidate
static constexpr int MMVD_BASE_MV_NUM =                                 2; ///< max number of base candidate
static constexpr int MMVD_ADD_NUM =                                     (MMVD_MAX_REFINE_NUM * MMVD_BASE_MV_NUM);///< total number of mmvd candidate
static constexpr int MMVD_MRG_MAX_RD_NUM =                              MRG_MAX_NUM_CANDS;
static constexpr int MMVD_MRG_MAX_RD_BUF_NUM =                          (MMVD_MRG_MAX_RD_NUM + 1);///< increase buffer size by 1

static constexpr int MAX_TU_LEVEL_CTX_CODED_BIN_CONSTRAINT_LUMA =      28;
static constexpr int MAX_TU_LEVEL_CTX_CODED_BIN_CONSTRAINT_CHROMA =    28;

static constexpr int BIO_EXTEND_SIZE              =                     1;
static constexpr int BIO_TEMP_BUFFER_SIZE         =                     (MAX_CU_SIZE + 2 * BIO_EXTEND_SIZE) * (MAX_CU_SIZE + 2 * BIO_EXTEND_SIZE);

static constexpr int PROF_BORDER_EXT_W            =                     1;
static constexpr int PROF_BORDER_EXT_H            =                     1;
static constexpr int BCW_NUM =                                          5; ///< the number of weight options
static constexpr int BCW_DEFAULT =                                      ((uint8_t)(BCW_NUM >> 1)); ///< Default weighting index representing for w=0.5
static constexpr int BCW_SIZE_CONSTRAINT =                            256; ///< disabling Bcw if cu size is smaller than 256
static constexpr int MAX_NUM_HMVP_CANDS =                              (MRG_MAX_NUM_CANDS-1); ///< maximum number of HMVP candidates to be stored and used in merge list
static constexpr int MAX_NUM_HMVP_AVMPCANDS =                          4; ///< maximum number of HMVP candidates to be used in AMVP list

static constexpr int ALF_VB_POS_ABOVE_CTUROW_LUMA = 4;
static constexpr int ALF_VB_POS_ABOVE_CTUROW_CHMA = 2;

static constexpr int MAX_ENCODER_DEBLOCKING_QUALITY_LAYERS =           8 ;

#if SHARP_LUMA_DELTA_QP
static constexpr uint32_t LUMA_LEVEL_TO_DQP_LUT_MAXSIZE =                1024; ///< max LUT size for QP offset based on luma

#endif
static constexpr int DMVR_SUBCU_WIDTH = 16;
static constexpr int DMVR_SUBCU_HEIGHT = 16;
static constexpr int DMVR_SUBCU_WIDTH_LOG2 = 4;
static constexpr int DMVR_SUBCU_HEIGHT_LOG2 = 4;
static constexpr int MAX_NUM_SUBCU_DMVR = ((MAX_CU_SIZE * MAX_CU_SIZE) >> (DMVR_SUBCU_WIDTH_LOG2 + DMVR_SUBCU_HEIGHT_LOG2));
static constexpr int DMVR_NUM_ITERATION = 2;

//QTBT high level parameters
//for I slice luma CTB configuration para.
static constexpr int    MAX_BT_DEPTH  =                                 4;      ///<  <=7
                                                                            //for P/B slice CTU config. para.
static constexpr int    MAX_BT_DEPTH_INTER =                            4;      ///< <=7
                                                                            //for I slice chroma CTB configuration para. (in luma samples)
static constexpr int    MAX_BT_DEPTH_C      =                           0;      ///< <=7
static constexpr int    MIN_DUALTREE_CHROMA_WIDTH  =                    4;
static constexpr int    MIN_DUALTREE_CHROMA_SIZE   =                   16;
static constexpr SplitSeries SPLIT_BITS         =                       5;
static constexpr SplitSeries SPLIT_DMULT        =                       5;
static constexpr SplitSeries SPLIT_MASK         =                      31;      ///< = (1 << SPLIT_BITS) - 1

static constexpr int    SKIP_DEPTH =                                    3;
static constexpr int    PICTURE_DISTANCE_TH =                           1;
static constexpr int    FAST_SKIP_DEPTH =                               2;

static constexpr double PBINTRA_RATIO     =                             1.1;
static constexpr int    NUM_MRG_SATD_CAND =                             4;
static constexpr double MRG_FAST_RATIO    =                             1.25;
static constexpr int    NUM_AFF_MRG_SATD_CAND =                         2;

static constexpr double AMAXBT_TH32 =                                  15.0;
static constexpr double AMAXBT_TH64 =                                  30.0;

static constexpr int FAST_METHOD_TT_ENC_SPEEDUP = 0x0001;  ///< Embedding flag, which, if false, de-activates all the following ABT_ENC_SPEEDUP_* modes
static constexpr int FAST_METHOD_HOR_XOR_VER = 0x0002;
static constexpr int FAST_METHOD_ENC_SPEEDUP_BT_BASED = 0x0004;
static constexpr int FAST_METHOD_TT_ENC_SPEEDUP_BSLICE = 0x0008;
static constexpr int FAST_METHOD_TT_ENC_SPEEDUP_ISLICE = 0x0010;

// need to know for static memory allocation
static constexpr int MAX_DELTA_QP   =                                   7;      ///< maximum supported delta QP value
static constexpr int MAX_TESTED_QPs =   ( 1 + 1 + ( MAX_DELTA_QP << 1 ) );      ///< dqp=0 +- max_delta_qp + lossless mode

static constexpr int COM16_C806_TRANS_PREC =                            0;

static constexpr int NTAPS_LUMA          = 8;   // Number of taps for luma
static constexpr int NTAPS_LUMA_AFFINE   = 6;   // Number of taps for luma affine
static constexpr int NTAPS_CHROMA        = 4;   // Number of taps for chroma
static constexpr int NTAPS_CHROMA_AFFINE = 4;   // Number of taps for chroma affine
static constexpr int NTAPS_BILINEAR      = 2;   // Number of taps for bilinear filter
static constexpr int MAX_FILTER_SIZE     = NTAPS_LUMA > NTAPS_CHROMA ? NTAPS_LUMA : NTAPS_CHROMA;

static constexpr int MAX_LADF_INTERVALS       =                         5; /// max number of luma adaptive deblocking filter qp offset intervals

static constexpr int ATMVP_SUB_BLOCK_SIZE =                             3; ///< sub-block size for ATMVP
static constexpr int GEO_MAX_NUM_UNI_CANDS =                            6;
static constexpr int GEO_MAX_NUM_CANDS = GEO_MAX_NUM_UNI_CANDS * (GEO_MAX_NUM_UNI_CANDS - 1);
static constexpr int GEO_MIN_CU_LOG2 =                                  3;
static constexpr int GEO_MAX_CU_LOG2 =                                  6;
static constexpr int GEO_MIN_CU_SIZE =               1 << GEO_MIN_CU_LOG2;
static constexpr int GEO_MAX_CU_SIZE =               1 << GEO_MAX_CU_LOG2;
static constexpr int GEO_NUM_CU_SIZE = ( GEO_MAX_CU_LOG2 - GEO_MIN_CU_LOG2 ) + 1;
static constexpr int GEO_NUM_PARTITION_MODE =                          64;
static constexpr int GEO_NUM_ANGLES =                                  32;
static constexpr int GEO_NUM_DISTANCES =                                4;
static constexpr int GEO_NUM_PRESTORED_MASK =                           6;
static constexpr int GEO_WEIGHT_MASK_SIZE = 3 * (GEO_MAX_CU_SIZE >> 3) * 2 + GEO_MAX_CU_SIZE;
static constexpr int GEO_MV_MASK_SIZE =         GEO_WEIGHT_MASK_SIZE >> 2;
static constexpr int GEO_MAX_TRY_WEIGHTED_SAD = 60;
static constexpr int GEO_MAX_TRY_WEIGHTED_SATD = 8;

static constexpr int SBT_MAX_SIZE =                                    64; ///< maximum CU size for using SBT
static constexpr int SBT_NUM_SL =                                      10; ///< maximum number of historical PU decision saved for a CU
static constexpr int SBT_NUM_RDO =                                      2; ///< maximum number of SBT mode tried for a PU

static constexpr int NUM_INTER_CU_INFO_SAVE =                           8; ///< maximum number of inter cu information saved for fast algorithm
static constexpr int LDT_MODE_TYPE_INHERIT =                            0; ///< No need to signal mode_constraint_flag, and the modeType of the region is inherited from its parent node
static constexpr int LDT_MODE_TYPE_INFER =                              1; ///< No need to signal mode_constraint_flag, and the modeType of the region is inferred as MODE_TYPE_INTRA
static constexpr int LDT_MODE_TYPE_SIGNAL =                             2; ///< Need to signal mode_constraint_flag, and the modeType of the region is determined by the flag

static constexpr int IBC_MAX_CAND_SIZE = 16; // max block size for ibc search
static constexpr int IBC_NUM_CANDIDATES = 64; ///< Maximum number of candidates to store/test
static constexpr int CHROMA_REFINEMENT_CANDIDATES = 8; /// 8 candidates BV to choose from
static constexpr int IBC_FAST_METHOD_NOINTRA_IBCCBF0 = 0x01;
static constexpr int IBC_FAST_METHOD_BUFFERBV = 0X02;
static constexpr int IBC_FAST_METHOD_ADAPTIVE_SEARCHRANGE = 0X04;
static constexpr int MV_EXPONENT_BITCOUNT    = 4;
static constexpr int MV_MANTISSA_BITCOUNT    = 6;
static constexpr int MV_MANTISSA_UPPER_LIMIT = ((1 << (MV_MANTISSA_BITCOUNT - 1)) - 1);
static constexpr int MV_MANTISSA_LIMIT       = (1 << (MV_MANTISSA_BITCOUNT - 1));
static constexpr int MV_EXPONENT_MASK        = ((1 << MV_EXPONENT_BITCOUNT) - 1);

static constexpr int MV_BITS =                                   18;
static constexpr int MV_MAX =              (1 << (MV_BITS - 1)) - 1;
static constexpr int MV_MIN =                 -(1 << (MV_BITS - 1));

static constexpr int MVD_MAX =                            (1 << 17) - 1;
static constexpr int MVD_MIN =                               -(1 << 17);

static constexpr int PIC_ANALYZE_CW_BINS =                           32;
static constexpr int PIC_CODE_CW_BINS =                              16;
static constexpr int LMCS_SEG_NUM =                                  32;
static constexpr int FP_PREC =                                       11;
static constexpr int CSCALE_FP_PREC =                                11;
static constexpr int LOG2_PALETTE_CG_SIZE =                           4;
static constexpr int RUN_IDX_THRE =                                   4;
static constexpr int MAX_CU_BLKSIZE_PLT =                            64;
static constexpr int NUM_TRELLIS_STATE =                              3;
static constexpr double ENC_CHROMA_WEIGHTING =                      0.8;
static constexpr int MAXPLTPREDSIZE = 63;
static constexpr int MAXPLTSIZE = 31;
static constexpr int MAXPLTPREDSIZE_DUALTREE = 31;
static constexpr int MAXPLTSIZE_DUALTREE = 15;
static constexpr double PLT_CHROMA_WEIGHTING =                      0.8;
static constexpr int PLT_ENCBITDEPTH = 8;
static constexpr int PLT_FAST_RATIO = 100;
#if RExt__DECODER_DEBUG_TOOL_MAX_FRAME_STATS
static constexpr int  EPBIN_WEIGHT_FACTOR =                           4;
#endif
static constexpr int ENC_PPS_ID_RPR =                                 3;
static constexpr int SCALE_RATIO_BITS =                              14;
static constexpr int MAX_SCALING_RATIO =                              2;  // max downsampling ratio for RPR
static const     std::pair<int, int> SCALE_1X = std::pair<int, int>( 1 << SCALE_RATIO_BITS, 1 << SCALE_RATIO_BITS );  // scale ratio 1x
static constexpr int DELTA_QP_ACT[4] =                  { -5, 1, 3, 1 };
static constexpr int MAX_TSRC_RICE =                                  8;  ///<Maximum supported TSRC Rice parameter
static constexpr int MIN_TSRC_RICE =                                  1;  ///<Minimum supported TSRC Rice parameter
static constexpr int MAX_CTI_LUT_SIZE =                              64;  ///<Maximum colour transform LUT size for CTI SEI
static constexpr int MAX_NUM_INTENSITIES =                          256;  ///<Maximum number of intensity intervals supported in FGC SEI
static constexpr int MAX_NUM_MODEL_VALUES =                           6;  ///<Maximum number of model values supported in FGC SEI
static constexpr int MAX_ALLOWED_MODEL_VALUES =                       3;
static constexpr int MAX_ALLOWED_COMP_MODEL_PAIRS =                  10;
static constexpr int MAX_STANDARD_DEVIATION =                       255;  // for 8-bit format; for higher bit depths, internal scaling is performed
static constexpr int DATA_BASE_SIZE =                                64;
static constexpr int BLK_8 =                                          8;
static constexpr int BLK_16 =                                        16;
static constexpr int BLK_32 =                                        32;
static constexpr int BIT_DEPTH_8 =                                    8;

static constexpr int MSE_WEIGHT_FRAC_BITS = 16;
static constexpr int MSE_WEIGHT_ONE       = 1 << MSE_WEIGHT_FRAC_BITS;
// ====================================================================================================================
// SEI and related constants
// ====================================================================================================================
#if JVET_Z0120_SII_SEI_PROCESSING
static constexpr double SII_PF_W2 =                                       0.6; // weight for current picture
static constexpr double SII_PF_W1 =                                       0.4; // weight for previous picture , it must be equal to 1.0 - SII_PF_W2
#endif
// ====================================================================================================================
// Macro functions
// ====================================================================================================================

struct ClpRng
{
  int min {0};
  int max {0};
  int bd  {0};
  int n   {0};
};

struct ClpRngs
{
  ClpRng comp[MAX_NUM_COMPONENT]; ///< the bit depth as indicated in the SPS
  bool used;
  bool chroma;
};

template <typename T> inline T Clip3 (const T minVal, const T maxVal, const T a) { return std::min<T> (std::max<T> (minVal, a) , maxVal); }  ///< general min/max clip
template <typename T> inline T ClipBD( const T x, const int bitDepth ) { return Clip3( T( 0 ), T( ( 1 << bitDepth ) - 1 ), x ); }
template <typename T> inline T ClipPel (const T a, const ClpRng& clpRng)         { return std::min<T> (std::max<T> (clpRng.min, a) , clpRng.max); }  ///< clip reconstruction

template <typename T> inline void Check3( T minVal, T maxVal, T a)
{
  CHECK( ( a > maxVal ) || ( a < minVal ), "ERROR: Range check " << minVal << " >= " << a << " <= " << maxVal << " failed" );
}  ///< general min/max clip

extern MsgLevel g_verbosity;

#include <stdarg.h>
inline void msg( MsgLevel level, const char* fmt, ... )
{
  if( g_verbosity >= level )
  {
    va_list args;
    va_start( args, fmt );
    vfprintf( level == ERROR ? stderr : stdout, fmt, args );
    va_end( args );
  }
}

template<typename T> bool isPowerOf2( const T val ) { return ( val & ( val - 1 ) ) == 0; }

#define MEMORY_ALIGN_DEF_SIZE       32  // for use with avx2 (256 bit)
#define CACHE_MEM_ALIGN_SIZE      1024

#define ALIGNED_MALLOC              1   ///< use 32-bit aligned malloc/free

#if ALIGNED_MALLOC
#if JVET_J0090_MEMORY_BANDWITH_MEASURE
void *cache_mem_align_malloc(int size, int align_size);
void cache_mem_align_free(void *ptr);
#define xMalloc(type, len)          cache_mem_align_malloc(sizeof(type) * len, CACHE_MEM_ALIGN_SIZE)
#define xFree(ptr)                  cache_mem_align_free(ptr)
#elif     ( _WIN32 && ( _MSC_VER > 1300 ) ) || defined (__MINGW64_VERSION_MAJOR)
#define xMalloc( type, len )        _aligned_malloc( sizeof(type)*(len), MEMORY_ALIGN_DEF_SIZE )
#define xFree( ptr )                _aligned_free  ( ptr )
#elif defined (__MINGW32__)
#define xMalloc( type, len )        __mingw_aligned_malloc( sizeof(type)*(len), MEMORY_ALIGN_DEF_SIZE )
#define xFree( ptr )                __mingw_aligned_free( ptr )
#else
namespace detail {
template<typename T>
T* aligned_malloc(size_t len, size_t alignement) {
  T *p = nullptr;
  if( posix_memalign( (void**)&p, alignement, sizeof(T)*(len) ) )
  {
    THROW("posix_memalign failed");
  }
  return p;
}
}
#define xMalloc( type, len )        detail::aligned_malloc<type>( len, MEMORY_ALIGN_DEF_SIZE )
#define xFree( ptr )                free( ptr )
#endif

#else
#define xMalloc( type, len )        malloc   ( sizeof(type)*(len) )
#define xFree( ptr )                free     ( ptr )
#endif //#if ALIGNED_MALLOC

#if defined _MSC_VER
#define ALIGN_DATA(nBytes,v) __declspec(align(nBytes)) v
#else
//#elif defined linux
#define ALIGN_DATA(nBytes,v) v __attribute__ ((aligned (nBytes)))
//#else
//#error unknown platform
#endif

#if defined(__GNUC__) && !defined(__clang__)
#    define GCC_VERSION_AT_LEAST(x,y) (__GNUC__ > x || __GNUC__ == x && __GNUC_MINOR__ >= y)
#else
#    define GCC_VERSION_AT_LEAST(x,y) 0
#endif

#ifdef __clang__
#    define CLANG_VERSION_AT_LEAST(x,y) (__clang_major__ > x || __clang_major__ == x && __clang_minor__ >= y)
#else
#    define CLANG_VERSION_AT_LEAST(x,y) 0
#endif

#ifdef __GNUC__
#    define ALWAYS_INLINE __attribute__((always_inline)) inline
#elif defined _MSC_VER
#    define ALWAYS_INLINE __forceinline
#else
#    define ALWAYS_INLINE
#endif

#if ENABLE_SIMD_OPT
#ifdef TARGET_SIMD_X86
typedef enum{
  SCALAR = 0,
  SSE41,
  SSE42,
  AVX,
  AVX2,
  AVX512
} X86_VEXT;

X86_VEXT read_x86_extension_flags(const std::string &extStrId = std::string());
const char* read_x86_extension(const std::string &extStrId);
#endif //TARGET_SIMD_X86
#endif //ENABLE_SIMD_OPT

template <typename ValueType> inline ValueType leftShift       (const ValueType value, const int shift) { return (shift >= 0) ? ( value                                  << shift) : ( value                                   >> -shift); }
template <typename ValueType> inline ValueType rightShift      (const ValueType value, const int shift) { return (shift >= 0) ? ( value                                  >> shift) : ( value                                   << -shift); }
template <typename ValueType> inline ValueType leftShift_round (const ValueType value, const int shift) { return (shift >= 0) ? ( value                                  << shift) : ((value + (ValueType(1) << (-shift - 1))) >> -shift); }
template <typename ValueType> inline ValueType rightShift_round(const ValueType value, const int shift) { return (shift > 0) ? ((value + (ValueType(1) << (shift - 1))) >> shift) : ( value                                   << -shift); }

static inline int floorLog2(uint32_t x)
{
  if (x == 0)
  {
    // note: ceilLog2() expects -1 as return value
    return -1;
  }
#ifdef __GNUC__
  return 31 - __builtin_clz(x);
#else
#ifdef _MSC_VER
  unsigned long r = 0;
  _BitScanReverse(&r, x);
  return r;
#else
  int result = 0;
  if (x & 0xffff0000)
  {
    x >>= 16;
    result += 16;
  }
  if (x & 0xff00)
  {
    x >>= 8;
    result += 8;
  }
  if (x & 0xf0)
  {
    x >>= 4;
    result += 4;
  }
  if (x & 0xc)
  {
    x >>= 2;
    result += 2;
  }
  if (x & 0x2)
  {
    x >>= 1;
    result += 1;
  }
  return result;
#endif
#endif
}

static inline int ceilLog2(uint32_t x)
{
  return (x==0) ? -1 : floorLog2(x - 1) + 1;
}


//CASE-BREAK for breakpoints
#if defined ( _MSC_VER ) && defined ( _DEBUG )
#define _CASE(_x) if(_x)
#define _BREAK while(0);
#define _AREA_AT(_a,_x,_y,_w,_h)  (_a.x==_x && _a.y==_y && _a.width==_w && _a.height==_h)
#define _AREA_CONTAINS(_a,_x,_y)  (_a.contains( Position{ _x, _y} ))
#define _UNIT_AREA_AT(_a,_x,_y,_w,_h) (_a.Y().x==_x && _a.Y().y==_y && _a.Y().width==_w && _a.Y().height==_h)
#else
#define _CASE(...)
#define _BREAK
#define _AREA_AT(...)
#define _AREA_CONTAINS(_a,_x,_y)
#define _UNIT_AREA_AT(_a,_x,_y,_w,_h)
#endif

static constexpr uint32_t CCALF_CANDS_COEFF_NR = 8;
static constexpr int CCALF_SMALL_TAB[CCALF_CANDS_COEFF_NR] = { 0, 1, 2, 4, 8, 16, 32, 64 };

//! \}

#endif // end of #ifndef  __COMMONDEF__

