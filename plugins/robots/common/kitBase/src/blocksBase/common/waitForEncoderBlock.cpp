/* Copyright 2007-2015 QReal Research Group
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include "kitBase/blocksBase/common/waitForEncoderBlock.h"

#include <utils/abstractTimer.h>

#include "kitBase/robotModel/robotParts/encoderSensor.h"
#include "kitBase/robotModel/robotModelUtils.h"

using namespace kitBase;
using namespace blocksBase::common;
using namespace robotModel;

WaitForEncoderBlock::WaitForEncoderBlock(RobotModelInterface &robotModel)
	: WaitForSensorBlock(robotModel)
{
	mActiveWaitingTimer->setInterval(1);
}

void WaitForEncoderBlock::run()
{
	// Empty expression is silently evaluated to 0, so the block would finish immediately instead of waiting.
	if (stringProperty("TachoLimit").trimmed().isEmpty()) {
		error(tr("Tacho limit value is not set"));
		return;
	}

	WaitForSensorBlock::run();
}

void WaitForEncoderBlock::responseSlot(const QVariant &reading)
{
	const int result = eval<int>("TachoLimit");
	if (!errorsOccured()) {
		processResponce(reading.toInt(), result);
	}
}

DeviceInfo WaitForEncoderBlock::device() const
{
	return DeviceInfo::create<robotParts::EncoderSensor>();
}
