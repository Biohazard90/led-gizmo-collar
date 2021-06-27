
#include <Arduino.h>
#include <ArduinoBLE.h>

#include <Adafruit_NeoPixel.h>

#include <gizmoled.h>

void ConnectionFX(float frameTime, uint8_t *rgb);
void AnimateBlink(float frameTime);
void AnimateWheel(float frameTime);
void AnimateSparkle(float frameTime);
void AnimatePulse(float frameTime);
void AnimateChristmas(float frameTime);


/// BLINK
BEGIN_EFFECT_SETTINGS(blink, EFFECTNAME_BLINK,
	DECLARE_EFFECT_SETTINGS_COLOR(GizmoLED::VARNAME_COLOR, 0xFF, 0, 0)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_BRIGHTNESS, 255, 1, 255)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_SPEED, 30, 1, 100)
DECLARE_EFFECT_SETTINGS_CHECKBOX(GizmoLED::VARNAME_FADEIN, 0)
DECLARE_EFFECT_SETTINGS_CHECKBOX(GizmoLED::VARNAME_FADEOUT, 1)
DECLARE_EFFECT_SETTINGS_CHECKBOX(GizmoLED::VARNAME_RAINBOWENABLED, 1)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_RAINBOWSPEED, 10, 1, 100)
)
EFFECT_VAR_COLOR(color)
EFFECT_VAR_SLIDER(brightness)
EFFECT_VAR_SLIDER(speed)
EFFECT_VAR_CHECKBOX(fadeIn)
EFFECT_VAR_CHECKBOX(fadeOut)
EFFECT_VAR_CHECKBOX(rainbowEnabled)
EFFECT_VAR_SLIDER(rainbowSpeed)
END_EFFECT_SETTINGS()


/// WHEEL
BEGIN_EFFECT_SETTINGS(wheel, EFFECTNAME_WHEEL,
	DECLARE_EFFECT_SETTINGS_COLOR(GizmoLED::VARNAME_COLOR, 0, 0xFF, 0)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_BRIGHTNESS, 255, 1, 255)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_SPEED, 50, 1, 100)
DECLARE_EFFECT_SETTINGS_CHECKBOX(GizmoLED::VARNAME_RAINBOWENABLED, 1)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_RAINBOWLENGTH, 50, 1, 100)
)
EFFECT_VAR_COLOR(color)
EFFECT_VAR_SLIDER(brightness)
EFFECT_VAR_SLIDER(speed)
EFFECT_VAR_CHECKBOX(rainbowEnabled)
EFFECT_VAR_SLIDER(rainbowLength)
END_EFFECT_SETTINGS()


/// SPARKLE
BEGIN_EFFECT_SETTINGS(sparkle, EFFECTNAME_SPARKLE,
	DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_BRIGHTNESS, 255, 1, 255)
DECLARE_EFFECT_SETTINGS_COLOR(GizmoLED::VARNAME_COLOR, 0xFF, 0, 0)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_DECAY, 10, 1, 100)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_LENGTH, 3, 1, 100)
DECLARE_EFFECT_SETTINGS_CHECKBOX(GizmoLED::VARNAME_RAINBOWENABLED, 1)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_RAINBOWSPEED, 10, 1, 100)
)
EFFECT_VAR_SLIDER(brightness)
EFFECT_VAR_COLOR(color)
EFFECT_VAR_SLIDER(decay)
EFFECT_VAR_SLIDER(length)
EFFECT_VAR_CHECKBOX(rainbowEnabled)
EFFECT_VAR_SLIDER(rainbowSpeed)
END_EFFECT_SETTINGS()


/// PULSE
BEGIN_EFFECT_SETTINGS(pulse, EFFECTNAME_PULSE,
	DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_BRIGHTNESS, 255, 1, 255)
DECLARE_EFFECT_SETTINGS_COLOR(GizmoLED::VARNAME_COLOR1, 0xFF, 0, 0)
DECLARE_EFFECT_SETTINGS_COLOR(GizmoLED::VARNAME_COLOR2, 0xFF, 0xFF, 0xFF)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_SPEED, 10, 1, 60)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_LENGTH, 20, 1, 100)
DECLARE_EFFECT_SETTINGS_CHECKBOX(GizmoLED::VARNAME_FADEOUT, 0)
DECLARE_EFFECT_SETTINGS_CHECKBOX(GizmoLED::VARNAME_RAINBOWENABLED, 1)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_RAINBOWLENGTH, 30, 1, 60)
)
EFFECT_VAR_SLIDER(brightness)
EFFECT_VAR_COLOR(color1)
EFFECT_VAR_COLOR(color2)
EFFECT_VAR_SLIDER(speed)
EFFECT_VAR_SLIDER(length)
EFFECT_VAR_CHECKBOX(fadeOut)
EFFECT_VAR_CHECKBOX(rainbowEnabled)
EFFECT_VAR_SLIDER(rainbowLength)
END_EFFECT_SETTINGS()


/// CHRISTMAS
BEGIN_EFFECT_SETTINGS(christmas, EFFECTNAME_CHRISTMAS,
	DECLARE_EFFECT_SETTINGS_COLOR(GizmoLED::VARNAME_COLOR, 0xFF, 0xFF, 0xFF)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_BRIGHTNESS, 255, 1, 255)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_SPEED, 30, 1, 100)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_LENGTH, 3, 2, 100)
DECLARE_EFFECT_SETTINGS_CHECKBOX(GizmoLED::VARNAME_RAINBOWENABLED, 1)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_RAINBOWSPEED, 10, 1, 100)
)
EFFECT_VAR_COLOR(color)
EFFECT_VAR_SLIDER(brightness)
EFFECT_VAR_SLIDER(speed)
EFFECT_VAR_SLIDER(length)
EFFECT_VAR_CHECKBOX(rainbowEnabled)
EFFECT_VAR_SLIDER(rainbowSpeed)
END_EFFECT_SETTINGS()


// EFFECT LIST
BEGIN_EFFECTS()
DECLARE_EFFECT(christmas, AnimateChristmas, GizmoLED::EFFECTTYPE_DEFAULT)
DECLARE_EFFECT(blink, AnimateBlink, GizmoLED::EFFECTTYPE_DEFAULT)
DECLARE_EFFECT(wheel, AnimateWheel, GizmoLED::EFFECTTYPE_DEFAULT)
DECLARE_EFFECT(pulse, AnimatePulse, GizmoLED::EFFECTTYPE_DEFAULT)
DECLARE_EFFECT(sparkle, AnimateSparkle, GizmoLED::EFFECTTYPE_DEFAULT)
END_EFFECTS()


#define LED_BUFFER_SIZE_COLLAR 9
#define LED_PIN_COLLAR 3

uint8_t *ledBufferCollar;
Adafruit_NeoPixel ledAccessCollar(LED_BUFFER_SIZE_COLLAR, LED_PIN_COLLAR, NEO_GRB + NEO_KHZ800);


#define ADD_CLAMPED_COLOR(buffer, position, additiveColor, factor) \
					{buffer[(position) * 3] = min(255, buffer[(position) * 3] + additiveColor[1] * (factor)); \
					buffer[(position) * 3 + 1] = min(255, buffer[(position) * 3 + 1] + additiveColor[0] * (factor)); \
					buffer[(position) * 3 + 2] = min(255, buffer[(position) * 3 + 2] + additiveColor[2] * (factor));}

void setup()
{
	Serial.begin(9600);
	//while (!Serial);

	// LED init
	ledAccessCollar.begin();
	ledBufferCollar = ledAccessCollar.getPixels();

	GizmoLED::connectionAnimation = ConnectionFX;
	GIZMOLED_SETUP();
}

void loop()
{
	GIZMOLED_LOOP();

	ledAccessCollar.show();
}

void ConnectionFX(float frameTime, float percent)
{
	float brightness = cos(float(2.0f * percent * M_PI * 2 - M_PI)) * 0.5f + 0.5f;
	const uint8_t rgb[] =
	{
		0 * brightness,
		96 * brightness,
		255 * brightness
	};

	for (int l = 0; l < LED_BUFFER_SIZE_COLLAR; ++l)
	{
		const float amp = 1.0f; // (LED_BUFFER_SIZE_COLLAR - l - 1) / float(LED_BUFFER_SIZE_COLLAR - 1);
		ledBufferCollar[l * 3] = rgb[1] * amp;
		ledBufferCollar[l * 3 + 1] = rgb[0] * amp;;
		ledBufferCollar[l * 3 + 2] = rgb[2] * amp;
	}
}

float blinkTime = 0.0f;
float blinkRainbowTime = 0.0f;

void AnimateBlink(float frameTime)
{
	const float brightness = *blinkSettings::brightness / 255.0f;
	uint8_t adjustedColor[3] =
	{
		blinkSettings::color[0] * brightness,
		blinkSettings::color[1] * brightness,
		blinkSettings::color[2] * brightness,
	};

	if (*blinkSettings::rainbowEnabled != 0)
	{
		const float rainbowSpeed = *blinkSettings::rainbowSpeed / 100.0f;
		blinkRainbowTime += rainbowSpeed * frameTime;
		while (blinkRainbowTime >= 1.0f)
		{
			blinkRainbowTime -= 1.0f;
		}

		HSV2RGB(blinkRainbowTime * 360.0f, 100, brightness * 100.0f, adjustedColor);
	}

	const float pos = blinkTime * (LED_BUFFER_SIZE_COLLAR);
	blinkTime += frameTime * *blinkSettings::speed / 30.0f;
	while (blinkTime >= 1.0f)
	{
		blinkTime -= 1.0f;
	}

	float blinkAmt = 1.0f;
	if (*blinkSettings::fadeOut != 0 && *blinkSettings::fadeIn != 0)
	{
		if (blinkTime > 0.5f)
			blinkAmt = 1.0f - (blinkTime - 0.5f) / 0.5f;
		else
			blinkAmt = blinkTime / 0.5f;
	}
	else if (*blinkSettings::fadeOut != 0)
	{
		blinkAmt = 1.0f - blinkTime;
	}
	else if (*blinkSettings::fadeIn != 0)
	{
		blinkAmt = blinkTime;
	}

	adjustedColor[0] *= blinkAmt;
	adjustedColor[1] *= blinkAmt;
	adjustedColor[2] *= blinkAmt;

	for (int l = 0; l < LED_BUFFER_SIZE_COLLAR; ++l)
	{
		ledBufferCollar[l * 3] = adjustedColor[1];
		ledBufferCollar[l * 3 + 1] = adjustedColor[0];
		ledBufferCollar[l * 3 + 2] = adjustedColor[2];
	}
}

float wheelTime = 0.0f;

void AnimateWheel(float frameTime)
{
	const float brightness = *wheelSettings::brightness / 255.0f;
	uint8_t adjustedColor[3] =
	{
		wheelSettings::color[0] * brightness,
		wheelSettings::color[1] * brightness,
		wheelSettings::color[2] * brightness,
	};

	const float pos = wheelTime * (LED_BUFFER_SIZE_COLLAR);
	wheelTime += frameTime * *wheelSettings::speed / 100.0f;
	while (wheelTime >= 1.0f)
	{
		wheelTime -= 1.0f;
	}

	if (*wheelSettings::rainbowEnabled != 0)
	{
		const float rainbowScale = *wheelSettings::rainbowLength / 100.0f;
		for (int l = 0; l < LED_BUFFER_SIZE_COLLAR; ++l)
		{
			const float ledRotation = fmod((pos + l * rainbowScale), LED_BUFFER_SIZE_COLLAR);
			const float hue = ledRotation / float(LED_BUFFER_SIZE_COLLAR);

			HSV2RGB(fmod(hue * 360.0f, 360.0f), 100, brightness * 100.0f, adjustedColor);
			ledBufferCollar[l * 3] = adjustedColor[1];
			ledBufferCollar[l * 3 + 1] = adjustedColor[0];
			ledBufferCollar[l * 3 + 2] = adjustedColor[2];
		}
	}
	else
	{
		for (int l = 0; l < LED_BUFFER_SIZE_COLLAR; ++l)
		{
			const int ledRotation = fmod(pos + l, LED_BUFFER_SIZE_COLLAR);
			const float light = abs(ledRotation - (LED_BUFFER_SIZE_COLLAR) / 2) /
				float((LED_BUFFER_SIZE_COLLAR) / 2);

			ledBufferCollar[l * 3] = adjustedColor[1] * light * light;
			ledBufferCollar[l * 3 + 1] = adjustedColor[0] * light * light;
			ledBufferCollar[l * 3 + 2] = adjustedColor[2] * light * light;
		}
	}
}

const int sparkleCount = 5;
float visualizerSparkleTimers[sparkleCount] = { 0.0f };
int visualizerSparklePositions[sparkleCount] = { 0 };
float sparkleRainbowHue[sparkleCount] = { 0.0f };

#define SPARKLE_TIME 1.2f
#define SPARKLE_FADE_IN 0.2f

float nextSparkleHue = 0.0f;
float sparkleTriggerTimers[sparkleCount] = { 0.0f };
void SimulateSparkle(float frameTime)
{
	for (int a = 0; a < sparkleCount; ++a)
	{
		sparkleTriggerTimers[a] += frameTime * 1.5f * (sparkleCount * 2 - a) / float(sparkleCount * 2);

		if (sparkleTriggerTimers[a] >= 1.0f &&
			visualizerSparkleTimers[a] == 0.0f)
		{
			//GizmoLED::audioData[a] = 1.0f;
			sparkleTriggerTimers[a] = 0.0f;

			visualizerSparklePositions[a] = random(0, LED_BUFFER_SIZE_COLLAR);
			visualizerSparkleTimers[a] = SPARKLE_TIME;
			if (*sparkleSettings::rainbowEnabled != 0)
			{
				sparkleRainbowHue[a] = nextSparkleHue;
				nextSparkleHue += *sparkleSettings::rainbowSpeed;
				while (nextSparkleHue >= 360.0f)
				{
					nextSparkleHue -= 360.0f;
				}
			}
		}
	}
}

void AnimateSparkle(float frameTime)
{
	SimulateSparkle(frameTime);

	const float sparkleDecay = *sparkleSettings::decay / 100.0f;
	const float sparkleLength = *sparkleSettings::length;

	for (int l = 0; l < LED_BUFFER_SIZE_COLLAR; ++l)
	{
		ledBufferCollar[l * 3] = 0;
		ledBufferCollar[l * 3 + 1] = 0;
		ledBufferCollar[l * 3 + 2] = 0;
	}

	const float brightness = *sparkleSettings::brightness / 255.0f;
	uint8_t adjustedColor[] =
	{
		sparkleSettings::color[0] * brightness,
		sparkleSettings::color[1] * brightness,
		sparkleSettings::color[2] * brightness
	};

	// Update sparkle data
	for (int s = 0; s < sparkleCount; ++s)
	{
		if (visualizerSparkleTimers[s] > 0.0f)
		{
			visualizerSparkleTimers[s] -= frameTime * sparkleDecay * 10.0f;
			if (visualizerSparkleTimers[s] <= 0.0f)
			{
				visualizerSparkleTimers[s] = 0.0f;
			}
			else
			{
				if (*sparkleSettings::rainbowEnabled != 0)
				{
					HSV2RGB(sparkleRainbowHue[s], 100.0f, brightness * 100.0f, adjustedColor);
				}

				int basePos = visualizerSparklePositions[s];
				basePos -= sparkleLength / 2;
				float sparkleB = visualizerSparkleTimers[s];
				if (sparkleB > 1.0f)
					sparkleB = 1.0f - (sparkleB - 1.0f) / SPARKLE_FADE_IN;

				if (basePos < 0)
					basePos += (LED_BUFFER_SIZE_COLLAR);

				for (int i = 0; i < sparkleLength; ++i)
				{
					const int pos = (basePos + i) % LED_BUFFER_SIZE_COLLAR;
					const float amp = 1.0f - abs(i - sparkleLength / 2.0f) / sparkleLength * 2.0f;

					ADD_CLAMPED_COLOR(ledBufferCollar, pos, adjustedColor, sparkleB * amp);
				}
			}
		}
	}
}

uint32_t pulseCount = 0;
float pulseTimer = 0.0f;

void AnimatePulse(float frameTime)
{
	pulseTimer += frameTime * *pulseSettings::speed / 40.0f;
	while (pulseTimer >= 1.0f)
	{
		pulseTimer -= 1.0f;
		++pulseCount;
	}

	const float brightness = *pulseSettings::brightness / 255.0f;
	uint8_t adjustedColor1[] =
	{
		pulseSettings::color1[0] * brightness,
		pulseSettings::color1[1] * brightness,
		pulseSettings::color1[2] * brightness
	};
	uint8_t adjustedColor0[] =
	{
		pulseSettings::color2[0] * brightness,
		pulseSettings::color2[1] * brightness,
		pulseSettings::color2[2] * brightness
	};
	int adjustedColorD[] =
	{
		adjustedColor1[0] - adjustedColor0[0],
		adjustedColor1[1] - adjustedColor0[1],
		adjustedColor1[2] - adjustedColor0[2],
	};

	const float pulseLength = float(*pulseSettings::length) / 10.0f;
	const float rainbowLength = float(*pulseSettings::rainbowLength);
	const bool useRainbow = *pulseSettings::rainbowEnabled != 0;
	const bool fadeOut = *pulseSettings::fadeOut != 0;
	if (useRainbow)
	{
		adjustedColorD[0] = 0;
		adjustedColorD[1] = 0;
		adjustedColorD[2] = 0;
	}

#define PULSE_LED_POS(width) \
		const float pos = i / float(width); \
		const float posFull = i / float(width - 1.0f); \
		const float pulseAlignment = pulseLength - pulseTimer * pulseLength; \
		float light = fmod(pos + pulseAlignment, pulseLength) / pulseLength * 1.2f; \
		if (light > 1.0f) \
			light = 1.0f - ((light - 1.0f) / 0.2f); \
		if (useRainbow) \
		{ \
			float hue = fmod(pulseCount * rainbowLength - ((pos + pulseAlignment >= pulseLength) ? rainbowLength : 0.0f), 360.0f); \
			HSV2RGB(hue, 100.0f, brightness * 100.0f, adjustedColor1); \
		} \
		else \
		{ \
			float colMix = fmod(posFull + pulseAlignment, pulseLength) / pulseLength; \
			adjustedColor1[0] = adjustedColor0[0] + adjustedColorD[0] * colMix; \
			adjustedColor1[1] = adjustedColor0[1] + adjustedColorD[1] * colMix; \
			adjustedColor1[2] = adjustedColor0[2] + adjustedColorD[2] * colMix; \
		} \
		if (fadeOut) \
		{ \
			light *= 1.0f - posFull; \
		} \
		light *= light

	for (int i = 0; i < LED_BUFFER_SIZE_COLLAR; ++i)
	{
		PULSE_LED_POS(LED_BUFFER_SIZE_COLLAR);

		ledBufferCollar[i * 3] = adjustedColor1[1] * light;
		ledBufferCollar[i * 3 + 1] = adjustedColor1[0] * light;
		ledBufferCollar[i * 3 + 2] = adjustedColor1[2] * light;
	}
}

float christmasTime = 0.0f;
float christmasRainbowTime = 0.0f;

void AnimateChristmas(float frameTime)
{
	const float brightness = *christmasSettings::brightness / 255.0f;
	uint8_t adjustedColor[3] =
	{
		christmasSettings::color[0] * brightness,
		christmasSettings::color[1] * brightness,
		christmasSettings::color[2] * brightness,
	};

	const int spacing = *christmasSettings::length;
	const int pos = wheelTime * spacing;
	wheelTime += frameTime * *christmasSettings::speed / 50.0f;
	while (wheelTime >= 1.0f)
	{
		wheelTime -= 1.0f;
	}
	
	if (*christmasSettings::rainbowEnabled != 0)
	{
		const float rainbowSpeed = *christmasSettings::rainbowSpeed / 100.0f;
		christmasRainbowTime += rainbowSpeed * frameTime;
		while (christmasRainbowTime >= 1.0f)
		{
			christmasRainbowTime -= 1.0f;
		}

		HSV2RGB(christmasRainbowTime * 360.0f, 100, brightness * 100.0f, adjustedColor);
	}

	for (int l = 0; l < LED_BUFFER_SIZE_COLLAR; ++l)
	{
		const float light = ((pos + l) % spacing) == 0 ? 1.0f : 0.0f;
		ledBufferCollar[l * 3] = adjustedColor[1] * light;
		ledBufferCollar[l * 3 + 1] = adjustedColor[0] * light;
		ledBufferCollar[l * 3 + 2] = adjustedColor[2] * light;
	}
}
