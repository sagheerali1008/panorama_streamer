/*
Copyright 2012-2014 Fastvideo, Ltd. All rights reserved.

Please refer to the Fastvideo Standard License Agreement (SLA), associated
 with this source code for terms and conditions that govern your use of
 this software. Any use, reproduction, disclosure, or distribution of
 this software and related documentation outside the terms of the SLA is strictly prohibited.

IN NO EVENT SHALL FASTVIDEO BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF FASTVIDEO HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

FASTVIDEO SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS PROVIDED "AS IS". FASTVIDEO HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
*/
#ifndef __DEBAYER_OPTIONS__
#define __DEBAYER_OPTIONS__

#include "BaseOptions.h"
#include "GrayscaleCorrectionOptions.h"

#include "fastvideo_sdk.h"

class DebayerOptions : public virtual BaseOptions, public virtual GrayscaleCorrectionOptions {
private:
	fastBayerPattern_t GetBayerPatternFromString(const char *pattern);
	fastDebayerType_t GetBayerAlgorithmType(const char *pattern);

public:
	char *LutDebayer;

	fastDebayerType_t BayerType;
	fastBayerPattern_t BayerFormat;
	bool IsRaw;
	bool Is2bytesOutput;

	DebayerOptions(void) { };
	~DebayerOptions(void) { };

	bool Parse(int argc, char *argv[]);
};

#endif // __DEBAYER_OPTIONS__