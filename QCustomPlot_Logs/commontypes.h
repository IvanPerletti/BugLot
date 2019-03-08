#ifndef COMMONTYPES_H
#define COMMONTYPES_H

typedef enum {
    EEE_CHECKSUM							 = 0   ,
    ANGOLO_START               			     = 1   ,
    HMINPENSILE                			     = 2   ,
    HMAXPENSILE                			     = 3   ,
    STEP_SPIRALE               			     = 4   ,
    POT_ROT_0                  			     = 5  ,
    POT_ROT_90                 			     = 6  ,
    POT_ROT_M90                			     = 7  ,
    MINPENSILELAT              			     = 8  ,
    MAXPENSILELAT              			     = 9 ,
    MINPENSILELONG             			     = 10  ,
    MAXPENSILELONG             			     = 11  ,
    CAMMA_BUCKY_CENTER         			     = 12  ,
    CAMMA_BUCKY_1              			     = 13  ,
    CAMMA_BUCKY_2              			     = 14  ,
    CAMMA_BUCKY_3              			     = 15  ,
    POSBKYLAT								 = 16  ,
    OFFSET_TB_BUCKY            			     = 17  ,
    POSBKYLONG                 			     = 18  ,
    WALLBKYPOS                 			     = 19  ,
    MIN_BUCKYVERT              			     = 20  ,
    MAX_BUCKYVERT              			     = 21  ,
    WALLBKY_PRESENT            			     = 22  ,
    WALLBKYROTATION            			     = 23  ,
    WALLBKYGRID                			     = 24  ,
    WALLBKYTILT_PRESENT        			     = 25  ,
    OFFSET_ROT_BUCKY           			     = 26  ,
    OFFSET_INC_BUCKY           			     = 27  ,
    OFF_DET_LAT                			     = 28  ,
    OFF_DET_LONG               			     = 29  ,
    MINDETLAT                  			     = 30  ,
    MINENCDETLAT             			     = 31  ,
    MAXDETLAT                  			     = 32  ,
    MAXENCDETLAT             			     = 33  ,
    MINDETLONG                 			     = 34  ,
    MINENCDETLONG            			     = 35  ,
    MAXDETLONG                 			     = 36  ,
    MAXENCDETLONG            			     = 37  ,
    OFF_CASS_FUORI_DET_LAT     			     = 38  ,
    POT_DETLAT_MIN             			     = 39  ,
    POT_DETLAT_MAX             			     = 40  ,
    DETROTATION                			     = 41  ,
    DETGRID                    			     = 42  ,

    OFF_CASS_FUORI_DET_LONG    			     = 43 ,
    CORSADETLAT                			     = 44 ,
    CORSADETLONG               			     = 45 ,
    MINIMOELEVIX               			     = 46 ,
    MASSIMOELEVIX              			     = 47 ,
    OFFSET_TB_ELEVIX           			     = 48 ,
    MIN_ANA_ELEVIX             			     = 49 ,
    MAX_ANA_ELEVIX             			     = 50 ,
    ELEVIX_PRESENT             			     = 51 ,
    ELEVIXPOS                  			     = 52 ,
    FOCELEVIX                  			     = 53 ,
    OFFSET_ROT_ELEVIX          			     = 54 ,
    OFFLATPORTACASS1_0         			     = 55 ,
    OFFLONGPORTACASS1_0        			     = 56 ,
    OFFTBPORTACASS1_0          			     = 57 ,
    OFFROTPORTACASS1_0         			     = 58 ,
    OFFINCPORTACASS1_0         			     = 59 ,
    FOCPORTACASS1_0            			     = 60 ,
    OFFLATPORTACASS1_45        			     = 61 ,
    OFFLONGPORTACASS1_45       			     = 62 ,
    OFFTBPORTACASS1_45         			     = 63 ,
    OFFROTPORTACASS1_45        			     = 64 ,
    OFFINCPORTACASS1_45        			     = 65 ,
    FOCPORTACASS1_45           			     = 66 ,
    OFFLATPORTACASS1_M45       			     = 67 ,
    OFFLONGPORTACASS1_M45      			     = 68 ,
    OFFTBPORTACASS1_M45        			     = 69 ,
    OFFROTPORTACASS1_M45       			     = 70 ,
    OFFINCPORTACASS1_M45       			     = 71 ,
    FOCPORTACASS1_M45          			     = 72 ,
    OFFLATPORTACASS2_0         			     = 73 ,
    OFFLONGPORTACASS2_0        			     = 74 ,
    OFFTBPORTACASS2_0          			     = 75 ,
    OFFROTPORTACASS2_0         			     = 76 ,
    OFFINCPORTACASS2_0         			     = 77 ,
    FOCPORTACASS2_0            			     = 78 ,
    OFFLATPORTACASS2_45        			     = 79 ,
    OFFLONGPORTACASS2_45       			     = 80 ,
    OFFTBPORTACASS2_45         			     = 81 ,
    OFFROTPORTACASS2_45        			     = 82 ,
    OFFINCPORTACASS2_45        			     = 83 ,
    FOCPORTACASS2_45           			     = 84 ,
    OFFLATPORTACASS2_M45       			     = 85 ,
    OFFLONGPORTACASS2_M45      			     = 86 ,
    OFFTBPORTACASS2_M45        			     = 87 ,
    OFFROTPORTACASS2_M45       			     = 88 ,
    OFFINCPORTACASS2_M45       			     = 89 ,
    FOCPORTACASS2_M45          			     = 90 ,

    OFF_LAT_BUCKY_ORIZZ        			     = 91 ,
    OFF_LONG_BUCKY_ORIZZ       			     = 92 ,
    OFFSET_TB_BUCKY_ORIZZ      			     = 93 ,
    OFFSET_ROT_BUCKY_ORIZZ     			     = 94 ,
    FOC_BUCKY_ORIZZ            			     = 95 ,
    OFF_LAT_BUCKY_45           			     = 96 ,
    OFF_LONG_BUCKY_45          			     = 97 ,
    OFFSET_TB_BUCKY_45         			     = 98 ,
    OFFSET_ROT_BUCKY_45        			     = 99 ,
    OFFSET_INC_BUCKY_45        			     = 100,
    FOC_BUCKY_45               			     = 101 ,
    H_BUCKY_ORIZZ              			     = 102 ,
    OFF_LAT_BUCKY_ORIZZ_2      			     = 103 ,
    OFF_LONG_BUCKY_ORIZZ_2     			     = 104 ,
    OFFSET_ROT_BUCKY_ORIZZ_2   			     = 105 ,
    AUTO_POS_LAT_1             			     = 106 ,
    AUTO_POS_LONG_1            			     = 107 ,
    AUTO_POS_ROT_1             			     = 108 ,
    AUTO_POS_INC_1             			     = 109 ,
    AUTO_POS_VERT_1            			     = 110 ,
    AUTO_POS_BKY_VERT_1        			     = 111 ,
    AUTO_POS_BKY_TILT_1        			     = 112 ,
    AUTO_POS_ELEV_1            			     = 113 ,
    AUTO_POS_LAT_2             			     = 114 ,
    AUTO_POS_LONG_2            			     = 115 ,
    AUTO_POS_ROT_2             			     = 116 ,
    AUTO_POS_INC_2             			     = 117 ,
    AUTO_POS_VERT_2            			     = 118 ,
    AUTO_POS_BKY_VERT_2        			     = 119 ,
    AUTO_POS_BKY_TILT_2        			     = 120 ,
    AUTO_POS_ELEV_2            			     = 121 ,
    AUTO_POS_LAT_3             			     = 122 ,
    AUTO_POS_LONG_3            			     = 123 ,
    AUTO_POS_ROT_3             			     = 124 ,
    AUTO_POS_INC_3             			     = 125 ,
    AUTO_POS_VERT_3            			     = 126 ,
    AUTO_POS_BKY_VERT_3        			     = 127 ,
    AUTO_POS_BKY_TILT_3        			     = 128 ,
    AUTO_POS_ELEV_3            			     = 129 ,
    AUTO_POS_LAT_4             			     = 130 ,
    AUTO_POS_LONG_4            			     = 131 ,
    AUTO_POS_ROT_4             			     = 132 ,
    AUTO_POS_INC_4             			     = 133 ,
    AUTO_POS_VERT_4            			     = 134 ,
    AUTO_POS_BKY_VERT_4        			     = 135 ,
    AUTO_POS_BKY_TILT_4        			     = 136 ,
    AUTO_POS_ELEV_4            			     = 137 ,
    AUTO_POS_LAT_5             			     = 138 ,
    AUTO_POS_LONG_5            			     = 139 ,
    AUTO_POS_ROT_5             			     = 140 ,
    AUTO_POS_INC_5             			     = 141 ,
    AUTO_POS_VERT_5            			     = 142 ,
    AUTO_POS_BKY_VERT_5        			     = 143 ,
    AUTO_POS_BKY_TILT_5        			     = 144 ,
    AUTO_POS_ELEV_5            			     = 145 ,
    AUTO_POS_LAT_6             			     = 146 ,
    AUTO_POS_LONG_6            			     = 147 ,
    AUTO_POS_ROT_6             			     = 148 ,
    AUTO_POS_INC_6             			     = 149 ,
    AUTO_POS_VERT_6            			     = 150 ,
    AUTO_POS_BKY_VERT_6        			     = 151 ,
    AUTO_POS_BKY_TILT_6        			     = 152 ,
    AUTO_POS_ELEV_6            			     = 153 ,
    SW_VERSION                 			     = 154 ,
    HW_CHECK                   			     = 155 ,
    OFFSET_BUCKY_UP            			     = 156 ,
    OFFSET_BUCKY_DOWN          			     = 157 ,
    DETETTORE_LONG_TARGET_SPEED_MEDIUM       = 158 ,
    DETETTORE_LONG_TARGET_SPEED_SLOW         = 159 ,
    DETETTORE_LONG_ACC_SPEED                 = 160 ,
    DETETTORE_LONG_DEC_SPEED                 = 161 ,
    DETETTORE_LONG_ACC_SPEED_SLOW            = 162 ,
    DETETTORE_LONG_DEC_SPEED_SLOW            = 163 ,
    DETETTORE_LAT_TARGET_SPEED_MEDIUM        = 164 ,
    DETETTORE_LAT_TARGET_SPEED_SLOW          = 165 ,
    DETETTORE_LAT_ACC_SPEED                  = 166 ,
    DETETTORE_LAT_DEC_SPEED                  = 167 ,
    DETETTORE_LAT_ACC_SPEED_SLOW             = 168 ,
    DETETTORE_LAT_DEC_SPEED_SLOW             = 169 ,

    PENSILE_VERT_SPEED                       = 170 ,
    PENSILE_VERT_ACC                         = 171 ,
    PENSILE_VERT_DEC                         = 172 ,
    PENSILE_INC_SPEED                        = 173 ,
    PENSILE_INC_ACC                          = 174 ,
    PENSILE_INC_DEC                          = 175 ,
    PENSILE_INC_SPEED_POS                    = 176 ,
    PENSILE_INC_ACC_POS                      = 177 ,
    PENSILE_INC_DEC_POS                      = 178 ,
    PENSILE_LAT_SPEED                        = 179 ,
    PENSILE_LAT_ACC                          = 180 ,
    PENSILE_LAT_DEC                          = 181 ,
    PENSILE_LAT_SPEED_POS                    = 182 ,
    PENSILE_LAT_ACC_POS                      = 183 ,
    PENSILE_LAT_DEC_POS                      = 184 ,
    PENSILE_ROT_SPEED                        = 185 ,
    PENSILE_ROT_ACC                          = 186 ,
    PENSILE_ROT_DEC                          = 187 ,
    PENSILE_ROT_SPEED_POS                    = 188 ,
    PENSILE_ROT_ACC_POS                      = 189 ,
    PENSILE_ROT_DEC_POS                      = 190 ,
    PENSILE_LONG_SPEED                       = 191 ,
    PENSILE_LONG_ACC                         = 192 ,
    PENSILE_LONG_DEC                         = 193 ,
    PENSILE_LONG_SPEED_POS                   = 194 ,
    PENSILE_LONG_ACC_POS                     = 195 ,
    PENSILE_LONG_DEC_POS                     = 196 ,
    DETETTORE_LAT_SPEED                      = 197 ,
    DETETTORE_LAT_ACC                        = 198 ,
    DETETTORE_LAT_DEC                        = 199 ,
    DETETTORE_LAT_SPEED_POS                  = 200 ,
    DETETTORE_LAT_ACC_POS                    = 201 ,
    DETETTORE_LAT_DEC_POS                    = 202 ,
    DETETTORE_LONG_SPEED                     = 203 ,
    DETETTORE_LONG_ACC                       = 204 ,
    DETETTORE_LONG_DEC                       = 205 ,
    DETETTORE_LONG_SPEED_POS                 = 206 ,
    DETETTORE_LONG_ACC_POS                   = 207 ,
    DETETTORE_LONG_DEC_POS                   = 208 ,
    BUCKY_TILT_SPEED                         = 209 ,
    BUCKY_TILT_ACC                           = 210 ,
    BUCKY_TILT_DEC                           = 211 ,
    BUCKY_TILT_SPEED_POS                     = 212 ,
    BUCKY_TILT_ACC_POS                       = 213 ,
    BUCKY_TILT_DEC_POS                       = 214 ,
    BUCKY_VERT_SPEED                         = 215 ,
    BUCKY_VERT_ACC                           = 216 ,
    BUCKY_VERT_DEC                           = 217 ,
    BUCKY_VERT_SPEED_POS                     = 218 ,
    BUCKY_VERT_ACC_POS                       = 219 ,
    BUCKY_VERT_DEC_POS                       = 220 ,
    BUCKY_AVERAGE_WINDOW                     = 221 ,
    TBT_AUTOPOSITIONING                      = 222 ,
    WB_AUTOPOSITIONING                  	 = 223 ,

    AUTO_POS_LAT_7     						 = 224 ,
    AUTO_POS_LONG_7                          = 225 ,
    AUTO_POS_ROT_7                           = 226 ,
    AUTO_POS_INC_7                           = 227 ,
    AUTO_POS_VERT_7                          = 228 ,
    AUTO_POS_BKY_VERT_7                      = 229 ,
    AUTO_POS_BKY_TILT_7                      = 230 ,
    AUTO_POS_ELEV_7                          = 231 ,
    AUTO_POS_LAT_8     						 = 232 ,
    AUTO_POS_LONG_8                          = 233 ,
    AUTO_POS_ROT_8                           = 234 ,
    AUTO_POS_INC_8                           = 235 ,
    AUTO_POS_VERT_8                          = 236 ,
    AUTO_POS_BKY_VERT_8                      = 237 ,
    AUTO_POS_BKY_TILT_8                      = 238 ,
    AUTO_POS_ELEV_8                          = 239 ,
    AUTO_POS_LAT_9     						 = 240 ,
    AUTO_POS_LONG_9                          = 241 ,
    AUTO_POS_ROT_9                           = 242 ,
    AUTO_POS_INC_9                           = 243 ,
    AUTO_POS_VERT_9                          = 244 ,
    AUTO_POS_BKY_VERT_9                      = 245 ,
    AUTO_POS_BKY_TILT_9                      = 246 ,
    AUTO_POS_ELEV_9                          = 247 ,
    AUTO_POS_LAT_10     					 = 248 ,
    AUTO_POS_LONG_10                         = 249 ,
    AUTO_POS_ROT_10                          = 250 ,
    AUTO_POS_INC_10                          = 251 ,
    AUTO_POS_VERT_10                         = 252 ,
    AUTO_POS_BKY_VERT_10                     = 253 ,
    AUTO_POS_BKY_TILT_10                     = 254 ,
    AUTO_POS_ELEV_10                         = 255 ,
    AUTO_POS_LAT_11     					 = 256 ,
    AUTO_POS_LONG_11                         = 257 ,
    AUTO_POS_ROT_11                          = 258 ,
    AUTO_POS_INC_11                          = 259 ,
    AUTO_POS_VERT_11                         = 260 ,
    AUTO_POS_BKY_VERT_11                     = 261 ,
    AUTO_POS_BKY_TILT_11                     = 262 ,
    AUTO_POS_ELEV_11                         = 263 ,
    AUTO_POS_LAT_12     					 = 264 ,
    AUTO_POS_LONG_12                         = 265 ,
    AUTO_POS_ROT_12                          = 266 ,
    AUTO_POS_INC_12                          = 267 ,
    AUTO_POS_VERT_12                         = 268 ,
    AUTO_POS_BKY_VERT_12                     = 269 ,
    AUTO_POS_BKY_TILT_12                     = 270 ,
    AUTO_POS_ELEV_12                         = 271 ,
    AUTO_POS_LAT_13     					 = 272 ,
    AUTO_POS_LONG_13                         = 273 ,
    AUTO_POS_ROT_13                          = 274 ,
    AUTO_POS_INC_13                          = 275 ,
    AUTO_POS_VERT_13                         = 276 ,
    AUTO_POS_BKY_VERT_13                     = 277 ,
    AUTO_POS_BKY_TILT_13                     = 278 ,
    AUTO_POS_ELEV_13                         = 279 ,
    AUTO_POS_LAT_14     					 = 280 ,
    AUTO_POS_LONG_14                         = 281 ,
    AUTO_POS_ROT_14                          = 282 ,
    AUTO_POS_INC_14                          = 283 ,
    AUTO_POS_VERT_14                         = 284 ,
    AUTO_POS_BKY_VERT_14                     = 285 ,
    AUTO_POS_BKY_TILT_14                     = 286 ,
    AUTO_POS_ELEV_14                         = 287 ,
    AUTO_POS_LAT_15     					 = 288 ,
    AUTO_POS_LONG_15                         = 289 ,
    AUTO_POS_ROT_15                          = 290 ,
    AUTO_POS_INC_15                          = 291 ,
    AUTO_POS_VERT_15                         = 292 ,
    AUTO_POS_BKY_VERT_15                     = 293 ,
    AUTO_POS_BKY_TILT_15                     = 294 ,
    AUTO_POS_ELEV_15                         = 295 ,
    AUTO_POS_LAT_16     					 = 296 ,
    AUTO_POS_LONG_16                         = 297 ,
    AUTO_POS_ROT_16                          = 298 ,
    AUTO_POS_INC_16                          = 299 ,
    AUTO_POS_VERT_16                         = 300 ,
    AUTO_POS_BKY_VERT_16                     = 301 ,
    AUTO_POS_BKY_TILT_16                     = 302 ,
    AUTO_POS_ELEV_16                         = 303 ,

    AUTO_POS_LAT_17     					 = 304 ,
    AUTO_POS_LONG_17                         = 305 ,
    AUTO_POS_ROT_17                          = 306 ,
    AUTO_POS_INC_17                          = 307 ,
    AUTO_POS_VERT_17                         = 308 ,
    AUTO_POS_BKY_VERT_17                     = 309 ,
    AUTO_POS_BKY_TILT_17                     = 310 ,
    AUTO_POS_ELEV_17                         = 311 ,
    AUTO_POS_LAT_18     					 = 312 ,
    AUTO_POS_LONG_18                         = 313 ,
    AUTO_POS_ROT_18                          = 314 ,
    AUTO_POS_INC_18                          = 315 ,
    AUTO_POS_VERT_18                         = 316 ,
    AUTO_POS_BKY_VERT_18                     = 317 ,
    AUTO_POS_BKY_TILT_18                     = 318 ,
    AUTO_POS_ELEV_18                         = 319 ,
    AUTO_POS_LAT_19     					 = 320 ,
    AUTO_POS_LONG_19                         = 321 ,
    AUTO_POS_ROT_19                          = 322 ,
    AUTO_POS_INC_19                          = 323 ,
    AUTO_POS_VERT_19                         = 324 ,
    AUTO_POS_BKY_VERT_19                     = 325 ,
    AUTO_POS_BKY_TILT_19                     = 326 ,
    AUTO_POS_ELEV_19                         = 327 ,
    AUTO_POS_LAT_20     					 = 328 ,
    AUTO_POS_LONG_20                         = 329 ,
    AUTO_POS_ROT_20                          = 330 ,
    AUTO_POS_INC_20                          = 331 ,
    AUTO_POS_VERT_20                         = 332 ,
    AUTO_POS_BKY_VERT_20                     = 333 ,
    AUTO_POS_BKY_TILT_20                     = 334 ,
    AUTO_POS_ELEV_20                         = 335 ,

    // LONG: Need two slots
    MINENCPENSILE							 = 336,
    MINENCPENSILE_MSB                        = 337,
    MAXENCPENSILE							 = 338,
    MAXENCPENSILE_MSB                        = 339,
    SSI_ENC_INC_0                            = 340,
    SSI_ENC_INC_0_MSB                        = 341,
    SSI_ENC_INC_90                           = 342,
    SSI_ENC_INC_90_MSB                       = 343,
    SSI_ENC_INC_M90                          = 344,
    SSI_ENC_INC_M90_MSB                      = 345,
    OFF_INC_0                                = 346,
    OFF_INC_0_MSB                            = 347,
    OFF_INC_90                               = 348,
    OFF_INC_90_MSB                           = 349,
    OFF_INC_M90                              = 350,
    OFF_INC_M90_MSB                          = 351,
    ENCFACTPENSILEINCSX                      = 352,
    ENCFACTPENSILEINCSX_MSB                  = 353,
    ENCFACTPENSILEINCDX                      = 354,
    ENCFACTPENSILEINCDX_MSB                  = 355,
    INCIDENCECORR_ROT_0                      = 356,
    INCIDENCECORR_ROT_0_MSB                  = 357,
    INCIDENCECORR_ROT_90                     = 358,
    INCIDENCECORR_ROT_90_MSB                 = 359,
    INCIDENCECORR_ROT_M90                    = 360,
    INCIDENCECORR_ROT_M90_MSB                = 361,
    ENCFACTPENSILEROTSX                      = 362,
    ENCFACTPENSILEROTSX_MSB                  = 363,
    ENCFACTPENSILEROTDX                      = 364,
    ENCFACTPENSILEROTDX_MSB                  = 365,
    SSI_ENC_ROT_0                            = 366,
    SSI_ENC_ROT_0_MSB                        = 367,
    SSI_ENC_ROT_90                           = 368,
    SSI_ENC_ROT_90_MSB                       = 369,
    SSI_ENC_ROT_M90                          = 370,
    SSI_ENC_ROT_M90_MSB                      = 371,
    ENCFACTPENSILELAT                        = 372,
    ENCFACTPENSILELAT_MSB                    = 373,
    ENCFACTPENSILELONG                       = 374,
    ENCFACTPENSILELONG_MSB                   = 375,
    MINENCBUCKYVERT                          = 376,
    MINENCBUCKYVERT_MSB                      = 377,
    MINENCBUCKYTILT                          = 378,
    MINENCBUCKYTILT_MSB                      = 379,
    MAXENCBUCKYTILT                          = 380,
    MAXENCBUCKYTILT_MSB                      = 381,
    ENCFACTBUCKYVERT                         = 382,
    ENCFACTBUCKYVERT_MSB                     = 383,
    ENCFACTDETLAT                            = 384,
    ENCFACTDETLAT_MSB                        = 385,
    ENCFACTDETLONG                           = 386,
    ENCFACTDETLONG_MSB                       = 387,
    CONFIGURATION                            = 388,
    CONFIGURATION_MSB                        = 389,

    // Elevix center position
    ELEVIX_CENTER_LONG					 	 = 390,		// Center of gravity for elevix model	(long ceiling axes as ref frame)
    ELEVIX_CENTER_LAT					 	 = 391,		// Center of gravity for elevix model	(lat ceiling axes as ref frame)
    // Calibration for collision
    EEE_ELEVIX_COLLISION					 = 392,

    // Inserted January 17th to check eeprom lengthen - Cecilia 22/01/18
    EEE_NUM_VAR								 = 393,					// INDEX FOR NUMBER OF VARIABLES IN EEPROM

    // Wallbucky center position
    WALLBUCKY_CENTER_LONG					 = 394,		// Center of gravity for wallbucky model	(long ceiling axes as ref frame)
    WALLBUCKY_CENTER_LAT					 = 395,		// Center of gravity for wallbucky model	(lat ceiling axes as ref frame)
    // Calibration for collision
    EEE_WALLBUCKY_COLLISION					 = 396,

    EEE_NUMEL          						 	  ,
} enEEAddr; /** EEprom Emulation Address  enum */

#pragma pack(1)
    typedef union {
        struct s_msg1 {
            short int iData1;             // Byte[0] + Byte [1]
            short int iData2;             // Byte[2] + Byte [3]
            short int iData3;             // Byte[4] + Byte [5]
            short int iData4;             // Byte[6] + Byte [7]
        }msg1;
        struct s_msg2 {
            __int8 i8Data1;         // Byte[0]
            __int8 i8Data2;         // Byte[1]
            __int8 i8Data3;         // Byte[2]
            __int8 i8Data4;         // Byte[3]
            __int8 i8Data5;         // Byte[4]
            __int8 i8Data6;         // Byte[5]
            __int8 i8Data7;         // Byte[6]
            __int8 i8Data8;         // Byte[7]
        }msg2;
        struct s_msg3 {
            long lData1;            // Byte[0] + Byte[1] + Byte[2] + Byte[3]
            long lData2;            // Byte[4] + Byte[5] + Byte[6] + Byte[7]
        }msg3;
        struct s_msg4 {
            short int iData1;             // Byte[0] + Byte[1]
            __int8 i8Data2;         // Byte[2]
            __int8 i8Data3;         // Byte[3]
            short int iData4;             // Byte[4] + Byte[5]
            short int iData5;             // Byte[6] + Byte[7]
        }msg4;
        struct s_msg5 {
            long lData1;            // Byte[0] + Byte[1] + Byte[2] + Byte[3]
            short int iData2;             // Byte[4]
            __int8 i8Data3;         // Byte[5]
            __int8 i8Data4;         // Byte[6]
            __int8 i8Data5;         // Byte[7]
            __int8 i8Data6;         // Byte[8]
        }msg5;
        struct s_msg6 {
            short int iData1;             // Byte[0] + Byte[1]
            short int iData2;             // Byte[2] + Byte[3]
            short int iData3;             // Byte[4] + Byte[5]
            __int8 i8Data4;         // Byte[6]
            __int8 i8Data5;         // Byte[7]
        }msg6;
        struct s_msg7 {
            short int iData1;             // Byte[0] + Byte[1]
            short int iData2;             // Byte[2] + Byte[3]
            long lData3;            // Byte[4] + Byte[5] + byte[6] + Byte[7]
        }msg7;
        struct s_msg8 {
            short int iData1;             // Byte[0] + Byte[1]
            __int8 i8Data2;         // Byte[2]
            __int8 i8Data3;         // Byte[3]
            __int8 i8Data4;         // Byte[4]
            __int8 i8Data5;         // Byte[5]
            __int8 i8Data6;         // Byte[6]
            __int8 i8Data7;         // Byte[7]
        }msg8;
        struct s_msg9 {
            short int iData1;             // Byte[0] + Byte[1]
            __int8 i8Data2;         // Byte[2]
            __int8 i8Data3;         // Byte[3]
            __int8 i8Data4;         // Byte[4]
            __int8 i8Data5;         // Byte[5]
            short int iData6;             // Byte[6] + Byte[7]
        }msg9;
        struct s_msgMM_1{
            short int iErrorID;     // Byte[0] + Byte[1]
            long lData1;            // Byte[2] + Byte[3] + byte[4] + Byte[5]
            short int iData2;             // Byte[6] + Byte[7]
        }msgMM_1;
        struct s_msgMM_2{
            short int iErrorID;           // Byte[0] + Byte[1]
            __int8 i8Data1;         // Byte[2]
            __int8 i8Data2;         // Byte[3]
            short int iData3;             // Byte[4] + Byte[5]
            __int8 i8Data4;         // Byte[6]
            __int8 i8Data5;         // Byte[7]
        }msgMM_2;
        struct s_msgMM_3{
            short int iErrorID;           // Byte[0] + Byte [1]
            short int iData1;             // Byte[2] + Byte [3]
            short int iData2;             // Byte[4] + Byte [5]
            short int iData3;             // Byte[6] + Byte [7]
        }msgMM_3;
        struct s_msgMM_4{
            short int iErrorID;           // Byte[0] + Byte [1]
            __int8 i8Data1;         // Byte[2]
            short int iData2;             // Byte[3] + Byte[4]
            short int iData3;             // Byte[5] + Byte[6]
        }msgMM_4;
        struct s_msgMM_5{
            short int iErrorID;           // Byte[0] + Byte [1]
            __int8 i8Data1;         // Byte[2]
            __int8 i8Data2;         // Byte[3]
            __int8 i8Data3;         // Byte[4]
            __int8 i8Data4;         // Byte[5]
            short int iData5;             // Byte[6] + Byte[7]
        }msgMM_5;
        struct s_msgMM_6{
            short int iErrorID;           // Byte[0] + Byte [1]
            short int iData1;             // Byte[2] + Byte [3]
            __int8 i8Data2;         // Byte[4]
            __int8 i8Data3;         // Byte[5]
            __int8 i8Data4;         // Byte[6]
            __int8 i8Data5;         // Byte[7]
        }msgMM_6;

        signed char caAllData[8];
    } unionDataInfo;

#pragma pack()

#endif // COMMONTYPES_H
