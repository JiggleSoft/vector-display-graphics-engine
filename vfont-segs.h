//=============================================================================
// Title:        VEctor Display Graphics Engine (vEdge) Font Segment Constants.
// Filename:     vfont-segs.h
// Platform:     Any supported by SDL version 2.
// Language:     ANSI C99
// Author:       Justin Lane (vedge@jigglesoft.co.uk)
// Date:         2021-03-25 17:16
// Version:      1.0.0-beta-1
//-----------------------------------------------------------------------------
// Copyright (c) 2021 Justin Lane
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//-----------------------------------------------------------------------------

#ifndef __VFONT_SEGS__H__
#define __VFONT_SEGS__H__


//-----------------------------------------------------------------------------
// Font Line Co-ordinates.
//-----------------------------------------------------------------------------

#define VFONT_LINE(a,b,c,d) { .x1 = a, .y1 = b, .x2 = c, .y2 = d }



//-----------------------------------------------------------------------------
// Arcade Font.
//-----------------------------------------------------------------------------
//
//      11  12  13  14  15  16  17  18  19
//      21  22  23  24  25  26  27  28  29
//      31  32  33  34  35  36  37  38  39
//      41  42  43  44  45  46  47  48  49
//      51  52  53  54  55  56  57  58  59
//      61  62  63  64  65  66  67  68  69
//      71  72  73  74  75  76  77  78  79
//      81  82  83  84  85  86  87  88  89
//      91  92  93  94  95  96  97  98  99
//
//-----------------------------------------------------------------------------

#define VFONT_ARCADE_A_B(a,b) VFONT_LINE( (((a-11)%10)-4), (((a-11)/10)-4), (((b-11)%10)-4), (((b-11)/10)-4) )

#define VFONT_ARCADE_13_93 VFONT_ARCADE_A_B(13,93)
#define VFONT_ARCADE_14_34 VFONT_ARCADE_A_B(14,34)
#define VFONT_ARCADE_14_94 VFONT_ARCADE_A_B(14,94)
#define VFONT_ARCADE_15_75 VFONT_ARCADE_A_B(15,75)
#define VFONT_ARCADE_16_36 VFONT_ARCADE_A_B(16,36)
#define VFONT_ARCADE_17_97 VFONT_ARCADE_A_B(17,97)
#define VFONT_ARCADE_22_28 VFONT_ARCADE_A_B(22,28)
#define VFONT_ARCADE_31_39 VFONT_ARCADE_A_B(31,39)
#define VFONT_ARCADE_71_79 VFONT_ARCADE_A_B(71,79)
#define VFONT_ARCADE_82_88 VFONT_ARCADE_A_B(82,88)
#define VFONT_ARCADE_85_95 VFONT_ARCADE_A_B(85,95)
#define VFONT_ARCADE_52_58 VFONT_ARCADE_A_B(52,58)
#define VFONT_ARCADE_22_52 VFONT_ARCADE_A_B(22,52)
#define VFONT_ARCADE_58_88 VFONT_ARCADE_A_B(58,88)
#define VFONT_ARCADE_16_96 VFONT_ARCADE_A_B(16,96)
#define VFONT_ARCADE_15_95 VFONT_ARCADE_A_B(15,95)
#define VFONT_ARCADE_51_59 VFONT_ARCADE_A_B(51,59)
#define VFONT_ARCADE_11_99 VFONT_ARCADE_A_B(11,99)
#define VFONT_ARCADE_19_91 VFONT_ARCADE_A_B(19,91)
#define VFONT_ARCADE_91_99 VFONT_ARCADE_A_B(91,99)
#define VFONT_ARCADE_11_91 VFONT_ARCADE_A_B(11,91)
#define VFONT_ARCADE_19_99 VFONT_ARCADE_A_B(19,99)
#define VFONT_ARCADE_19_59 VFONT_ARCADE_A_B(19,59)
#define VFONT_ARCADE_51_59 VFONT_ARCADE_A_B(51,59)
#define VFONT_ARCADE_51_91 VFONT_ARCADE_A_B(51,91)
#define VFONT_ARCADE_11_51 VFONT_ARCADE_A_B(11,51)
#define VFONT_ARCADE_59_99 VFONT_ARCADE_A_B(59,99)
#define VFONT_ARCADE_11_55 VFONT_ARCADE_A_B(11,55)
#define VFONT_ARCADE_55_19 VFONT_ARCADE_A_B(55,19)
#define VFONT_ARCADE_55_95 VFONT_ARCADE_A_B(55,95)
#define VFONT_ARCADE_55_99 VFONT_ARCADE_A_B(55,99)
#define VFONT_ARCADE_35_45 VFONT_ARCADE_A_B(35,45)
#define VFONT_ARCADE_65_75 VFONT_ARCADE_A_B(65,75)
#define VFONT_ARCADE_65_74 VFONT_ARCADE_A_B(65,74)
#define VFONT_ARCADE_85_94 VFONT_ARCADE_A_B(85,94)
#define VFONT_ARCADE_15_26 VFONT_ARCADE_A_B(15,26)
#define VFONT_ARCADE_11_13 VFONT_ARCADE_A_B(11,13)
#define VFONT_ARCADE_11_31 VFONT_ARCADE_A_B(11,31)
#define VFONT_ARCADE_31_33 VFONT_ARCADE_A_B(31,33)
#define VFONT_ARCADE_13_33 VFONT_ARCADE_A_B(13,33)
#define VFONT_ARCADE_77_79 VFONT_ARCADE_A_B(77,79)
#define VFONT_ARCADE_77_97 VFONT_ARCADE_A_B(77,97)
#define VFONT_ARCADE_97_99 VFONT_ARCADE_A_B(97,99)
#define VFONT_ARCADE_79_99 VFONT_ARCADE_A_B(79,99)
#define VFONT_ARCADE_11_19 VFONT_ARCADE_A_B(11,19)
#define VFONT_ARCADE_17_23 VFONT_ARCADE_A_B(17,23)
#define VFONT_ARCADE_23_83 VFONT_ARCADE_A_B(23,83)
#define VFONT_ARCADE_83_97 VFONT_ARCADE_A_B(83,97)
#define VFONT_ARCADE_13_27 VFONT_ARCADE_A_B(14,26)
#define VFONT_ARCADE_27_87 VFONT_ARCADE_A_B(26,86)
#define VFONT_ARCADE_87_93 VFONT_ARCADE_A_B(86,94)
#define VFONT_ARCADE_51_57 VFONT_ARCADE_A_B(51,57)
#define VFONT_ARCADE_19_51 VFONT_ARCADE_A_B(19,51)
#define VFONT_ARCADE_51_99 VFONT_ARCADE_A_B(51,99)
#define VFONT_ARCADE_11_59 VFONT_ARCADE_A_B(11,59)
#define VFONT_ARCADE_59_91 VFONT_ARCADE_A_B(59,91)
#define VFONT_ARCADE_13_17 VFONT_ARCADE_A_B(13,17)
#define VFONT_ARCADE_93_97 VFONT_ARCADE_A_B(93,97)
#define VFONT_ARCADE_77_99 VFONT_ARCADE_A_B(77,99)
#define VFONT_ARCADE_11_95 VFONT_ARCADE_A_B(11,95)
#define VFONT_ARCADE_19_95 VFONT_ARCADE_A_B(19,95)
#define VFONT_ARCADE_11_93 VFONT_ARCADE_A_B(11,93)
#define VFONT_ARCADE_55_93 VFONT_ARCADE_A_B(55,93)
#define VFONT_ARCADE_55_97 VFONT_ARCADE_A_B(55,97)
#define VFONT_ARCADE_19_97 VFONT_ARCADE_A_B(19,97)
#define VFONT_ARCADE_55_59 VFONT_ARCADE_A_B(55,59)
#define VFONT_ARCADE_55_75 VFONT_ARCADE_A_B(55,75)
#define VFONT_ARCADE_19_55 VFONT_ARCADE_A_B(19,55)
#define VFONT_ARCADE_15_33 VFONT_ARCADE_A_B(15,33)
#define VFONT_ARCADE_15_37 VFONT_ARCADE_A_B(15,37)
#define VFONT_ARCADE_91_95 VFONT_ARCADE_A_B(91,95)
#define VFONT_ARCADE_51_53 VFONT_ARCADE_A_B(51,53)
#define VFONT_ARCADE_19_53 VFONT_ARCADE_A_B(19,53)
#define VFONT_ARCADE_53_99 VFONT_ARCADE_A_B(53,99)
#define VFONT_ARCADE_15_31 VFONT_ARCADE_A_B(15,31)
#define VFONT_ARCADE_15_39 VFONT_ARCADE_A_B(15,39)
#define VFONT_ARCADE_31_91 VFONT_ARCADE_A_B(31,91)
#define VFONT_ARCADE_39_99 VFONT_ARCADE_A_B(39,99)
#define VFONT_ARCADE_11_17 VFONT_ARCADE_A_B(11,17)
#define VFONT_ARCADE_91_97 VFONT_ARCADE_A_B(91,97)
#define VFONT_ARCADE_17_39 VFONT_ARCADE_A_B(17,39)
#define VFONT_ARCADE_79_97 VFONT_ARCADE_A_B(79,97)
#define VFONT_ARCADE_39_79 VFONT_ARCADE_A_B(39,79)
#define VFONT_ARCADE_57_39 VFONT_ARCADE_A_B(57,39)
#define VFONT_ARCADE_57_79 VFONT_ARCADE_A_B(57,79)
#define VFONT_ARCADE_14_32 VFONT_ARCADE_A_B(14,32)
#define VFONT_ARCADE_14_36 VFONT_ARCADE_A_B(14,36)
#define VFONT_ARCADE_32_98 VFONT_ARCADE_A_B(32,98)
#define VFONT_ARCADE_36_72 VFONT_ARCADE_A_B(36,72)
#define VFONT_ARCADE_58_94 VFONT_ARCADE_A_B(58,94)
#define VFONT_ARCADE_72_94 VFONT_ARCADE_A_B(72,94)
#define VFONT_ARCADE_19_11 VFONT_ARCADE_A_B(19,11)
#define VFONT_ARCADE_33_73 VFONT_ARCADE_A_B(33,73)
#define VFONT_ARCADE_37_33 VFONT_ARCADE_A_B(37,33)
#define VFONT_ARCADE_73_79 VFONT_ARCADE_A_B(73,79)
#define VFONT_ARCADE_77_37 VFONT_ARCADE_A_B(77,37)
#define VFONT_ARCADE_79_19 VFONT_ARCADE_A_B(79,19)



//-----------------------------------------------------------------------------
// Seven Segment Displays.
//-----------------------------------------------------------------------------
//
//      ----A----
//     |         |
//     F         B
//     |         |
//     |----G----|
//     |         |
//     E         C
//     |         |
//      ----A----   P
//
//-----------------------------------------------------------------------------

#define VFONT_7SEG_A  { .x1 = -4, .y1 = -4, .x2 =  4, .y2 = -4 }
#define VFONT_7SEG_B  { .x1 =  4, .y1 = -4, .x2 =  4, .y2 =  0 }
#define VFONT_7SEG_C  { .x1 =  4, .y1 =  0, .x2 =  4, .y2 =  4 }
#define VFONT_7SEG_D  { .x1 = -4, .y1 =  4, .x2 =  4, .y2 =  4 }
#define VFONT_7SEG_E  { .x1 = -4, .y1 =  0, .x2 = -4, .y2 =  4 }
#define VFONT_7SEG_F  { .x1 = -4, .y1 = -4, .x2 = -4, .y2 =  0 }
#define VFONT_7SEG_G  { .x1 = -4, .y1 =  0, .x2 =  4, .y2 =  0 }

#define VFONT_7SEG_P  { .x1 =  6, .y1 =  3, .x2 =  6, .y2 =  4 }

#define VFONT_7SEG_EF { .x1 = -4, .y1 = -4, .x2 = -4, .y2 =  4 }
#define VFONT_7SEG_BC { .x1 =  4, .y1 = -4, .x2 =  4, .y2 =  4 }



//-----------------------------------------------------------------------------
// 16 Segment Display
//-----------------------------------------------------------------------------
//
//      -----1---- ----18----
//     |  \       |       /  |
//     4     3    2    17   16
//     |       \  |  /       |
//      -----5---- ----15----
//     |       /  |  \       |
//     8     7    6    14   13
//     |  /       |       \  |
//      -----9---- ----10----    12
//
//-----------------------------------------------------------------------------

#define VFONT_16SEG_1 VFONT_LINE(-4, -4, 0, -4)
#define VFONT_16SEG_2 VFONT_LINE( 0, -4, 0,  0)
#define VFONT_16SEG_3 { .x1 = -4, .y1 = -4, .x2 = 0, .y2 = 0 }
#define VFONT_16SEG_4 { .x1 = -4, .y1 = -4, .x2 = -4, .y2 =  0 }
#define VFONT_16SEG_5 { .x1 = -4, .y1 = 0, .x2 = 0, .y2 = 0 }
#define VFONT_16SEG_6 { .x1 = 0, .y1 = 0, .x2 = 0, .y2 = 4 }
#define VFONT_16SEG_7 { .x1 = 0, .y1 = 0, .x2 = -4, .y2 = 4 }
#define VFONT_16SEG_8 { .x1 = -4, .y1 =  0, .x2 = -4, .y2 =  4 }
#define VFONT_16SEG_9 { .x1 = -4, .y1 = 4, .x2 = 0, .y2 = 4 }
#define VFONT_16SEG_10 { .x1 = 0, .y1 = 4, .x2 = 4, .y2 = 4 }
#define VFONT_16SEG_12 { .x1 =  6, .y1 =  3, .x2 =  6, .y2 =  4 }
#define VFONT_16SEG_13 { .x1 =  4, .y1 =  0, .x2 =  4, .y2 =  4 }
#define VFONT_16SEG_14 { .x1 = 0, .y1 = 0, .x2 = 4, .y2 = 4 }
#define VFONT_16SEG_15 { .x1 = 0, .y1 = 0, .x2 = 4, .y2 = 0 }
#define VFONT_16SEG_16 { .x1 =  4, .y1 = -4, .x2 =  4, .y2 =  0 }
#define VFONT_16SEG_17 { .x1 = 0, .y1 = 0, .x2 = 4, .y2 = -4 }
#define VFONT_16SEG_18 { .x1 = 0, .y1 = -4, .x2 = 4, .y2 = -4 }

#define VFONT_16SEG_1_18 { .x1 = -4, .y1 = -4, .x2 =  4, .y2 = -4 }
#define VFONT_16SEG_4_8 { .x1 = -4, .y1 = -4, .x2 = -4, .y2 =  4 }
#define VFONT_16SEG_9_10 { .x1 = -4, .y1 =  4, .x2 =  4, .y2 =  4 }
#define VFONT_16SEG_13_16 { .x1 =  4, .y1 = -4, .x2 =  4, .y2 =  4 }

#define VFONT_16SEG_2_6 { .x1 = 0, .y1 = -4, .x2 = 0, .y2 = 4 }
#define VFONT_16SEG_3_14 { .x1 = -4, .y1 = -4, .x2 = 4, .y2 = 4 }
#define VFONT_16SEG_5_15 { .x1 = -4, .y1 =  0, .x2 =  4, .y2 =  0 }
#define VFONT_16SEG_7_17 { .x1 = -4, .y1 = 4, .x2 = 4, .y2 = -4 }



#endif /* __VFONT_SEGS__H__ */


