
			
//-------------------------------------------------------------------------------------------------------------------
// xiApi header file
#ifndef __XIAPI_H
#define __XIAPI_H

#ifdef WIN32
#include <windows.h>
#else
// linux
#include "wintypedefs.h"
#endif
#include <stddef.h>
#include "m3Identify.h"
#ifdef XIAPI_EXPORTS
#define XIAPI __declspec(dllexport)
#else
#define XIAPI __declspec(dllimport)
#endif

typedef int XI_RETURN;

#ifdef __cplusplus
extern "C" {
#endif

//-------------------------------------------------------------------------------------------------------------------
// xiApi parameters

// Basic
#define  XI_PRM_EXPOSURE                        "exposure"                // Exposure time in microseconds 
#define  XI_PRM_GAIN_SELECTOR                   "gain_selector"           // Gain selector for parameter Gain allows to select different type of gains. XI_GAIN_SELECTOR_TYPE
#define  XI_PRM_GAIN                            "gain"                    // Gain in dB 
#define  XI_PRM_DOWNSAMPLING                    "downsampling"            // Change image resolution by binning or skipping. XI_DOWNSAMPLING_VALUE
#define  XI_PRM_DOWNSAMPLING_TYPE               "downsampling_type"       // Change image downsampling type. XI_DOWNSAMPLING_TYPE
#define  XI_PRM_IMAGE_DATA_FORMAT               "imgdataformat"           // Output data format. XI_IMG_FORMAT
#define  XI_PRM_SHUTTER_TYPE                    "shutter_type"            // Change sensor shutter type(CMOS sensor). XI_SHUTTER_TYPE
#define  XI_PRM_SENSOR_TAPS                     "sensor_taps"             // Number of taps XI_SENSOR_TAP_CNT
#define  XI_PRM_AEAG                            "aeag"                    // Automatic exposure/gain 
#define  XI_PRM_AEAG_ROI_OFFSET_X               "aeag_roi_offset_x"       // Automatic exposure/gain ROI offset X 
#define  XI_PRM_AEAG_ROI_OFFSET_Y               "aeag_roi_offset_y"       // Automatic exposure/gain ROI offset Y 
#define  XI_PRM_AEAG_ROI_WIDTH                  "aeag_roi_width"          // Automatic exposure/gain ROI Width 
#define  XI_PRM_AEAG_ROI_HEIGHT                 "aeag_roi_height"         // Automatic exposure/gain ROI Height 
#define  XI_PRM_BPC                             "bpc"                     // Correction of bad pixels 
#define  XI_PRM_AUTO_WB                         "auto_wb"                 // Automatic white balance 
#define  XI_PRM_MANUAL_WB                       "manual_wb"               // Calculates White Balance(xiGetImage function must be called) 
#define  XI_PRM_WB_KR                           "wb_kr"                   // White balance red coefficient 
#define  XI_PRM_WB_KG                           "wb_kg"                   // White balance green coefficient 
#define  XI_PRM_WB_KB                           "wb_kb"                   // White balance blue coefficient 
#define  XI_PRM_WIDTH                           "width"                   // Width of the Image provided by the device (in pixels). 
#define  XI_PRM_HEIGHT                          "height"                  // Height of the Image provided by the device (in pixels). 
#define  XI_PRM_OFFSET_X                        "offsetX"                 // Horizontal offset from the origin to the area of interest (in pixels). 
#define  XI_PRM_OFFSET_Y                        "offsetY"                 // Vertical offset from the origin to the area of interest (in pixels). 
// AE Setup
#define  XI_PRM_EXP_PRIORITY                    "exp_priority"            // Exposure priority (0.8 - exposure 80%, gain 20%). 
#define  XI_PRM_AG_MAX_LIMIT                    "ag_max_limit"            // Maximum limit of gain in AEAG procedure 
#define  XI_PRM_AE_MAX_LIMIT                    "ae_max_limit"            // Maximum time (us) used for exposure in AEAG procedure 
#define  XI_PRM_AEAG_LEVEL                      "aeag_level"              // Average intensity of output signal AEAG should achieve(in %) 
// Performance
#define  XI_PRM_LIMIT_BANDWIDTH                 "limit_bandwidth"         // Set/get bandwidth(datarate)(in Megabits) 
#define  XI_PRM_SENSOR_DATA_BIT_DEPTH           "sensor_bit_depth"        // Sensor output data bit depth. XI_BIT_DEPTH
#define  XI_PRM_OUTPUT_DATA_BIT_DEPTH           "output_bit_depth"        // Device output data bit depth. XI_BIT_DEPTH
#define  XI_PRM_IMAGE_DATA_BIT_DEPTH            "image_data_bit_depth"    // bitdepth of data returned by function xiGetImage XI_BIT_DEPTH
#define  XI_PRM_OUTPUT_DATA_PACKING             "output_bit_packing"      // Device output data packing (or grouping) enabled. Packing could be enabled if output_data_bit_depth > 8 and packing capability is available. 
#define  XI_PRM_OUTPUT_DATA_PACKING_TYPE        "output_bit_packing_type" // Data packing type. Some cameras supports only specific packing type. XI_OUTPUT_DATA_PACKING_TYPE
// Temperature
#define  XI_PRM_IS_COOLED                       "iscooled"                // Returns 1 for cameras that support cooling. 
#define  XI_PRM_COOLING                         "cooling"                 // Start camera cooling. 
#define  XI_PRM_TARGET_TEMP                     "target_temp"             // Set sensor target temperature for cooling. 
#define  XI_PRM_CHIP_TEMP                       "chip_temp"               // Camera sensor temperature 
#define  XI_PRM_HOUS_TEMP                       "hous_temp"               // Camera housing tepmerature 
// Color Correction
#define  XI_PRM_CMS                             "cms"                     // Mode of color management system. XI_CMS_MODE
#define  XI_PRM_APPLY_CMS                       "apply_cms"               // Enable applying of CMS profiles to xiGetImage (see XI_PRM_INPUT_CMS_PROFILE, XI_PRM_OUTPUT_CMS_PROFILE). 
#define  XI_PRM_INPUT_CMS_PROFILE               "input_cms_profile"       // Filename for input cms profile (e.g. input.icc) 
#define  XI_PRM_OUTPUT_CMS_PROFILE              "output_cms_profile"      // Filename for output cms profile (e.g. input.icc) 
#define  XI_PRM_IMAGE_IS_COLOR                  "iscolor"                 // Returns 1 for color cameras. 
#define  XI_PRM_COLOR_FILTER_ARRAY              "cfa"                     // Returns color filter array type of RAW data. XI_COLOR_FILTER_ARRAY
#define  XI_PRM_GAMMAY                          "gammaY"                  // Luminosity gamma 
#define  XI_PRM_GAMMAC                          "gammaC"                  // Chromaticity gamma 
#define  XI_PRM_SHARPNESS                       "sharpness"               // Sharpness Strenght 
#define  XI_PRM_CC_MATRIX_00                    "ccMTX00"                 // Color Correction Matrix element [0][0] 
#define  XI_PRM_CC_MATRIX_01                    "ccMTX01"                 // Color Correction Matrix element [0][1] 
#define  XI_PRM_CC_MATRIX_02                    "ccMTX02"                 // Color Correction Matrix element [0][2] 
#define  XI_PRM_CC_MATRIX_03                    "ccMTX03"                 // Color Correction Matrix element [0][3] 
#define  XI_PRM_CC_MATRIX_10                    "ccMTX10"                 // Color Correction Matrix element [1][0] 
#define  XI_PRM_CC_MATRIX_11                    "ccMTX11"                 // Color Correction Matrix element [1][1] 
#define  XI_PRM_CC_MATRIX_12                    "ccMTX12"                 // Color Correction Matrix element [1][2] 
#define  XI_PRM_CC_MATRIX_13                    "ccMTX13"                 // Color Correction Matrix element [1][3] 
#define  XI_PRM_CC_MATRIX_20                    "ccMTX20"                 // Color Correction Matrix element [2][0] 
#define  XI_PRM_CC_MATRIX_21                    "ccMTX21"                 // Color Correction Matrix element [2][1] 
#define  XI_PRM_CC_MATRIX_22                    "ccMTX22"                 // Color Correction Matrix element [2][2] 
#define  XI_PRM_CC_MATRIX_23                    "ccMTX23"                 // Color Correction Matrix element [2][3] 
#define  XI_PRM_CC_MATRIX_30                    "ccMTX30"                 // Color Correction Matrix element [3][0] 
#define  XI_PRM_CC_MATRIX_31                    "ccMTX31"                 // Color Correction Matrix element [3][1] 
#define  XI_PRM_CC_MATRIX_32                    "ccMTX32"                 // Color Correction Matrix element [3][2] 
#define  XI_PRM_CC_MATRIX_33                    "ccMTX33"                 // Color Correction Matrix element [3][3] 
#define  XI_PRM_DEFAULT_CC_MATRIX               "defccMTX"                // Set default Color Correction Matrix 
// Device IO
#define  XI_PRM_TRG_SOURCE                      "trigger_source"          // Defines source of trigger. XI_TRG_SOURCE
#define  XI_PRM_TRG_SOFTWARE                    "trigger_software"        // Generates an internal trigger. XI_PRM_TRG_SOURCE must be set to TRG_SOFTWARE. 
#define  XI_PRM_TRG_SELECTOR                    "trigger_selector"        // Selects the type of trigger. XI_TRG_SELECTOR
#define  XI_PRM_ACQ_FRAME_BURST_COUNT           "acq_frame_burst_count"   // Sets number of frames acquired by burst. This burst is used only if trigger is set to FrameBurstStart 
// GPIO Setup
#define  XI_PRM_GPI_SELECTOR                    "gpi_selector"            // Selects GPI XI_GPI_SELECTOR
#define  XI_PRM_GPI_MODE                        "gpi_mode"                // Defines GPI functionality XI_GPI_MODE
#define  XI_PRM_GPI_LEVEL                       "gpi_level"               // GPI level 
#define  XI_PRM_GPO_SELECTOR                    "gpo_selector"            // Selects GPO XI_GPO_SELECTOR
#define  XI_PRM_GPO_MODE                        "gpo_mode"                // Defines GPO functionality XI_GPO_MODE
#define  XI_PRM_LED_SELECTOR                    "led_selector"            // Selects LED XI_LED_SELECTOR
#define  XI_PRM_LED_MODE                        "led_mode"                // Defines LED functionality XI_LED_MODE
#define  XI_PRM_DEBOUNCE_EN                     "dbnc_en"                 // Enable/Disable debounce to selected GPI 
// Debounce Setup
#define  XI_PRM_DEBOUNCE_T0                     "dbnc_t0"                 // Debounce time (x * 10us) 
#define  XI_PRM_DEBOUNCE_T1                     "dbnc_t1"                 // Debounce time (x * 10us) 
#define  XI_PRM_DEBOUNCE_POL                    "dbnc_pol"                // Debounce polarity (pol = 1 t0 - falling edge, t1 - rising edge) 
// Lens Control
#define  XI_PRM_LENS_MODE                       "lens_mode"               // Status of lens control interface. This shall be set to XI_ON before any Lens operations. 
#define  XI_PRM_LENS_APERTURE_VALUE             "lens_aperture_value"     // Current lens aperture value in stops. Examples: 2.8, 4, 5.6, 8, 11 
#define  XI_PRM_LENS_FOCUS_MOVEMENT_VALUE       "lens_focus_movement_value"// Lens current focus movement value to be used by XI_PRM_LENS_FOCUS_MOVE in motor steps. 
#define  XI_PRM_LENS_FOCUS_MOVE                 "lens_focus_move"         // Moves lens focus motor by steps set in XI_PRM_LENS_FOCUS_MOVEMENT_VALUE. 
#define  XI_PRM_LENS_FOCUS_DISTANCE             "lens_focus_distance"     // Lens focus distance in cm. 
#define  XI_PRM_LENS_FOCAL_LENGTH               "lens_focal_length"       // Lens focal distance in mm. 
#define  XI_PRM_LENS_FEATURE_SELECTOR           "lens_feature_selector"   // Selects the current feature which is accessible by XI_PRM_LENS_FEATURE. XI_LENS_FEATURE
#define  XI_PRM_LENS_FEATURE                    "lens_feature"            // Allows access to lens feature value currently selected by XI_PRM_LENS_FEATURE_SELECTOR. 
// Device info parameters
#define  XI_PRM_DEVICE_NAME                     "device_name"             // Return device name 
#define  XI_PRM_DEVICE_TYPE                     "device_type"             // Return device type 
#define  XI_PRM_DEVICE_MODEL_ID                 "device_model_id"         // Return device model id 
#define  XI_PRM_DEVICE_SN                       "device_sn"               // Return device serial number 
#define  XI_PRM_DEVICE_SENS_SN                  "device_sens_sn"          // Return sensor serial number 
#define  XI_PRM_DEVICE_ID                       "device_id"               // Return unique device ID 
#define  XI_PRM_DEVICE_INSTANCE_PATH            "device_inst_path"        // Return device system instance path. 
#define  XI_PRM_DEVICE_USER_ID                  "device_user_id"          // Return custom ID of camera. 
#define  XI_PRM_DEVICE_MANIFEST                 "device_manifest"         // Return device capability description XML. 
// Device acquisition settings
#define  XI_PRM_IMAGE_DATA_FORMAT_RGB32_ALPHA   "imgdataformatrgb32alpha" // The alpha channel of RGB32 output image format. 
#define  XI_PRM_IMAGE_PAYLOAD_SIZE              "imgpayloadsize"          // Buffer size in bytes sufficient for output image returned by xiGetImage 
#define  XI_PRM_TRANSPORT_PIXEL_FORMAT          "transport_pixel_format"  // Current format of pixels on transport layer. XI_GenTL_Image_Format_e
#define  XI_PRM_SENSOR_CLOCK_FREQ_HZ            "sensor_clock_freq_hz"    // Sensor clock frequency in Hz. 
#define  XI_PRM_SENSOR_CLOCK_FREQ_INDEX         "sensor_clock_freq_index" // Sensor clock frequency index. Sensor with selected frequencies have possibility to set the frequency only by this index. 
#define  XI_PRM_SENSOR_OUTPUT_CHANNEL_COUNT     "sensor_output_channel_count"// Number of output channels from sensor used for data transfer. XI_SENSOR_OUTPUT_CHANNEL_COUNT
#define  XI_PRM_FRAMERATE                       "framerate"               // Define framerate in Hz 
#define  XI_PRM_COUNTER_SELECTOR                "counter_selector"        // Select counter XI_COUNTER_SELECTOR
#define  XI_PRM_COUNTER_VALUE                   "counter_value"           // Counter status 
#define  XI_PRM_ACQ_TIMING_MODE                 "acq_timing_mode"         // Type of sensor frames timing. XI_ACQ_TIMING_MODE
#define  XI_PRM_AVAILABLE_BANDWIDTH             "available_bandwidth"     // Calculate and return available interface bandwidth(int Megabits) 
#define  XI_PRM_BUFFER_POLICY                   "buffer_policy"           // Data move policy XI_BP
#define  XI_PRM_LUT_EN                          "LUTEnable"               // Activates LUT. 
#define  XI_PRM_LUT_INDEX                       "LUTIndex"                // Control the index (offset) of the coefficient to access in the LUT. 
#define  XI_PRM_LUT_VALUE                       "LUTValue"                // Value at entry LUTIndex of the LUT 
#define  XI_PRM_TRG_DELAY                       "trigger_delay"           // Specifies the delay in microseconds (us) to apply after the trigger reception before activating it. XI_GPI_SELECTOR
#define  XI_PRM_TS_RST_MODE                     "ts_rst_mode"             // Defines how time stamp reset engine will be armed XI_TS_RST_MODE
#define  XI_PRM_TS_RST_SOURCE                   "ts_rst_source"           // Defines which source will be used for timestamp reset. Writing this parameter will trigger settings of engine (arming) XI_TS_RST_SOURCE
// Extended Device parameters
#define  XI_PRM_IS_DEVICE_EXIST                 "isexist"                 // Returns 1 if camera connected and works properly. 
#define  XI_PRM_ACQ_BUFFER_SIZE                 "acq_buffer_size"         // Acquisition buffer size in buffer_size_unit. Default bytes. 
#define  XI_PRM_ACQ_BUFFER_SIZE_UNIT            "acq_buffer_size_unit"    // Acquisition buffer size unit in bytes. Default 1. E.g. Value 1024 means that buffer_size is in KiBytes 
#define  XI_PRM_ACQ_TRANSPORT_BUFFER_SIZE       "acq_transport_buffer_size"// Acquisition transport buffer size in bytes 
#define  XI_PRM_BUFFERS_QUEUE_SIZE              "buffers_queue_size"      // Queue of field/frame buffers 
#define  XI_PRM_RECENT_FRAME                    "recent_frame"            // GetImage returns most recent frame 
// Sensor Defects Correction
// Sensor features
#define  XI_PRM_SENSOR_MODE                     "sensor_mode"             // Current sensor mode. Allows to select sensor mode by one integer. Setting of this parameter affects: image dimensions and downsampling. XI_SENSOR_MODE
#define  XI_PRM_HDR                             "hdr"                     // Enable High Dynamic Range feature. 
#define  XI_PRM_HDR_KNEEPOINT_COUNT             "hdr_kneepoint_count"     // The number of kneepoints in the PWLR. 
#define  XI_PRM_HDR_T1                          "hdr_t1"                  // position of first kneepoint(in % of XI_PRM_EXPOSURE) 
#define  XI_PRM_HDR_T2                          "hdr_t2"                  // position of second kneepoint (in % of XI_PRM_EXPOSURE) 
#define  XI_PRM_KNEEPOINT1                      "hdr_kneepoint1"          // value of first kneepoint (% of sensor saturation) 
#define  XI_PRM_KNEEPOINT2                      "hdr_kneepoint2"          // value of second kneepoint (% of sensor saturation) 
#define  XI_PRM_IMAGE_BLACK_LEVEL               "image_black_level"       // Last image black level counts. Can be used for Offline processing to recall it. 
// Version info
#define  XI_PRM_API_VERSION                     "api_version"             // Returns version of API. 
#define  XI_PRM_DRV_VERSION                     "drv_version"             // Returns version of current device driver. 
#define  XI_PRM_MCU1_VERSION                    "version_mcu1"            // Returns version of MCU1 firmware. 
#define  XI_PRM_MCU2_VERSION                    "version_mcu2"            // Returns version of MCU2 firmware. 
#define  XI_PRM_FPGA1_VERSION                   "version_fpga1"           // Returns version of FPGA1 firmware. 
// API features
#define  XI_PRM_DEBUG_LEVEL                     "debug_level"             // Set debug level XI_DEBUG_LEVEL
#define  XI_PRM_AUTO_BANDWIDTH_CALCULATION      "auto_bandwidth_calculation"// Automatic bandwidth calculation, 
// Camera FFS
#define  XI_PRM_READ_FILE_FFS                   "read_file_ffs"           // Read file from camera flash filesystem. 
#define  XI_PRM_WRITE_FILE_FFS                  "write_file_ffs"          // Write file to camera flash filesystem. 
#define  XI_PRM_FFS_FILE_NAME                   "ffs_file_name"           // Set name of file to be written/read from camera FFS. 
#define  XI_PRM_FREE_FFS_SIZE                   "free_ffs_size"           // Size of free camera FFS. 
#define  XI_PRM_USED_FFS_SIZE                   "used_ffs_size"           // Size of used camera FFS. 
#define  XI_PRM_FFS_ACCESS_KEY                  "ffs_access_key"          // Setting of key enables file operations on some cameras. 
// APIContextControl
#define  XI_PRM_API_CONTEXT_LIST                "xiapi_context_list"      // List of current parameters settings context - parameters with values. Used for offline processing. 
// Sensor Control
#define  XI_PRM_SENSOR_FEATURE_SELECTOR         "sensor_feature_selector" // Selects the current feature which is accessible by XI_PRM_SENSOR_FEATURE_VALUE. XI_SENSOR_FEATURE_SELECTOR
#define  XI_PRM_SENSOR_FEATURE_VALUE            "sensor_feature_value"    // Allows access to sensor feature value currently selected by XI_PRM_SENSOR_FEATURE_SELECTOR. 
// Extended Features

//-------------------------------------------------------------------------------------------------------------------
// Error codes xiApi
typedef enum
{	
	XI_OK                             = 0, // Function call succeeded
	XI_INVALID_HANDLE                 = 1, // Invalid handle
	XI_READREG                        = 2, // Register read error
	XI_WRITEREG                       = 3, // Register write error
	XI_FREE_RESOURCES                 = 4, // Freeing resiurces error
	XI_FREE_CHANNEL                   = 5, // Freeing channel error
	XI_FREE_BANDWIDTH                 = 6, // Freeing bandwith error
	XI_READBLK                        = 7, // Read block error
	XI_WRITEBLK                       = 8, // Write block error
	XI_NO_IMAGE                       = 9, // No image
	XI_TIMEOUT                        =10, // Timeout
	XI_INVALID_ARG                    =11, // Invalid arguments supplied
	XI_NOT_SUPPORTED                  =12, // Not supported
	XI_ISOCH_ATTACH_BUFFERS           =13, // Attach buffers error
	XI_GET_OVERLAPPED_RESULT          =14, // Overlapped result
	XI_MEMORY_ALLOCATION              =15, // Memory allocation error
	XI_DLLCONTEXTISNULL               =16, // DLL context is NULL
	XI_DLLCONTEXTISNONZERO            =17, // DLL context is non zero
	XI_DLLCONTEXTEXIST                =18, // DLL context exists
	XI_TOOMANYDEVICES                 =19, // Too many devices connected
	XI_ERRORCAMCONTEXT                =20, // Camera context error
	XI_UNKNOWN_HARDWARE               =21, // Unknown hardware
	XI_INVALID_TM_FILE                =22, // Invalid TM file
	XI_INVALID_TM_TAG                 =23, // Invalid TM tag
	XI_INCOMPLETE_TM                  =24, // Incomplete TM
	XI_BUS_RESET_FAILED               =25, // Bus reset error
	XI_NOT_IMPLEMENTED                =26, // Not implemented
	XI_SHADING_TOOBRIGHT              =27, // Shading too bright
	XI_SHADING_TOODARK                =28, // Shading too dark
	XI_TOO_LOW_GAIN                   =29, // Gain is too low
	XI_INVALID_BPL                    =30, // Invalid bad pixel list
	XI_BPL_REALLOC                    =31, // Bad pixel list realloc error
	XI_INVALID_PIXEL_LIST             =32, // Invalid pixel list
	XI_INVALID_FFS                    =33, // Invalid Flash File System
	XI_INVALID_PROFILE                =34, // Invalid profile
	XI_INVALID_CALIBRATION            =35, // Invalid calibration
	XI_INVALID_BUFFER                 =36, // Invalid buffer
	XI_INVALID_DATA                   =38, // Invalid data
	XI_TGBUSY                         =39, // Timing generator is busy
	XI_IO_WRONG                       =40, // Wrong operation open/write/read/close
	XI_ACQUISITION_ALREADY_UP         =41, // Acquisition already started
	XI_OLD_DRIVER_VERSION             =42, // Old version of device driver installed to the system.
	XI_GET_LAST_ERROR                 =43, // To get error code please call GetLastError function.
	XI_CANT_PROCESS                   =44, // Data cant be processed
	XI_ACQUISITION_STOPED             =45, // Acquisition has been stopped. It should be started before GetImage.
	XI_ACQUISITION_STOPED_WERR        =46, // Acquisition has been stoped with error.
	XI_INVALID_INPUT_ICC_PROFILE      =47, // Input ICC profile missed or corrupted
	XI_INVALID_OUTPUT_ICC_PROFILE     =48, // Output ICC profile missed or corrupted
	XI_DEVICE_NOT_READY               =49, // Device not ready to operate
	XI_SHADING_TOOCONTRAST            =50, // Shading too contrast
	XI_ALREADY_INITIALIZED            =51, // Module already initialized
	XI_NOT_ENOUGH_PRIVILEGES          =52, // Application doesnt enough privileges(one or more app
	XI_NOT_COMPATIBLE_DRIVER          =53, // Installed driver not compatible with current software
	XI_TM_INVALID_RESOURCE            =54, // TM file was not loaded successfully from resources
	XI_DEVICE_HAS_BEEN_RESETED        =55, // Device has been reseted, abnormal initial state
	XI_NO_DEVICES_FOUND               =56, // No Devices Found
	XI_RESOURCE_OR_FUNCTION_LOCKED    =57, // Resource(device) or function locked by mutex
	XI_BUFFER_SIZE_TOO_SMALL          =58, // Buffer provided by user is too small
	XI_COULDNT_INIT_PROCESSOR         =59, // Couldnt initialize processor.
	XI_NOT_INITIALIZED                =60, // The object/module/procedure/process being referred to has not been started.
	XI_UNKNOWN_PARAM                  =100, // Unknown parameter
	XI_WRONG_PARAM_VALUE              =101, // Wrong parameter value
	XI_WRONG_PARAM_TYPE               =103, // Wrong parameter type
	XI_WRONG_PARAM_SIZE               =104, // Wrong parameter size
	XI_BUFFER_TOO_SMALL               =105, // Input buffer too small
	XI_NOT_SUPPORTED_PARAM            =106, // Parameter info not supported
	XI_NOT_SUPPORTED_PARAM_INFO       =107, // Parameter info not supported
	XI_NOT_SUPPORTED_DATA_FORMAT      =108, // Data format not supported
	XI_READ_ONLY_PARAM                =109, // Read only parameter
	XI_BANDWIDTH_NOT_SUPPORTED        =111, // This camera does not support currently available bandwidth
	XI_INVALID_FFS_FILE_NAME          =112, // FFS file selector is invalid or NULL
	XI_FFS_FILE_NOT_FOUND             =113, // FFS file not found
	XI_PROC_OTHER_ERROR               =201, // Processing error - other
	XI_PROC_PROCESSING_ERROR          =202, // Error while image processing.
	XI_PROC_INPUT_FORMAT_UNSUPPORTED  =203, // Input format is not supported for processing.
	XI_PROC_OUTPUT_FORMAT_UNSUPPORTED =204, // Output format is not supported for processing.
	
}XI_RET;

//-------------------------------------------------------------------------------------------------------------------
// xiAPI enumerators
// Downsampling value enumerator.
typedef enum
{
	XI_DWN_1x1                   =1, // Downsampling 1x1.
	XI_DWN_2x2                   =2, // Downsampling 2x2.
	XI_DWN_3x3                   =3, // Downsampling 3x3.
	XI_DWN_4x4                   =4, // Downsampling 4x4.
	XI_DWN_5x5                   =5, // Downsampling 5x5.
	XI_DWN_6x6                   =6, // Downsampling 6x6.
	XI_DWN_7x7                   =7, // Downsampling 7x7.
	XI_DWN_8x8                   =8, // Downsampling 8x8.
	XI_DWN_9x9                   =9, // Downsampling 9x9.
	XI_DWN_10x10                 =10, // Downsampling 10x10.
	
} XI_DOWNSAMPLING_VALUE;

// Sensor tap count enumerator.
typedef enum
{
	XI_TAP_CNT_1                 =1, // 1 sensor tap selected.
	XI_TAP_CNT_2                 =2, // 2 sensor taps selected.
	XI_TAP_CNT_4                 =4, // 4 sensor taps selected.
	
} XI_SENSOR_TAP_CNT;

// Bit depth enumerator.
typedef enum
{
	XI_BPP_8                     =8, // 8 bit per pixel
	XI_BPP_10                    =10, // 10 bit per pixel
	XI_BPP_12                    =12, // 12 bit per pixel
	XI_BPP_14                    =14, // 14 bit per pixel
	
} XI_BIT_DEPTH;

// Debug level enumerator.
typedef enum
{
	XI_DL_DETAIL                 =0, // Same as trace plus locking resources
	XI_DL_TRACE                  =1, // Information level.
	XI_DL_WARNING                =2, // Warning level.
	XI_DL_ERROR                  =3, // Error level.
	XI_DL_FATAL                  =4, // Fatal error level.
	XI_DL_DISABLED               =100, // Print no errors at all.
	
} XI_DEBUG_LEVEL;

// Image output format enumerator.
typedef enum
{
	XI_MONO8                     =0, // 8 bits per pixel
	XI_MONO16                    =1, // 16 bits per pixel
	XI_RGB24                     =2, // RGB data format
	XI_RGB32                     =3, // RGBA data format
	XI_RGB_PLANAR                =4, // RGB planar data format
	XI_RAW8                      =5, // 8 bits per pixel raw data from sensor
	XI_RAW16                     =6, // 16 bits per pixel raw data from sensor
	XI_FRM_TRANSPORT_DATA        =7, // Data from transport layer (e.g. packed). Format see XI_PRM_TRANSPORT_PIXEL_FORMAT
	
} XI_IMG_FORMAT;

// Image output format enumerator for GenTL.
typedef enum
{
	XI_GenTL_Image_Format_Mono8  =0x01080001, // Pixel format 8bit monochrome
	XI_GenTL_Image_Format_BGRA8Packed=0x02200017, // Pixel format RGBA 8bit color
	XI_GenTL_Image_Format_RGB8Planar=0x02180021, // Pixel format RGB 8bit planar
	XI_GenTL_Image_Format_BayerRG8=0x01080009, // Pixel format Bayer RG 8.
	XI_GenTL_Image_Format_Mono10 =0x01100003, // Pixel format Mono10
	XI_GenTL_Image_Format_Mono12 =0x01100005, // Pixel format Mono 12
	XI_GenTL_Image_Format_Mono14 =0x01100025, // Pixel format Mono 14
	XI_GenTL_Image_Format_BayerRG10=0x0110000D, // Pixel format Bayer RG 10
	XI_GenTL_Image_Format_BayerRG12=0x01100011, // Pixel format Bayer RG 12
	XI_GenTL_Image_Format_BayerGR8=0x01080008, // Pixel format Bayer GR 8
	XI_GenTL_Image_Format_BayerGB8=0x0108000A, // Pixel format Bayer GB 8
	XI_GenTL_Image_Format_BayerGR10=0x0110000C, // Pixel format Bayer GR 10
	XI_GenTL_Image_Format_BayerGB10=0x0110000E, // Pixel format Bayer GB 10
	XI_GenTL_Image_Format_BayerGR12=0x01100010, // Pixel format Bayer GR 12
	XI_GenTL_Image_Format_BayerBG8=0x0108000B, // Pixel format Bayer BG 8
	XI_GenTL_Image_Format_BayerBG10=0x0110000F, // Pixel format Bayer BG 10
	XI_GenTL_Image_Format_BayerBG12=0x01100013, // Pixel format Bayer BG 12
	XI_GenTL_Image_Format_BayerGB12=0x01100012, // Pixel format Bayer GB 12
	XI_GenTL_Image_Format_RGB8   =0x02180014, // Pixel format RGB 8bit
	XI_GenTL_Image_Format_BGR8   =0x02180015, // Pixel format BGR 8bit
	XI_GenTL_Image_Format_BayerRG14=0x8000010C, // Pixel format one 14 bit pixel
	XI_GenTL_Image_Format_BayerGR14=0x8000020C, // Pixel format one 14 bit pixel
	XI_GenTL_Image_Format_BayerBG14=0x8000030C, // Pixel format one 14 bit pixel
	XI_GenTL_Image_Format_BayerGB14=0x8000040C, // Pixel format one 14 bit pixel
	XI_GenTL_Image_Format_BayerBG10p=0x010A0052, // Pixel format 10bit packed
	XI_GenTL_Image_Format_BayerGB10p=0x010A0054, // Pixel format 10bit packed
	XI_GenTL_Image_Format_BayerGR10p=0x010A0056, // Pixel format 10bit packed
	XI_GenTL_Image_Format_BayerRG10p=0x010A0058, // Pixel format 10bit packed
	XI_GenTL_Image_Format_Mono10p=0x010a0046, // Pixel format 10bit packed
	XI_GenTL_Image_Format_BayerBG12p=0x010C0053, // Pixel format 12bit packed
	XI_GenTL_Image_Format_BayerGB12p=0x010C0055, // Pixel format 12bit packed
	XI_GenTL_Image_Format_BayerGR12p=0x010C0057, // Pixel format 12bit packed
	XI_GenTL_Image_Format_BayerRG12p=0x010C0059, // Pixel format 12bit packed
	XI_GenTL_Image_Format_Mono12p=0x010c0047, // Pixel format 12bit packed
	XI_GenTL_Image_Format_BayerBG14p=0x8100010E, // Pixel format 14bit packed
	XI_GenTL_Image_Format_BayerGB14p=0x8100020E, // Pixel format 14bit packed
	XI_GenTL_Image_Format_BayerGR14p=0x8100030E, // Pixel format 14bit packed
	XI_GenTL_Image_Format_BayerRG14p=0x8100040E, // Pixel format 14bit packed
	XI_GenTL_Image_Format_Mono14p=0x8100000E, // Pixel format 14bit packed
	XI_GenTL_Image_Format_xiBayerBG10g160=0x8200010A, // Pixel format 10bit
	XI_GenTL_Image_Format_xiBayerGB10g160=0x8200020A, // Pixel format 10bit
	XI_GenTL_Image_Format_xiBayerGR10g160=0x8200030A, // Pixel format 10bit
	XI_GenTL_Image_Format_xiBayerRG10g160=0x8200040A, // Pixel format 10bit
	XI_GenTL_Image_Format_xiMono10g160=0x8200000A, // Pixel format 10bit
	XI_GenTL_Image_Format_xiBayerBG12g192=0x8200010C, // Pixel format 12bit
	XI_GenTL_Image_Format_xiBayerGB12g192=0x8200020C, // Pixel format 12bit
	XI_GenTL_Image_Format_xiBayerGR12g192=0x8200030C, // Pixel format 12bit
	XI_GenTL_Image_Format_xiBayerRG12g192=0x8200040C, // Pixel format 12bit
	XI_GenTL_Image_Format_xiMono12g192=0x8200000C, // Pixel format 12bit
	XI_GenTL_Image_Format_xiBayerBG14g224=0x8200010E, // Pixel format 14bit
	XI_GenTL_Image_Format_xiBayerGB14g224=0x8200020E, // Pixel format 14bit
	XI_GenTL_Image_Format_xiBayerGR14g224=0x8200030E, // Pixel format 14bit
	XI_GenTL_Image_Format_xiBayerRG14g224=0x8200040E, // Pixel format 14bit
	XI_GenTL_Image_Format_xiMono14g224=0x8200000E, // Pixel format 14bit
	XI_GenTL_Image_Format_xiMono8TS01=0x82010008, // Pixel format 8bit(2 taps)
	XI_GenTL_Image_Format_xiMono10TS01=0x8201000A, // Pixel format 10bit(2 taps)
	XI_GenTL_Image_Format_xiMono12TS01=0x8201000C, // Pixel format 12bit(2 taps)
	XI_GenTL_Image_Format_xiMono14TS01=0x8201000E, // Pixel format 14bit(2 taps)
	XI_GenTL_Image_Format_xiBayerRG8TS01=0x82010408, // Pixel format (2 taps)
	XI_GenTL_Image_Format_xiBayerRG10TS01=0x8201040A, // Pixel format 10 bits
	XI_GenTL_Image_Format_xiBayerRG12TS01=0x8201040C, // Pixel format 12 bits
	XI_GenTL_Image_Format_xiBayerRG14TS01=0x8201040E, // Pixel format 14 bits
	XI_GenTL_Image_Format_xiBayerBG8TS01=0x82010108, // Pixel format (2 taps)
	XI_GenTL_Image_Format_xiBayerBG10TS01=0x8201010A, // Pixel format 10 bits
	XI_GenTL_Image_Format_xiBayerBG12TS01=0x8201010C, // Pixel format 12 bits
	XI_GenTL_Image_Format_xiBayerBG14TS01=0x8201010E, // Pixel format 14 bits
	XI_GenTL_Image_Format_xiBayerGB8TS01=0x82010208, // Pixel format (2 taps)
	XI_GenTL_Image_Format_xiBayerGB10TS01=0x8201020A, // Pixel format 10 bits
	XI_GenTL_Image_Format_xiBayerGB12TS01=0x8201020C, // Pixel format 12 bits
	XI_GenTL_Image_Format_xiBayerGB14TS01=0x8201020E, // Pixel format 14 bits
	XI_GenTL_Image_Format_xiBayerGR8TS01=0x82010308, // Pixel format (2 taps)
	XI_GenTL_Image_Format_xiBayerGR10TS01=0x8201030A, // Pixel format 10 bits
	XI_GenTL_Image_Format_xiBayerGR12TS01=0x8201030C, // Pixel format 12 bits
	XI_GenTL_Image_Format_xiBayerGR14TS01=0x8201030E, // Pixel format 14 bits
	XI_GenTL_Image_Format_xiMono8TS03=0x82030008, // Pixel format 8bit(4 taps)
	XI_GenTL_Image_Format_xiMono10TS03=0x8203000A, // Pixel format 10bit(4 taps)
	XI_GenTL_Image_Format_xiMono12TS03=0x8203000C, // Pixel format 12bit(4 taps)
	XI_GenTL_Image_Format_xiMono14TS03=0x8203000E, // Pixel format 14bit(4 taps)
	XI_GenTL_Image_Format_xiBayerRG8TS03=0x82030408, // Pixel format (4 taps)
	XI_GenTL_Image_Format_xiBayerRG10TS03=0x8203040A, // Pixel format 10 bits
	XI_GenTL_Image_Format_xiBayerRG12TS03=0x8203040C, // Pixel format 12 bits
	XI_GenTL_Image_Format_xiBayerRG14TS03=0x8203040E, // Pixel format 14 bits
	XI_GenTL_Image_Format_xiBayerBG8TS03=0x82030108, // Pixel format (4 taps)
	XI_GenTL_Image_Format_xiBayerBG10TS03=0x8203010A, // Pixel format 10 bits
	XI_GenTL_Image_Format_xiBayerBG12TS03=0x8203010C, // Pixel format 12 bits
	XI_GenTL_Image_Format_xiBayerBG14TS03=0x8203010E, // Pixel format 14 bits
	XI_GenTL_Image_Format_xiBayerGB8TS03=0x82030208, // Pixel format (4 taps)
	XI_GenTL_Image_Format_xiBayerGB10TS03=0x8203020A, // Pixel format 10 bits
	XI_GenTL_Image_Format_xiBayerGB12TS03=0x8203020C, // Pixel format 12 bits
	XI_GenTL_Image_Format_xiBayerGB14TS03=0x8203020E, // Pixel format 14 bits
	XI_GenTL_Image_Format_xiBayerGR8TS03=0x82030308, // Pixel format (4 taps)
	XI_GenTL_Image_Format_xiBayerGR10TS03=0x8203030A, // Pixel format 10 bits
	XI_GenTL_Image_Format_xiBayerGR12TS03=0x8203030C, // Pixel format 12 bits
	XI_GenTL_Image_Format_xiBayerGR14TS03=0x8203030E, // Pixel format 14 bits
	XI_GenTL_Image_Format_xiMono16=0x01100007, // Pixel format 16 monochrome
	XI_GenTL_Image_Format_xiBayerGR16=0x0110002E, // Pixel format Bayer GR 16
	XI_GenTL_Image_Format_xiBayerRG16=0x0110002F, // Pixel format Bayer RG 16
	XI_GenTL_Image_Format_xiBayerGB16=0x01100030, // Pixel format Bayer GB 16
	XI_GenTL_Image_Format_xiBayerBG16=0x01100031, // Pixel format Bayer BG 16
	
} XI_GenTL_Image_Format_e;

// Bayer color matrix enumerator.
typedef enum
{
	XI_CFA_NONE                  =0, //  B/W sensors
	XI_CFA_BAYER_RGGB            =1, // Regular RGGB
	XI_CFA_CMYG                  =2, // AK Sony sens
	XI_CFA_RGR                   =3, // 2R+G readout
	XI_CFA_BAYER_BGGR            =4, // BGGR readout
	XI_CFA_BAYER_GRBG            =5, // GRBG readout
	XI_CFA_BAYER_GBRG            =6, // GBRG readout
	
} XI_COLOR_FILTER_ARRAY;

// structure containing information about buffer policy(can be safe, data will be copied to user/app buffer or unsafe, user will get internally allocated buffer without data copy).
typedef enum
{
	XI_BP_UNSAFE                 =0, // User gets pointer to internally allocated circle buffer and data may be overwritten by device.
	XI_BP_SAFE                   =1, // Data from device will be copied to user allocated buffer or xiApi allocated memory.
	
} XI_BP;

// structure containing information about trigger source
typedef enum
{
	XI_TRG_OFF                   =0, // Camera works in free run mode.
	XI_TRG_EDGE_RISING           =1, // External trigger (rising edge).
	XI_TRG_EDGE_FALLING          =2, // External trigger (falling edge).
	XI_TRG_SOFTWARE              =3, // Software(manual) trigger.
	
} XI_TRG_SOURCE;

// structure containing information about trigger functionality
typedef enum
{
	XI_TRG_SEL_FRAME_START       =0, // Selects a trigger starting the capture of one frame
	XI_TRG_SEL_EXPOSURE_ACTIVE   =1, // Selects a trigger controlling the duration of one frame.
	XI_TRG_SEL_FRAME_BURST_START =2, // Selects a trigger starting the capture of the bursts of frames in an acquisition.
	XI_TRG_SEL_FRAME_BURST_ACTIVE=3, // Selects a trigger controlling the duration of the capture of the bursts of frames in an acquisition.
	XI_TRG_SEL_MULTIPLE_EXPOSURES=4, // Selects a trigger which when first trigger starts exposure and consequent pulses are gating exposure(active HI)
	
} XI_TRG_SELECTOR;

// structure containing information about acqisition timing modes
typedef enum
{
	XI_ACQ_TIMING_MODE_FREE_RUN  =0, // Selects a mode when sensor timing is given by fastest framerate possible (by exposure time and readout).
	XI_ACQ_TIMING_MODE_FRAME_RATE=1, // Selects a mode when sensor frame acquisition start is given by frame rate.
	
} XI_ACQ_TIMING_MODE;

// Enumeration for XI_PRM_GPI_SELECTOR for CB cameras.
typedef enum
{
	XI_GPI_SEL_CB_IN1            =1, // Input1 - Pin3 (Opto Isolated).
	XI_GPI_SEL_CB_IN2            =2, // Input2 - Pin4 (Opto Isolated).
	XI_GPI_SEL_CB_INOUT1         =3, // Input/Output1 - Pin6
	XI_GPI_SEL_CB_INOUT2         =4, // Input/Output2 - Pin7
	XI_GPI_SEL_CB_INOUT3         =5, // Input/Output3 - Pin11
	XI_GPI_SEL_CB_INOUT4         =6, // Input/Output4 - Pin12
	
} XI_GPI_SEL_CB;

// Enumeration for XI_PRM_GPO_SELECTOR for CB cameras.
typedef enum
{
	XI_GPO_SEL_CB_OUT1           =1, // Output1 - Pin8 (Opto Isolated).
	XI_GPO_SEL_CB_OUT2           =2, // Output2 - Pin9 (Opto Isolated).
	XI_GPO_SEL_CB_INOUT1         =3, // Input/Output1 - Pin6
	XI_GPO_SEL_CB_INOUT2         =4, // Input/Output2 - Pin7
	XI_GPO_SEL_CB_INOUT3         =5, // Input/Output3 - Pin11
	XI_GPO_SEL_CB_INOUT4         =6, // Input/Output4 - Pin12
	
} XI_GPO_SEL_CB;

// structure containing information about GPI functionality
typedef enum
{
	XI_GPI_OFF                   =0, // Input off. In this mode the input level can be get using parameter XI_PRM_GPI_LEVEL.
	XI_GPI_TRIGGER               =1, // Trigger input
	XI_GPI_EXT_EVENT             =2, // External signal input. It is not implemented yet.
	
} XI_GPI_MODE;

// Enumerator for GPI port selection.
typedef enum
{
	XI_GPI_PORT1                 =1, // GPI port 1
	XI_GPI_PORT2                 =2, // GPI port 2
	XI_GPI_PORT3                 =3, // GPI port 3
	XI_GPI_PORT4                 =4, // GPI port 4
	XI_GPI_PORT5                 =5, // GPI port 5
	XI_GPI_PORT6                 =6, // GPI port 6
	
} XI_GPI_SELECTOR;

// structure containing information about GPO functionality
typedef enum
{
	XI_GPO_OFF                   =0, // Output off
	XI_GPO_ON                    =1, // Logical level.
	XI_GPO_FRAME_ACTIVE          =2, // On from exposure started until read out finished.
	XI_GPO_FRAME_ACTIVE_NEG      =3, // Off from exposure started until read out finished.
	XI_GPO_EXPOSURE_ACTIVE       =4, // On during exposure(integration) time
	XI_GPO_EXPOSURE_ACTIVE_NEG   =5, // Off during exposure(integration) time
	XI_GPO_FRAME_TRIGGER_WAIT    =6, // On when sensor is ready for next trigger edge.
	XI_GPO_FRAME_TRIGGER_WAIT_NEG=7, // Off when sensor is ready for next trigger edge.
	XI_GPO_EXPOSURE_PULSE        =8, // Short On/Off pulse on start of each exposure.
	XI_GPO_EXPOSURE_PULSE_NEG    =9, // Short Off/On pulse on start of each exposure.
	XI_GPO_BUSY                  =10, // ON when camera is busy (trigger mode - starts with trigger reception and ends with end of frame transfer from sensor; freerun - active when acq active)
	XI_GPO_BUSY_NEG              =11, // OFF when camera is busy (trigger mode  - starts with trigger reception and ends with end of frame transfer from sensor; freerun - active when acq active)
	
} XI_GPO_MODE;

// Enumerator for GPO port selection.
typedef enum
{
	XI_GPO_PORT1                 =1, // GPO port 1
	XI_GPO_PORT2                 =2, // GPO port 2
	XI_GPO_PORT3                 =3, // GPO port 3
	XI_GPO_PORT4                 =4, // GPO port 4
	XI_GPO_PORT5                 =5, // GPO port 5
	XI_GPO_PORT6                 =6, // GPO port 6
	
} XI_GPO_SELECTOR;

// structure containing information about LED functionality
typedef enum
{
	XI_LED_HEARTBEAT             =0, // Blinking (1Hz) if all is OK (CURRERA-R only).
	XI_LED_TRIGGER_ACTIVE        =1, // On if trigger detected (CURRERA-R only).
	XI_LED_EXT_EVENT_ACTIVE      =2, // On if external signal detected (CURRERA-R only)
	XI_LED_LINK                  =3, // On if link is OK (Currera-R only)
	XI_LED_ACQUISITION           =4, // On if data streaming is on
	XI_LED_EXPOSURE_ACTIVE       =5, // On if sensor is integrating
	XI_LED_FRAME_ACTIVE          =6, // On if frame is active (exposure or readout)
	XI_LED_OFF                   =7, // Off
	XI_LED_ON                    =8, // On
	XI_LED_BLINK                 =9, // Blinking (1Hz)
	
} XI_LED_MODE;

// Enumerator for LED selection.
typedef enum
{
	XI_LED_SEL1                  =1, // LED 1
	XI_LED_SEL2                  =2, // LED 2
	XI_LED_SEL3                  =3, // LED 3
	
} XI_LED_SELECTOR;

// structure contains frames counter
typedef enum
{
	XI_CNT_SEL_TRANSPORT_SKIPPED_FRAMES=0, // Number of skipped frames on transport layer (e.g. when image gets lost while transmission). Occur when capacity of transport channel does not allow to transfer all data.
	XI_CNT_SEL_API_SKIPPED_FRAMES=1, // Number of skipped frames on API layer. Occur when application does not process the images as quick as they are received from the camera.
	XI_CNT_SEL_TRANSPORT_TRANSFERRED_FRAMES=2, // Number of successfully transferred frames on transport layer.
	
} XI_COUNTER_SELECTOR;

// structure containing information about time stamp reset arming
typedef enum
{
	XI_TS_RST_ARM_ONCE           =0, // TimeStamp reset is armed once, after execution engine is disabled
	XI_TS_RST_ARM_PERSIST        =1, // TimeStamp reset is armed permanently if source is selected 
	
} XI_TS_RST_MODE;

// structure containing information about possible timestamp reset sources
typedef enum
{
	XI_TS_RST_OFF                =0, // No source selected, timestamp reset effectively disabled
	XI_TS_RST_SRC_GPI_1          =1, // TimeStamp reset source selected GPI1 (after de bounce)
	XI_TS_RST_SRC_GPI_2          =2, // TimeStamp reset source selected GPI2 (after de bounce)
	XI_TS_RST_SRC_GPI_3          =3, // TimeStamp reset source selected GPI3 (after de bounce)
	XI_TS_RST_SRC_GPI_4          =4, // TimeStamp reset source selected GPI4 (after de bounce)
	XI_TS_RST_SRC_GPI_1_INV      =5, // TimeStamp reset source selected GPI1 inverted (after de bounce)
	XI_TS_RST_SRC_GPI_2_INV      =6, // TimeStamp reset source selected GPI2 inverted (after de bounce)
	XI_TS_RST_SRC_GPI_3_INV      =7, // TimeStamp reset source selected GPI3 inverted (after de bounce)
	XI_TS_RST_SRC_GPI_4_INV      =8, // TimeStamp reset source selected GPI4 inverted (after de bounce)
	XI_TS_RST_SRC_GPO_1          =9, // TimeStamp reset source selected GPO1 (after de bounce)
	XI_TS_RST_SRC_GPO_2          =10, // TimeStamp reset source selected GPO2 (after de bounce)
	XI_TS_RST_SRC_GPO_3          =11, // TimeStamp reset source selected GPO3 (after de bounce)
	XI_TS_RST_SRC_GPO_4          =12, // TimeStamp reset source selected GPO4 (after de bounce)
	XI_TS_RST_SRC_GPO_1_INV      =13, // TimeStamp reset source selected GPO1 inverted (after de bounce)
	XI_TS_RST_SRC_GPO_2_INV      =14, // TimeStamp reset source selected GPO2 inverted (after de bounce)
	XI_TS_RST_SRC_GPO_3_INV      =15, // TimeStamp reset source selected GPO3 inverted (after de bounce)
	XI_TS_RST_SRC_GPO_4_INV      =16, // TimeStamp reset source selected GPO4 inverted (after de bounce)
	XI_TS_RST_SRC_TRIGGER        =17, // TimeStamp reset source selected TRIGGER (signal for sensor)
	XI_TS_RST_SRC_TRIGGER_INV    =18, // TimeStamp reset source selected TRIGGER (signal for sensor)
	XI_TS_RST_SRC_SW             =19, // TimeStamp reset source selected software (has immediate effect and is self cleared)
	XI_TS_RST_SRC_EXPACTIVE      =20, // TimeStamp reset source selected exposure active 
	XI_TS_RST_SRC_EXPACTIVE_INV  =21, // TimeStamp reset source selected exposure active 
	XI_TS_RST_SRC_FVAL           =22, // TimeStamp reset source selected frame valid signal from sensor
	XI_TS_RST_SRC_FVAL_INV       =23, // TimeStamp reset source selected frame valid inverted signal from sensor
	
} XI_TS_RST_SOURCE;

// structure containing information about parameters type
typedef enum
{
	xiTypeInteger                =0, // integer parameter type
	xiTypeFloat                  =1, // float parameter type
	xiTypeString                 =2, // string parameter type
	xiTypeEnum                   =3, // enumerator parameter type
	xiTypeBoolean                =4, // boolean parameter type
	xiTypeCommand                =5, // command parameter type
	
} XI_PRM_TYPE;

// Turn parameter On/Off
typedef enum
{
	XI_OFF                       =0, // Turn parameter off
	XI_ON                        =1, // Turn parameter on
	
} XI_SWITCH;

// Data packing(grouping) types.
typedef enum
{
	XI_DATA_PACK_XI_GROUPING     =0, // Data grouping (10g160, 12g192, 14g224).
	XI_DATA_PACK_PFNC_LSB_PACKING=1, // Data packing (10p, 12p)
	
} XI_OUTPUT_DATA_PACKING_TYPE;

// Downsampling types
typedef enum
{
	XI_BINNING                   =0, // Downsampling is using  binning
	XI_SKIPPING                  =1, // Downsampling is using  skipping
	
} XI_DOWNSAMPLING_TYPE;

// Gain selector
typedef enum
{
	XI_GAIN_SELECTOR_ALL         =0, // Gain selector selects all channels. Implementation of gain type depends on camera.
	XI_GAIN_SELECTOR_ANALOG_ALL  =1, // Gain selector selects all analog channels. This is available only on some cameras.
	XI_GAIN_SELECTOR_DIGITAL_ALL =2, // Gain selector selects all digital channels. This is available only on some cameras.
	
} XI_GAIN_SELECTOR_TYPE;

// Shutter mode types
typedef enum
{
	XI_SHUTTER_GLOBAL            =0, // Sensor Global Shutter(CMOS sensor)
	XI_SHUTTER_ROLLING           =1, // Sensor Electronic Rolling Shutter(CMOS sensor)
	XI_SHUTTER_GLOBAL_RESET_RELEASE=2, // Sensor Global Reset Release Shutter(CMOS sensor)
	
} XI_SHUTTER_TYPE;

// structure containing information about CMS functionality
typedef enum
{
	XI_CMS_DIS                   =0, // CMS disable
	XI_CMS_EN                    =1, // CMS enable
	XI_CMS_EN_FAST               =2, // CMS enable(fast)
	
} XI_CMS_MODE;

// structure containing information about options for selection of camera before onening
typedef enum
{
	XI_OPEN_BY_INST_PATH         =0, // Open camera by its hardware path
	XI_OPEN_BY_SN                =1, // Open camera by its serial number
	XI_OPEN_BY_USER_ID           =2, // open camera by its custom user ID
	
} XI_OPEN_BY;

// Lens feature selector selects which feature will be accessed.
typedef enum
{
	XI_LENS_FEATURE_MOTORIZED_FOCUS_SWITCH=1, // Status of lens motorized focus switch
	XI_LENS_FEATURE_MOTORIZED_FOCUS_BOUNDED=2, // On read = 1 if motorized focus is on one of limits.
	XI_LENS_FEATURE_MOTORIZED_FOCUS_CALIBRATION=3, // On read = 1 if motorized focus is calibrated. Write 1 to start calibration.
	XI_LENS_FEATURE_IMAGE_STABILIZATION_ENABLED=4, // On read = 1 if image stabilization is enabled. Write 1 to enable image stabilization.
	XI_LENS_FEATURE_IMAGE_STABILIZATION_SWITCH_STATUS=5, // On read = 1 if image stabilization switch is in position On.
	XI_LENS_FEATURE_IMAGE_ZOOM_SUPPORTED=6, // On read = 1 if lens supports zoom = are not prime.
	
} XI_LENS_FEATURE;

// Sensor feature selector selects which feature will be accessed.
typedef enum
{
	XI_SENSOR_FEATURE_ZEROROT_DISABLE=0, // Zero ROT disaable for ONSEMI PYTHON family
	XI_SENSOR_FEATURE_ZEROROT_ENABLE=1, // Zero ROT enable for ONSEMI PYTHON family
	
} XI_SENSOR_FEATURE_SELECTOR;

//-------------------------------------------------------------------------------------------------------------------
// xiAPI structures
// structure containing description of image areas and format.
typedef struct
{
	DWORD         Area0Left; // Pixels of Area0 of image left.
	DWORD         Area1Left; // Pixels of Area1 of image left.
	DWORD         Area2Left; // Pixels of Area2 of image left.
	DWORD         Area3Left; // Pixels of Area3 of image left.
	DWORD         Area4Left; // Pixels of Area4 of image left.
	DWORD         Area5Left; // Pixels of Area5 of image left.
	DWORD         ActiveAreaWidth;// Width of active area.
	DWORD         Area5Right;// Pixels of Area5 of image right.
	DWORD         Area4Right;// Pixels of Area4 of image right.
	DWORD         Area3Right;// Pixels of Area3 of image right.
	DWORD         Area2Right;// Pixels of Area2 of image right.
	DWORD         Area1Right;// Pixels of Area1 of image right.
	DWORD         Area0Right;// Pixels of Area0 of image right.
	DWORD         Area0Top;  // Pixels of Area0 of image top.
	DWORD         Area1Top;  // Pixels of Area1 of image top.
	DWORD         Area2Top;  // Pixels of Area2 of image top.
	DWORD         Area3Top;  // Pixels of Area3 of image top.
	DWORD         Area4Top;  // Pixels of Area4 of image top.
	DWORD         Area5Top;  // Pixels of Area5 of image top.
	DWORD         ActiveAreaHeight;// Height of active area.
	DWORD         Area5Bottom;// Pixels of Area5 of image bottom.
	DWORD         Area4Bottom;// Pixels of Area4 of image bottom.
	DWORD         Area3Bottom;// Pixels of Area3 of image bottom.
	DWORD         Area2Bottom;// Pixels of Area2 of image bottom.
	DWORD         Area1Bottom;// Pixels of Area1 of image bottom.
	DWORD         Area0Bottom;// Pixels of Area0 of image bottom.
	DWORD         format;    // Current format of pixels. XI_GenTL_Image_Format_e.
	DWORD         flags;     // description of areas and image.
	
}XI_IMG_DESC, *LPXI_IMG_DESC;

// structure containing information about incoming image.
typedef struct
{
	DWORD         size;      // Size of current structure on application side. When xiGetImage is called and size>=SIZE_XI_IMG_V2 then GPI_level, tsSec and tsUSec are filled.
	LPVOID        bp;        // Pointer to data. In XI_BP_UNSAFE mode the bp will be set to buffer allocated by API. If XI_BP_SAFE mode the data will be copied to bp, which should be allocated by application.
	DWORD         bp_size;   // Filled buffer size. When buffer policy is set to XI_BP_SAFE, xiGetImage will fill this field with current size of image data received.
	XI_IMG_FORMAT frm;       // Format of image data get from xiGetImage.
	DWORD         width;     // width of incoming image.
	DWORD         height;    // height of incoming image.
	DWORD         nframe;    // frame number(reset by exposure, gain, downsampling change).
	DWORD         tsSec;     // TimeStamp in seconds
	DWORD         tsUSec;    // TimeStamp in microseconds
	DWORD         GPI_level; // Input level
	DWORD         black_level;// Black level of image (ONLY for MONO and RAW formats)
	DWORD         padding_x; // Number of extra bytes provided at the end of each line to facilitate image alignment in buffers.
	DWORD         AbsoluteOffsetX;// Horizontal offset of origin of sensor and buffer image first pixel.
	DWORD         AbsoluteOffsetY;// Vertical offset of origin of sensor and buffer image first pixel.
	DWORD         transport_frm;// Current format of pixels on transport layer. XI_GenTL_Image_Format_e.
	XI_IMG_DESC   img_desc;  // description of image areas and format.
	DWORD         DownsamplingX;// Horizontal downsampling
	DWORD         DownsamplingY;// Vertical downsampling
	DWORD         flags;     // description of XI_IMG.
	DWORD         exposure_time_us;// Exposure time of this image in microseconds
	float         gain_db;   // Gain used for this image in deci-bells
	DWORD         acq_nframe;// Number of frames acquired from acquisition start
	
}XI_IMG, *LPXI_IMG;

//-------------------------------------------------------------------------------------------------------------------
// Global definitions

#define SIZE_XI_IMG_V1               offsetof(XI_IMG, tsSec)// structure size default
#define SIZE_XI_IMG_V2               offsetof(XI_IMG, black_level)// structure size with timestamp and GPI level information
#define SIZE_XI_IMG_V3               offsetof(XI_IMG, padding_x)// structure size with black level information
#define SIZE_XI_IMG_V4               offsetof(XI_IMG, AbsoluteOffsetX)// structure size with horizontal buffer padding information padding_x
#define SIZE_XI_IMG_V5               offsetof(XI_IMG, transport_frm)// structure size with AbsoluteOffsetX, AbsoluteOffsetY
#define SIZE_XI_IMG_V6               offsetof(XI_IMG, img_desc)// structure size with transport_frm
#define SIZE_XI_IMG_V7               offsetof(XI_IMG, DownsamplingX)// structure size with img_desc
#define SIZE_XI_IMG_V8               (offsetof(XI_IMG, flags)+sizeof(DWORD))// structure size with flags
#define SIZE_XI_IMG_V9               (offsetof(XI_IMG, gain_db)+sizeof(float))// structure size with gain_db
#define SIZE_XI_IMG_V10              (offsetof(XI_IMG, acq_nframe)+sizeof(DWORD))// structure size with acq_nframe
#define XI_PRM_INFO_MIN              ":min"               // Parameter minimum
#define XI_PRM_INFO_MAX              ":max"               // Parameter maximum
#define XI_PRM_INFO_INCREMENT        ":inc"               // Parameter increment
#define XI_PRM_INFO                  ":info"              // Parameter value
#define XI_PRMM_DIRECT_UPDATE        ":direct_update"     // Parameter modifier for direct update without stopping the streaming. E.g. XI_PRM_EXPOSURE XI_PRMM_DIRECT_UPDATE can be used with this modifier
#define XI_MQ_LED_STATUS1            1                    // MQ Status 1 LED selection value.
#define XI_MQ_LED_STATUS2            2                    // MQ Status 2 LED selection value.
#define XI_MQ_LED_POWER              3                    // MQ Power LED selection value.
#define XI_MS_LED_STATUS1            1                    // CURRERA-R LED 1 selection value.
#define XI_MS_LED_STATUS2            2                    // CURRERA-R LED 2 selection value.
/*************************************************************************************/

#ifdef XIAPI_AS_APPLICATION
#undef XIAPI
#define XIAPI
#endif // XIAPI_AS_APPLICATION

/*************************************************************************************/
/**
   \brief Return number of discovered devices
   
   Returns the pointer to the number of all discovered devices.

   @param[out] pNumberDevices			number of discovered devices
   @return XI_OK on success, error value otherwise.
 */
XIAPI XI_RETURN __cdecl xiGetNumberDevices(OUT PDWORD pNumberDevices);
/**
   \brief Get device parameter
   
   Allows the user to get the current device state and information.
  Parameters can be used:XI_PRM_DEVICE_SN, XI_PRM_DEVICE_INSTANCE_PATH, XI_PRM_DEVICE_TYPE, XI_PRM_DEVICE_NAME

   @param[in] DevId						index of the device
   @param[in] prm						parameter name string.
   @param[in] val						pointer to parameter set value.
   @param[in] size						pointer to integer.
   @param[in] type						pointer to type container.
   @return XI_OK on success, error value otherwise.
 */
XIAPI XI_RETURN __cdecl xiGetDeviceInfo(IN DWORD DevId, const char* prm, void* val, DWORD * size, XI_PRM_TYPE * type);
/**
   \brief Initialize device
   
   This function prepares the camera's software for work.
   It populates structures, runs initializing procedures, allocates resources - prepares the camera for work.

	\note Function creates and returns handle of the specified device. To de-initialize the camera and destroy the handler xiCloseDevice should be called.	

   @param[in] DevId						index of the device
   @param[out] hDevice					handle to device
   @return XI_OK on success, error value otherwise.
 */
XIAPI XI_RETURN __cdecl xiOpenDevice(IN DWORD DevId, OUT PHANDLE hDevice);
/**   
	\brief Initialize selected device      
	
	This function prepares the camera's software for work. Camera is selected by using appropriate enumerator and input parameters. 
	It populates structures, runs initializing procedures, allocates resources - prepares the camera for work.	
	
	\note Function creates and returns handle of the specified device. To de-initialize the camera and destroy the handler xiCloseDevice should be called.	  
	
	@param[in]  sel                     select method to be used for camera selection
	@param[in]  prm                     input string to be used during camera selection
	@param[out] hDevice					handle to device   @return XI_OK on success, error value otherwise. 
	*/
XIAPI XI_RETURN __cdecl xiOpenDeviceBy(IN XI_OPEN_BY sel, IN const char* prm, OUT PHANDLE hDevice);
/**
   \brief Uninitialize device
   
   Closes camera handle and releases allocated resources.

   @param[in] hDevice					handle to device
   @return XI_OK on success, error value otherwise.
 */
XIAPI XI_RETURN __cdecl xiCloseDevice(IN HANDLE hDevice);
/**
   \brief Start image acquisition
   
   Begins the work cycle and starts data acquisition from the camera.

   @param[in] hDevice					handle to device
   @return XI_OK on success, error value otherwise.
 */
XIAPI XI_RETURN __cdecl xiStartAcquisition(IN HANDLE hDevice);
/**
   \brief Stop image acquisition
   
   Ends the work cycle of the camera, stops data acquisition and deallocates internal image buffers.

   @param[in] hDevice					handle to device
   @return XI_OK on success, error value otherwise.
 */
XIAPI XI_RETURN __cdecl xiStopAcquisition(IN HANDLE hDevice);
/**
   \brief Return pointer to image structure
   
   Allows the user to retrieve the frame into LPXI_IMG structure.

   @param[in] hDevice					handle to device
   @param[in] timeout					time interval required to wait for the image (in milliseconds).
   @param[out] img						pointer to image info structure
   @return XI_OK on success, error value otherwise.
 */
XIAPI XI_RETURN __cdecl xiGetImage(IN HANDLE hDevice, IN DWORD timeout, OUT LPXI_IMG img);
/**
   \brief Set device parameter
   
   Allows the user to control device.

   @param[in] hDevice					handle to device
   @param[in] prm						parameter name string.
   @param[in] val						pointer to parameter set value.
   @param[in] size						size of val.
   @param[in] type						val data type.
   @return XI_OK on success, error value otherwise.
 */
XIAPI XI_RETURN __cdecl xiSetParam(IN HANDLE hDevice, const char* prm, void* val, DWORD size, XI_PRM_TYPE type);
/**
   \brief Get device parameter
   
   Allows the user to get the current device state and information.

   @param[in] hDevice					handle to device
   @param[in] prm						parameter name string.
   @param[in] val						pointer to parameter set value.
   @param[in] size						pointer to integer.
   @param[in] type						pointer to type container.
   @return XI_OK on success, error value otherwise.
 */
XIAPI XI_RETURN __cdecl xiGetParam(IN HANDLE hDevice, const char* prm, void* val, DWORD * size, XI_PRM_TYPE * type);

/*-----------------------------------------------------------------------------------*/
//Set device parameter
XIAPI XI_RETURN __cdecl xiSetParamInt(IN HANDLE hDevice, const char* prm, const int val);
XIAPI XI_RETURN __cdecl xiSetParamFloat(IN HANDLE hDevice, const char* prm, const float val);
XIAPI XI_RETURN __cdecl xiSetParamString(IN HANDLE hDevice, const char* prm, void* val, DWORD size);
/*-----------------------------------------------------------------------------------*/
//Get device parameter
XIAPI XI_RETURN __cdecl xiGetParamInt(IN HANDLE hDevice, const char* prm, int* val);
XIAPI XI_RETURN __cdecl xiGetParamFloat(IN HANDLE hDevice, const char* prm, float* val);
XIAPI XI_RETURN __cdecl xiGetParamString(IN HANDLE hDevice, const char* prm, void* val, DWORD size);
/*-----------------------------------------------------------------------------------*/
//Get device info
XIAPI XI_RETURN __cdecl xiGetDeviceInfoInt(IN DWORD DevId, const char* prm, int* value);
XIAPI XI_RETURN __cdecl xiGetDeviceInfoString(IN DWORD DevId, const char* prm, char* value, DWORD value_size);
/*-----------------------------------------------------------------------------------*/


/*************************************************************************************/
// XIMEA Offline Processing Interface
// All functions can be called independently on camera device
/*************************************************************************************/

/*-----------------------------------------------------------------------------------*/
// Workflow:
//
// xiProcessingHandle_t proc;
// xiProcOpen(proc)
// get cam_context (string) previously stored in acquisition time
// xiProcSetParam(proc, XI_PRM_API_CONTEXT_LIST, cam_context, strlen(cam_context), xiTypeString)
// while (in_image is available)
// {
//    xiProcPushImage(proc, in_image)
//    xiProcPullImage(proc, out_image)
//    use processed image (out_image)
// }
// xiProcClose(proc)
/*-----------------------------------------------------------------------------------*/

typedef void* xiProcessingHandle_t;

/**
* OpenProcessing
* Opens new instance for Image Processing entity
* @param[out] processing_handle New processing handle - valid on success
*/
XIAPI XI_RETURN __cdecl xiProcOpen(xiProcessingHandle_t* processing_handle);

/**
* xiSetProcParam
* Sets the selected parameter to processing
* @param[in] processing_handle			Handle for processing
* @param[in] prm						parameter name string.
* @param[in] val						pointer to parameter set value.
* @param[in] size						size of val.
* @param[in] type						val data type.
* @return XI_OK on success, error value otherwise.
*/
XIAPI XI_RETURN __cdecl xiProcSetParam(xiProcessingHandle_t processing_handle, const char* prm, void* val, DWORD size, XI_PRM_TYPE type);

/**
* xiPushImage
* Set unprocessed image to processing chain
* @param[in] processing_handle Processing handle
* @param[out] fist_pixel First byte of first pixel of image to be processed
*/
XIAPI XI_RETURN __cdecl xiProcPushImage(xiProcessingHandle_t processing_handle, unsigned char* first_pixel);

/**
* xiPushImage
* Set unprocessed image to processing chain
* @param[in] processing_handle Processing handle
* @param[in] Pointer to XI_IMG structure
*/
XIAPI XI_RETURN __cdecl xiProcPushXiImg(xiProcessingHandle_t processing_handle, XI_IMG* image);

/**
* xiPullImage
* Gets processed image from processing chain
* @param[in] processing_handle Processing handle
* @param[in] timeout_ms Processing handle
*/
XIAPI XI_RETURN __cdecl xiProcPullImage(xiProcessingHandle_t processing_handle, int timeout_ms, XI_IMG* new_image);

/**
* CloseProcessing
* Closes instance for Image Processing entity
* @param processing_handle[out] Processing handle to be closed
*/
XIAPI XI_RETURN __cdecl xiProcClose(xiProcessingHandle_t processing_handle);

/*************************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __XIAPI_H */
